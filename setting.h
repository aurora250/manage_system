#ifndef SETTING_H
#define SETTING_H

#include <QString>
#include <QMap>
#include <QStandardPaths>
//#include <QCoreApplication>
#include <QRegularExpressionValidator>

namespace setting{

bool valid_check(QString _var, QString _tar);

extern const QStringList titles;
extern const QString root_path;
extern const QString resources_path;
extern const QString database_path;
extern const QString cache_path;
extern const QString barber_icon;
extern const QString main_icon;
extern const QString desk_path;
extern const QStringList checkList;
extern const QMap<QString, QRegularExpressionValidator*> rootValidators;
extern const QMap<QString, QRegularExpressionValidator*> checkValidator;
extern const QMap<QString, QRegularExpressionValidator*> inputValidator;
}

#endif // SETTING_H
