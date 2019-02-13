#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Add buttons for pre-defined messages to be sent

    addZMQButton("Section Pickup Up", "SectionPickedUp", 0, 0);
    addZMQButton("Arrived At Dropoff","ArrivedAtDropoff", 1, 0);
    addZMQButton("Section Placed", "SectionPlaced", 2, 0);
    addZMQButton("Arrived At Pickup", "ArrivedAtPickup", 3, 0);

    //TODO:add a dialog for adding new buttons that will send a particular message

    //TODO: change it so that it automagically figures out the row

    //TODO: change it so that you can add button pairs

    //add connections for the listview
    connect(&m_messenger, &Messenger::messageProcessed, this, &MainWindow::handleSubscriberMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addZMQButton(QString name, QString message, int row, int column)
{
    QPushButton *button = new QPushButton(name);
    connect(button,  &QPushButton::clicked, this, [=]{m_messenger.publish(message);});
    ui->ButtonLayout->addWidget(button, row, column);
}

void MainWindow::handleSubscriberMessage(const QString message){
    ui->SubscriberMessages->addItem(message);
    ui->SubscriberMessages->scrollToBottom();
}

