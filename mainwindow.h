#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QString>
#include <QVector>
#include <QHash>
#include <QPushButton>
#include <QMessageBox>
#include <random>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer=new QTimer();
    QTime time;
    QVector<QString> tarjetas{"tarjeta01", "tarjeta02", "tarjeta03", "tarjeta04","tarjeta05","tarjeta06"
                              "tarjeta07", "tarjeta08", "tarjeta09", "tarjeta10","tarjeta11","tarjeta12"
                              "tarjeta13", "tarjeta14", "tarjeta15", "tarjeta16","tarjeta17","tarjeta18"};
    QHash<QString, QString> reparto;
    int puntaje=0;
    bool jugadaIniciada;
    QPushButton* tarjetaAnterior;
    QPushButton* tarjetaActual;
    int parejasRestantes;
    QMessageBox msgBox; //mensaje para mostrarle al usuario


private slots:
    void actualizarCronometro();
    void tarjetaDescubierta();
    void mezclar(QVector<QString> &tarjetas);
    void repartir(QVector<QString> &tarjetas, QHash<QString, QString> &reparto);
    void definirResultadoParcial();
    void reiniciarTarjetas();
    void mostrarImagen();
    void definirResultadoFinal();
    void actualizarEstado();
    void inicializarJuego();


private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
