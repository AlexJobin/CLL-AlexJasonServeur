#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
#include <QDir>
#include <QTimer>
#include <QtGui>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <string>
#include <QVariant>

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
    void on_btnPartirServeur_clicked();
    void sltimerout();
    void Cherchejoueurs();
    void nouvconnection();
    int randInt(int low, int high);

    void on_MainWindow_destroyed();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    bool PartiEnCours;
    bool JoueurMort;
    bool J1;
    bool J2;
    int nbJoueurs;
    QTcpSocket *SocketJ1;
    QTcpSocket *SocketJ2;
    QTcpServer *Serveur;
    QVariant Note;
    QByteArray Envoie;
    QByteArray Recue;
};

#endif // MAINWINDOW_H
