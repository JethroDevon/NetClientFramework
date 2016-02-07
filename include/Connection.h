#ifndef CONNECTION_H
#define CONNECTION_H
/*

    This class manages multiple socketWrapper objects and controls many connections
    as a server or many connections to different servers as a client handler, when a connection
    to a server is called a connection is made and the socket is put on a vector, this
    vector is cycled through and received data is returned if a request for it is available
    this is the same for data to send, sendTo(string, string)will take the sockets name in first
     args and message in second, receiveFrom(string) will return a string from the connection which shares the same name

     Inbuilt ping connection for use with server and client, kills connection within pingTimeOut(time) pops the connection
     off the stack

*/


#include "sockWrapper.h"
#include <string>
#include <iostream>
#include <vector>
#include <time.h>

class Connection{

    public:
        Connection(float);
        virtual ~Connection();

        //send and receive from name of connection in args, second arg in send to is the actual message
        void sendTo(std::string, std::string);
        std::string recieveFrom(std::string);

        //used to poll connections to check if there is data on the stack
        //if connection with matching name to string in args has data will return true
        bool dataAvailable(std::string);

        //creates a new socket and connection and passes it to the array handler
        //overloaded functions are for server then client constructors of sockWrapper
        //respectively
        void addSocket(std::string, unsigned short);
        void addSocket(std::string, std::string, unsigned short);

        //kills connection with same name as args
        void killConnection(std::string);

    private:

        //pings a connection and sets pinged timer/flag to true
        void pingConnection();

        //if ping does not return ping within time at args kill connection
        void pingTimeOut(float);

        //getter method for ticks, this is to return passed time from last call
        std::clock_t getTicks();

        //vector to store and handle socketWrapper objects
        std::vector<sockWrapper*> socketConnections;
        //time variable
        std::clock_t ticks;

        float timeOut;
};

#endif // CONNECTION_H
