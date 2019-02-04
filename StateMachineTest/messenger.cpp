#include <QString>
#include <QDebug>

#include "messenger.h"

Messenger::Messenger(QObject *parent) : QObject(parent),
    m_context(1),
    m_publisher(m_context, ZMQ_PUB)
{
    //bind the publisher
    m_publisher.bind("tcp://127.0.0.1:5556");
    //setup the subscriber thread
    SubscriberThread *subscriberThread = new SubscriberThread();//I wanted to do new SubscriberThread(this); but it didn't take it?
    //make connections between subscriber thread and handler


    connect(subscriberThread, &SubscriberThread::messageReceived, this, &Messenger::processMessage);
    //start subscriber thread
    subscriberThread->start();
}

void Messenger::publish(const QString &message)
{
    QByteArray messageArray = message.toUtf8();
    zmq::message_t zmqmessage (messageArray.size());
    memcpy( zmqmessage.data(), messageArray.data(), messageArray.size() );
    m_publisher.send(zmqmessage, zmqmessage.size());
//  TODO: handle error if send fails
}

void Messenger::processMessage(const QString message){
    //todo to work as a library, I guess I need to separate this out as its own class so each node implements its own thing here
    //todo, connect message to console window
    //The intention here is to process the message, parsing it into the envelope, message, and parameters
    //I may have this as something that ends up in the application rather than the library
    //for now, I just pass the message to the application
    emit messageProcessed(message);
}

void SubscriberThread::run() {
    //then I'll set it up so it can properly shut itself down.
    //then I'll set it up for xpub/xsub
    //then I'll standardize message structure

    //I need to initialize the subscriber in the mainwindow, and then run it...


    //set up socket
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://127.0.0.1:5556");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);//subscribes to all messages
    while (true){
        //recieve and hand off messages
        zmq::message_t received;
        subscriber.recv (&received);
        qDebug() << "Received Message";
        QString message = QString::fromUtf8(static_cast<char*>(received.data()), received.size());
        qDebug() << message;
        emit messageReceived(message);
        //message.clear();
    }
}
