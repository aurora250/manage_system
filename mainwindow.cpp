#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signupform.h"
#include "manageform.h"
#include "setting.h"
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QDialog>

//sql:
void sql_init(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(setting::database_path);
    if(!db.open()) qDebug()<<"错误打开";
    QString set_sql = QString("create table if not exists user(id integer primary key autoincrement,"
                              "username ntext unique not NULL,"
                              "password ntext not NULL)");
    QSqlQuery query;
    if(!query.exec(set_sql)){
        qDebug()<<"创建成功";
    }
    else{
        qDebug()<<"创建失败";
    }
}
//mainwindow:
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    focus = 'u';
    ui->username_le->setFocus();
    this->setWindowIcon(QIcon(setting::main_icon));
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint&~Qt::WindowMinMaxButtonsHint);
    ui->password_le->setValidator(setting::inputValidator["password"]);
    ui->username_le->setValidator(setting::inputValidator["username"]);

    QPixmap *pixmap = new QPixmap;
    pixmap->load(setting::barber_icon);
    //pixmap->save(setting::barber_icon,"PNG");  //ICCP
    QSize size = ui->log_image->size();
    ui->log_image->setPixmap(pixmap->scaled(size));

    QGraphicsDropShadowEffect *back_shadow = new QGraphicsDropShadowEffect;
    back_shadow->setOffset(-3, 0);
    back_shadow->setBlurRadius(30);
    ui->log_image->setGraphicsEffect(back_shadow);

    connect(ui->signup_bt ,SIGNAL(clicked(bool)), this, SLOT(signup_bt_clicked()));
    connect(ui->login_bt, SIGNAL(clicked(bool)), this, SLOT(login_bt_clicked()));
    //qDebug()<<setting::cache_path;
}
MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::signup_bt_clicked(){
    Signup *s = new Signup;
    s->show();
    this->close();
}

void MainWindow::login_bt_clicked(){
    sql_init();
    QString user_name = ui->username_le->text();
    QString password = ui->password_le->text();
    QString sql = QString("select * from user where username='%1' and password='%2'").arg(user_name, password);
    QSqlQuery query(sql);
    if(!query.next()){
        qDebug()<<"登录失败";
        QMessageBox::information(this, "登录", "登录失败！请检查账户或密码是否正确；若无账户，请注册新的账户");
    }
    else{
        qDebug()<<"登录成功";
        Manageform *mf = new Manageform;
        mf->show();
        this->close();
    }
}
void MainWindow::keyPressEvent(QKeyEvent* _event)
{
    auto _key = _event->key();
    if (_key == Qt::Key_Enter) this->login_bt_clicked();
    else if(_key == Qt::Key_Up || _key == Qt::Key_W || _key == Qt::Key_S || _key == Qt::Key_Down){
        if(this->focus == 'u'){
            ui->password_le->setFocus();
            this->focus = 'd';
        }
        else if(this->focus == 'd'){
            ui->username_le->setFocus();
            this->focus = 'u';
        }
        else qDebug()<<"非法焦点";
    }
}
