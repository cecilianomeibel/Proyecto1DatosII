#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer=new QTimer();
    QTime time;
    int parejasRestantes; //definir variable

private slots:
    void actualizarEstado();
    void actualizarCronometro();
    void definirResultadoFinal();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
