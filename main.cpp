#include "registrar.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Objeto para manejar las traducciones
    QTranslator traducion;
    // Solicitando al usuario que seleccione un idioma
    QStringList idiomas;
    idiomas  << "Español" << "Ruso";
    QString idiomaSeleccionado = QInputDialog::getItem(NULL,
                                                       "Idioma",
                                                       "Seleccione un idioma",
                                                       idiomas);
    // Dependiendo del idioma seleccionado, carga el archivo de rtaducción
    if (idiomaSeleccionado == "Ruso"){
        traducion.load(":/registrar_ru.qm");
    }
    // Si es diferente de español, se instala la traducción en TODA la aplicación
        if (idiomaSeleccionado != "Español"){
            a.installTranslator(&traducion);
        }
        // Muestra la ventana principal
    Registrar w;
    w.show();
    return a.exec();
}
