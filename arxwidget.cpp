#include "arxwidget.h"
#include "ui_arxwidget.h"

ARXWidget::ARXWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ARXWidget)
{
    ui->setupUi(this);
     setWindowFlags(Qt::Window);
    setWindowTitle("ARX");
     ui->WektorA->setText("-0.4");
    ui->WektorB->setText("0.6");
     ui->Opoznienie->setValue(0);
    //ui->Opoznienie->setMinimum(1);
}

ARXWidget::~ARXWidget()
{
    delete ui;
}


void ARXWidget::on_Zapisz_clicked()
{

    QVector<double> wektorA;
    for (const QString& value : ui->WektorA->text().split(",")) {
        wektorA.append(value.trimmed().toDouble());

    }
    QVector<double> wektorB;
    for (const QString& value : ui->WektorB->text().split(",")) {
        wektorB.append(value.trimmed().toDouble());
    }
    int opoznienie = ui->Opoznienie->value();

    emit ZmianaARX(wektorA, wektorB, opoznienie);

    this->close();
}

