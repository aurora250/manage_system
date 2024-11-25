#include "chooseform.h"
#include "manage.h"
#include "setting.h"
#include "ui_chooseform.h"
#include <QPushButton>
#include <QMessageBox>

Chooseform::Chooseform(QString _card, Manageform *_mf, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Chooseform){
    ui->setupUi(this);
    this->setWindowIcon(QIcon(setting::main_icon));

    this->card=_card;
    qDebug()<<card;
    this->id="";
    this->name="";
    this->mf=_mf;

    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint&~Qt::WindowMinMaxButtonsHint);

    ui->employee_ec->clear();
    QStringList header1;
    header1<<"姓名"<<"编号"<<" ";
    ui->employee_ec->setColumnCount(header1.size());
    ui->employee_ec->setHorizontalHeaderLabels(header1);
    ui->employee_ec->verticalHeader()->hide();
    ui->employee_ec->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int row=0;
    for(emp_constIter iter=manage::emp_constBegin();iter!=manage::emp_constEnd();iter++){
        employee* staff = iter.value();
        ui->employee_ec->setRowCount(row+1);
        ui->employee_ec->setItem(row, 0, new QTableWidgetItem(staff->_name()));
        ui->employee_ec->setItem(row, 1, new QTableWidgetItem(staff->_id()));
        QPushButton *pt=new QPushButton("选择");
        pt->setProperty("row", row);
        connect(pt, SIGNAL(clicked(bool)), this, SLOT(choose_em_bt_clicked()));
        ui->employee_ec->setCellWidget(row, 2, pt);
        row++;
    }

    ui->service_ec->clear();
    QStringList header2;
    header2<<"名称"<<"价格"<<" ";
    ui->service_ec->setColumnCount(header2.size());
    ui->service_ec->setHorizontalHeaderLabels(header2);
    ui->service_ec->verticalHeader()->hide();
    ui->service_ec->setEditTriggers(QAbstractItemView::NoEditTriggers);
    row=0;
    for(ser_constIter iter=dress::ser_constBegin();iter!=dress::ser_constEnd();iter++){
        ui->service_ec->setRowCount(row+1);
        ui->service_ec->setItem(row, 0, new QTableWidgetItem(iter.key()));
        ui->service_ec->setItem(row, 1, new QTableWidgetItem(QString::number(iter.value()->_price())));
        QPushButton *pt=new QPushButton("选择");
        pt->setProperty("row", row);
        connect(pt, SIGNAL(clicked(bool)), this, SLOT(choose_se_bt_clicked()));
        ui->service_ec->setCellWidget(row, 2, pt);
        row++;
    }

    connect(ui->yes_bt, SIGNAL(clicked(bool)), this, SLOT(yes_bt_clicked()));
    connect(ui->cancel_bt, SIGNAL(clicked(bool)), this, SLOT(cancel_bt_clicked()));
}

Chooseform::~Chooseform(){
    delete ui;
}

void Chooseform::choose_em_bt_clicked(){
    QPushButton *bt = dynamic_cast<QPushButton*>(this->sender());
    if(bt == nullptr) return;
    int row = bt->property("row").toInt();  //index.row()
    this->id=ui->employee_ec->item(row, 1)->text().trimmed();
    qDebug()<<id;
}
void Chooseform::choose_se_bt_clicked(){
    QPushButton *bt = dynamic_cast<QPushButton*>(this->sender());
    if(bt == nullptr) return;
    int row = bt->property("row").toInt();
    this->name=ui->service_ec->item(row, 0)->text().trimmed();
    qDebug()<<name;
}
void Chooseform::yes_bt_clicked(){
    if(id.isEmpty()){
        QMessageBox msg;
        msg.setText(u8"未选择美发师！");
        msg.exec();
        return;
    }
    if(name.isEmpty()){
        QMessageBox msg;
        msg.setText(u8"未选择服务！");
        msg.exec();
        return;
    }
    manage::dress(this->id, this->card, this->name);
    QMessageBox msg;
    msg.setText(u8"已登记！");
    msg.exec();
}
void Chooseform::cancel_bt_clicked(){
    mf->refresh_ser();
    this->close();
}
