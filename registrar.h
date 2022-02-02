#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Registrar; }
QT_END_NAMESPACE

class Registrar : public QMainWindow
{
    Q_OBJECT

public:
    Registrar(QWidget *parent = nullptr);
    ~Registrar();

private:
    Ui::Registrar *ui;
};
#endif // REGISTRAR_H
