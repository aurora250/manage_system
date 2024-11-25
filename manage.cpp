#include "manage.h"
#include "setting.h"
#include <QDebug>
#include <QIODevice>
#include <QFile>
#include <QDir>

//QJson:
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

//QXlsx:
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxworkbook.h"

using namespace QXlsx;
using namespace setting;

cus_kvtype manage::customers = {};
emp_kvtype manage::employees = {};

manage::manage(){}
manage::~manage(){}
void manage::register_ser(QString _name, QString _price, int _times){
    dress::add_ser(_name, _price, _times);
}
void manage::register_cus(QString _name, QString _card, QString _gender, QString _age, QString _phone, const record_type& _record){
    if(not customers.contains(_card)) customers[_card]=new customer(_name, _card, _gender, _age, _phone, _record);
}
void manage::register_emp(QString _name, QString _id, QString _gender, QString _age, QString _phone, const record_type& _record){
    if(not employees.contains(_id)) employees[_id]=new employee(_name, _id, _gender, _age, _phone, _record);
}
customer* manage::search_cus(QString _card){
    if(customers.contains(_card))return customers[_card];
    else return nullptr;
}
employee* manage::search_emp(QString _id){
    if(employees.contains(_id))return employees[_id];
    else return nullptr;
}
service* manage::search_ser(QString _name){
    return dress::search_ser(_name);
}
cus_kvtype* manage::search_all_cus(QString _target){
    cus_kvtype* tem_list = new cus_kvtype;
    qDebug()<<"搜索中";
    int get = 0;
    bool have;
    qDebug()<<"顾客： ";
    for(cus_constIter iter=cus_constBegin();iter!=cus_constEnd();iter++){
        have=false;
        customer* _tem=iter.value();
        if(_tem->_name()!=_target){
            if(_tem->_phone()!=_target && not have){
                if(_tem->_gender()!=_target && not have){
                    if(_tem->_card()!=_target && not have){
                        if(QString::number(_tem->_age())!=_target && not have){}
                        else have=true;
                    }
                    else have=true;
                }
                else have=true;
            }
            else have=true;
        }
        else have=true;
        if(have){
            get++;
            (*tem_list)[_tem->_card()]=_tem;
        }
    }
    if(get==0)qDebug()<<"无";
    return tem_list;
}
emp_kvtype* manage::search_all_emp(QString _target){
    emp_kvtype* tem_list = new emp_kvtype;
    qDebug()<<"搜索中";
    int get = 0;
    bool have;
    qDebug()<<"员工： ";
    for(emp_constIter iter=emp_constBegin();iter!=emp_constEnd();iter++){
        have=false;
        employee* _tem = iter.value();
        if(_tem->_name()!=_target){
            if(_tem->_phone()!=_target && not have){
                if(_tem->_gender()!=_target && not have){
                    if(_tem->_id()!=_target && not have){
                        if(QString::number(_tem->_age())!=_target && not have){}
                        else have=true;
                    }
                    else have=true;
                }
                else have=true;
            }
            else have=true;
        }
        else have=true;
        if(have){
            get++;
            (*tem_list)[_tem->_id()]=_tem;
        }
    }
    if(get==0)qDebug()<<"无";
    return tem_list;
}
ser_kvtype* manage::search_all_ser(QString _target){
    return dress::search_all_ser(_target);
}
cus_iter manage::cus_begin(){ return customers.begin(); }
cus_iter manage::cus_end(){ return customers.end(); }
emp_iter manage::emp_begin(){ return employees.begin(); }
emp_iter manage::emp_end(){ return employees.end(); }
cus_constIter manage::cus_constBegin() { return customers.constBegin(); }
cus_constIter manage::cus_constEnd() { return customers.constEnd(); }
emp_constIter manage::emp_constBegin() { return employees.constBegin(); }
emp_constIter manage::emp_constEnd() { return employees.constEnd(); }

void manage::show_cus(){
    int have=0;
    qDebug()<<"顾客： ";
    for(cus_constIter iter=cus_constBegin();iter!=cus_constEnd();iter++){
        //iter.value()->print();
        have++;
    }
    if(have==0)qDebug()<<"无";
}
void manage::chg_cus(QString _name, QString _card, QString _gender, QString _age, QString _phone){
    customer* _tem_cus = search_cus(_card);
    if(_tem_cus==nullptr) return;
    _tem_cus->_name(_name);
    _tem_cus->_phone(_phone);
    _tem_cus->_gender(_gender);
    _tem_cus->_age(_age);
    //_tem_cus->print();
}
void manage::del_cus(QString _card){
    if(customers.contains(_card)) customers.remove(_card);
    else qDebug()<<"无此顾客";
}
void manage::show_emp(){
    int have=0;
    qDebug()<<"员工： ";
    for(emp_constIter iter=emp_constBegin();iter!=emp_constEnd();iter++){
        //iter.value()->print();
        have++;
    }
    if(have==0)qDebug()<<"无";
}
void manage::chg_emp(QString _name, QString _id, QString _gender, QString _age, QString _phone){
    employee* _tem_emp = search_emp(_id);
    if(_tem_emp==nullptr) return;
    _tem_emp->_name(_name);
    _tem_emp->_phone(_phone);
    _tem_emp->_gender(_gender);
    _tem_emp->_age(_age);
    //_tem_emp->print();
}
void manage::del_emp(QString _id){
    if(employees.contains(_id)) employees.remove(_id);
    else qDebug()<<"无此员工";
}
void manage::chg_ser(QString _name, QString _price){
    dress::chg_ser(_name, _price);
}
void manage::del_menu(QString _name){
    dress::del_ser(_name);
}
bool manage::save_excel(QString _path){
    Document* xlsx = new Document(_path);
    int index=0;
    foreach(QString var, titles){
        xlsx->addSheet(var);
        AbstractSheet *csheet=xlsx->sheet(var);
        csheet->workbook()->setActiveSheet(index);
        Worksheet *wsheet=(Worksheet*)csheet->workbook()->activeSheet();
        info_kvtype *_tem=normalize(var);
        int i=1;
        for(info_iter iter=_tem->begin();iter!=_tem->end();iter++){
            QStringList *_list=iter.value();
            for(int j=1;j<=_list->size();j++){
                wsheet->write(i, j, (*_list)[j-1]);
            }
            i++;
        }
        index++;
    }
    if(not xlsx->save()) return false;
    else return true;
}
bool manage::save_txt(QString _path){
    QFile file(_path);
    if(!file.open(QIODevice::WriteOnly |QIODevice::Text)) return false;
    QTextStream outf(&file);
    foreach(QString var, titles){
        outf<<var<<":\n";
        info_kvtype *_tem=normalize(var);
        for(info_constIter iter=_tem->constBegin();iter!=_tem->constEnd();iter++){
            for(QStringList::ConstIterator it=iter.value()->constBegin();it!=iter.value()->constEnd();it++){
                outf<<*it<<"\t";
            }
            outf<<"\n";
        }
    }
    file.close();
    qDebug()<<"保存完毕";
    return true;
}
bool manage::save_json(QString _path){
    QJsonObject obj_root;
    QJsonObject obj_cus;
    for(cus_constIter iter=cus_constBegin();iter!=cus_constEnd();iter++){
        QJsonObject obj_cusinfo;
        QStringList info=*iter.value()->base_info();  //QString _name, QString _card, QString _gender, int _age, QString _phone
        obj_cusinfo.insert("name", info[0]);
        obj_cusinfo.insert("card", info[1]);
        obj_cusinfo.insert("gender", info[2]);
        obj_cusinfo.insert("age", info[3]);
        obj_cusinfo.insert("phone", info[4]);

        QJsonArray obj_cusrecord;
        record_type *_record = iter.value()->_record();
        for(record_constIter it=_record->constBegin();it!=_record->constEnd();it++){
            QJsonObject tem_pair;
            tem_pair.insert(it->first, (int)it->second);
            obj_cusrecord.push_back(tem_pair);
        }
        obj_cusinfo.insert("record", obj_cusrecord);

        obj_cus.insert(iter.key(), obj_cusinfo);
    }
    obj_root.insert("customers", obj_cus);

    QJsonObject obj_emp;
    for(emp_constIter iter=emp_constBegin();iter!=emp_constEnd();iter++){
        QJsonObject obj_empinfo;
        QStringList info=*iter.value()->base_info();  //QString _name, QString _id, QString _gender, int _age, QString _phone
        obj_empinfo.insert("name", info[0]);
        obj_empinfo.insert("id", info[1]);
        obj_empinfo.insert("gender", info[2]);
        obj_empinfo.insert("age", info[3]);
        obj_empinfo.insert("phone", info[4]);

        QJsonArray obj_emprecord;
        record_type* _record = iter.value()->_record();
        for(record_constIter it=_record->constBegin();it!=_record->constEnd();it++){
            QJsonObject tem_pair;
            tem_pair.insert(it->first, (int)it->second);
            obj_emprecord.push_back(tem_pair);
        }
        obj_empinfo.insert("record", obj_emprecord);

        obj_emp.insert(iter.key(), obj_empinfo);
    }
    obj_root.insert("employees", obj_emp);

    QJsonObject obj_ser;
    for(ser_constIter iter=dress::ser_constBegin();iter!=dress::ser_constEnd();iter++){
        QJsonObject obj_serinfo;
        QStringList info=*iter.value()->base_info();
        obj_serinfo.insert("name", info[0]);
        obj_serinfo.insert("price", info[1]);
        obj_serinfo.insert("times", QString::number(dress::get_times(info[0])));
        obj_ser.insert(iter.key(), obj_serinfo);
    }
    obj_root.insert("services", obj_ser);

    QJsonDocument json_docu(obj_root);
    QByteArray json_data = json_docu.toJson();

    QFile file(_path);
    if(file.open(QIODevice::WriteOnly)){
        file.write(json_data);
        file.close();
        return true;
    }
    else return false;
}
bool manage::load_excel(QString _path){
    Document* xlsx = new Document(_path);
    if(not xlsx->load()){
        qDebug()<<"打开失败";
        return false;
    }
    QStringList sheets = xlsx->sheetNames();
    info_lists _cus, _emp, _ser;
    if(sheets.contains(titles[0]) && sheets.contains(titles[1]) && sheets.contains(titles[2])){
        foreach(QString var, titles){  //"员工", "顾客", "商品与服务"
            AbstractSheet *csheet = xlsx->sheet(var);
            if (NULL == csheet) continue;
            csheet->workbook()->setActiveSheet(sheets.indexOf(var));
            Worksheet *wsheet = (Worksheet*)csheet->workbook()->activeSheet();
            if (NULL == wsheet) continue;
            int row = wsheet->dimension().rowCount();
            int column = wsheet->dimension().columnCount();
            info_list _tem;
            for(int i = 1; i <= row; i++){
                _tem.clear();
                if(var==titles[0]){
                    column=(column>=6?6:column);
                    for(int j = 1; j <= column; j++)
                    {
                        QVariant value = wsheet->read(i, j);
                        if(!value.isNull()) _tem.push_back(value.toString());
                        else _tem.push_back("NULL");
                    }
                    _emp.push_back(_tem);
                }
                else if(var==titles[1]){
                    column=(column>=5?5:column);
                    for(int j = 1; j <= column; j++)
                    {
                        QVariant value = wsheet->read(i, j);
                        if(!value.isNull()) _tem.push_back(value.toString());
                        else _tem.push_back("NULL");
                    }
                    _cus.push_back(_tem);
                }
                else if(var==titles[2]){
                    column=(column>=3?3:column);
                    for(int j = 1; j <= column; j++)
                    {
                        QVariant value = wsheet->read(i, j);
                        if(!value.isNull()) _tem.push_back(value.toString());
                        else _tem.push_back("NULL");
                    }
                    _ser.push_back(_tem);
                }
            }
        }
        foreach(info_list var ,_emp){
            register_emp(var[0], var[2], var[3], var[4], var[5], {});
        }
        foreach(info_list var ,_cus){
            register_cus(var[0], var[1], var[2], var[3], var[4], {});
        }
        foreach(info_list var ,_ser){
            register_ser(var[0], var[1], 0);
        }
        return true;
    }
    else{
        qDebug()<<"不是标准可载入文件";
        return false;
    }
}
bool manage::load_json(QString _path){
    QFile file(_path);
    QByteArray jsonData;
    if(file.open(QIODevice::ReadOnly)){
        jsonData = file.readAll();
        file.close();
    }
    else return false;
    QJsonDocument jsonDocu = QJsonDocument::fromJson(jsonData);
    if(jsonDocu.isObject()){
        QJsonObject obj_root = jsonDocu.object();
        foreach(QString key , obj_root.keys()){
            if(key=="customers"){
                QJsonObject obj_cus = obj_root.value(key).toObject();
                foreach(QString tem_card, obj_cus.keys()){
                    QJsonObject cus_info=obj_cus.value(tem_card).toObject();
                    record_type _tem_record = {};
                    QString _name, _card, _gender, _age, _phone;
                    foreach(QString info, cus_info.keys()){
                        if(info=="name")  _name=cus_info.value(info).toString();
                        else if(info=="card") _card=cus_info.value(info).toString();
                        else if(info=="gender") _gender=cus_info.value(info).toString();
                        else if(info=="age") _age=cus_info.value(info).toString();
                        else if(info=="phone") _phone=cus_info.value(info).toString();
                        else if(info=="record"){
                            QJsonArray cus_record=cus_info.value(info).toArray();
                            for(int i=0;i<cus_record.size();i++){
                                QJsonObject tem_pair=cus_record.at(i).toObject();
                                QString pair_name=tem_pair.keys().at(0);
                                _tem_record.push_back({pair_name, (size_t4)tem_pair.value(pair_name).toInt()});
                            }
                        }
                        else qDebug()<<"无此属性";
                    }
                    register_cus(_name, _card, _gender, _age, _phone, _tem_record);
                }
            }
            else if(key=="employees"){
                QJsonObject obj_emp = obj_root.value(key).toObject();
                foreach(QString tem_id, obj_emp.keys()){
                    QJsonObject emp_info=obj_emp.value(tem_id).toObject();
                    QString _name, _id, _gender, _age, _phone;
                    record_type _tem_record;
                    foreach(QString info, emp_info.keys()){
                        if(info=="name") _name=emp_info.value(info).toString();
                        else if(info=="id") _id=emp_info.value(info).toString();
                        else if(info=="gender") _gender=emp_info.value(info).toString();
                        else if(info=="age") _age=emp_info.value(info).toString();
                        else if(info=="phone") _phone=emp_info.value(info).toString();
                        else if(info=="record"){
                            QJsonArray emp_record=emp_info.value(info).toArray();
                            for(size_t4 i=0;i<emp_record.size();i++){
                                QJsonObject tem_pair=emp_record.at(i).toObject();
                                QString pair_name=tem_pair.keys().at(0);
                                _tem_record.push_back({pair_name, (size_t4)tem_pair.value(pair_name).toInt()});
                            }
                        }
                        else qDebug()<<"无此属性";
                    }
                    register_emp(_name, _id, _gender, _age, _phone, _tem_record);
                }
            }
            else if(key=="services"){
                QJsonObject obj_ser = obj_root.value(key).toObject();
                foreach(QString tem_name, obj_ser.keys()){
                    QJsonObject ser_info=obj_ser.value(tem_name).toObject();
                    QString _name, _price, _times;
                    foreach(QString info, ser_info.keys()){
                        if(info=="name") _name=ser_info.value(info).toString();
                        else if(info=="price") _price=ser_info.value(info).toString();
                        else if(info=="times") _times=ser_info.value(info).toString();
                        else qDebug()<<"无此属性";
                    }
                    register_ser(_name, _price, _times.toInt());
                }
            }
            else qDebug()<<"无此分类";
        }
    }
    return true;
}
info_kvtype* manage::normalize(QString _type){
    info_kvtype* contexts=new info_kvtype;
    if(_type==titles[0]){
        for(emp_constIter iter=emp_constBegin();iter!=emp_constEnd();iter++){
            (*contexts)[iter.key()]=iter.value()->base_info();
        }
    }
    else if(_type==titles[1]){
        for(cus_constIter iter=cus_constBegin();iter!=cus_constEnd();iter++){
            (*contexts)[iter.key()]=iter.value()->base_info();
        }
    }
    else if(_type==titles[2]){
        for(ser_constIter iter=dress::ser_constBegin();iter!=dress::ser_constEnd();iter++){
            (*contexts)[iter.key()]=iter.value()->base_info();
        }
    }
    else{
        delete contexts;
        return nullptr;
    }
    return contexts;
}
size_t4 manage::statistic(){
    size_t4 sum=0;
    for(emp_constIter iter=emp_constBegin();iter!=emp_constEnd();iter++){
        sum+=iter.value()->sum_up();
    }
    return sum;
}
int manage::get_times(QString _name){
    return dress::get_times(_name);
}
QStringList* manage::get_all_ser(){
    QStringList* _names=new QStringList;
    for(emp_constIter iter=emp_constBegin();iter!=emp_constEnd();iter++){
        for(record_constIter it=iter.value()->rec_constBegin();it!=iter.value()->rec_constEnd();it++){
            if(not _names->contains(it->first)) _names->append(it->first);
        }
    }
    for(ser_constIter iter=dress::ser_constBegin();iter!=dress::ser_constEnd();iter++){
        if(not _names->contains(iter.key())) _names->append(iter.key());
    }
    return _names;
}
void manage::dress(QString _id, QString _card, QString _service){
    customer* _cus=search_cus(_card);
    employee* _emp=search_emp(_id);
    service* _ser=search_ser(_service);
    if(_cus!=nullptr){
        if(_emp!=nullptr){
            if(_ser!=nullptr){
                _emp->dress_cus({_service, _ser->_price()}, *_cus);
                dress::add_times(_service);
            }
            else qDebug()<<"无此服务";
        }
        else qDebug()<<"无此员工";
    }
    else qDebug()<<"无此顾客";
}
void manage::clear(){
    customers.clear();
    employees.clear();
}
