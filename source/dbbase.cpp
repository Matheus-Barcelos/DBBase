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


QStringList DBBase::getTables()
{
    QSqlQuery query("show tables", this->database);
    query.exec();

    QStringList list;
    while(query.next())
    {
        QSqlRecord record = query.record();
        list.append(record.value(0).toString());
    }
    return list;
}



