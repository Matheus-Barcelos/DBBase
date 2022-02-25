#include "dbbase.hpp"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlDriver>


QSharedPointer<DBBase> DBBase::singleton;

DBBase::DBBase(QString driver, QString host, QString database, int port, QString user, QString passwd)
    : QObject()
{
    this->database = QSqlDatabase::addDatabase(driver);
    this->database.setHostName(host);
    this->database.setDatabaseName(database);
    this->database.setPort(port);
    this->database.setUserName(user);
    this->database.setPassword(passwd);

    QSqlDriver* sqlDriver = this->database.driver();
    this->connect(sqlDriver, SIGNAL(notification(QString,QSqlDriver::NotificationSource,QVariant)), this, SIGNAL(notify(QString,QSqlDriver::NotificationSource,QVariant)));

    if(!this->database.open())
        throw std::runtime_error("Erro ao abrir o banco de dados");

}

QSharedPointer<DBBase> DBBase::getInstance(QString driver, QString host,  QString database, int port, QString user, QString passwd)
{
    if(!DBBase::singleton.isNull())
    {
        DBBase::singleton = QSharedPointer<DBBase>(new DBBase(driver, host, database, port, user, passwd));
    }
    else
    {
        DBBase::singleton.reset();
        DBBase::singleton = QSharedPointer<DBBase>(new DBBase(driver, host, database, port, user, passwd));
    }
    return DBBase::singleton;
}

QSharedPointer<DBBase> DBBase::getInstance()
{
    return DBBase::singleton;
}

QList<QSqlRecord> DBBase::query(QString queryString)
{
    QSqlQuery query(queryString, this->database);
    query.exec();

    QList<QSqlRecord> list;
    while(query.next())
    {
        list.append(query.record());
    }
    return list;
}


QStringList DBBase::getTables()
{
    QList<QSqlRecord> list = this->query("show tables");
    QStringList result;
    for(QSqlRecord& record : list)
    {
        result.append(record.value(0).toString());
    }
    return result;
}



