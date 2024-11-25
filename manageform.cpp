#include "manageform.h"
#include "ui_manageform.h"
#include "manage.h"
#include "setting.h"
#include "searchform.h"
#include "chooseform.h"
#include "mainwindow.h"
#include "statisticform.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QPushButton>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>

//QMap<size_t4, QObject*> Manageform::lineedit_map = {};

Manageform::Manageform(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::manageform)
    , m(new manage){
    ui->setupUi(this);
    QPixmap *pixmap = new QPixmap;
    pixmap->load(setting::barber_icon);
    QSize size = ui->icon_area->size();
    ui->icon_area->setPixmap(pixmap->scaled(size));
    this->setWindowIcon(QIcon(setting::main_icon));
    this->setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint&~Qt::WindowMinMaxButtonsHint);
    //qDebug()<<setting::root_path;
    __init__();
}
Manageform::~Manageform(){
    delete ui;
    delete m;
    delete form_menu;
}

void Manageform::__init__(){
    m->clear();
    m->load_json(); // 缺省setting::cache_path
    set_panel();
    set_menu();
    limite();
    set_connect();
}
void Manageform::limite(){
    ui->em_name_le->setValidator(setting::inputValidator["name"]);
    ui->em_id_le->setValidator(setting::inputValidator["id"]);
    ui->em_posi_le->setValidator(setting::inputValidator["position"]);
    ui->em_gen_le->setValidator(setting::inputValidator["gender"]);
    ui->em_age_le->setValidator(setting::inputValidator["age"]);
    ui->em_pho_le->setValidator(setting::inputValidator["phone"]);
    ui->cu_name_le->setValidator(setting::inputValidator["name"]);
    ui->cu_card_le->setValidator(setting::inputValidator["card"]);
    ui->cu_gen_le->setValidator(setting::inputValidator["gender"]);
    ui->cu_age_le->setValidator(setting::inputValidator["age"]);
    ui->cu_pho_le->setValidator(setting::inputValidator["phone"]);
    ui->se_name_le->setValidator(setting::inputValidator["name"]);
    ui->se_price_le->setValidator(setting::inputValidator["price"]);
    ui->se_times_le->setFocusPolicy(Qt::NoFocus);
}
void Manageform::set_menu(){
    form_menu = new QMenuBar(this);
    setMenuBar(form_menu);
    //file:
    QMenu *menu_file = new QMenu("文件", this);
    QAction *menu_save=new QAction("保存");
    connect(menu_save, SIGNAL(triggered(bool)), this, SLOT(menu_save_triggered()));
    menu_file->addAction(menu_save);
    QMenu *menu_import=new QMenu("导入");
    QAction *import_excel=new QAction("Excel", this);
    connect(import_excel, SIGNAL(triggered(bool)), this, SLOT(import_excel_triggered()));
    menu_import->addAction(import_excel);
    QAction *import_json=new QAction("Json", this);
    connect(import_json, SIGNAL(triggered(bool)), this, SLOT(import_json_triggered()));
    menu_import->addAction(import_json);
    menu_file->addMenu(menu_import);
    QMenu *menu_export=new QMenu("导出");
    QAction *export_excel=new QAction("Excel", this);
    menu_export->addAction(export_excel);
    connect(export_excel, SIGNAL(triggered(bool)), this, SLOT(export_excel_triggered()));
    QAction *export_txt=new QAction("Txt", this);
    menu_export->addAction(export_txt);
    connect(export_txt, SIGNAL(triggered(bool)), this, SLOT(export_txt_triggered()));
    QAction *export_json=new QAction("Json", this);
    menu_export->addAction(export_json);
    connect(export_json, SIGNAL(triggered(bool)), this, SLOT(export_json_triggered()));
    menu_file->addMenu(menu_export);
    form_menu->addMenu(menu_file);
    //data:
    QMenu *menu_data=new QMenu("数据", this);
    QAction *menu_revenue=new QAction("营收", this);
    connect(menu_revenue, SIGNAL(triggered(bool)), this, SLOT(menu_revenue_triggered()));
    menu_data->addAction(menu_revenue);
    QAction *menu_search=new QAction("查找", this);
    connect(menu_search, SIGNAL(triggered(bool)), this, SLOT(menu_search_triggered()));
    menu_data->addAction(menu_search);
    form_menu->addMenu(menu_data);
    //form:
    QMenu *menu_form=new QMenu("页面", this);
    QAction *menu_return=new QAction("返回登录界面", this);
    connect(menu_return, SIGNAL(triggered(bool)), this, SLOT(menu_return_triggered()));
    menu_form->addAction(menu_return);
    QAction *menu_exit=new QAction("退出", this);
    connect(menu_exit, SIGNAL(triggered(bool)), this, SLOT(menu_exit_triggered()));
    menu_form->addAction(menu_exit);
    form_menu->addMenu(menu_form);
}
void Manageform::refresh_cus(){
    ui->customer_ec->blockSignals(true);
    ui->customer_ec->clear();
    QStringList header_text;
    header_text<<"姓名"<<"卡号"<<"性别"<<"年龄"<<"电话"<<"";
    ui->customer_ec->setColumnCount(header_text.size());
    ui->customer_ec->setHorizontalHeaderLabels(header_text);
    ui->customer_ec->verticalHeader()->hide();
    //ui->customer_ec->setShowGrid(false);
    ui->customer_ec->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int row=0;
    for(cus_constIter iter=m->cus_constBegin();iter!=m->cus_constEnd();iter++){
        customer* staff = iter.value();
        ui->customer_ec->setRowCount(row+1);
        ui->customer_ec->setItem(row, 0, new QTableWidgetItem(staff->_name()));
        ui->customer_ec->setItem(row, 1, new QTableWidgetItem(staff->_card()));
        ui->customer_ec->setItem(row, 2, new QTableWidgetItem(staff->_gender()));
        ui->customer_ec->setItem(row, 3, new QTableWidgetItem(QString::number(staff->_age())));
        ui->customer_ec->setItem(row, 4, new QTableWidgetItem(staff->_phone()));
        QPushButton *pt=new QPushButton("消费");
        pt->setProperty("row", row);
        connect(pt, SIGNAL(clicked(bool)), this, SLOT(choose_bt_clicked()));
        ui->customer_ec->setCellWidget(row, 5, pt);
        row++;
    }
    ui->customer_ec->blockSignals(false);
    ui->main_tab->setCurrentIndex(1);
}
void Manageform::refresh_emp(){
    ui->employee_ec->blockSignals(true);
    ui->employee_ec->clear();
    QStringList header_text;
    header_text<<"姓名"<<"职务"<<"编号"<<"性别"<<"年龄"<<"电话";
    ui->employee_ec->setColumnCount(header_text.size());
    ui->employee_ec->setHorizontalHeaderLabels(header_text);
    ui->employee_ec->verticalHeader()->hide();
    //ui->employee_ec->setShowGrid(false);
    ui->employee_ec->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int row=0;
    for(emp_constIter iter=m->emp_constBegin();iter!=m->emp_constEnd();iter++){
        employee* staff = iter.value();
        ui->employee_ec->setRowCount(row+1);
        ui->employee_ec->setItem(row, 0, new QTableWidgetItem(staff->_name()));
        ui->employee_ec->setItem(row, 1, new QTableWidgetItem("理发师"));
        ui->employee_ec->setItem(row, 2, new QTableWidgetItem(staff->_id()));
        ui->employee_ec->setItem(row, 3, new QTableWidgetItem(staff->_gender()));
        ui->employee_ec->setItem(row, 4, new QTableWidgetItem(QString::number(staff->_age())));
        ui->employee_ec->setItem(row, 5, new QTableWidgetItem(staff->_phone()));
        row++;
    }
    ui->employee_ec->blockSignals(false);
    ui->main_tab->setCurrentIndex(0);
}
void Manageform::refresh_ser(){
    ui->service_ec->blockSignals(true);
    ui->service_ec->clear();
    QStringList header_text;
    header_text<<"名称"<<"价格"<<"消费次数";
    ui->service_ec->setColumnCount(header_text.size());
    ui->service_ec->setHorizontalHeaderLabels(header_text);
    ui->service_ec->verticalHeader()->hide();
    //ui->service_ec->setShowGrid(false);
    ui->service_ec->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int row=0;
    for(ser_constIter iter=dress::ser_constBegin();iter!=dress::ser_constEnd();iter++){
        ui->service_ec->setRowCount(row+1);
        ui->service_ec->setItem(row, 0, new QTableWidgetItem(iter.key()));
        ui->service_ec->setItem(row, 1, new QTableWidgetItem(QString::number(iter.value()->_price())));
        ui->service_ec->setItem(row, 2, new QTableWidgetItem(QString::number(m->get_times(iter.key()))));
        row++;
    }
    ui->service_ec->blockSignals(false);
    ui->main_tab->setCurrentIndex(2);
}
void Manageform::set_panel(){
    refresh_ser();
    refresh_cus();
    refresh_emp();
}
void Manageform::save_modify_auto(){
    if(m->save_json()) qDebug()<<"自动保存";
    else qDebug()<<"保存失败";
}
void Manageform::set_connect(){
    connect(ui->exit_save_bt, SIGNAL(clicked(bool)), this, SLOT(exit_save_bt_clicked()));
    connect(ui->exit_nsave_bt, SIGNAL(clicked(bool)), this, SLOT(exit_nsave_bt_clicked()));
    //employee:
    connect(ui->em_add_bt, SIGNAL(clicked(bool)), this, SLOT(em_add_bt_clicked()));
    connect(ui->em_del_bt, SIGNAL(clicked(bool)), this, SLOT(em_del_bt_clicked()));
    connect(ui->em_chg_bt, SIGNAL(clicked(bool)), this, SLOT(em_chg_bt_clicked()));
    connect(ui->em_clear_bt, SIGNAL(clicked(bool)), this, SLOT(em_clear_bt_clicked()));
    //customer:
    connect(ui->cu_add_bt, SIGNAL(clicked(bool)), this, SLOT(cu_add_bt_clicked()));
    connect(ui->cu_del_bt, SIGNAL(clicked(bool)), this, SLOT(cu_del_bt_clicked()));
    connect(ui->cu_chg_bt, SIGNAL(clicked(bool)), this, SLOT(cu_chg_bt_clicked()));
    connect(ui->cu_clear_bt, SIGNAL(clicked(bool)), this, SLOT(cu_clear_bt_clicked()));
    //service:
    connect(ui->se_add_bt, SIGNAL(clicked(bool)), this, SLOT(se_add_bt_clicked()));
    connect(ui->se_del_bt, SIGNAL(clicked(bool)), this, SLOT(se_del_bt_clicked()));
    connect(ui->se_chg_bt, SIGNAL(clicked(bool)), this, SLOT(se_chg_bt_clicked()));
    connect(ui->se_clear_bt, SIGNAL(clicked(bool)), this, SLOT(se_clear_bt_clicked()));
    //tab_view:
    connect(ui->employee_ec, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(employee_view(QTableWidgetItem*)));
    connect(ui->customer_ec, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(customer_view(QTableWidgetItem*)));
    connect(ui->service_ec, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(service_view(QTableWidgetItem*)));
}

//slot:
//-employee:
void Manageform::em_add_bt_clicked(){
    QString _name=ui->em_name_le->text().trimmed();
    QString _id=ui->em_id_le->text().trimmed();
    QString _gender=ui->em_gen_le->text().trimmed();
    QString _age=ui->em_age_le->text().trimmed();
    QString _phone=ui->em_pho_le->text().trimmed();
    ui->main_tab->setCurrentIndex(0);
    if(m->search_emp(_id)!=nullptr){
        qDebug()<<"id已存在!";
        QMessageBox msgBox;
        msgBox.setText(u8"id已存在!");
        msgBox.exec();
        return;
    }
    if(_name.isEmpty() ||_id.isEmpty() || _gender.isEmpty() || _age.isEmpty() || _phone.isEmpty()){
        qDebug()<<"属性不全!";
        QMessageBox msgBox;
        msgBox.setText(u8"属性不全!");
        msgBox.exec();
        return;
    }
    m->register_emp(_name, _id, _gender, _age, _phone, {});
    this->refresh_emp();
}
void Manageform::em_del_bt_clicked(){
    QString _id=ui->em_id_le->text().trimmed();
    ui->main_tab->setCurrentIndex(0);
    if(_id.isEmpty()){
        QMessageBox msgBox;
        msgBox.setText(u8"无id!");
        msgBox.exec();
        return;
    }
    if(m->search_emp(_id)!=nullptr){
        QMessageBox::StandardButton button = QMessageBox::question(this, "提示", "会删除id对应的成员，确认继续么？",
                                                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (button == QMessageBox::Yes){
            m->del_emp(_id);
            this->refresh_emp();
            this->em_clear_bt_clicked();
        }
    }
}
void Manageform::em_chg_bt_clicked(){
    QString _id=ui->em_id_le->text().trimmed();
    ui->main_tab->setCurrentIndex(0);
    if(m->search_emp(_id)!=nullptr){
        QMessageBox::StandardButton button = QMessageBox::question(this, "提示", "会更改id对应的成员，确认继续么？",
                                                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (button == QMessageBox::Yes){
            QString _name=ui->em_name_le->text().trimmed();
            QString _gender=ui->em_gen_le->text().trimmed();
            QString _age=ui->em_age_le->text().trimmed();
            QString _phone=ui->em_pho_le->text().trimmed();
            m->chg_emp(_name, _id, _gender, _age, _phone);
            this->refresh_emp();
        }
    }
}
void Manageform::em_clear_bt_clicked(){
    ui->em_name_le->clear();
    ui->em_posi_le->clear();
    ui->em_id_le->clear();
    ui->em_gen_le->clear();
    ui->em_age_le->clear();
    ui->em_pho_le->clear();
    qDebug()<<"清空";
}
//-customer:
void Manageform::cu_add_bt_clicked(){
    QString _name=ui->cu_name_le->text().trimmed();
    QString _card=ui->cu_card_le->text().trimmed();
    QString _gender=ui->cu_gen_le->text().trimmed();
    QString _age=ui->cu_age_le->text().trimmed();
    QString _phone=ui->cu_pho_le->text().trimmed();
    ui->main_tab->setCurrentIndex(1);
    if(m->search_cus(_card)!=nullptr){
        qDebug()<<"卡号已存在!";
        QMessageBox msgBox;
        msgBox.setText(u8"卡号已存在!");
        msgBox.exec();
        return;
    }
    if(_name.isEmpty() ||_card.isEmpty() || _gender.isEmpty() || _age.isEmpty() || _phone.isEmpty()){
        qDebug()<<"属性不全!";
        QMessageBox msgBox;
        msgBox.setText(u8"属性不全!");
        msgBox.exec();
        return;
    }
    m->register_cus(_name, _card, _gender, _age, _phone, {});
    this->refresh_cus();
}
void Manageform::cu_del_bt_clicked(){
    QString _card=ui->cu_card_le->text().trimmed();
    ui->main_tab->setCurrentIndex(1);
    if(_card.isEmpty()){
        QMessageBox msgBox;
        msgBox.setText(u8"无卡号!");
        msgBox.exec();
        return;
    }
    if(m->search_cus(_card)!=nullptr){
        QMessageBox::StandardButton button = QMessageBox::question(this, "提示", "会删除卡号对应的成员，确认继续么？",
                                                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (button == QMessageBox::Yes){
            m->del_cus(_card);
            this->refresh_cus();
            this->cu_clear_bt_clicked();
        }
    }
}
void Manageform::cu_chg_bt_clicked(){
    QString _card=ui->cu_card_le->text().trimmed();
    ui->main_tab->setCurrentIndex(1);
    if(m->search_cus(_card)!=nullptr){
        QMessageBox::StandardButton button = QMessageBox::question(this, "提示", "会更改卡号对应的成员，确认继续么？",
                                                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (button == QMessageBox::Yes){
            QString _name=ui->cu_name_le->text().trimmed();
            QString _gender=ui->cu_gen_le->text().trimmed();
            QString _age=ui->cu_age_le->text().trimmed();
            QString _phone=ui->cu_pho_le->text().trimmed();
            m->chg_cus(_name, _card, _gender, _age, _phone);
            this->refresh_cus();
        }
    }
}
void Manageform::cu_clear_bt_clicked(){
    ui->cu_name_le->clear();
    ui->cu_card_le->clear();
    ui->cu_gen_le->clear();
    ui->cu_age_le->clear();
    ui->cu_pho_le->clear();
    qDebug()<<"清空";
}
//-service:
void Manageform::se_add_bt_clicked(){
    QString _name=ui->se_name_le->text().trimmed();
    ui->main_tab->setCurrentIndex(2);
    if(m->search_ser(_name)!=nullptr){
        qDebug()<<"名称已存在!";
        QMessageBox msg;
        msg.setText(u8"名称已存在!");
        msg.exec();
        return;
    }
    QString _price=ui->se_price_le->text().trimmed();
    if(_price.isEmpty())return;
    m->register_ser(_name, _price, 0);
    this->refresh_ser();
}
void Manageform::se_del_bt_clicked(){
    QString _name=ui->se_name_le->text().trimmed();
    ui->main_tab->setCurrentIndex(2);
    if(_name.isEmpty()){
        QMessageBox msg;
        msg.setText(u8"无名称!");
        msg.exec();
        return;
    }
    if(m->search_ser(_name)!=nullptr){
        QMessageBox::StandardButton button = QMessageBox::question(this, "提示", "会删除名称对应的项目，确认继续么？",
                                                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (button == QMessageBox::Yes){
            m->del_menu(_name);
            this->refresh_ser();
            this->se_clear_bt_clicked();
        }
        else if(button==QMessageBox::No) return;
    }
}
void Manageform::se_chg_bt_clicked(){
    QString _name=ui->se_name_le->text().trimmed();
    ui->main_tab->setCurrentIndex(2);
    if(m->search_ser(_name)!=nullptr){
        QMessageBox::StandardButton button = QMessageBox::question(this, "提示", "会更改名称对应的项目，确认继续么？",
                                                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (button == QMessageBox::Yes){
            QString _price=ui->se_price_le->text().trimmed();
            if(_price.isEmpty()) return;
            m->chg_ser(_name, _price);
        }
    }
}
void Manageform::se_clear_bt_clicked(){
    ui->se_name_le->clear();
    ui->se_price_le->clear();
    ui->se_times_le->clear();
    qDebug()<<"清空";
}
//-tab:
void Manageform::employee_view(QTableWidgetItem*){
    int row=ui->employee_ec->currentRow();
    ui->em_name_le->setText(ui->employee_ec->item(row, 0)->text());
    ui->em_posi_le->setText(ui->employee_ec->item(row, 1)->text());
    ui->em_id_le->setText(ui->employee_ec->item(row, 2)->text());
    ui->em_gen_le->setText(ui->employee_ec->item(row, 3)->text());
    ui->em_age_le->setText(ui->employee_ec->item(row, 4)->text());
    ui->em_pho_le->setText(ui->employee_ec->item(row, 5)->text());
    ui->side_tab->setCurrentIndex(1);
    ui->view_tab->setCurrentIndex(0);
}
void Manageform::customer_view(QTableWidgetItem*){
    int row=ui->customer_ec->currentRow();
    ui->cu_name_le->setText(ui->customer_ec->item(row, 0)->text());
    ui->cu_card_le->setText(ui->customer_ec->item(row, 1)->text());
    ui->cu_gen_le->setText(ui->customer_ec->item(row, 2)->text());
    ui->cu_age_le->setText(ui->customer_ec->item(row, 3)->text());
    ui->cu_pho_le->setText(ui->customer_ec->item(row, 4)->text());
    ui->side_tab->setCurrentIndex(1);
    ui->view_tab->setCurrentIndex(1);
}
void Manageform::service_view(QTableWidgetItem*){
    int row=ui->service_ec->currentRow();
    ui->se_name_le->setText(ui->service_ec->item(row, 0)->text());
    ui->se_price_le->setText(ui->service_ec->item(row, 1)->text());
    ui->se_times_le->setText(ui->service_ec->item(row, 2)->text());
    ui->side_tab->setCurrentIndex(1);
    ui->view_tab->setCurrentIndex(2);
}
//menu/action:
void Manageform::menu_revenue_triggered(){
    Statisticform *sf=new Statisticform;
    sf->show();
}
void Manageform::menu_search_triggered(){
    Searchform *sf=new Searchform(*this);
    sf->show();
}
void Manageform::menu_exit_triggered(){
    exit_save_bt_clicked();
}
void Manageform::menu_return_triggered(){
    QMessageBox msg;
    msg.setInformativeText(u8"您确认返回登录界面么？您的更改将被保存");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::No);
    int rec=msg.exec();
    if(rec==QMessageBox::No) return;
    else if(rec==QMessageBox::Yes){
        this->save_modify_auto();
        MainWindow *mw=new MainWindow;
        this->close();
        mw->show();
    }
}
void Manageform::menu_save_triggered(){
    this->save_modify_auto();
}
void Manageform::import_excel_triggered(){
    QString exc_path = QFileDialog::getOpenFileName(this, QStringLiteral("选择载入文件")
                                                    , setting::desk_path, "Excel Files(*.xlsx)");
    if(exc_path.isEmpty()) return;
    QMessageBox msg;
    msg.setInformativeText(u8"若载入，当前工作区成员会与载入文件成员合并。是否继续？");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);
    int ret = msg.exec();
    if(ret==QMessageBox::Cancel) return;
    else if(ret==QMessageBox::Yes){
        bool loaded=m->load_excel(exc_path);
        if(not loaded){
            QMessageBox msgBox;
            msgBox.setText(u8"载入失败！可载入的Excel应当含有“员工”“顾客”“服务与商品”三个Sheet");
            msgBox.exec();
            return;
        }
        this->set_panel();
    }
}
void Manageform::import_json_triggered(){
    QString exc_path = QFileDialog::getOpenFileName(this,QStringLiteral("选择载入文件")
                                                    , setting::desk_path, "Json Files(*.json)");
    if(exc_path.isEmpty()) return;
    QMessageBox msg;
    msg.setInformativeText(u8"若载入，当前工作区成员会与载入文件成员合并。是否继续？");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);
    int ret = msg.exec();
    if(ret==QMessageBox::Cancel) return;
    else if(ret==QMessageBox::Yes){
        if(not m->load_json(exc_path)){
            QMessageBox msgBox;
            msgBox.setText(u8"载入失败！可载入的Json应当含有“customers”“employees”“services”三个键");
            msgBox.exec();
            return;
        }
        this->set_panel();
    }
}
void Manageform::export_excel_triggered(){
    QString exc_path = QFileDialog::getSaveFileName(this,QStringLiteral("选择导出路径")
                                                    , setting::desk_path, "Excel Files(*.xlsx)");
    if(exc_path.isEmpty()) return;
    if(m->save_excel(exc_path)){
        QMessageBox msg;
        msg.setText(u8"保存完毕");
        msg.exec();
    }
    else{
        QMessageBox msg;
        msg.setText(u8"保存失败！请检查保存路径");
        msg.exec();
    }
}
void Manageform::export_txt_triggered(){
    QString exc_path = QFileDialog::getSaveFileName(this,QStringLiteral("选择导出路径")
                                                    , setting::desk_path, "Text Files(*.txt)");
    if(exc_path.isEmpty()) return;
    if(m->save_txt(exc_path)){
        QMessageBox msg;
        msg.setText(u8"保存完毕");
        msg.exec();
    }
    else{
        QMessageBox msg;
        msg.setText(u8"保存失败！请检查保存路径");
        msg.exec();
    }
}
void Manageform::export_json_triggered(){
    QString exc_path = QFileDialog::getSaveFileName(this,QStringLiteral("选择导出路径")
                                                    , setting::desk_path, "Json Files(*.json)");
    if(exc_path.isEmpty()) return;
    if(m->save_json(exc_path)){
        QMessageBox msg;
        msg.setText(u8"保存完毕");
        msg.exec();
    }
}
//exit:
void Manageform::exit_save_bt_clicked(){
    QMessageBox::StandardButton button = QMessageBox::question(this, "提示", "确认退出么？",
                                                               QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (button == QMessageBox::Yes){
        this->save_modify_auto();
        this->close();
    }
}
void Manageform::exit_nsave_bt_clicked(){
    QMessageBox msg;
    msg.setText(u8"您确认退出么？");
    msg.setInformativeText(u8"是否要保存你的修改？");
    msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Save);
    switch (msg.exec()) {
    case QMessageBox::Save:
        qDebug() << "save";
        this->save_modify_auto();
        this->close();
        break;
    case QMessageBox::Discard:
        qDebug() << "Discard";
        this->close();
        break;
    case QMessageBox::Cancel:
        qDebug() << "Cancel";
        break;
    default:
        break;
    }
}
void Manageform::choose_bt_clicked(){
    QPushButton *bt = dynamic_cast<QPushButton*>(sender());
    if(bt == nullptr) return;
    int row = bt->property("row").toInt();
    QString card=ui->customer_ec->item(row, 1)->text();
    Chooseform *cf=new Chooseform(card, this);
    cf->show();
}
void Manageform::keyPressEvent(QKeyEvent* _event)
{
    auto _key = _event->key();
    if(_key == Qt::Key_Up || _key == Qt::Key_W){

    }
    else if(_key == Qt::Key_Down || _key == Qt::Key_S){

    }
    else if(_key == Qt::Key_A || _key == Qt::Key_Left){

    }
    else if(_key == Qt::Key_D || _key == Qt::Key_Right){

    }
    else qDebug()<<"非法焦点";
}
