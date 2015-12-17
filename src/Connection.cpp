#include "Connection.h"
///TO-DO            Comment all of this well


Connection::Connection(float _timeOut):timeOut(_timeOut){


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
std::string Connection::recieveFrom(std::string _name){


     for(auto socks: socketConnections){

        if(socks->getName() == _name){

            if(socks->unreadMessages() > 0){

                return socks->getMessage();
            }
        }
    }

    return "not found!";
}

//kills connection with same name as args
void Connection::killConnection(std::string _name){


    for(auto socks: socketConnections){

        if(socks->getName() == _name){

            socks->setAlive(false);
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

/// POSSIBLY: return true if connection is valid for following two functions

//adds server socket in args to vector
void Connection::addSocket(std::string _name, unsigned short _port){

    socketConnections.push_back(new sockWrapper(_name, _port));

    socketConnections.back()->setAlive(true);

    socketConnections.back()->connect();

    socketConnections.back()->run.launch();
}

//adds client socket in args to vector
void Connection::addSocket(std::string _name, std::string _ip, unsigned short _port){

    socketConnections.push_back(new sockWrapper(_name, _ip,  _port));

    socketConnections.back()->setAlive(true);

    socketConnections.back()->connect();

    socketConnections.back()->run.launch();
}


