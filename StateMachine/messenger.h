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

//both signals and slots are provided for everything, so that I can copy and paste code into ZMQ nodes
//signals for commands to send commands to ZMQ nodes
    void signalMoveToDropoff();
    void signalArrivedAtDropoff();
    void signalPlaceSection();
    void signalSectionPlaced();
    void signalMoveToPickup();
    void signalArrivedAtPickup();
    void signalPickupSection();
    void signalSectionPickedUp();

//signals to turn on and off services in ZMQ nodes
    void signalEnableJoystickInput();
    void signalJoystickInputEnabled();
    void signalDisableJoystickInput();
    void signalJoystickInputDisabled();

    void signalActivateLights();
    void signalLightsActivated();
    void signalDeactivateLights();
    void signalLightsDeactivated();

    void signalVideoLoggerActivate();
    void signalVideoLoggerActivated();
    void signalVideoLoggerDeactivate();
    void signalVideoLoggerDeactivated();

public slots:

    void slotMoveToDropoff();
    void slotArrivedAtDropoff();
    void slotPlaceSection();
    void slotSectionPlaced();
    void slotMoveToPickup();
    void slotArrivedAtPickup();
    void slotPickupSection();
    void slotSectionPickedUp();

    void slotEnableJoystickInput();
    void slotJoystickInputEnabled();
    void slotDisableJoystickInput();
    void slotJoystickInputDisabled();

    void slotActivateLights();
    void slotLightsActivated();
    void slotDeactivateLights();
    void slotLightsDeactivated();

    void slotVideologgerActivate();
    void slotVideoLoggerActivated();
    void slotVideologgerDeactivate();
    void slotVideoLoggerDeactivated();

    void processMessage(const QString message);//will take a QJsonObject class and parse it.I will likely remove this.

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


//The Intermediary class starts the hub of the XSUB/XPUB pattern.

class IntermediaryThread : public QThread
{

    Q_OBJECT

    void run() override;
};

#endif // MESSENGER_H
