#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    //Connect timer to the slot that will handle the timer
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizarEstado()));

    //Conectar cada boton Connect each button to the same slot, which will figure out which button was pressed and show its associated image file accordingly
    connect(ui->tarjeta01, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta02, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta03, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta04, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta05, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta06, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta07, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta08, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta09, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta10, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta11, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta12, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta13, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta14, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta15, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta16, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta17, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta18, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));

    inicializarJuego();
}


void MainWindow::tarjetaDescubierta(){
    //get the tile that was pressed
    tarjetaActual=qobject_cast<QPushButton*>(sender()); //para saber cual boton ha sido presionado

    //get the image linked to that tile in the map and set tile background to it
    mostrarImagen();

    //disable current tile so it can't be clicked again (unless there is no match, in which case it will be re-enabled)
    tarjetaActual->setEnabled(false); //bloquea un doble click sobre la misma tarjeta

    //do something depending on whether the revealed tile is the first or the second tile in the turn
    if (!jugadaIniciada){
        tarjetaAnterior=tarjetaActual;
        jugadaIniciada=true;
    }
    else{
        //change score and display it
        definirResultadoParcial();

        //reset turn
        jugadaIniciada=false;
    }
}


void MainWindow::mostrarImagen(){
    QString nombre_tarjeta=tarjetaActual->objectName();
    QString img=reparto[nombre_tarjeta];
    tarjetaActual->setStyleSheet("#" + nombre_tarjeta + "{ background-image: url(://" + img + ") }");
}


void MainWindow::reiniciarTarjetas(){
    //return tiles from current turn to the default state (remove backgrounds)
    tarjetaAnterior->setStyleSheet("#" + tarjetaAnterior->objectName() + "{ }");
    tarjetaActual->setStyleSheet("#" + tarjetaActual->objectName() + "{ }");

    //re-enable both tiles so they can be used on another turn
    tarjetaActual->setEnabled(true);
    tarjetaAnterior->setEnabled(true);

    //re-enable the whole tile section
    ui->frame->setEnabled(true);
}


void MainWindow::definirResultadoFinal(){
    msgBox.setWindowTitle("Juego terminado");
    msgBox.setIcon(QMessageBox::Information); //insertar icono de informacion en la ventanilla de juego terminado
    msgBox.setStandardButtons(QMessageBox::Yes); // insertar boton de "Si"
    msgBox.addButton(QMessageBox::No); // insertar boton de "No"
    msgBox.setDefaultButton(QMessageBox::Yes); //remarca a este boton por defecto
    msgBox.setEscapeButton(QMessageBox::No); //cuando el usuario presiona la tacla escape en el teclado

    if (parejasRestantes==0){
        timer->stop(); // metodo para detener el reloj
        msgBox.setText("¡Ha Ganado! El puntaje final es: " + QString::number(puntaje) + "\n¿Jugar de nuevo?"); //muestra un texto al usuario de que ha ganado el juego y pregunta si desea volver a jugar
        if (QMessageBox::Yes == msgBox.exec()){ // compara para ver si el usuario presiono el boton de "Si"
            inicializarJuego(); // se vuelve a reiniciar el juego
        }
        else{
            QCoreApplication::quit();
        }
    }
    else{
        if (time.toString()=="00:00:00"){
            timer->stop(); //detener el reloj
            ui->frame->setEnabled(false);
            msgBox.setText("Ha perdido ;( \n¿Jugar de nuevo?");
            if (QMessageBox::Yes == msgBox.exec()){
                inicializarJuego(); //se vuelve a reiniciar el juego
            }
            else{  //cierra el programa
                QCoreApplication::quit();
            }
        }
    }
}


void MainWindow::definirResultadoParcial(){
    //check if there is a match (the current tile matches the previous tile in the turn)
    if (reparto[tarjetaActual->objectName()]==reparto[tarjetaAnterior->objectName()]){
        puntaje+=10;
        ui->lblPuntaje->setText(QString::number(puntaje));
        parejasRestantes--;

        //if there is a match, find out if all tiles have been matched.
        definirResultadoFinal();
    }
    else{
        puntaje-=3;
        ui->lblPuntaje->setText(QString::number(puntaje));

        //disable the whole tile section so no tiles can be turned during the 1-second "memorizing period"
        ui->frame->setEnabled(false);

        //if there is no match, let user memorize tiles and after 1 second hide tiles from current turn so they can be used on another turn
        QTimer::singleShot(1000, this, SLOT(reiniciarTarjetas()));
    }
}

void MainWindow::inicializarJuego(){
    //start turn
    jugadaIniciada=false;

    //Set score
    puntaje=0;
    ui->lblPuntaje->setText(QString::number(puntaje));;

    //Set matches counter
    parejasRestantes=9;

    //Set clock for countdown
    time.setHMS(0,1,30);

    //Initialize countdown
    ui->cronometro->setText(time.toString("m:ss")); //formato del cronometro

    // Start timer with a value of 1000 milliseconds, indicating that it will time out every second.
    timer->start(1000);

    //Randomly sort tiles in container
    mezclar(tarjetas);

    //Grab pairs of tiles and bind the name of an image file to each pair
    repartir(tarjetas, reparto);

    //enable tiles frame
    ui->frame->setEnabled(true);

    //enable every tile and reset its image
    QList<QPushButton *> botones =  ui->centralwidget->findChildren<QPushButton*>();
    foreach (QPushButton* b, botones) {
        b->setEnabled(true);
        b->setStyleSheet("#" + b->objectName() + "{ }");
    }
}


void MainWindow::actualizarCronometro(){
    time=time.addSecs(-1);
    ui->cronometro->setText(time.toString("m:ss"));
}


void MainWindow::actualizarEstado(){
    actualizarCronometro();
    definirResultadoFinal();
}


void MainWindow::mezclar(QVector<QString> &tarjetas){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (tarjetas.begin(), tarjetas.end(), std::default_random_engine(seed)); //generador de numeros aleatorios
}


void MainWindow::repartir(QVector<QString> &tarjetas, QHash<QString, QString> &reparto){
    auto iterador=tarjetas.begin();
    for (int i=1; i<=8; i++){
        QString file_name="0"+QString::number(i)+".png";
        reparto[(*iterador)]=file_name;
        iterador++;
        reparto[(*iterador)]=file_name;
        iterador++;
    }
}


MainWindow::~MainWindow(){
    delete ui;
}

