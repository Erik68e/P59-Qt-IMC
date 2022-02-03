#include "registrar.h"
#include "ui_registrar.h"

Registrar::Registrar(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Registrar)
{
    ui->setupUi(this);
}

Registrar::~Registrar()
{
    delete ui;
}

QString Registrar::currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80]; tstruct = *localtime(&now);

    strftime(buf, sizeof (buf), "%Y-%m-%d | %X", &tstruct);

    return buf;
}

void Registrar::limpiar()
{
    ui->inPeso->setValue(0.00);
    ui->inAltura->setValue(0.00);
}
void Registrar::calcular()
{
    ui->outFecha->setText(currentDateTime());
    // Obtener datos de la GUI
    m_peso = ui -> inPeso -> value();
    qDebug() << m_peso;
    // Altura en m
    m_altura = ui -> inAltura -> value();
    qDebug() << m_altura;
    if(m_peso == 0 || m_altura == 0){
        /*
            QMessageBox msgBox;
            msgBox.setText("El nombre o el numero de horas esta vacio");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
            */
        QMessageBox::warning(this,"Advertencia", "No hay informacion para calcular su IMC");
        return;
    }

    if(m_pesoMin < m_peso){
        m_pesoMin = m_peso;
        QString min = "";
        min.append(QString::number(m_pesoMin));
        ui->outPesoMin->setText(min);
        QString minimo = ui->outPesoMin->text();
        m_pesoMin = minimo.toFloat();
    }else if(m_pesoMin > m_peso){
        m_pesoMax = m_peso;
        QString max = "";
        max.append(QString::number(m_pesoMax));
        ui->outPesoMax->setText(max);
    }

    // Calcular la masa muscular
    m_IMC = m_peso/(m_altura*m_altura);
    qDebug() << m_IMC;
    QString masaC = QString::number(m_IMC/ 1.0, 'f', 2);
    ui->outIMC->setText(masaC);
    if(1 == 1){
        QString str = "";
        str.append(currentDateTime() + " - " + QString::number(m_peso) + "kg - " + QString::number(m_altura) + "m - IMC: " + masaC +"\n");
        // Mandar al historial
        ui->outHistorial->appendPlainText(str);
        // Limpiar la interfaz
        limpiar();
        // Mostrar mensage por 5 segundos en la barra de estado
        ui->statusbar->showMessage("Calculando su IMC ",5000);
    }else{
        QMessageBox::critical(this,
                              "Error",
                              "Error al calcular el IMC.");
    }
}

void Registrar::guardar()
{
    // Abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar datos",
                                                         QDir::home().absolutePath(),
                                                         "Archivo de salarios (*.slr)");
    qDebug() << nombreArchivo;
    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrir para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // Crear un stream de texto
        QTextStream salida(&archivo);
        // Enviar los datos del resultado a la salida
        salida << ui->outHistorial->toPlainText();
        salida << "." << endl;
        // Mostrar 5 segundos que todo fue bien
        ui->statusbar->showMessage("Datos almacenados en " + nombreArchivo,5000);
    }else{
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             "Guardar datos",
                             "No se pudo guardar los datos");
    }
    //Cerrar archivo
    archivo.close();
}

void Registrar::abrir()
{
    // Abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar datos",
                                                         QDir::home().absolutePath(),
                                                         "Archivo de salarios (*.slr)");
    qDebug() << nombreArchivo;
    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrir para LECTURA
    if(archivo.open(QFile::ReadOnly)){
        // Crear un stream de texto
        QTextStream entrada(&archivo);
        // Leer todo el contenido del archivo
        QString datos = "", hasta = "";
        while(entrada.atEnd() == false && hasta != ".") {
           hasta = entrada.readLine();
           datos += hasta + "\n";
        }
        // Cargar todo el contenido a la area del texto
        ui->outHistorial->clear();
        ui->outHistorial->setPlainText(datos);
        ui->outFecha->text();
        ui->outIMC->text();
        // Mostrar 5 segundos que todo fue bien
        ui->statusbar->showMessage("Datos almacenados en " + nombreArchivo,5000);
    }else{
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             "Abrir datos",
                             "No se pudo abrir el archivo");
    }
    //Cerrar archivo
    archivo.close();
}

void Registrar::on_Calcular_clicked()
{
    QString masaC = QString::number((0*m_IMC)/ 1.0, 'f', 2);
    calcular();
}

void Registrar::on_actionNuevo_triggered()
{
    limpiar();
    ui->outHistorial->clear();
    ui->outFecha->clear();
    ui->outFecha->setText("-/-/-");
    ui->outIMC->clear();
    ui->outIMC->setText("0.0");
}

void Registrar::on_actionGuardar_triggered()
{
    guardar();
}

void Registrar::on_actionAbrir_triggered()
{
    abrir();
}

void Registrar::on_actionSalir_triggered()
{
    close();
}
