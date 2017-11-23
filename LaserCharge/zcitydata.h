#ifndef ZCITYDATA_H
#define ZCITYDATA_H

#include <QFrame>
#include <QLabel>
#include <QList>
#include <QGridLayout>
class ZCityData : public QFrame
{
    Q_OBJECT
public:
    ZCityData();
    ~ZCityData();

    void ZSetCityData(QString cityName,QStringList cinemaList);
//protected:
//    void paintEvent(QPaintEvent *e);
private:
    QLabel *m_llCity;
    QList<QLabel*> m_llCinemaList;

    QHBoxLayout *m_hLayoutTop;
    QHBoxLayout *m_hLayoutBottom;

    QVBoxLayout *m_vLayoutLeft;
    QVBoxLayout *m_vLayoutRight;
    QHBoxLayout *m_hLayoutCenter;

    QVBoxLayout *m_vLayoutMain;

};

#endif // ZCITYDATA_H
