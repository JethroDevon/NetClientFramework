#include "Connection.h"
///TO-DO            Comment all of this better


Connection::Connection(float _timeOut): listenThread( &Connection::addServer, this), timeOut(_timeOut) {

    listening = true;
}

Connection::~Connection(){

}

//this function uses the first string args to find the connection to send the message in  string args2
void Connection::sendTo(std::string _name, std::string _message){

    for(auto &socks: socketConnections){

        if(socks->getName() == _name){

            //set to send is true, the socket now knows it can post a message as message has been initialised
            socks->setToSend(true);

            //post message has been updated, connection now has a message to send
            socks->setPostMessage(_message);
        }
    }
}

//returns the most recently received message in the top of the stack for the connection named as the same as in args
std::string Connection::receiveFrom(std::string _name){

     for(auto &socks: socketConnections){

        if(socks->getName() == _name){

            if(socks->unreadMessages() > 0){

                return socks->getMessage();
            }
        }
    }

    return "no data from " + _name;
}

//kills connection with same name as args
void Connection::killConnection(std::string _name){

    if(_name.compare("server")){

        //stops loop in thread and halts block mode of socket
        //this way the connection is closed
        listening = false;
        listener.setBlocking(false);
    }else{

        //esle loops until finds name of socket wrapper
        for(auto &socks: socketConnections){

            if(socks->getName() == _name){

                socks->setAlive(false);
                socks->closeSocket();
                std::cout<<"\n"<<socks->getName()<<" has been disconnected!"<<std::endl;
            }
        }
    }
}

//used to poll connections to check if there is data on the stack
//if connection with matching name to string in args has data will return true
bool Connection::dataAvailable(std::string _name){

     for(auto &socks: socketConnections){

        if(socks->getName() == _name){

            if((socks->messageStack.size()) > 0 ){

                return true;
            }else{

                return false;
            }
        }
    }
}

//pings a connection and sets pinged timer/flag to true
void Connection::pingConnection(){

}

//if ping does not return ping within time at args kill connection
void Connection::pingTimeOut(float fl){

}
//getter method for ticks, this is to return passed time from last call
std::clock_t Connection::getTicks(){

    return ticks;
}

//sets teh port number to listen for connections on then launches the server in a thread
void Connection::createServer(unsigned short _port){

    port = _port;
   
    if (listener.listen( port) != sf::Socket::Done){
        
        std::cout<<" Couldn't bind to the port: " << port << std::endl;
    }else{

        std::cout<<"Launching server."<< std::endl;
        listenThread.launch();
    }
}

//must be called in a thread
void Connection::addServer(){

    //constantly listening for a new connection
    while(listening){

        //new socket wrapper object to add to array of connections
        socketConnections.push_back(new sockWrapper( "server", "127.0.0.1",  port));

        //blocks untilll connection is made
        if (listener.accept( socketConnections.back()->socket) == sf::Socket::Done){
        
            std::cout <<" connection made to server."<< std::endl;
            std::cout<< "Total connections: " << socketConnections.size() << std::endl;
            socketConnections.back()->send("Connected.");
            socketConnections.back()->setAlive(true);
            socketConnections.back()->runThread();
        }
    }
}


//adds client socket in args to vector
void Connection::addSocket(std::string _name, std::string _ip, unsigned short _port){

    //adds a new socket to the socket array list with arguments
    socketConnections.push_back(new sockWrapper(_name, _ip,  _port));

    //connect the socket to the server
    socketConnections.back()->connect();
}




