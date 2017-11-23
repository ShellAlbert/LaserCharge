#include "resmanager.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "sql.h"
ZResManager* ZResManager::m_pInstance=NULL;
qint32 ZResManager::ZLoadProvince(QStringList &provinceList)
{
    QSqlQuery query(this->m_db);
    if(query.exec("SELECT * FROM province"))
    {
        while(query.next())
        {
            QString province;
            province.append(query.value(0).toString());
            province.append("[,]");
            province.append(query.value(1).toString());
            province.append("[,]");
            province.append(query.value(2).toString());
            provinceList.append(province);
        }
    }
    return 0;
}
qint32 ZResManager::ZLoadCity(QStringList &cityList)
{
    QSqlQuery query(this->m_db);
    if(query.exec("SELECT * FROM city"))
    {
        while(query.next())
        {
            QString city;
            city.append(query.value(0).toString());
            city.append("[,]");
            city.append(query.value(1).toString());
            city.append("[,]");
            city.append(query.value(2).toString());
            city.append("[,]");
            city.append(query.value(3).toString());
            cityList.append(city);
        }
    }
    return 0;
}
qint32 ZResManager::ZLoadCinema(QStringList &cinemaList)
{
    QSqlQuery query(this->m_db);
    if(query.exec("SELECT * FROM cinema"))
    {
        while(query.next())
        {
            QString cinema;
            cinema.append(query.value(0).toString());
            cinema.append("[,]");
            cinema.append(query.value(1).toString());
            cinema.append("[,]");
            cinema.append(query.value(2).toString());
            cinema.append("[,]");
            cinema.append(query.value(3).toString());
            cinemaList.append(cinema);
        }
    }
    return 0;
}
qint32 ZResManager::ZLoadDevice(QStringList &deviceList)
{
    QSqlQuery query(this->m_db);
    if(query.exec("SELECT * FROM device"))
    {
        while(query.next())
        {
            QString device;
            device.append(query.value(0).toString());
            device.append("[,]");
            device.append(query.value(1).toString());
            device.append("[,]");
            qreal totalHour=query.value(2).toFloat();
            device.append(QString::number(totalHour,'f',1));
            device.append("[,]");
            device.append(query.value(3).toString());
            device.append("[,]");
            device.append(query.value(4).toString());
            deviceList.append(device);
        }
    }
    return 0;
}
ZResManager::ZResManager()
{
    this->m_db=QSqlDatabase::addDatabase("QSQLITE");
    this->m_db.setDatabaseName(DB_NAME);
    this->m_db.setUserName(DB_USER);
    this->m_db.setPassword(DB_PASS);

    //initial counter.
    this->m_provinceNum=0;
    this->m_cityNum=0;
    this->m_cinemaNum=0;
    this->m_deviceNum=0;
}
qint32 ZResManager::ZCreateIfItNotExist(void)
{
    if(this->m_db.open())
    {
        QSqlQuery query(this->m_db);
        query.prepare(SQL_CHECK_PROVINCE);
        if(query.exec())
        {
            qint32 nRet=-1;
            if(query.next())
            {
                nRet=query.value(0).toInt();
            }
            if(0==nRet)
            {
                //not exist,create all.
                if(!query.exec(SQL_CREATE_PROVINCE_TABLE))
                {
                    qDebug()<<query.lastError();
                    return -1;
                }
                qDebug()<<"<province> table create okay.";
            }
        }
        query.prepare(SQL_CHECK_CITY);
        if(query.exec())
        {
            qint32 nRet=-1;
            if(query.next())
            {
                nRet=query.value(0).toInt();
            }
            if(0==nRet)
            {
                //not exist,create all.
                if(!query.exec(SQL_CREATE_CITY_TABLE))
                {
                    qDebug()<<query.lastError();
                    return -1;
                }
                qDebug()<<"<city> table create okay.";
            }
        }
        query.prepare(SQL_CHECK_CINEMA);
        if(query.exec())
        {
            qint32 nRet=-1;
            if(query.next())
            {
                nRet=query.value(0).toInt();
            }
            if(0==nRet)
            {
                //not exist,create all.
                if(!query.exec(SQL_CREATE_CINEMA_TABLE))
                {
                    qDebug()<<query.lastError();
                    return -1;
                }
                qDebug()<<"<cinema> table create okay.";
            }
        }
        query.prepare(SQL_CHECK_DEVICE);
        if(query.exec())
        {
            qint32 nRet=-1;
            if(query.next())
            {
                nRet=query.value(0).toInt();
            }
            if(0==nRet)
            {
                //not exist,create all.
                if(!query.exec(SQL_CREATE_DEVICE_TABLE))
                {
                    qDebug()<<query.lastError();
                    return -1;
                }
                qDebug()<<"<device> table create okay.";
            }
        }
        query.prepare(SQL_CHECK_DATA);
        if(query.exec())
        {
            qint32 nRet=-1;
            if(query.next())
            {
                nRet=query.value(0).toInt();
            }
            if(0==nRet)
            {
                //not exist,create all.
                if(!query.exec(SQL_CREATE_DATA_TABLE))
                {
                    qDebug()<<query.lastError();
                    return -1;
                }
                qDebug()<<"<data> table create okay.";
            }
        }
    }
    //qDebug()<<"check db okay.";
    return 0;
}
bool ZResManager::ZExecSQL(QString sql)
{
    if(!this->m_db.isOpen())
    {
        qDebug()<<this->m_db.lastError();
        return false;
    }
    qDebug()<<sql;
    QSqlQuery queryResult=this->m_db.exec(sql);
    if(queryResult.numRowsAffected())
    {
        return true;
    }
    return false;
}
