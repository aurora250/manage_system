#include "signupform.h"
#include "ui_signupform.h"
#include "mainwindow.h"
#include "setting.h"
#include <QMessageBox>

Signup::Signup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Signup)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(setting::main_icon));
    ui->username_le->setValidator(setting::inputValidator["username"]);
    ui->password_le->setValidator(setting::inputValidator["password"]);
    ui->check_le->setValidator(setting::inputValidator["password"]);

    QPixmap *pixmap = new QPixmap(setting::barber_icon);
    QSize size = ui->sign_image->size();
    ui->sign_image->setPixmap(pixmap->scaled(size));

    connect(ui->signup_bt, SIGNAL(clicked(bool)), this, SLOT(signup_bt_clicked()));
    connect(ui->return_bt, SIGNAL(clicked(bool)), this, SLOT(return_bt_clicked()));
}

Signup::~Signup()
{
    delete ui;
}

void Signup::return_bt_clicked(){
    MainWindow *w = new MainWindow;
    w->show();
    this->close();
}

void Signup::signup_bt_clicked(){
    sql_init();
    QString username = ui->username_le->text().trimmed();
    QString password = ui->password_le->text().trimmed();
    QString check = ui->check_le->text().trimmed();
    if(password == check)
    {
        QString sql = QString("insert into user(username,password) values('%1','%2');").arg(username, password);
        QSqlQuery query;
        if(!query.exec(sql))
        {
            qDebug()<<"insert into error";
            QMessageBox::information(this, "注册", "注册失败！用户已存在！");
        }
        else
        {
            qDebug()<<"insert into success";
            QMessageBox::information(this, "注册", "注册成功！");
            MainWindow *w = new MainWindow;
            w->show();
            this->close();
        }
    }else{
        QMessageBox::information(this, "注册", "两次密码输入不一致！");
    }
}
