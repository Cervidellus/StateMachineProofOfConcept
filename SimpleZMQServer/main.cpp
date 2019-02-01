#include <QCoreApplication>
#include <zmq.hpp>

#include <string>

#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    zmq::context_t context (1);
     zmq::socket_t socket (context, ZMQ_PUB);
     std::cout << "Connecting." << std::endl;
     socket.bind("tcp://127.0.0.1:5556");
     //  Do 10 requests, waiting each time for a response
     int msgnumber = 1;
     while (true) {
         std::cout << "Press enter to send message." << std::endl;
         std::cin.ignore();
         zmq::message_t zmqmessage (5);
         memcpy (zmqmessage.data (), "Hello", 5);
         std::cout << "Sending message " << msgnumber << "…" << std::endl;
         socket.send (zmqmessage);
     }
    return a.exec();
}
