#include "searchform.h"
#include "ui_searchform.h"
#include "setting.h"
#include <QMessageBox>

Searchform::Searchform(Manageform &_m, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Searchform){
    ui->setupUi(this);
    this->setWindowIcon(QIcon(setting::main_icon));
    m=&_m;
    titles=setting::titles;
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint&~Qt::WindowMinMaxButtonsHint);
    changed=false;
    ui->search_tar_cb->addItems(titles);
    ui->search_tar_cb->setCurrentIndex(0);
    connect(ui->search_bt, SIGNAL(clicked(bool)), this, SLOT(search_bt_clicked()));
    connect(ui->search_ec, SIGNAL(cellChanged(int,int)), this, SLOT(search_ec_cellChanged(int,int)));
    connect(ui->close_bt, SIGNAL(clicked(bool)), this, SLOT(close_bt_clicked()));
}

Searchform::~Searchform(){
    delete ui;
}

void Searchform::refresh_cus(){
    ui->search_ec->blockSignals(true);
    ui->search_ec->clear();
    QStringList header_text;
    header_text<<"姓名"<<"卡号"<<"性别"<<"年龄"<<"电话"<<"";
    ui->search_ec->setColumnCount(header_text.size());
    ui->search_ec->setHorizontalHeaderLabels(header_text);
    ui->search_ec->verticalHeader()->hide();
    int row=0;
    for(cus_constIter iter=cus_search_fin.constBegin();iter!=cus_search_fin.constEnd();iter++){
        customer* staff = iter.value();
        ui->search_ec->setRowCount(row+1);
        ui->search_ec->setItem(row, 0, new QTableWidgetItem(staff->_name()));
        QTableWidgetItem *item = new QTableWidgetItem(staff->_card());
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        ui->search_ec->setItem(row, 1, item);
        ui->search_ec->setItem(row, 2, new QTableWidgetItem(staff->_gender()));
        ui->search_ec->setItem(row, 3, new QTableWidgetItem(QString::number(staff->_age())));
        ui->search_ec->setItem(row, 4, new QTableWidgetItem(staff->_phone()));
        QPushButton *pt=new QPushButton("删除");
        pt->setProperty("row", row);
        ui->search_ec->blockSignals(false);
        connect(pt, SIGNAL(clicked(bool)), this, SLOT(del_bt_clicked()));
        ui->search_ec->blockSignals(true);
        ui->search_ec->setCellWidget(row, 5, pt);
        row++;
    }
    ui->search_ec->blockSignals(false);
    m->refresh_cus();
}
void Searchform::refresh_emp(){
    ui->search_ec->blockSignals(true);
    ui->search_ec->clear();
    QStringList header_text;
    header_text<<"姓名"<<"职务"<<"编号"<<"性别"<<"年龄"<<"电话"<<"";
    ui->search_ec->setColumnCount(header_text.size());
    ui->search_ec->setHorizontalHeaderLabels(header_text);
    ui->search_ec->verticalHeader()->hide();
    //ui->search_ec->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int row=0;
    for(emp_constIter iter=emp_search_fin.constBegin();iter!=emp_search_fin.constEnd();iter++){
        employee* staff = iter.value();
        ui->search_ec->setRowCount(row+1);
        ui->search_ec->setItem(row, 0, new QTableWidgetItem(staff->_name()));
        ui->search_ec->setItem(row, 1, new QTableWidgetItem("理发师"));
        QTableWidgetItem *item = new QTableWidgetItem(staff->_id());
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        ui->search_ec->setItem(row, 2, item);
        ui->search_ec->setItem(row, 3, new QTableWidgetItem(staff->_gender()));
        ui->search_ec->setItem(row, 4, new QTableWidgetItem(QString::number(staff->_age())));
        ui->search_ec->setItem(row, 5, new QTableWidgetItem(staff->_phone()));
        QPushButton *pt=new QPushButton("删除");
        pt->setProperty("row", row);
        ui->search_ec->blockSignals(false);
        connect(pt, SIGNAL(clicked(bool)), this, SLOT(del_bt_clicked()));
        ui->search_ec->blockSignals(true);
        ui->search_ec->setCellWidget(row, 6, pt);
        row++;
    }
    ui->search_ec->blockSignals(false);
    m->refresh_emp();
}
void Searchform::refresh_ser(){
    ui->search_ec->blockSignals(true);
    ui->search_ec->clear();
    QStringList header_text;
    header_text<<"名称"<<"价格"<<"";
    ui->search_ec->setColumnCount(header_text.size());
    ui->search_ec->setHorizontalHeaderLabels(header_text);
    ui->search_ec->verticalHeader()->hide();
    int row=0;
    for(ser_constIter iter=ser_search_fin.constBegin();iter!=ser_search_fin.constEnd();iter++){
        ui->search_ec->setRowCount(row+1);
        QTableWidgetItem *item = new QTableWidgetItem(iter.key());
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        ui->search_ec->setItem(row, 0, item);
        ui->search_ec->setItem(row, 1, new QTableWidgetItem(QString::number(iter.value()->_price())));
        QPushButton *pt=new QPushButton("删除");
        pt->setProperty("row", row);
        ui->search_ec->blockSignals(false);
        connect(pt, SIGNAL(clicked(bool)), this, SLOT(del_bt_clicked()));
        ui->search_ec->blockSignals(true);
        ui->search_ec->setCellWidget(row, 2, pt);
        row++;
    }
    ui->search_ec->blockSignals(false);
    m->refresh_ser();
}

//slot:
void Searchform::close_bt_clicked(){
    this->close();
}
void Searchform::del_bt_clicked(){
    QMessageBox::StandardButton button = QMessageBox::question(this, "提示", "会删除本行成员，确认继续么？",
                                                               QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(button==QMessageBox::Yes){
        QPushButton *bt = dynamic_cast<QPushButton*>(sender()); //获取信号发出的对象
        if(bt == nullptr) return;
        int row = bt->property("row").toInt();
        qDebug()<<row;
        if(type==titles[0]){  //"员工", "顾客", "商品/服务"
            QString id=ui->search_ec->item(row, 2)->text().trimmed();
            manage::del_emp(id);
            emp_search_fin.remove(id);
            this->refresh_emp();
        }
        else if(type==titles[1]){
            QString card=ui->search_ec->item(row, 1)->text().trimmed();
            manage::del_cus(card);
            cus_search_fin.remove(card);
            this->refresh_cus();
        }
        else if(type==titles[2]){
            QString name=ui->search_ec->item(row, 0)->text().trimmed();
            manage::del_menu(name);
            ser_search_fin.remove(name);
            this->refresh_ser();
        }
    }
}
void Searchform::search_ec_cellChanged(int row, int){
    //QString change=ui->search_ec->item(row, column)->text().trimmed();
    changed=true;
    if(type==titles[0]){  //QString _name, QString _id, QString _gender, QString _age, QString _phone
        //"姓名"<<"职务"<<"编号"<<"性别"<<"年龄"<<"电话"<<""
        QString _name=ui->search_ec->item(row, 0)->text();
        QString _id=ui->search_ec->item(row, 2)->text();
        QString _gender=ui->search_ec->item(row, 3)->text();
        QString _age=ui->search_ec->item(row, 4)->text();
        QString _phone=ui->search_ec->item(row, 5)->text();
        manage::chg_emp(_name, _id, _gender, _age, _phone);
        m->refresh_emp();
    }
    else if(type==titles[1]){  //"姓名"<<"卡号"<<"性别"<<"年龄"<<"电话"
        QString _name=ui->search_ec->item(row, 0)->text();
        QString _card=ui->search_ec->item(row, 1)->text();
        QString _gender=ui->search_ec->item(row, 2)->text();
        QString _age=ui->search_ec->item(row, 3)->text();
        QString _phone=ui->search_ec->item(row, 4)->text();
        manage::chg_cus(_name, _card, _gender, _age, _phone);
        m->refresh_cus();
    }
    else if(type==titles[2]){
        QString _name=ui->search_ec->item(row, 0)->text();
        QString _price=ui->search_ec->item(row, 1)->text();
        manage::chg_ser(_name, _price);
        m->refresh_ser();
    }
}
void Searchform::search_bt_clicked(){
    QString _target=ui->search_le->text().trimmed();
    if(_target.isEmpty()) return;
    type=ui->search_tar_cb->currentText();
    if(type==titles[1]){
        cus_search_fin.clear();
        cus_search_fin = *manage::search_all_cus(_target);
        this->refresh_cus();
    }
    else if(type==titles[0]){
        emp_search_fin.clear();
        emp_search_fin = *manage::search_all_emp(_target);
        this->refresh_emp();
    }
    else if(type==titles[2]){
        ser_search_fin.clear();
        ser_search_fin = *manage::search_all_ser(_target);
        this->refresh_ser();
    }
}

cus_kvtype Searchform::cus_search_fin={};
emp_kvtype Searchform::emp_search_fin={};
ser_kvtype Searchform::ser_search_fin={};
