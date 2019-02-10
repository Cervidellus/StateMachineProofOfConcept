#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "messenger.h"

#include <QStateMachine>
#include <QFinalState>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    Messenger *messenger = new Messenger();

    QStateMachine *machine = new QStateMachine();

    ui->setupUi(this);
    //Create the states
    QState *initialState = createState("Inital State");

    QState *runningState = createState("Running State");
    QState *pickupSectionState = createState("Picking Up Section", runningState);
    QState *movingToDropoffState = createState("Moving To Section Dropoff", runningState);
    QState *droppingOffSectionState = createState("Dropping Off Section", runningState);
    QState *movingToPickupState = createState("Moving To Section Pickup", runningState);
    QFinalState *runningFinalState = new QFinalState(runningState);
    runningState->setInitialState(pickupSectionState);

    QFinalState *finalState = new QFinalState();
    finalState->setObjectName("Final State");

    //Add the transitions to the state machine
    initialState->addTransition(ui->pushButton1, &QPushButton::clicked, runningState);
    runningState->addTransition(runningState, &QState::finished, finalState);
    pickupSectionState->addTransition(ui->pushButton2, &QPushButton::clicked, movingToDropoffState);
    pickupSectionState->addTransition(messenger, &Messenger::lightsDeactivated, movingToDropoffState);
    movingToDropoffState->addTransition(ui->pushButton1, &QPushButton::clicked, droppingOffSectionState);
    droppingOffSectionState->addTransition(ui->pushButton2, &QPushButton::clicked, movingToPickupState);
    movingToPickupState->addTransition(ui->pushButton1, &QPushButton::clicked, pickupSectionState);

    //Add the top level states to machine. Child states are automatically added.
    machine->addState(initialState);
    machine->addState(runningState);
    machine->addState(finalState);

    //Implement actions to occur on entry or exit from states
    connect(runningState, &QState::entered, messenger, &Messenger::lightsActivate);
    connect(runningState, &QState::exited, messenger, &Messenger::lightsDeactivate);
    connect(movingToDropoffState, &QState::entered, messenger, &Messenger::videologgerActivate);
    connect(movingToDropoffState, &QState::exited, messenger, &Messenger::videologgerDeactivate);
    connect(movingToPickupState, &QState::entered, messenger, &Messenger::videologgerActivate);
    connect(movingToPickupState, &QState::exited, messenger, &Messenger::videologgerDeactivate);

    //Connect state machine signals to the GUI.
    connect (messenger, &Messenger::lightsActivated, this, [this](){ui->lightsRadioButton->setChecked(true);});
    connect (messenger, &Messenger::lightsDeactivated, this, [this](){ui->lightsRadioButton->setChecked(false);});
    connect (messenger, &Messenger::videologgerActivated, this, [this](){ui->videoLoggingRadioButton->setChecked(true);});
    connect (messenger, &Messenger::videologgerDeactivated, this, [this](){ui->videoLoggingRadioButton->setChecked(false);});


    //Signal to the GUI that the state machine has finished
    //connect(finalState, &QFinalState::entered, this, [finalState,this](){ui->label->setText("State Machine Finished");});

    //Start the state machine
    machine->setInitialState(initialState);
    machine->start();

    ui->statesTreeWidget->insertTopLevelItems(0, mStatesList);

    //setup the message passing connections and tie them to the main event loop.


}

MainWindow::~MainWindow()
{
    delete ui;
}



QState* MainWindow::createState(QString name, QState *parent)
{
    QState *state = new QState(parent);
    //set text to be used in the gui
    state->setObjectName(name);
    //state->assignProperty(ui->label, "text", state->objectName());
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setBackgroundColor(0, Qt::red);
    item->setText(0, state->objectName());
    connect(state, &QState::entered,
            [item](){item->setBackground(0,Qt::green);});
    connect(state, &QState::exited,
            [item](){item->setBackground(0,Qt::red);});

    mStatesList.append(item);
    return state;
}

//TODO: createStatusButton


