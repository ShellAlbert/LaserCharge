#include "zpropertyeditor.h"
#include <QPainter>
#include <QDebug>
#include "resmanager.h"
#include "sql.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDateTime>
ZPropertyEditor::ZPropertyEditor()
{
    this->setObjectName("ZPropertyEditor");

    for(qint32 i=0;i<6;i++)
    {
        this->m_llLabels[i]=new ZDetailLabel;
        this->m_llLabels[i]->setAlignment(Qt::AlignCenter);
        switch(i)
        {
        case 0:
            this->m_llLabels[i]->setToolTip(tr("累计充值时长"));
            this->m_llLabels[i]->setObjectName("ZPropertyEditorTotalHours");
            this->m_actChargeHour=this->m_llLabels[i]->ZAddAction(QIcon(":/icons/images/Hours.png"),tr("充时长"));
            this->m_actChargePeriod=this->m_llLabels[i]->ZAddAction(QIcon(":/icons/images/Period.png"),tr("充时段"));
            this->m_actChargeHistory=this->m_llLabels[i]->ZAddAction(QIcon(":/icons/images/History.png"),tr("充值历史"));
            this->m_actTotalHourSetup=this->m_llLabels[i]->ZAddAction(QIcon(":/icons/images/Setup.png"),tr("设置..."));

            connect(this->m_actChargeHour,SIGNAL(triggered(bool)),this,SIGNAL(ZSigChargeHour()));
            connect(this->m_actChargePeriod,SIGNAL(triggered(bool)),this,SIGNAL(ZSigChargePeriod()));
            connect(this->m_actChargeHistory,SIGNAL(triggered(bool)),this,SIGNAL(ZSigChargeHistory()));
            break;
        case 1:
            this->m_llLabels[i]->setToolTip(tr("设备ID编号"));
            this->m_llLabels[i]->setObjectName("ZPropertyEditorDeviceID");
            this->m_actCopyId=this->m_llLabels[i]->ZAddAction(QIcon(":/icons/images/Copy.png"),tr("复制ID"));
            this->m_actDevIDSetup=this->m_llLabels[i]->ZAddAction(QIcon(":/icons/images/Setup.png"),tr("设置..."));
            break;
        case 2:
            this->m_llLabels[i]->setToolTip(tr("设备所在省"));
            this->m_llLabels[i]->setObjectName("ZPropertyEditorProvince");
            break;
        case 3:
            this->m_llLabels[i]->setToolTip(tr("设备所在市"));
            this->m_llLabels[i]->setObjectName("ZPropertyEditorCity");
            break;
        case 4:
            this->m_llLabels[i]->setToolTip(tr("设备所在影院"));
            this->m_llLabels[i]->setObjectName("ZPropertyEditorCinema");
            break;
        case 5:
            this->m_llLabels[i]->setToolTip(tr("近期行为记录"));
            this->m_llLabels[i]->setObjectName("ZPropertyEditorAction");
            this->m_llLabels[i]->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            break;
        }
    }

    this->m_chart=new QChart;
    this->m_chart->setTitle(tr("近10次充值统计图"));
    this->m_chart->legend()->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->m_chart->legend()->hide();

    //this->m_chart->setBackgroundBrush(QBrush(Qt::darkGray));
    this->m_chart->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->m_barSeries=new QBarSeries;
    this->m_barSeries->setLabelsVisible(true);
    this->m_barSeries->setLabelsPosition(QAbstractBarSeries::LabelsCenter);
    for(qint32 i=0;i<10;i++)
    {
        this->m_barSet[i]=new QBarSet(QString::number(i,'f',1));
        this->m_barSet[i]->append(10.0f*i);
        this->m_barSeries->append(this->m_barSet[i]);
    }

    this->m_chart->addSeries(this->m_barSeries);
    this->m_chart->createDefaultAxes();
    this->m_chart->axisX()->setLabelsVisible(false);

    this->m_chartView=new QChartView;
    //this->m_chartView->setBackgroundBrush(QBrush(Qt::darkGray));
    this->m_chartView->setContentsMargins(0,0,0,0);
    this->m_chartView->setChart(this->m_chart);
    this->m_chartView->setRenderHint(QPainter::Antialiasing);

    this->m_gLayout=new QGridLayout;
    this->m_gLayout->setSpacing(10);
    this->m_gLayout->setContentsMargins(10,10,10,10);

    this->m_gLayout->addWidget(this->m_llLabels[0],0,0,2,1);//totalHours.
    this->m_gLayout->addWidget(this->m_llLabels[1],0,1,1,3);//device id.
    this->m_gLayout->addWidget(this->m_llLabels[2],1,1,1,1);//province.
    this->m_gLayout->addWidget(this->m_llLabels[3],1,2,1,1);//city.
    this->m_gLayout->addWidget(this->m_llLabels[4],1,3,1,1);//cinema.

    this->m_gLayout->addWidget(this->m_chartView,2,0,1,2);//chart.
    this->m_gLayout->addWidget(this->m_llLabels[5],2,2,1,2);//memo.
    this->m_gLayout->setColumnStretch(0,2);
    this->m_gLayout->setColumnStretch(1,1);
    this->m_gLayout->setColumnStretch(2,1);
    this->m_gLayout->setColumnStretch(3,1);

    this->setLayout(this->m_gLayout);
}
ZPropertyEditor::~ZPropertyEditor()
{
    delete this->m_actChargeHour;
    delete this->m_actChargePeriod;
    delete this->m_actChargeHistory;
    delete this->m_actTotalHourSetup;

    delete this->m_actCopyId;
    delete this->m_actDevIDSetup;

    for(qint32 i=0;i<6;i++)
    {
        delete this->m_llLabels[i];
    }
    for(qint32 i=0;i<10;i++)
    {
        delete this->m_barSet[i];
    }
    delete  this->m_barSeries;
    delete this->m_chart;
    delete this->m_chartView;
    delete this->m_gLayout;
}
void ZPropertyEditor::ZSetDeviceID(QString id)
{
    this->m_llLabels[1]->setText(id);
    qint32 barSetIndex=0;
    //fetch recent 10 charge record.
    QSqlQuery query(ZResManager::ZGetInstance()->ZGetDB());
    query.prepare(SQL_GET_TOP10);
    query.bindValue(":id",id);
    if(query.exec())
    {
        while(query.next())
        {
            QDateTime dt=QDateTime::fromString(query.value(0).toString(),"yyyy-MM-dd hh:mm:ss");
            qreal hours=query.value(1).toFloat();

            this->m_barSet[barSetIndex]->setLabel(dt.toString("yyyy/MM/dd"));
            this->m_barSet[barSetIndex]->replace(0,hours);
            barSetIndex++;
        }
    }
}
QString ZPropertyEditor::ZGetDeviceID()
{
    return this->m_llLabels[1]->text();
}
void ZPropertyEditor::ZSetTotalHours(QString hours)
{
    this->m_llLabels[0]->setText(hours);
}
void ZPropertyEditor::ZSetProvinceCityCinema(QString province,QString city,QString cinema)
{
    this->m_llLabels[2]->setText(province);
    this->m_llLabels[3]->setText(city);
    this->m_llLabels[4]->setText(cinema);
}
void ZPropertyEditor::ZSetRecentAction(QString action)
{
    this->m_llLabels[5]->setText(action);
}
