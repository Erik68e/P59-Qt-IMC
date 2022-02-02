#include "registrar.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Registrar w;
    w.show();
    return a.exec();
}
