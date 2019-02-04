#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>

class MessageHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageHandler(QObject *parent = nullptr);

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
};

#endif // MESSAGEHANDLER_H
