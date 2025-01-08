#include "arxwidget.h"
#include "ui_arxwidget.h"

ARXWidget::ARXWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ARXWidget)
{
    ui->setupUi(this);
     setWindowFlags(Qt::Window);
    setWindowTitle("ARX");
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
    int opoznienie = ui->Opoznienie->text().toInt();

    emit ZmianaARX(wektorA, wektorB, opoznienie);

    this->close();
}

