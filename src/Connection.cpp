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

    return "no data from " + _name;
}

//kills connection with same name as args
void Connection::killConnection(std::string _name){

    for(auto socks: socketConnections){

        if(socks->getName() == _name){

            socks->setAlive(false);
        }
    }
}

//used to poll connections to check if there is data on the stack
//if connection with matching name to string in args has data will return true
bool Connection::dataAvailable(std::string _name){

     for(auto socks: socketConnections){

        if(socks->getName() == _name){

            if(socks->unreadMessages() > 0){

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

///TO-DO: errors must be handled well, implement robust strategy

//adds server socket in args to vector
void Connection::addSocket(std::string _name, unsigned short _port){

    socketConnections.push_back(new sockWrapper(_name, _port));

    socketConnections.back()->setAlive(true);

    socketConnections.back()->connect();

    socketConnections.back()->run.launch();
}

//adds client socket in args to vector
void Connection::addSocket(std::string _name, std::string _ip, unsigned short _port){

    //adds a new socket to the socket array list with arguments
    socketConnections.push_back(new sockWrapper(_name, _ip,  _port));

    //activate the socket
    socketConnections.back()->setAlive(true);

    //connect the socket to the server
    socketConnections.back()->connect();

    //run the socket in its own thread
    socketConnections.back()->run.launch();
}


