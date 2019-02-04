#include "messagehandler.h"

#include <QDebug>
#include "zmq.hpp"

MessageHandler::MessageHandler(QObject *parent) : QObject(parent)
{

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
    std::string mymessage = "testing";
    zmq::message_t message(mymessage.size());
    memcpy (message.data(), mymessage.data(), mymessage.size());
 //   publisher().send(message);
    qDebug() << "videologgerActivate triggered by messenger";
    qDebug() << "sending " << message.data();
    emit videologgerActivated();
}

void MessageHandler::videologgerDeactivate()
{
    qDebug() << "videologgerDeactivate triggered by messenger";
    emit videologgerDeactivated();
}
