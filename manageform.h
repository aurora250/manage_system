#ifndef MANAGEFORM_H
#define MANAGEFORM_H

#include "manage.h"
#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QTableWidgetItem>
#include <QSystemTrayIcon>

namespace Ui {
class manageform;
}

class Manageform : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manageform(QWidget *parent = nullptr);
    ~Manageform();
    void __init__();
    void refresh_cus();
    void refresh_emp();
    void refresh_ser();
    void save_modify_auto();
    void set_panel();
    void set_menu();
    void set_connect();
    void set_tray();
    void limite();

private slots:
    //button:
    void em_add_bt_clicked();
    void em_del_bt_clicked();
    void em_chg_bt_clicked();
    void em_clear_bt_clicked();
    void cu_add_bt_clicked();
    void cu_del_bt_clicked();
    void cu_chg_bt_clicked();
    void cu_clear_bt_clicked();
    void se_add_bt_clicked();
    void se_del_bt_clicked();
    void se_chg_bt_clicked();
    void se_clear_bt_clicked();
    void exit_save_bt_clicked();
    void exit_nsave_bt_clicked();
    void choose_bt_clicked();
    //tablewidget:
    void service_view(QTableWidgetItem*);
    void employee_view(QTableWidgetItem*);
    void customer_view(QTableWidgetItem*);
    //menu/action:
    void menu_revenue_triggered();
    void menu_search_triggered();
    void menu_exit_triggered();
    void menu_return_triggered();
    void menu_save_triggered();
    void import_excel_triggered();
    void import_json_triggered();
    void export_excel_triggered();
    void export_txt_triggered();
    void export_json_triggered();
    //keybord:
    void keyPressEvent(QKeyEvent* _event);

private:
    Ui::manageform *ui;
    manage *m;
    QMenuBar *form_menu;
    size_t4 focus;
    //static QMap<size_t4, QLineEdit*> lineedit_map;
};

#endif // MANAGEFORM_H
