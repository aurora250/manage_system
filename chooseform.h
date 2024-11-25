#ifndef CHOOSEFORM_H
#define CHOOSEFORM_H

#include <QWidget>
#include "manageform.h"

namespace Ui {
class Chooseform;
}

class Chooseform : public QWidget
{
    Q_OBJECT

public:
    explicit Chooseform(QString _card, Manageform *_mf, QWidget *parent = nullptr);
    ~Chooseform();

private slots:
    void choose_em_bt_clicked();
    void choose_se_bt_clicked();
    void yes_bt_clicked();
    void cancel_bt_clicked();

private:
    Ui::Chooseform *ui;
    Manageform *mf;
    QString card;
    QString id;
    QString name;
};

#endif // CHOOSEFORM_H
