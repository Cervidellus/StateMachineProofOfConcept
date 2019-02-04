#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>

class Messenger;

//This class is meant to provide the signals and slots for communicating
//between a node and the zmq sockets.
//when this becomes a library, this will become an abstract class
//each node will have to subclass it and reimplemnt the signals and slots
//defaults will be just be qDebug output

class MessageHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageHandler(QObject *parent = nullptr);//here we set up connections between messages and signals/slots


    signals:
        //signals for triggering changes in the state machine
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

    private:
        Messenger *m_messenger;
};

#endif // MESSAGEHANDLER_H
