#include "dbbase.hpp"
#include <QCoreApplication>

#include <iostream>
#include <QSqlDriver>
#include <QVariant>
#include <QCoreApplication>

void printNotification(const QString &name, QSqlDriver::NotificationSource source, const QVariant &payload)
{
    std::cout<<name.toStdString()<<std::endl;
    std::cout<<payload.toString().toStdString()<<std::endl;
}

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    DBBase::getInstance(argv[1], argv[2],argv[3] ,std::atoi(argv[4]), argv[5], argv[6]);

    QObject::connect(DBBase::getInstance().data(), &DBBase::notify, &printNotification );

    QStringList list = DBBase::getInstance()->getTables();
    for(int i = 0; i<list.size(); i++)
    {
        std::cout<<list[i].toStdString()<<" ";
    }
    std::cout<<std::endl;

    return app.exec();
}
