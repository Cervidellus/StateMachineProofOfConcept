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
     socket.connect("tcp://127.0.0.1:5556");
     while (true) {
         std::cout << "Enter Message to Send:" << std::endl;
         std::string message;
         std::cin >> message;
         std::cout << "Sending " << message << std::endl << std::endl;
         zmq::message_t zmqmessage (message.size());
         memcpy (zmqmessage.data (), message.c_str(), message.size());
         socket.send (zmqmessage);
     }
    return a.exec();
}
