#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <zmq.hpp>
#include <QtWidgets>
#include <QDebug>
#include <QString>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Add buttons for pre-defined messages to be sent
    addZMQButton("Lights Turned On", "message 1", 0, 0);
    addZMQButton("Lights Turned Off", "message 2", 0, 1);
    addZMQButton("testbutton", "message 3", 1, 0);
    addZMQButton("test2", "message 4", 1, 1);

    //add a dialog for adding new buttons that will send a particular message

    //create the subscriber and publishers for this node.
    //TODO:: I need to be able to pass the subscriber to the polling function
    zmq::context_t *context = new zmq::context_t(1);
    zmq::socket_t *subscriber = new zmq::socket_t(*context, ZMQ_SUB);
    subscriber->connect("tcp://localhost:5556");
    zmq::socket_t publisher(*context, ZMQ_PUB);
    publisher.connect("tcp://localhost:5555");

    //Connect a ZMQ polling function to the main loop
    QTimer *timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, this, &MainWindow::pollZMQ);
    connect(timer, &QTimer::timeout, this,[=](){ this->pollZMQ(subscriber);});
    timer->start(500);//polling rate in milliseconds, use zero for fastest rate

    //change it so that it automagically figures out the row

    //change it so that you can add button pairs


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addZMQButton(QString name, QString message, int row, int column)
{
    QPushButton *button = new QPushButton(name);
    connect(button,  &QPushButton::clicked, this, [=]{sendMessage(message); });
    ui->ButtonLayout->addWidget(button, row, column);
}

void MainWindow::sendMessage(QString message)
{
    qDebug() << message;
}

void MainWindow::pollZMQ(zmq::socket_t* subscriber)
{
    qDebug() << "Polling ZMQ";
    zmq::message_t testmessage;


 //   zmq_getsockopt(subscriber,ZMQ_EVENTS, &events, &eventsSize);

//    try {
    subscriber->recv(&testmessage);
//    }
//    catch(zmq::error_t& e){}

//    int rc = zmq::message_t.;
//    qDebug() << rc;

//    subscriber->recv(&message, flags);
//    qDebug() << message.data();
}
