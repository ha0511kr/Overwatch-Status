#include "nametag.h"
#include "ui_nametag.h"

Nametag::Nametag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nametag)
{
    ui->setupUi(this);
}

Nametag::~Nametag()
{
    delete ui;
}
