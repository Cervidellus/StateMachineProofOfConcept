#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QTreeWidgetItem;
class QState;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    //signals for the state machine
    void lightsOn();
    void lightsOff();
    void videoLogStart();
    void videoLogStop();
public slots:

protected:
    //trying to make a qtreewidget of states
    QList<QTreeWidgetItem *> mStatesList;
private:
    Ui::MainWindow *ui;
    QState* createState(QString name, QState *parent = 0);
};

#endif // MAINWINDOW_H
