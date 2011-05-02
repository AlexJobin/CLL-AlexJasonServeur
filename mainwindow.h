#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QVariant>
#include <QDir>
#include <QTimer>
#include <QtGui>
#include <QThread>
#include <string>

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

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    bool PartiEnCours;
    int nbJoueurs;
    int VieJ1;
    int VieJ2;
    QString NomJ1;
    QString NomJ2;
};

#endif // MAINWINDOW_H
