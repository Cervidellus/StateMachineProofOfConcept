TEMPLATE = subdirs

SUBDIRS += StateMachine StateMachineZMQTest SimpleZMQClient SimpleZMQServer \
    Messenger

CONFIG += ordered

INCLUDEPATH += $$PWD/


