#ifndef INNEWARTOSCIWIDGET_H
#define INNEWARTOSCIWIDGET_H

#include <QWidget>
#include "generator.h"
namespace Ui {
class InneWartosciWIDGET;
}

class InneWartosciWIDGET : public QWidget
{
    Q_OBJECT

public:
    explicit InneWartosciWIDGET(QWidget *parent = nullptr);
    ~InneWartosciWIDGET();
    void odblokuj();

signals:
    void ZmianaGeneratora(Typ typ,
                          double amplituda,
                          int okres,
                          int czasAktywacji,
                          double wartoscStala,
                          double p,
                          double interwal);

private slots:
    void on_Zapisz_clicked();
    void on_typComboBox_highlighted(int index);

    void on_typComboBox_activated(int index);

private:
    Ui::InneWartosciWIDGET *ui;
};

#endif // INNEWARTOSCIWIDGET_H
