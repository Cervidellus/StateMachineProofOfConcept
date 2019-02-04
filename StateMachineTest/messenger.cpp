#include "messenger.h"

#include <QTimer>
#include <QDebug>
#include <QDataStream>
#include <zmq.hpp>

Messenger::Messenger(QObject *parent) : QObject(parent) , context_(1)
{
    //Start the intermediary thread for the XPUB/XSUB pattern, to be used by all other nodes.
//    IntermediaryThread *intermediaryThread = new IntermediaryThread;
//    intermediaryThread->start();
//I might nees to set up my socket manually like so:
//    context_.setctxopt()
    //xpux/xsub owns 5555 and 5556

    //create the subscriber and publishers for this node
    zmq::context_t context(1);
//    zmq::socket_t subscriber(context, ZMQ_SUB);
//    subscriber.connect("tcp://127.0.0.1:5555");

    zmq::socket_t publisher(context, ZMQ_PUB);

    publisher.bind("tcp://127.0.0.1:5556");

//    //Connect a message polling function to the main event loop
//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, [&](){
//        std::string teststring2 = "stdstring test";
//        zmq::message_t testZmqMessage(teststring2.data(), teststring2.length());
//        //memcpy(testZmqMessage.data(), teststring2.c_str(), teststring2.length());
//        try {
//            publisher.send(testZmqMessage);
//        } catch (const std::exception& e) {
//            qDebug() << e.what();
//          //  qDebug() << "error in try block";
//        }
//        qDebug() << "sent " << teststring2.data();
//    });
//    connect(timer, &QTimer::timeout, this, &Messenger::poll);
//    timer->start(1000);//polling rate in milliseconds, use zero for fastest rate



    std::string teststring2 = "12345";
    zmq::message_t testZmqMessage(5);
    memcpy (testZmqMessage.data(), "Hello", 5);
    try {
        publisher.send(testZmqMessage);

    } catch (const std::exception& e) {
        qDebug() << e.what();
      //  qDebug() << "error in try block";
    }
    qDebug() << "sent " << teststring2.data();

}

void Messenger::poll()
{
//    zmq::message_t &message = "test";
//    publisher.send(message);
    //qDebug() << "Polled";
}

void Messenger::lightsActivate()
{
    zmq::message_t message;
   // publisher.send(message);
    qDebug() << "lightsActivate triggered by messenger";
    emit lightsActivated();
}

void Messenger::lightsDeactivate()
{
    qDebug() << "lightsDeactivate triggered by messenger";
    emit lightsDeactivated();
}

void Messenger::videologgerActivate()
{
    std::string mymessage = "testing";
    zmq::message_t message(mymessage.size());
    memcpy (message.data(), mymessage.data(), mymessage.size());
 //   publisher().send(message);
    qDebug() << "videologgerActivate triggered by messenger";
    qDebug() << "sending " << message.data();
    emit videologgerActivated();
}

void Messenger::videologgerDeactivate()
{
    qDebug() << "videologgerDeactivate triggered by messenger";
    emit videologgerDeactivated();
}

void IntermediaryThread::run()
{
    qDebug() << "IntermediaryThread started";
        //sets up the central XPUB/XSUB node
        zmq::context_t intermediaryContext(1);
        zmq::socket_t centralPub(intermediaryContext, ZMQ_XPUB);
        centralPub.bind("tcp://127.0.0.1:5555");
        zmq::socket_t centralSub(intermediaryContext, ZMQ_XSUB);
        centralSub.bind("tcp://127.0.0.1:5556");
        zmq::proxy(static_cast<void *>(centralSub), static_cast<void *>(centralPub), nullptr);
}
