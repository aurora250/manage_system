#ifndef PEOPLE_H
#define PEOPLE_H

#include "dress.h"
#include <QString>
#include <QMap>
#include <QVector>

typedef QPair<QString, size_t4> serpair_type;
typedef QVector<serpair_type> record_type;
typedef QMap<QString, size_t4> sta_type;
typedef record_type::ConstIterator record_constIter;
typedef record_type::Iterator record_iter;

class people{  //构造与析构函数->属性器->成员函数
public:
    people();
    people(QString _name, QString _sex, QString _age, QString _phone,  const record_type& _record);
    virtual ~people();

    record_type* _record() const;
    void _record(const record_type& _record);
    QString _name() const;
    void _name(QString _name);
    QString _gender() const;
    void _gender(QString _gender);
    QString _phone() const;
    void _phone(QString _phone);
    size_t4 _age() const;
    void _age(QString _age);

    record_iter rec_begin();
    record_iter rec_end();
    record_constIter rec_constBegin() const;
    record_constIter rec_constEnd() const;
    void show_record() const;
    void write_record(serpair_type _service);
    size_t4 sum_up() const;
    sta_type* sta_record() const;
    void print() const;
    virtual QStringList* base_info() const=0;
protected:
    QString name;
    QString gender;
    size_t4 age;
    QString phone;
    QString identifier;
    record_type record;
};

class customer: public people{
public:
    customer();
    customer(QString _name, QString _card, QString _sex, QString _age, QString _phone,  const record_type& _record);
    customer(const customer &_c);
    ~customer();

    QString _card() const;
    void _card(QString _card);

    void print() const;
    QStringList* base_info() const;
};

class employee: public people{
public:
    employee();
    employee(QString _name, QString _id, QString _sex, QString _age, QString _phone,  const record_type& _record);
    employee(const employee &_e);
    ~employee();

    QString _id() const;
    void _id(QString _id);
    void refresh_menu();

    void dress_cus(serpair_type _service, customer &_cus);
    void print() const;
    QStringList* base_info() const;
};

#endif // PEOPLE_H
