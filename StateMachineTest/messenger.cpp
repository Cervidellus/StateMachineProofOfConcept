#include <QString>
#include <QDebug>

#include "messenger.h"

Messenger::Messenger(QObject *parent) : QObject(parent),
    m_context(1),
    m_publisher(m_context, ZMQ_PUB)
{

    //start the XPUB/XSUB intermediary thread
    IntermediaryThread *intermediaryThread = new IntermediaryThread();
    intermediaryThread->start();

    //setup the subscriber thread
    SubscriberThread *subscriberThread = new SubscriberThread();

    //make connections between subscriber thread and handler
    connect(subscriberThread, &SubscriberThread::messageReceived, this, &Messenger::processMessage);
    //start subscriber thread
    subscriberThread->start();

    //test making a new publisher here and sending a message, then test the m_context
    //throws no error, but does not work?
    Sleep(1000);
//    zmq::context_t testContext(1);
//    zmq::socket_t socket(testContext, ZMQ_PUB);
    m_publisher.connect("tcp://127.0.0.1:5556");
    Sleep(100);


//test send a message
    zmq::message_t msg (5);
    memcpy(msg.data(), "Super", 5);
    m_publisher.send(msg);//works... I need to wait long enough so that the intermediary thread is running

}

void Messenger::publish(const QString &message)
{
//    QByteArray messageArray = message.toUtf8().constData();
//  TODO: handle error if send fails
    std::string stringMessage = message.toLocal8Bit().constData();
    int size = stringMessage.size();
    zmq::message_t zmqmessage (size);
    memcpy (zmqmessage.data (), stringMessage.c_str(), size);
    m_publisher.send(zmqmessage);
}

void Messenger::processMessage(const QString message){
    //todo, connect message to console window
    //The intention here is to process the message, parsing it into the envelope, message, and parameters
    //I may have this as something that ends up in the application rather than the library

    //If else statements to parse out message.

    if (message == "VideoLoggerActivated"){
        emit videologgerActivated();
    }

    qDebug() << "Message Received:" << message;
    emit messageProcessed(message);
}

void SubscriberThread::run() {
    //TODO: I'll set it up so it can properly shut itself down.
    //TODO: I'll set it up for xpub/xsub
    //TODO: I'll standardize message structure

    //I need to initialize the subscriber in the mainwindow, and then run it...


    //set up socket
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://127.0.0.1:5555");
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


void IntermediaryThread::run()
{
        //sets up the central XPUB/XSUB node

        zmq::context_t intermediaryContext(1);

        zmq::socket_t centralSub(intermediaryContext, ZMQ_XSUB);
        centralSub.bind("tcp://127.0.0.1:5556");

        zmq::socket_t centralPub(intermediaryContext, ZMQ_XPUB);
        centralPub.bind("tcp://127.0.0.1:5555");

        zmq::proxy(centralSub, centralPub, nullptr);
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
    qDebug() << "videologgerActivate triggered by messenger";
    publish("VideoLoggerActivate");
    //emit videologgerActivated(); `
}

void Messenger::videologgerDeactivate()
{
    qDebug() << "videologgerDeactivate triggered by messenger";
    emit videologgerDeactivated();
}
