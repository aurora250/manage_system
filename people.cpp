#include "people.h"
#include "setting.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QValidator>

//people:
people::people(){
    this->_name("NULL");
    this->_gender("NULL");
    this->_phone("NULL");
    this->_age(NULL);
    this->_record({});
}
people::people(QString _name, QString _gender, QString _age, QString _phone, const record_type& _record){
    this->_name(_name);
    this->_gender(_gender);
    this->_phone(_phone);
    this->_age(_age);
    this->_record(_record);
}
people::~people(){}
record_type* people::_record() const{
    record_type* _tem = new record_type();
    for(record_constIter iter=rec_constBegin();iter!=rec_constEnd();iter++){
        _tem->push_back({iter->first, iter->second});
    }
    return _tem;
}
void people::_record(const record_type& _record){
    this->record = {};
    if(not _record.isEmpty()){
        for(record_constIter iter=_record.constBegin();iter!=_record.constEnd();iter++){
            this->record.push_back({iter->first, iter->second});
        }
    }
}
QString people::_name() const{ return name; }
void people::_name(QString _name){ this->name=(setting::valid_check(_name, "name")?_name:
                      ((this->name!="NULL")?this->name:"NULL")); }
QString people::_gender() const{ return gender; }
void people::_gender(QString _gen){ this->gender=(setting::valid_check(_gen, "gender")?_gen:
                        ((this->gender!="NULL")?this->gender:"NULL")); }
QString people::_phone() const{ return phone; }
void people::_phone(QString _pho){ this->phone=(setting::valid_check(_pho, "phone")?_pho:
                       ((this->phone!="NULL")?this->phone:"NULL")); }
size_t4 people::_age() const{ return age; }
void people::_age(QString _age){ this->age=(setting::valid_check(_age, "age")?_age.toInt():
                     ((this->age!=NULL)?this->age:NULL)); }
record_iter people::rec_begin() { return record.begin(); }
record_iter people::rec_end() { return record.end(); }
record_constIter people::rec_constBegin() const { return record.constBegin(); }
record_constIter people::rec_constEnd() const { return record.constEnd(); }
size_t4 people::sum_up() const{
    size_t4 sum = 0;
    for(record_constIter iter=rec_constBegin();iter!=rec_constEnd();iter++){
        sum+=(*iter).second;
    }
    return sum;
}
sta_type* people::sta_record() const{
    sta_type* _record=new sta_type;
    for(record_constIter iter=rec_constBegin();iter!=rec_constEnd();iter++){
        if(not _record->contains(iter->first)) (*_record)[iter->first]=0;
        (*_record)[iter->first]+=iter->second;
    }
    //this->show_record();
    return _record;
}
void people::show_record() const{
    qDebug()<<"记录:";
    if(record.empty()) qDebug()<<"无";
    else{
        for(record_constIter iter=rec_constBegin();iter!=rec_constEnd();iter++){
            qDebug()<<(*iter).first<<", "<<(*iter).second<<";";
        }
    }
}
void people::write_record(serpair_type _service){
    record.append(_service);
}
void people::print() const{
    qDebug()<<*base_info()<<':';
    this->show_record();
}

//customer:
customer::customer(): people(){
    this->_card("");
}
customer::customer(QString _name, QString _card, QString _gender, QString _age, QString _phone, const record_type& _record):
    people(_name, _gender, _age, _phone, _record){
    this->_card(_card);
}
customer::customer(const customer &_c):
    people(_c._name(), _c._gender(), QString::number(_c._age()), _c._phone(), *_c._record()){
    this->_card(_c._card());
}
customer::~customer(){}
QString customer::_card() const{ return this->identifier; }
void customer::_card(QString _card){ this->identifier=(setting::valid_check(_card, "card")?_card:
                             ((this->identifier!="NULL")?this->identifier:"NULL")); }
QStringList* customer::base_info() const{
    QStringList *final=new QStringList;  //QString _name, QString _card, QString _gender, int _age, QString _phone
    *final<<_name()<<_card()<<_gender()<<QString::number(_age())<<_phone();
    return final;
}

//employee:
employee::employee(): people(){
    this->_id("");
}
employee::employee(QString _name, QString _id, QString _gender, QString _age, QString _phone, const record_type& _record):
    people(_name, _gender, _age, _phone, _record){
    this->_id(_id);
}
employee::employee(const employee &_e):
    people(_e._name(), _e._gender(), QString::number(_e._age()), _e._phone(), *_e._record()){
    this->_id(_e._id());
}
employee::~employee(){}
QString employee::_id() const{ return this->identifier; }
void employee::_id(QString _id){ this->identifier=(setting::valid_check(_id, "id")?_id:
                    ((this->identifier!="NULL")?this->identifier:"NULL")); }
QStringList* employee::base_info() const{
    QStringList* final=new QStringList;
    *final<<_name()<<_id()<<_gender()<<QString::number(_age())<<_phone();
    return final;
}
void employee::dress_cus(serpair_type _service, customer &_cus){
    this->write_record(_service);
    _cus.write_record(_service);
    qDebug()<<this->_name()<<"为"<<_cus._name()<<_service<<'.';
}
