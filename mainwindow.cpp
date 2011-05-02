#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nbJoueurs =0;
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(sltimerout()));
    PartiEnCours =false;
    //connect(Serveur, SIGNAL(newConnection()), this, SLOT(nouvconnection()));
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

    }
}
void MainWindow::nouvconnection()
{
    if(nbJoueurs != 2)
    nbJoueurs ++;
}
void MainWindow::Cherchejoueurs()
{
    while(nbJoueurs !=2)
    {
        //Serveur->listen(QHostAddress::Any,0);
    }
}
