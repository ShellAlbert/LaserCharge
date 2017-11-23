#include "zcitydata.h"
#include <QDebug>
#include <QPainter>
ZCityData::ZCityData()
{
    this->m_llCity=new QLabel;
    this->m_llCity->setAlignment(Qt::AlignCenter);
    this->m_llCity->setObjectName("ZCityDataCityLabel");
    this->m_llCity->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    this->m_hLayoutTop=new QHBoxLayout;
    this->m_hLayoutBottom=new QHBoxLayout;
    this->m_vLayoutLeft=new QVBoxLayout;
    this->m_vLayoutRight=new QVBoxLayout;
    this->m_hLayoutCenter=new QHBoxLayout;
    this->m_hLayoutCenter->addLayout(this->m_vLayoutLeft,1);
    this->m_hLayoutCenter->addWidget(this->m_llCity,1);
    this->m_hLayoutCenter->addLayout(this->m_vLayoutRight,1);

    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->addLayout(this->m_hLayoutTop,1);
    this->m_vLayoutMain->addLayout(this->m_hLayoutCenter,2);
    this->m_vLayoutMain->addLayout(this->m_hLayoutBottom,1);
    this->setLayout(this->m_vLayoutMain);

    this->setObjectName("ZCityData");

}
ZCityData::~ZCityData()
{
    for(qint32 i=0;i<this->m_llCinemaList.size();i++)
    {
        delete this->m_llCinemaList.at(i);
    }
    this->m_llCinemaList.clear();


    delete this->m_hLayoutTop;
    delete this->m_hLayoutBottom;

    delete this->m_vLayoutLeft;
    delete this->m_llCity;
    delete this->m_vLayoutRight;
    delete this->m_hLayoutCenter;

    delete this->m_vLayoutMain;
}

void ZCityData::ZSetCityData(QString cityName,QStringList cinemaList)
{
    this->m_llCity->setText(cityName);

    for(qint32 i=0;i<this->m_llCinemaList.size();i++)
    {
        delete this->m_llCinemaList.at(i);
    }
    this->m_llCinemaList.clear();

    qint32 nEachItems=cinemaList.size()/4;
    qint32 nRestItems=cinemaList.size()%4;
    qint32 cinemaIndex=0;
    for(qint32 i=0;i<4;i++)
    {
        for(qint32 j=0;j<nEachItems;j++)
        {
            QLabel *llCity=new QLabel(cinemaList.at(cinemaIndex));
            llCity->setAlignment(Qt::AlignCenter);
            llCity->setObjectName("ZCityDataCinemaLabel");
            llCity->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
            switch(i)
            {
            case 0://top.
                this->m_hLayoutTop->addWidget(llCity);
                break;
            case 1://right.
                this->m_vLayoutRight->addWidget(llCity);
                break;
            case 2://bottom.
                this->m_hLayoutBottom->addWidget(llCity);
                break;
            case 3://left.
                this->m_vLayoutLeft->addWidget(llCity);
                break;
            }
            cinemaIndex++;
            this->m_llCinemaList.append(llCity);
        }
    }
    if(nRestItems>0)
    {
        for(qint32 i=0;i<nRestItems;i++)
        {
            QLabel *llCity=new QLabel(cinemaList.at(cinemaIndex));
            llCity->setAlignment(Qt::AlignCenter);
            llCity->setObjectName("ZCityDataCinemaLabel");
            llCity->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

            this->m_hLayoutBottom->addWidget(llCity);
            cinemaIndex++;
            this->m_llCinemaList.append(llCity);
        }
    }
    //insert stretchor.
//    this->m_hLayoutTop->insertStretch(0,1);
//    this->m_hLayoutTop->insertStretch(-1,1);

//    this->m_hLayoutBottom->insertStretch(0,1);
//    this->m_hLayoutBottom->insertStretch(-1,1);

//    this->m_vLayoutLeft->insertStretch(0,1);
//    this->m_vLayoutLeft->insertStretch(-1,1);

//    this->m_vLayoutRight->insertStretch(0,1);
//    this->m_vLayoutRight->insertStretch(-1,1);

//    this->update();
}
//void ZCityData::paintEvent(QPaintEvent *e)
//{
//    Q_UNUSED(e);
//    QFrame::paintEvent(e);

//    QPainter painter(this);
//    QPoint ptCity(this->m_llCity->x(),this->m_llCity->y());
//    for(qint32 i=0;i<this->m_llCinemaList.size();i++)
//    {
//        QLabel *llCinema=this->m_llCinemaList.at(i);
//        QPoint ptWidget(llCinema->x(),llCinema->y());
//        painter.setPen(QPen(Qt::red,2));
//        painter.drawLine(ptCity,ptWidget);
//    }
//}
