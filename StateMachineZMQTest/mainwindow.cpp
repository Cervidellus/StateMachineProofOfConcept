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
    addZMQButton("Turn Lights On", "Turn Light On", 0 , 0);
    addZMQButton("Lights Turned On", "Lights Turned On", 0, 1);
    addZMQButton("Turn Lights Off", "Turn Lights Off", 1, 0);
    addZMQButton("Lights Turned Off", "Lights Turned Off", 1 , 1);
    addZMQButton("Turn Video Logger On", "Turn Video Logger On", 2, 0);
    addZMQButton("Video Logger Activated", "VideoLoggerActivated", 2, 1);
    addZMQButton("Video Logger Deactivated", "VideoLoggerDeactivated", 3, 1);
    addZMQButton("Move To Pickup", "Move To Pickup", 4, 0);
    addZMQButton("Moved to Pickup", "Moved to Pickup", 4, 1);
    addZMQButton("Pick Up Section", "PickupSection", 5, 0);
    addZMQButton("Section Pickup Up", "SectionPickedUp", 5, 1);

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

