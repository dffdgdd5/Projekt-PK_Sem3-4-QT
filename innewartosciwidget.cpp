#include "innewartosciwidget.h"
#include "ui_innewartosciwidget.h"

InneWartosciWIDGET::InneWartosciWIDGET(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InneWartosciWIDGET)
{
    ui->setupUi(this);
     setWindowFlags(Qt::Window);
    setWindowTitle("Inne Wartości");
}

InneWartosciWIDGET::~InneWartosciWIDGET()
{
    delete ui;

}

void InneWartosciWIDGET::on_Zapisz_clicked()
{
    Typ typ = static_cast<Typ>(ui->typComboBox->currentIndex());
    double amplituda = ui->amplituda->text().toDouble();
    int okres = ui->okres->text().toInt();
    int czasAktywacji = ui->czasAktywacji->text().toInt();
    double wartoscStala = ui->wartoscStala->text().toDouble();
    double p = ui->p->text().toDouble();


    qDebug() << "Wprowadzone dane w InneWartosciWidget:";
    qDebug() << "Typ generatora:" << static_cast<int>(typ);
    qDebug() << "Amplituda:" << amplituda;
    qDebug() << "Okres:" << okres;
    qDebug() << "Czas aktywacji:" << czasAktywacji;
    qDebug() << "Stała całkowania:" << wartoscStala;
    qDebug() << "Wzmocnienie (p):" << p;

    emit ZmianaGeneratora(typ, amplituda, okres, czasAktywacji, wartoscStala, p);

    this->close();
}

