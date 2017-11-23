#ifndef ZPROVINCEDATA_H
#define ZPROVINCEDATA_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QList>
class ZProvinceData : public QFrame
{
    Q_OBJECT
public:
    ZProvinceData();
    ~ZProvinceData();

    void ZSetData(QString provinceName,QString addDate);
    void ZSetCityList(QStringList cityList);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QLabel *m_llProvinceName;
    QLabel *m_llAddDate;
    QHBoxLayout *m_hLayout;


    QList<QLabel*> m_llCityList;
    QList<qint32> m_nCinemaNumList;
    QGridLayout *m_gLayout;

    QVBoxLayout *m_vLayout;
};

#endif // ZPROVINCEDATA_H
