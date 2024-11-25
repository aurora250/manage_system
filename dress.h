#ifndef DRESS_H
#define DRESS_H

#include<QString>
#include<QMap>

class manage;
typedef unsigned int size_t4;

class service{
public:
    service();
    service(QString _name, QString _price);
    service(const service& _it);
    ~service();

    void _name(QString _name);
    QString _name() const;
    void _price(QString _price);
    void _price(int _price);
    size_t4 _price() const;

    QStringList* base_info() const;
private:
    QString name;
    size_t4 price;
};

typedef QMap<QString, service*> ser_kvtype;
typedef QMap<QString, size_t4> times_kvtype;
typedef ser_kvtype::Iterator ser_iter;
typedef times_kvtype::Iterator times_iter;
typedef ser_kvtype::ConstIterator ser_constIter;
typedef times_kvtype::ConstIterator times_constIter;

class dress{
public:
    dress();
    ~dress();
    static ser_iter ser_begin();
    static ser_iter ser_end();
    static ser_constIter ser_constBegin();
    static ser_constIter ser_constEnd();
    static times_iter times_begin();
    static times_iter times_end();
    static times_constIter times_constBegin();
    static times_constIter times_constEnd();
    static void clear();
    friend class manage;
private:
    static service* search_ser(QString _name);
    static ser_kvtype* search_all_ser(QString _target);
    static void print();
    static void add_ser(QString _name, QString _price, int _times = 0);
    static void del_ser(QString _name);
    static void chg_ser(QString _name, QString _price);
    static void add_times(QString _name);
    static int get_times(QString _name);

    static ser_kvtype services;
    static times_kvtype ser_times;
};

#endif
