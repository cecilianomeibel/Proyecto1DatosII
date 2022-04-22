#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( timer,SIGNAL(timeout()), this, SLOT(actualizarEstado()));
}

void MainWindow::definirResultadoFinal(){
    if (parejasRestantes==0){

    }
    else{
        if ()
    }


}

void MainWindow::actualizarCronometro(){
    time=time.addSecs(-1);
    ui->cronometro->setText(time.toString("m:ss")); //convierte lo del reloj a string
}
void MainWindow::actualizarEstado(){
    actualizarCronometro();
    definirResultadoFinal();
}

MainWindow::~MainWindow()
{
    delete ui;
}

