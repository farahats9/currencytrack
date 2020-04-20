#include "datadisplay.h"
#include "ui_datadisplay.h"
#include <QDebug>

DataDisplay::DataDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataDisplay)
{
    ui->setupUi(this);
}

DataDisplay::~DataDisplay()
{
    delete ui;
}

void DataDisplay::setSymbol(QString s)
{
    s.replace(QString("_"), QString("⇒"));
    ui->label->setText(s);
}

void DataDisplay::updateValue(double value, int direction)
{
    qDebug()<<direction;
    ui->lcdNumber->display(value);
    if(direction>0){
        ui->arrowLabel->setText("▲");
        ui->arrowLabel->setStyleSheet("color: rgb(0, 255, 0);");
    }else if(direction<0){
        ui->arrowLabel->setText("▼");
        ui->arrowLabel->setStyleSheet("color: rgb(255, 0, 0);");
    }
}
