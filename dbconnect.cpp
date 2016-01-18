#include "dbinfo.h"
#include "dbconnect.h"

DbConnect::DbConnect(QString name)
{
    db = QSqlDatabase::addDatabase( DB_DRIVAR_NAME, name );
    db.setHostName( DB_HOST_NAME );
    db.setPort( DB_HOST_PORT );
    db.setDatabaseName( DB_DATABASE_NAME );
    db.setUserName( DB_USER_NAME );
    db.setPassword( DB_PASSWORD );
    db.setConnectOptions( DB_CONNECT_OPTION );

    bool ok = db.open();
    qDebug() << ok << db.lastError() << db.connectionName();
}

/**
 * @brief DbConnect::queryExecute
 * @param sql QString
 * @return QSqlQuery* 実行済みクエリー
 *
 * クエリーを実行して結果を返却する
 */
QSqlQuery* DbConnect::queryExecute(QString sql)
{
    QSqlQuery *query = new QSqlQuery( db );
    query->exec(sql);

    return query;
}

/**
 * @brief DbConnect::queryPrepareExecute
 * @param sql QString
 * @param params　QHash
 * @return QSqlQuery* 実行済みクエリー
 *
 * 名前付きプレースホルダのクエリーを実行して結果を返却する
 */
QSqlQuery* DbConnect::queryPrepareExecute(QString sql, QHash<QString, QString> params)
{
    QSqlQuery *query = new QSqlQuery( db );
    query->prepare(sql);

    QHashIterator<QString, QString> i(params);
    while ( i.hasNext() ) {
        i.next();
        query->bindValue( i.key() , i.value() );
    }
    query->exec();

    return query;
}


DbConnect::~DbConnect()
{
    QString connectionName = db.connectionName();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase( connectionName );
}
