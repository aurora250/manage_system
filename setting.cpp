#include "setting.h"

bool setting::valid_check(QString _var, QString _tar){
    int pos=0;
    if(not checkList.contains(_tar)) return NULL;
    if(checkValidator[_tar]->validate(_var, pos)==QValidator::Acceptable) return true;
    else return false;
}

const QStringList setting::titles={"员工", "顾客", "商品与服务"};

const QString setting::root_path="D:/Workspace/Cpp Workspace/Qt Workspace/demo_05";
const QString setting::resources_path=root_path+"/resources_base";
const QString setting::database_path=root_path+"/user.db";
const QString setting::cache_path=root_path+"/data.json";
const QString setting::barber_icon=resources_path+"/barber shop.png";
const QString setting::main_icon=resources_path+"/people_manage.png";
const QString setting::desk_path=QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0);
const QStringList setting::checkList={"username", "name", "age", "phone", "gender", "id", "card", "password", "price", "position"};

const QMap<QString, QRegularExpressionValidator*> setting::rootValidators{
    {"zh_en_t20", new QRegularExpressionValidator(QRegularExpression("[\u4e00-\u9fa5A-Za-z]{1,20}$"))},
    {"zh_en_nu_t20", new QRegularExpressionValidator(QRegularExpression("[\u4e00-\u9fa5A-Z0-9a-z]{1,20}$"))},
    {"nu_t2", new QRegularExpressionValidator(QRegularExpression("[0-9]{1,2}$"))},
    {"nu_11", new QRegularExpressionValidator(QRegularExpression("[0-9]{11}$"))},
    {"nu_t11", new QRegularExpressionValidator(QRegularExpression("[0-9]{1,11}$"))},
    {"mw", new QRegularExpressionValidator(QRegularExpression("男|女"))},
    {"nu_en_t11", new QRegularExpressionValidator(QRegularExpression("[0-9A-Za-z]{1,11}$"))},
    {"nu_t5", new QRegularExpressionValidator(QRegularExpression("[0-9]{1,5}$"))},
    {"zh_t10", new QRegularExpressionValidator(QRegularExpression("[\u4e00-\u9fa5]{1,10}$"))}
};
const QMap<QString, QRegularExpressionValidator*> setting::checkValidator{
    {"username", rootValidators["zh_en_nu_t20"]},
    {"name", rootValidators["zh_en_t20"]},
    {"age", rootValidators["nu_t2"]},
    {"phone", rootValidators["nu_t11"]},
    {"gender", rootValidators["mw"]},
    {"id", rootValidators["nu_en_t11"]},
    {"card", rootValidators["nu_en_t11"]},
    {"password", rootValidators["nu_en_t11"]},
    {"price", rootValidators["nu_t5"]},
    {"position", rootValidators["zh_t10"]}
};
const QMap<QString, QRegularExpressionValidator*> setting::inputValidator{
    {"username", rootValidators["zh_en_nu_t20"]},
    {"name", rootValidators["zh_en_t20"]},
    {"age", rootValidators["nu_t2"]},
    {"phone", rootValidators["nu_11"]},
    {"gender", rootValidators["mw"]},
    {"id", rootValidators["nu_en_t11"]},
    {"card", rootValidators["nu_en_t11"]},
    {"password", rootValidators["nu_en_t11"]},
    {"price", rootValidators["nu_t5"]},
    {"position", rootValidators["zh_t10"]}
};
