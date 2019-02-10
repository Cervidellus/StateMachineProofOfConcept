#include "messagehandler.h"

#include <QDebug>
#include <QString>
#include "zmq.hpp"
#include "messenger.h"

MessageHandler::MessageHandler(QObject *parent) : QObject(parent),
    m_messenger()
{
    //try and initialize messenger in initializer list
   m_messenger = new Messenger();
   m_messenger->publish("TestOfTheMessageHandlersssss");
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
    qDebug() << "videologgerActivate triggered by messenger";
    m_messenger->publish("VideoLoggerActivate");
    //emit videologgerActivated(); `
}

void MessageHandler::videologgerDeactivate()
{
    qDebug() << "videologgerDeactivate triggered by messenger";
    emit videologgerDeactivated();
}
