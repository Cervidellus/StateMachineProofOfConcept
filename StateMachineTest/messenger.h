#ifndef MESSENGER_H
#define MESSENGER_H

//The messenger class:
//1. connects to the ZMQ messanging ports
//2. Sends command messages over ZMQ to other nodes
//3. Translates ZMQ messages from other nodes into Qt signals
//4. Sends logging messages over ZMQ to the textlogger node

#include <QObject>
#include <QThread>

class Messenger : public QObject
{
    Q_OBJECT
public:
    explicit Messenger(QObject *parent = nullptr);

signals:
    //signals for the state machine
    void lightsActivated();
    void lightsDeactivated();
    void videologgerActivated();
    void videologgerDeactivated();

public slots:
    //slots to trigger outgoing ZMQ messages
    void lightsActivate();
    void lightsDeactivate();
    void videologgerActivate();
    void videologgerDeactivate();

private slots:
    void poll();

private:
    //void sendLightsOn();
};

//The Intermediary class starts the hub of the XSUB/XPUB pattern.
class IntermediaryThread : public QThread
{
    Q_OBJECT

    void run() override;
};

#endif // MESSENGER_H
