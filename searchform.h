#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include "manageform.h"
#include <QWidget>

namespace Ui {
class Searchform;
}

class Searchform : public QWidget
{
    Q_OBJECT

public:
    explicit Searchform(Manageform& m ,QWidget *parent = nullptr);
    ~Searchform();
    void refresh_cus();
    void refresh_emp();
    void refresh_ser();

private slots:
    void search_bt_clicked();
    void close_bt_clicked();
    void del_bt_clicked();
    void search_ec_cellChanged(int row, int column);

private:
    Ui::Searchform *ui;
    Manageform *m;
    bool changed;
    QString type;
    QStringList titles;
    static cus_kvtype cus_search_fin;
    static emp_kvtype emp_search_fin;
    static ser_kvtype ser_search_fin;
};

#endif // SEARCHFORM_H
