#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <zmq.hpp>
//#include <oldmessenger.h>
#include "messenger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:


private slots:
    void handleSubscriberMessage(const QString message);

private:
    Ui::MainWindow *ui;
    Messenger m_messenger; //used for state machine communications
    void addZMQButton(QString name, QString message, int row, int column);
};

#endif // MAINWINDOW_H
