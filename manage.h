#ifndef MANAGE_H
#define MANAGE_H

#include "people.h"
#include "dress.h"
#include "setting.h"
#include <QVector>
#include <QMap>
#include <QSql>
#include <QRegularExpressionValidator>

typedef QMap<QString, customer*> cus_kvtype;
typedef QMap<QString, employee*> emp_kvtype;
typedef QMap<QString, QStringList*> info_kvtype;
typedef cus_kvtype::Iterator cus_iter;
typedef emp_kvtype::Iterator emp_iter;
typedef info_kvtype::Iterator info_iter;
typedef cus_kvtype::ConstIterator cus_constIter;
typedef emp_kvtype::ConstIterator emp_constIter;
typedef info_kvtype::ConstIterator info_constIter;
typedef QVector<QString> info_list;
typedef QVector<info_list> info_lists;

class manage
{
public:
    manage();
    ~manage();
    static void register_cus(QString _name, QString _card, QString _gender, QString _age, QString _phone, const record_type& _record = {});
    static void register_emp(QString _name, QString _id, QString _gender, QString _age, QString _phone, const record_type& _record = {});
    static void register_ser(QString _name, QString _price, int _times = 0);

    static customer* search_cus(QString _card);
    static employee* search_emp(QString _id);
    static service* search_ser(QString _name);
    static cus_kvtype* search_all_cus(QString _target);
    static emp_kvtype* search_all_emp(QString _target);
    static ser_kvtype* search_all_ser(QString _target);

    static cus_iter cus_begin();
    static cus_iter cus_end();
    static emp_iter emp_begin();
    static emp_iter emp_end();
    static cus_constIter cus_constBegin();
    static cus_constIter cus_constEnd();
    static emp_constIter emp_constBegin();
    static emp_constIter emp_constEnd();

    static void show_cus();
    static void show_emp();
    static void chg_cus(QString _name, QString _card, QString _gender, QString _age, QString _phone);
    static void chg_emp(QString _name, QString _id, QString _gender, QString _age, QString _phone);
    static void chg_ser(QString _name, QString _price);
    static void del_cus(QString _card);
    static void del_emp(QString _id);
    static void del_menu(QString _name);

    static bool save_excel(QString _path);
    static bool save_txt(QString _path);
    static bool save_json(QString _path = setting::cache_path);
    static bool load_excel(QString _path);
    static bool load_json(QString _path = setting::cache_path);
    static info_kvtype* normalize(QString _type);
    static size_t4 statistic();
    static int get_times(QString _name);
    static QStringList* get_all_ser();
    static void dress(QString _id, QString _card, QString _service);
    static void clear();
private:
    static cus_kvtype customers;
    static emp_kvtype employees;
};

#endif // MANAGE_H
