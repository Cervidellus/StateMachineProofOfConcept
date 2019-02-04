#include "messagehandler.h"

#include <QDebug>
#include <QString>
#include "zmq.hpp"
#include "messenger.h"

MessageHandler::MessageHandler(QObject *parent) : QObject(parent)
{
   Messenger *m_messenger = new Messenger();

}

void MessageHandler::lightsActivate()
{
    zmq::message_t message;
   // publisher.send(message);
    qDebug() << "lightsActivate triggered by messenger";
    emit lightsActivated();
}

void MessageHandler::lightsDeactivate()
{
    qDebug() << "lightsDeactivate triggered by messenger";
    emit lightsDeactivated();
}

void MessageHandler::videologgerActivate()
{
    QString message = "testing_zmq_communication";
//    std::string mymessage = "testing";
//    zmq::message_t message(mymessage.size());
//    memcpy (message.data(), mymessage.data(), mymessage.size());

//    qDebug() << "videologgerActivate triggered by messenger";
//    qDebug() << "sending " << message.data();
    m_messenger->publish(message);
    emit videologgerActivated();
}

void MessageHandler::videologgerDeactivate()
{
    qDebug() << "videologgerDeactivate triggered by messenger";
    emit videologgerDeactivated();
}
