#include "empl.h"
#include "ui_empl.h"

empl::empl(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::empl)
{
    ui->setupUi(this);
}

empl::~empl()
{
    delete ui;
}
