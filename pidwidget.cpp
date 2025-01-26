#include "pidwidget.h"
#include "ui_pidwidget.h"

PIDWidget::PIDWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PIDWidget)
{
    ui->setupUi(this);
        setWindowFlags(Qt::Window);
    setWindowTitle("PID");
    ui->wzmocnienie->setValue(0.5);
    ui->stalaCalkowania->setValue(10);
    ui->stalaRozniczkowania->setValue(0.2);
    ui->minWyjscie->setMinimum(-500);
    ui->maxWyjscie->setMaximum(500);
    ui->minWyjscie->setValue(-100);
    ui->maxWyjscie->setValue(100);
}

PIDWidget::~PIDWidget()
{
    delete ui;

}
void PIDWidget::on_Zapisz_clicked()
{
    double wzmocnienie = ui->wzmocnienie->value();
    double stalaCalkowania = ui->stalaCalkowania->value();
    double stalaRozniczkowania = ui->stalaRozniczkowania->value();
    double minWyjscie = ui->minWyjscie->value();
    double maxWyjscie = ui->maxWyjscie->value();

    emit ZmianaPID(wzmocnienie, stalaCalkowania, stalaRozniczkowania, minWyjscie, maxWyjscie);

   this->close();
}
