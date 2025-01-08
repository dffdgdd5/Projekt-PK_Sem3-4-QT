#include "pidwidget.h"
#include "ui_pidwidget.h"

PIDWidget::PIDWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PIDWidget)
{
    ui->setupUi(this);
        setWindowFlags(Qt::Window);
    setWindowTitle("PID");
}

PIDWidget::~PIDWidget()
{
    delete ui;

}
void PIDWidget::on_Zapisz_clicked()
{
    double wzmocnienie = ui->wzmocnienie->text().toDouble();
    double stalaCalkowania = ui->stalaCalkowania->text().toDouble();
    double stalaRozniczkowania = ui->stalaRozniczkowania->text().toDouble();
    double minWyjscie = ui->minWyjscie->text().toDouble();
    double maxWyjscie = ui->maxWyjscie->text().toDouble();

    emit ZmianaPID(wzmocnienie, stalaCalkowania, stalaRozniczkowania, minWyjscie, maxWyjscie);

   this->close();
}
