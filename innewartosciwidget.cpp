#include "innewartosciwidget.h"
#include "ui_innewartosciwidget.h"

InneWartosciWIDGET::InneWartosciWIDGET(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InneWartosciWIDGET)
{
    ui->setupUi(this);
     setWindowFlags(Qt::Window);
    setWindowTitle("Inne Wartości");

    ui->amplituda->setValue(3);
    ui->okres->setValue(5);
    ui->czasAktywacji->setValue(0);
    ui->p->setValue(1);
    ui->Interwal->setValue(0.1);
    ui->wartoscStala->setValue(1);
    ui->amplituda->setDisabled(true);
    ui->okres->setDisabled(true);
    ui->p->setDisabled(true);
    ui->p->setMinimum(0.1);
    ui->okres->setMinimum(1);
}

InneWartosciWIDGET::~InneWartosciWIDGET()
{
    delete ui;

}

void InneWartosciWIDGET::on_Zapisz_clicked()
{
    Typ typ = static_cast<Typ>(ui->typComboBox->currentIndex());
    double amplituda = ui->amplituda->value();
    int okres = ui->okres->value();
    int czasAktywacji = ui->czasAktywacji->value();
    double wartoscStala = ui->wartoscStala->value();
    double p = ui->p->value();
    double interwal = ui->Interwal->value();

    qDebug() << "Wprowadzone dane w InneWartosciWidget:";
    qDebug() << "Typ generatora:" << static_cast<int>(typ);
    qDebug() << "Amplituda:" << amplituda;
    qDebug() << "Okres:" << okres;
    qDebug() << "Czas aktywacji:" << czasAktywacji;
    qDebug() << "Stała całkowania:" << wartoscStala;
    qDebug() << "Wzmocnienie (p):" << p;
    qDebug() << "Interwał (p):" << interwal;
    emit ZmianaGeneratora(typ, amplituda, okres, czasAktywacji, wartoscStala, p, interwal);

    this->close();
}


void InneWartosciWIDGET::on_typComboBox_highlighted(int index)
{




}

void InneWartosciWIDGET::odblokuj(){
    ui->amplituda->setDisabled(false);
    ui->okres->setDisabled(false);
    ui->czasAktywacji->setDisabled(false);
    ui->wartoscStala->setDisabled(false);
    ui->p->setDisabled(false);
    ui->Interwal->setDisabled(false);

}

void InneWartosciWIDGET::on_typComboBox_activated(int index)
{
    switch (index) {
    default:
        odblokuj();
        break;
    case 0:
        odblokuj();
        ui->amplituda->setDisabled(true);
        ui->okres->setDisabled(true);
        ui->p->setDisabled(true);
        break;
    case 1:
        odblokuj();
        ui->czasAktywacji->setDisabled(true);
        ui->wartoscStala->setDisabled(true);
        ui->p->setDisabled(true);

        break;

    case 2:
        odblokuj();
        ui->czasAktywacji->setDisabled(true);
        ui->wartoscStala->setDisabled(true);

        break;
    }

}

