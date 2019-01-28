#include "messenger.h"

#include <QTimer>
#include <QDebug>
#include <zmq.hpp>

Messenger::Messenger(QObject *parent) : QObject(parent)
{
    //Start the intermediary thread for the XPUB/XSUB pattern, to be used by all other nodes.
    IntermediaryThread *intermediaryThread = new IntermediaryThread;
    intermediaryThread->start();

    //create the subscriber and publishers for this node
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5556");
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.connect("tcp://localhost:5555");

    //Connect a message polling function to the main event loop
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Messenger::poll);
    timer->start(500);//polling rate in milliseconds, use zero for fastest rate

}

void Messenger::poll()
{
    //qDebug() << "Polled";
}

void Messenger::lightsActivate()
{
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
    qDebug() << "videologgerActivate triggered by messenger";
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
