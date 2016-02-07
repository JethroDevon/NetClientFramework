#include "sockWrapper.h"
#include <iostream>

//TCP server socket constructor, first initialiser list arg is directly initialising thread as it cannot have a default constructor
sockWrapper::sockWrapper(std::string _serverName, unsigned short _port):  run(&sockWrapper::runConnection, this), connectionName( _serverName), port( _port){

    isAlive = false;
    toSend = false;
    socket.setBlocking(false);
}

//TCP client constructor, first initialiser list arg is directly initialising thread as it cannot have a default constructor
sockWrapper::sockWrapper(std::string _clientName, std::string _ipAddress, unsigned short _port): run(&sockWrapper::runConnection, this), connectionName( _clientName), IP( _ipAddress), port ( _port){

    isAlive = false;
    toSend = false;
    socket.setBlocking(false);
}

sockWrapper::~sockWrapper(){

}

std::string sockWrapper::getName(){

    return connectionName;
}

//wraps listen function and connects to socket, to be called in a thread
void sockWrapper::serverListen(unsigned short _port){

    //tells listener to listen on _port in args
    listener.listen(_port);

    //when connection is made pass connection to socket
    listener.accept(socket);

    //outputs new connection address to console
    std::cout << "New client connected to " << connectionName << " - " <<socket.getRemoteAddress() << std::endl;
}

void sockWrapper::send( std::string _message){

    socket.send(_message.c_str(), _message.size() + 1);
}

void sockWrapper::recieve(){

    char data[1000];
    std::size_t received = 0;

    // TCP socket:
    if (socket.receive(data, 1000, received) == sf::Socket::Done){

        //messageStack.push(std::string (data));
        messageStack.push("pissflaps");
        std::cout<<std::string (data)<<std::endl;
    }
}

//returns size of message stack
int sockWrapper::unreadMessages(){

    return messageStack.size();
}

void sockWrapper::connect(){

    //connect to server
    socket.connect(getIP(), getPort());

    //returns 0 if there is no connection, this is grounds to set alive to false
    //and close this socket
    if(socket.getRemotePort() != 0){

        std::cout << "connection made by " << connectionName <<"."<< std::endl;
    }else{

        setAlive(false);
         std::cout << "connection by " << connectionName << " failed." << std::endl;
    }
}

std::string sockWrapper::getIP(){

    return IP;
}

unsigned short sockWrapper::getPort(){

    return port;
}

bool sockWrapper::getAlive(){

    return isAlive;
}

void sockWrapper::setAlive( bool _a){

    isAlive = _a;
}

std::string sockWrapper::getMessage(){

    if(!messageStack.empty()){

        std::string temp = messageStack.back();
        messageStack.pop();
        return temp;
    }
}

void sockWrapper::setPostMessage(std::string _m){

    message = _m;
}

bool sockWrapper::getToSend(){

    return toSend;
}

void sockWrapper::setToSend(bool _b){

    toSend = _b;
}

std::string sockWrapper::postMessage(){

    return message;
}

void sockWrapper::closeSocket(){

    socket.disconnect();
}

void sockWrapper::runConnection(){


    //mutex lock to avoid waste-full spinning
    mutex.lock();
    while(getAlive()){

        if(getToSend()){
            send(postMessage());
        }

        //sets message back to ""
        message = "";

        //sets flag to post something back to false
        toSend = false;

        recieve();
    }
    mutex.unlock();
}
