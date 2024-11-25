#include "dress.h"
#include "setting.h"
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QMainWindow>

//service:
service::service(){
    this->_name("NULL");
    this->_price(NULL);
}
service::service(QString _name, QString _price){
    this->_name(_name);
    this->_price(_price);
}
service::service(const service& _it){
    this->_name(_it._name());
    this->_price(_it._price());
}
service::~service(){}

void service::_name(QString _name){ this->name=(setting::valid_check(_name, "name")?_name:"NULL"); }
QString service::_name() const{ return name; }
void service::_price(QString _price){ this->price=(setting::valid_check(_price, "price")?_price.toInt():NULL); }
void service::_price(int _price){ this->price=((price>0 && price<100000)?_price:NULL); }
size_t4 service::_price() const{ return price; }

QStringList* service::base_info() const{
    QStringList *info=new QStringList;
    *info<<_name()<<QString::number(_price());
    return info;
}

//dress:
dress::dress(){}
dress::~dress(){}

void dress::print(){
    for(ser_iter iter=services.begin();iter!=services.end();iter++){
        qDebug()<<iter.key()<<"\t"<<iter.value()->_name()<<"\t"<<iter.value()->_price();
    }
}
void dress::add_ser(QString _name, QString _price, int _times){
    if(services.contains(_name)) qDebug()<<"项目对菜单已存在";
    else{
        services[_name]=new service(_name, _price);
        ser_times[_name]=_times>0 ? _times : 0;
    }
}
void dress::del_ser(QString _name){
    if(services.contains(_name)) services.remove(_name);
    else qDebug()<<"项目对菜单不存在";
}
void dress::chg_ser(QString _name, QString _price){
    if(services.contains(_name)) services[_name]->_price(_price);
    else qDebug()<<"项目对菜单不存在";
}
service* dress::search_ser(QString _name){
    if(services.contains(_name)) return services[_name];
    else return nullptr;
}
ser_kvtype* dress::search_all_ser(QString _target){
    ser_kvtype* tem_list=new ser_kvtype;
    qDebug()<<"搜索中";
    int get = 0;
    bool have = false;
    qDebug()<<"顾客： ";
    for(ser_constIter iter=ser_constBegin();iter!=ser_constEnd();iter++){
        have=false;
        service* _tem=iter.value();
        if(_tem->_name()!=_target){
            if(QString::number(_tem->_price())!=_target && not have){}
            else have=true;
        }
        else have=true;
        if(have){
            get++;
            (*tem_list)[_tem->_name()]=_tem;
        }
    }
    if(get==0) qDebug()<<"无";
    return tem_list;
}
void dress::add_times(QString _service){
    if(services.contains(_service)) ser_times[_service]++;
    else qDebug()<<"对菜单无此项目";
}
ser_iter dress::ser_begin(){ return services.begin(); }
ser_iter dress::ser_end(){ return services.end(); }
ser_constIter dress::ser_constBegin() { return services.constBegin(); }
ser_constIter dress::ser_constEnd() { return services.constEnd(); }
times_iter dress::times_begin(){ return ser_times.begin(); }
times_iter dress::times_end(){ return ser_times.end(); }
times_constIter dress::times_constBegin() { return ser_times.constBegin(); }
times_constIter dress::times_constEnd() { return ser_times.constEnd(); }
void dress::clear() {
    services.clear();
    ser_times.clear();
}
int dress::get_times(QString _name){
    if(services.contains(_name)) return ser_times[_name];
    else return -1;
}

ser_kvtype dress::services={};
times_kvtype dress::ser_times={};
