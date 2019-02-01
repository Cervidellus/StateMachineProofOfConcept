#include <QCoreApplication>
#include <QString>

#include <zmq.hpp>
#include <iostream>

//#define sleep(n)    Sleep(n)

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_SUB);
    socket.connect ("tcp://127.0.0.1:5556");
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    while (true) {
        zmq::message_t received;
        //  Wait for next request from client
        std::cout << "Waiting for message." << std::endl;
        socket.recv (&received);
        std::cout << "Received Message" << std::endl;
        std::string message = std::string(static_cast<char*>(received.data()), received.size());
        std::cout << message << std::endl << std::endl;
    }

    return a.exec();
}
