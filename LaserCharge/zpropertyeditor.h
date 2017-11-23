#ifndef ZPROPERTYEDITOR_H
#define ZPROPERTYEDITOR_H

#include <QFrame>
#include <QGridLayout>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QBarCategoryAxis>
#include "zcustomwidget.h"
using namespace QtCharts;
class ZPropertyEditor : public QFrame
{
    Q_OBJECT
public:
    ZPropertyEditor();
    ~ZPropertyEditor();

    void ZSetDeviceID(QString id);
    QString ZGetDeviceID();

    void ZSetTotalHours(QString hours);
    void ZSetProvinceCityCinema(QString province,QString city,QString cinema);
    void ZSetRecentAction(QString action);


signals:
    void ZSigTotalHours(QString devId);
    void ZSigChargeHour();
    void ZSigChargePeriod();
    void ZSigChargeHistory();
protected:

private:
    ZDetailLabel *m_llLabels[6];
    QChartView *m_chartView;
    QChart *m_chart;
    QBarSeries *m_barSeries;
    QBarSet *m_barSet[10];
    QGridLayout *m_gLayout;

    //totalHours.
    QAction *m_actChargeHour;
    QAction *m_actChargePeriod;
    QAction *m_actChargeHistory;
    QAction *m_actTotalHourSetup;

    //deviceId.
    QAction *m_actCopyId;
    QAction *m_actDevIDSetup;
};

#endif // ZPROPERTYEDITOR_H
