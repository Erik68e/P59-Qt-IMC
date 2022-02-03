#include "registrar.h"
#include "ui_registrar.h"

Registrar::Registrar(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Registrar)
{
    ui->setupUi(this);
    lienzo = QPixmap(750,130);
    this->dibujar();

    ui->outCuadro->setPixmap(lienzo);

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

void Registrar::dibujar()
{
    lienzo.fill(Qt::white);

    QPainter painter(&lienzo);

    int x = 0;
    int y = 0;

    // Crear un pincel para los bordes
    QPen pincel;
    pincel.setWidth(5);
    pincel.setColor(Qt::red);
    pincel.setJoinStyle(Qt::MiterJoin);

    // Establecer el pincel al "pintor"
    painter.setPen(pincel);

    // Dibujar primera barra
    painter.drawRect(x+25, y+25,50,70);

    // Crear un objeto color para el relleno
    QColor colorRelleno(190,120,162);
    // Crear otro objeto color para el borde
    QColor colorBorde(78,3,48);
    //* Para aclarar los numeros
    // Establecer un pincel azul
    painter.setPen(Qt::blue);
    // Establecer un tipo de letra (font)
    painter.setFont(QFont("Arial", 7));
    // Dibujar un texto
    painter.drawText(10,110,"15");

    // Cambiar el color del pincel
    pincel.setColor(colorBorde);

    // Volver a establecer el pincel al "pintor"
    painter.setPen(pincel);

    // Establecer el color al brush (relleno)
    painter.setBrush(colorRelleno);

    // Dibujar segunda barra
    painter.drawRect(x+85, y+25, 55, 70);

    // Creando los colores de la tercera barra
    QColor cRellenoBarra3(253, 253, 115);
    QColor cBordeBarra3(174, 14, 51);

    // Estableciendo colores al pincel y al painter
    pincel.setColor(cBordeBarra3);
    painter.setPen(pincel);
    painter.setBrush(cRellenoBarra3);

    //* Para aclarar los numeros
    // Establecer un pincel azul
    painter.setPen(Qt::blue);
    // Establecer un tipo de letra (font)
    painter.setFont(QFont("Arial", 7));
    // Dibujar un texto
    painter.drawText(70,110,"20");

    // Dibujar tercera barra
    painter.drawRect(x+150,y+25,75,70);

    // Creando los colores de la tercera barra
    QColor cRellenoBarra4(130, 178, 255);
    QColor cBordeBarra4(100, 174, 51);

    // Estableciendo colores al pincel y al painter
    pincel.setColor(cBordeBarra4);
    painter.setPen(pincel);
    painter.setBrush(cRellenoBarra4);

    //* Para aclarar los numeros
    // Establecer un pincel azul
    painter.setPen(Qt::blue);
    // Establecer un tipo de letra (font)
    painter.setFont(QFont("Arial", 7));
    // Dibujar un texto
    painter.drawText(135,110,"25");
    painter.drawText(20,13,tr("|         Promedio"));
    painter.drawText(142,13,tr("| Sobrepeso |"));
    painter.drawText(300,13,tr("    Obesidad                     |"));

    // Dibujar cuarta barra
    painter.drawRect(x+235,y+25,85,70);

    // Creando los colores de la tercera barra
    QColor cRellenoBarra5(178, 208, 255);
    QColor cBordeBarra5(45, 174, 51);

    // Estableciendo colores al pincel y al painter
    pincel.setColor(cBordeBarra5);
    painter.setPen(pincel);
    painter.setBrush(cRellenoBarra5);

    //* Para aclarar los numeros
    // Establecer un pincel azul
    painter.setPen(Qt::blue);
    // Establecer un tipo de letra (font)
    painter.setFont(QFont("Arial", 7));
    // Dibujar un texto
    painter.drawText(215,110,"32.7");

    // Dibujar quinta barra
    painter.drawRect(x+330,y+25,100,70);

    //* Para aclarar los numeros
    // Establecer un pincel azul
    painter.setPen(Qt::blue);
    // Establecer un tipo de letra (font)
    painter.setFont(QFont("Arial", 7));
    // Dibujar un texto
    painter.drawText(310,110,"45");
    painter.drawText(425,110,"55");
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
        str.append(currentDateTime() + " - " + QString::number(m_peso) + tr("kg - ") + QString::number(m_altura) + tr("m - IMC: ") + masaC +"\n");
        // Mandar al historial
        ui->outHistorial->appendPlainText(str);
        // Limpiar la interfaz
        limpiar();
        // Mostrar mensage por 5 segundos en la barra de estado
        ui->statusbar->showMessage(tr("Calculando su IMC "),0100);
    }else{
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Error al calcular el IMC."));
    }
}

void Registrar::guardar()
{
    // Abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         tr("Guardar datos"),
                                                         QString(),
                                                         tr("Archivo de salarios (*.slr)"));
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
        ui->statusbar->showMessage(tr("Datos almacenados en ") + nombreArchivo,5000);
    }else{
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             tr("Guardar datos"),
                             tr("No se pudo guardar los datos"));
    }
    //Cerrar archivo
    archivo.close();
}

void Registrar::abrir()
{
    // Abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         tr("Guardar datos"),
                                                         QDir::home().absolutePath(),
                                                         tr("Archivo de salarios (*.slr)"));
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
        ui->statusbar->showMessage(tr("Datos almacenados en ") + nombreArchivo,5000);
    }else{
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             tr("Abrir datos"),
                             tr("No se pudo abrir el archivo"));
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
    if(1==1){
        QString historial = "";
        historial.append(tr("                                   - - Historial - -\n--------------------------------------------------------------------"));
        limpiar();
        ui->outHistorial->clear();
        ui->outHistorial->appendPlainText(historial);
        ui->outFecha->clear();
        ui->outFecha->setText("-/-/-");
        ui->outIMC->clear();
        ui->outIMC->setText("0.0");
    }
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
