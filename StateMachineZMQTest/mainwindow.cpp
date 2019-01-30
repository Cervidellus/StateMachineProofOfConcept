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
    addZMQButton("Lights Turned On", "Lights Turned On", 0, 0);
    addZMQButton("Lights Turned Off", "Lights Turned Off", 0, 1);
    addZMQButton("Video Logger Started", "Video Logger Started", 1, 0);
    addZMQButton("Video Logger Stopped", "Video Logger Stopped", 1, 1);

    //add a dialog for adding new buttons that will send a particular message

    //TODO: change it so that it automagically figures out the row

    //TODO: change it so that you can add button pairs
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


