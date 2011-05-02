#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVariant>
#include <qglobal.h>
#include <QTime>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nbJoueurs =0;
    VieJ1 =10;
    VieJ2 =10;
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(sltimerout()));
    connect(Serveur, SIGNAL(newConnection()), this, SLOT(nouvconnection()));
    PartiEnCours =false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnPartirServeur_clicked()
{
    while (1)
    {
        while(PartiEnCours == false)
        {
            Cherchejoueurs();
            timer->start();
        }
    }
}

void MainWindow::sltimerout()
{

    if(VieJ1 ==0 || VieJ2 ==0)
    {
        timer->stop();
        PartiEnCours = false;
    }
    else
    {
        PartiEnCours = true;
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        Note.setValue(randInt(0,5));
        Envoie.append(Note.BitArray);
        SocketJ1->write(Envoie);
        SocketJ2->write(Envoie);
    }
}
void MainWindow::nouvconnection()
{
    if(nbJoueurs == 0)
    {
        SocketJ1 = Serveur->nextPendingConnection();
        nbJoueurs ++;
    }

    if(nbJoueurs == 1)
    {
        SocketJ2 = Serveur->nextPendingConnection();
        nbJoueurs ++;
    }
}
void MainWindow::Cherchejoueurs()
{
    while(nbJoueurs !=2)
    {
        Serveur->listen(QHostAddress::Any,0);
    }
}

int MainWindow::randInt(int low, int high)
    {
        return qrand() % ((high + 1) - low) + low;
    }
