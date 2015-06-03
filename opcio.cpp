#include "opcio.h"
#include "ui_opcio.h"
#include <QString>

Opcio::Opcio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Opcio)
{
    ui->setupUi(this);
}

Opcio::~Opcio()
{
    delete ui;
}

void Opcio::on_pushButton_2_clicked()
{
    this->close();
}

void Opcio::on_pushButton_clicked()
{
    alarm = ui->lineEdit->text()+":"+ui->lineEdit_2->text()+":"+ui->lineEdit_3->text();
    ui->label->setText(alarm);
    //this->close();
}
