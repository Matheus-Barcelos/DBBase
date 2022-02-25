#ifndef DBBASE_HPP
#define DBBASE_HPP


#include <QSqlDatabase>
#include <QSharedPointer>
#include <QObject>
#include <QSqlDriver>

class DBBase : public QObject
{
    Q_OBJECT

public:
    static QSharedPointer<DBBase> getInstance();
    static QSharedPointer<DBBase> getInstance(QString driver, QString host, QString database, int port, QString user, QString passwd);

    QStringList getTables();

private:
    DBBase(QString driver, QString host, QString database, int port, QString user, QString passwd);
    QList<QSqlRecord> query(QString queryString);
    QSqlDatabase database;

    static QSharedPointer<DBBase> singleton;

signals:
    void notify(const QString &name, QSqlDriver::NotificationSource source, const QVariant &payload);

};

#endif // DBBASE_HPP
