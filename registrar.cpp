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

