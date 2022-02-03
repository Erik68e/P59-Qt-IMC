#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Registrar; }
QT_END_NAMESPACE

class Registrar : public QMainWindow
{
    Q_OBJECT

public:
    Registrar(QWidget *parent = nullptr);
    ~Registrar();

    QString currentDateTime();
    QString fecha();
    QString informacion();

private slots:
    void on_Calcular_clicked();

    void on_actionNuevo_triggered();

    void on_actionGuardar_triggered();

    void on_actionAbrir_triggered();

    void on_actionSalir_triggered();

private:
    Ui::Registrar *ui;

    void limpiar();
    void calcular();
    void guardar();
    void abrir();

    float m_peso = 0.0;
    float m_pesoMin = 0.0;
    float m_pesoMax = 0.0;
    float m_altura = 0.0;
    float m_IMC;

};
#endif // REGISTRAR_H

