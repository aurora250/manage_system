#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

void sql_init();

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event);
    //void closeEvent(QCloseEvent *);

private slots:
    void signup_bt_clicked();
    void login_bt_clicked();

private:
    Ui::MainWindow *ui;
    char focus;
};
#endif // MAINWINDOW_H
