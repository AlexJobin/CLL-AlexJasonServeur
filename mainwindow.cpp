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
    timer = new QTimer;
    Serveur = new QTcpServer;
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
    while (true)
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
    QVariant v;
    if(SocketJ1->bytesAvailable() != 0)
    {
        Recue.append((SocketJ1->read(SocketJ1->bytesAvailable())));
        v.setValue(Recue);
        VieJ1 = v.toInt();
        Envoie.append("V:"+ v.toString());
        SocketJ2->write(Envoie);
    }
    if(SocketJ2->bytesAvailable() != 0)
    {
        Recue.append((SocketJ2->read(SocketJ2->bytesAvailable())));
        v.setValue(Recue);
        VieJ2 = v.toInt();
        Envoie.append("V:"+ v.toString());
        SocketJ1->write(Envoie);
    }

    if(VieJ1 ==0 || VieJ2 ==0)
    {
        timer->stop();
        PartiEnCours = false;
        QString s = "Fin de la partie";
        v.setValue(s);
        Envoie = v.toByteArray();
        SocketJ1->write(Envoie);
        SocketJ2->write(Envoie);
    }
    else
    {
        PartiEnCours = true;
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        Note.setValue(randInt(1,5));
        Envoie.append(Note.ByteArray);
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
        if(!Serveur->isListening())
        Serveur->listen(QHostAddress::Any,0);
    }
}

int MainWindow::randInt(int low, int high)
    {
        return qrand() % ((high + 1) - low) + low;
    }

void MainWindow::on_MainWindow_destroyed()
{
    Serveur->close();
    SocketJ1->close();
    SocketJ2->close();
}
