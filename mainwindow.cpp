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
    timer = new QTimer;
    Serveur = new QTcpServer();
    timer->setInterval(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(sltimerout()));
    connect(Serveur, SIGNAL(newConnection()), this, SLOT(nouvconnection()));
    //Serveur->setMaxPendingConnections(2);
    Serveur->listen(QHostAddress::Any,65124);
    PartiEnCours =false;
    JoueurMort = false;
    J1 = true;
    J2 = true;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnPartirServeur_clicked()
{
}

void MainWindow::sltimerout()
{
    QVariant v;
    if(SocketJ1->bytesAvailable() != 0)
      {

        Recue.append((SocketJ1->read(SocketJ1->bytesAvailable())));
        if(Recue.length() > 1)
            Recue.remove(0,1);
        v.setValue(Recue);

        if(v.toString() != "#")
        {
            if(v.toString() == "F")
            {
                Envoie.append("F");
                JoueurMort = true;
            }
            if(v.toString() == "V")
                Envoie.append("V");

            SocketJ2->write(Envoie);
            SocketJ2->waitForBytesWritten();
        }
        else
            J1 = true;
        }

    if(SocketJ2->bytesAvailable() != 0)
      {

        Recue.append((SocketJ2->read(SocketJ2->bytesAvailable())));
        if(Recue.length() > 1)
            Recue.remove(0,1);
        v.setValue(Recue);

        if(v.toString() != "#")
        {
            if(v.toString() == "F")
            {
                Envoie.append("F");
                JoueurMort = true;
            }
            if(v.toString() == "V")
                Envoie.append("V");

            SocketJ1->write(Envoie);
            SocketJ1->waitForBytesWritten();
      }
        else
            J2 = true;
    }


    if(JoueurMort)
    {
        timer->stop();
        PartiEnCours = false;
        QString s = "F";
        v.setValue(s);
        Envoie = v.toByteArray();
        SocketJ1->write(Envoie);
        SocketJ1->waitForBytesWritten();
        SocketJ2->write(Envoie);
        SocketJ2->waitForBytesWritten();
    }
    else
    {
        if(J1 == true && J2 == true)
        {
            PartiEnCours = true;
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());
            Note.setValue(randInt(1,9));

            Envoie.append(Note.toByteArray());
            if(Envoie.length() > 1)
                Envoie.remove(0,1);
            SocketJ1->write(Envoie);
            SocketJ2->write(Envoie);
            SocketJ1->waitForBytesWritten();
            SocketJ2->waitForBytesWritten();
            J1 = false;
            J2 = false;
        }
    }
}
void MainWindow::nouvconnection()
{
    if(PartiEnCours == false)
    {
        if(nbJoueurs == 1)
        {
            SocketJ2 = Serveur->nextPendingConnection();
            nbJoueurs ++;
            JoueurMort = false;
            J1 = true;
            J2 = true;
            timer->start();
        }

        if(nbJoueurs == 0)
        {
            SocketJ1 = Serveur->nextPendingConnection();
            nbJoueurs ++;
        }


    }
}
void MainWindow::Cherchejoueurs()
{
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
