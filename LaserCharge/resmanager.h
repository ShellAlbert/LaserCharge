#ifndef RESMANAGER_H
#define RESMANAGER_H

#define DB_NAME "LaserCharge.db"
#define DB_USER "root"
#define DB_PASS "123456"

#include <QtSql/QSqlDatabase>

class ZResManager
{
public:
    static ZResManager* ZGetInstance()
    {
        if(m_pInstance==NULL)
        {
            m_pInstance=new ZResManager;
        }
        return m_pInstance;
    }
    QSqlDatabase ZGetDB()
    {
        return this->m_db;
    }
    qint32 ZLoadProvince(QStringList &provinceList);
    qint32 ZLoadCity(QStringList &cityList);
    qint32 ZLoadCinema(QStringList &cinemaList);
    qint32 ZLoadDevice(QStringList &deviceList);
    qint32 ZCreateIfItNotExist(void);

    bool ZExecSQL(QString sql);

public:
    qint32 m_provinceNum;
    qint32 m_cityNum;
    qint32 m_cinemaNum;
    qint32 m_deviceNum;
private:
    ZResManager();


private:
    static ZResManager *m_pInstance;
private:
    QSqlDatabase m_db;
};

#endif // RESMANAGER_H
