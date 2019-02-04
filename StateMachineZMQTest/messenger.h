#ifndef MESSENGER_H
#define MESSENGER_H

//sets up communication channels between the state machine and other nodes

#include <QObject>
#include <QThread>
#include <zmq.hpp>

class QThread;
class QString;

class Messenger : public QObject
{
    Q_OBJECT
public:
    explicit Messenger(QObject *parent = nullptr);
    void publish(const QString &message); //publishes a message to the state machine communication publisher channel

signals:
    void messageProcessed(const QString message);//passes the message from subscriber to GUI

    //signals for the state machine
    //    void lightsActivated();
    //    void lightsDeactivated();
    //    void videologgerActivated();
    //    void videologgerDeactivated();
    //    void movedToPickup();

public slots:
    void processMessage(const QString message);//will take a QJsonObject class and parse it.I will likely remove this.

    //slots to trigger outgoing ZMQ messages
//    void lightsActivate();
//    void lightsDeactivate();
//    void videologgerActivate();
//    void videologgerDeactivate();
//    void movetoPickup();

private:
    zmq::context_t m_context;
    zmq::socket_t m_publisher;

};


//SubscriberThread receives messages from the state machine communication subscriber channel
class SubscriberThread : public QThread
{
    Q_OBJECT

    void run() override;

signals:
    void messageReceived(const QString message);

};

#endif // MESSENGER_H
