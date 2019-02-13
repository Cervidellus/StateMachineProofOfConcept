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

    Sleep(1000);//this might be removeable or maybe could be shortened.. just waiting for the xpub/xsub node ot get established
    m_publisher.connect("tcp://127.0.0.1:5556");
    Sleep(100);
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

//    void slotVideologgerActivate();
//    void slotVideoLoggerActivated();
//    void slotVideologgerDeactivate();
//    void slotVideoLoggerDeactivated();

    if (message == "MoveToDropoff"){
        emit signalMoveToDropoff();
    }
    else if (message == "ArrivedAtDropoff"){
        emit signalArrivedAtDropoff();
    }
    else if (message == "PlaceSection"){
        emit signalPlaceSection();
    }
    else if (message == "SectionPlaced"){
        emit signalSectionPlaced();
    }
    else if (message == "MoveToPickup"){
        emit signalMoveToPickup();
    }
    else if (message == "ArrivedAtPickup"){
        emit signalArrivedAtPickup();
    }
    else if (message == "PickupSection"){
        emit signalPickupSection();
    }
    else if (message == "SectionPickupUp"){
        emit signalSectionPickedUp();
    }
    else if (message == "EnableJoystickInput"){
        emit signalEnableJoystickInput();
    }
    else if (message == "JoystickInputEnabled"){
        emit signalJoystickInputEnabled();
    }
    else if (message == "DisableJoystickInput"){
        emit signalDisableJoystickInput();
    }
    else if (message == "JoystickInputDisabled"){
        emit signalJoystickInputDisabled();
    }
    else if (message == "ActivateLights"){
        emit signalActivateLights();
    }
    else if (message == "LightsActivated"){
        emit signalLightsActivated();
    }
    else if (message == "DeactivateLights"){
        emit signalDeactivateLights();
    }
    else if (message == "LightsDeactivated"){
        emit signalLightsDeactivated();
    }
    else if (message == "VideoLoggerActivate"){
        emit signalVideoLoggerActivate();
    }
    else if (message == "VideoLoggerActivated"){
        emit signalVideoLoggerActivated();
    }
    else if (message == "VideoLoggerDeactivate"){
        emit signalVideoLoggerDeactivate();
    }
    else if (message == "VideoLoggerDeactivated"){
        emit signalVideoLoggerDeactivated();
    }

    qDebug() << "Message Received:" << message;
    emit messageProcessed(message);
}

void SubscriberThread::run() {
    //TODO: I'll set it up so it can properly shut itself down.
    //TODO: I'll standardize message structure

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

//slots used to publish messages
void Messenger::slotMoveToDropoff()
{
    publish("MoveToDropoff");
}

void Messenger::slotArrivedAtDropoff()
{
    publish("ArrivedAtDropoff");
}

void Messenger::slotPlaceSection()
{
    publish("PlaceSection");
}

void Messenger::slotSectionPlaced()
{
    publish("SecionPlaced");
}

void Messenger::slotMoveToPickup()
{
    publish("MoveToPickup");
}

void Messenger::slotArrivedAtPickup()
{
    publish("ArrivedAtPickup");
}

void Messenger::slotPickupSection()
{
    publish("PickupSection");
}

void Messenger::slotSectionPickedUp()
{
    publish("SectionPickedUp");
}

void Messenger::slotEnableJoystickInput()
{
    publish("EnableJoystickInput");
}

void Messenger::slotJoystickInputEnabled()
{
    publish("JoystickInputEnabled");
}

void Messenger::slotDisableJoystickInput()
{
    publish("DisableJoystickInput");
}

void Messenger::slotJoystickInputDisabled()
{
    publish("JoystickInputDisabled");
}

void Messenger::slotActivateLights()
{
    publish("ActivateLights");
}

void Messenger::slotLightsActivated()
{
    publish("LightsActivated");
}

void Messenger::slotDeactivateLights()
{
    publish("DeactivateLights");
}

void Messenger::slotLightsDeactivated()
{
    publish("LightsDeactivated");
}

void Messenger::slotVideologgerActivate()
{
    publish("VideoLoggerActivate");
}

void Messenger::slotVideoLoggerActivated()
{
    publish("VideoLoggerDeactivated");
}

void Messenger::slotVideologgerDeactivate()
{
    publish("VideoLoggerDeactivate");
}

void Messenger::slotVideoLoggerDeactivated()
{
    publish("VideoLoggerDeactivated");
}


