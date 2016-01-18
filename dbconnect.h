#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QtSql>

class DbConnect
{
public:
    DbConnect(QString name = "DEFAULT");
    ~DbConnect();
    QSqlQuery* queryExecute(QString sql);
    QSqlQuery* queryPrepareExecute(QString sql, QHash<QString, QString> params);

private:
    QSqlDatabase db;

};

#endif // DBCONNECT_H
