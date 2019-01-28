#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <zmq.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
        void sendMessage(QString message);
        void pollZMQ(zmq::socket_t* subscriber);

private:
    Ui::MainWindow *ui;
    void addZMQButton(QString name, QString message, int row, int column);

//    void *context;
//    void *subscriber;
};

#endif // MAINWINDOW_H
