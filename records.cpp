#include "records.h"
#include "ui_records.h"

Records::Records(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Records)
{
    ui->setupUi(this);
}

Records::~Records()
{
    delete ui;
}
