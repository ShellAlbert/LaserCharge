#include "zprovincedata.h"
#include <QPainter>
#include <QDebug>
ZProvinceData::ZProvinceData()
{
    this->m_llProvinceName=new QLabel;
    this->m_llProvinceName->setAlignment(Qt::AlignCenter);
    this->m_llProvinceName->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->m_llAddDate=new QLabel;
    this->m_llAddDate->setAlignment(Qt::AlignCenter);
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_llProvinceName);
    this->m_hLayout->addWidget(this->m_llAddDate);
    this->m_hLayout->addStretch(1);

    this->m_gLayout=new QGridLayout;

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addLayout(this->m_hLayout);
    this->m_vLayout->addLayout(this->m_gLayout);    
    this->setLayout(this->m_vLayout);

    this->setObjectName("ZProvinceData");
    this->m_llProvinceName->setObjectName("ZProvinceDataProvince");
}
ZProvinceData::~ZProvinceData()
{
    delete this->m_llProvinceName;
    delete this->m_llAddDate;
    delete this->m_hLayout;
    for(qint32 i=0;i<this->m_llCityList.size();i++)
    {
        QLabel *cityLL=this->m_llCityList.at(i);
        delete cityLL;
    }
    this->m_llCityList.clear();
    delete this->m_gLayout;
    delete this->m_vLayout;
}

void ZProvinceData::ZSetData(QString provinceName,QString addDate)
{
    this->m_llProvinceName->setText(provinceName);
    this->m_llAddDate->setText(addDate);
}
void ZProvinceData::ZSetCityList(QStringList cityList)
{
    //free previous memory.
    for(qint32 i=0;i<this->m_llCityList.size();i++)
    {
        QLabel *cityLL=this->m_llCityList.at(i);
        delete cityLL;
    }
    this->m_llCityList.clear();
    this->m_nCinemaNumList.clear();

    //add new .
    for(qint32 i=0;i<cityList.size();i++)
    {
        //city,cinemaNum.
        QStringList cityCinemaList=cityList.at(i).split(",");
        if(cityCinemaList.size()!=2)
        {
            continue;//bypass invalid item.
        }
        //qDebug()<<cityCinemaList;
        QLabel *cityLL=new QLabel(cityCinemaList.at(0));
        cityLL->setObjectName("ZProvinceDataCityList");
        this->m_llCityList.append(cityLL);
        this->m_nCinemaNumList.append(cityCinemaList.at(1).toInt());
    }

    //re-layout.
    qint32 row=0,col=0;
    for(qint32 i=0;i<this->m_llCityList.size();i++)
    {
        QLabel *cityLL=this->m_llCityList.at(i);
        //City.
        this->m_gLayout->addWidget(cityLL,row,col,1,1,Qt::AlignCenter);
        if((col+1)%4==0)
        {
            row++;//next row.
            col=0;
        }else{
            col++;
        }
    }    
    //re-paint.
    this->update();
}
void ZProvinceData::paintEvent(QPaintEvent *event)
{

    qint32 provinceX=this->m_llProvinceName->x()+this->m_llProvinceName->width()/2;
    qint32 provinceY=this->m_llProvinceName->y()+this->m_llProvinceName->height();
    for(qint32 i=0;i<this->m_llCityList.size();i++)
    {
        QLabel *cityLL=this->m_llCityList.at(i);
        qint32 cityX=cityLL->x()+cityLL->width()/2;
        qint32 cityY=cityLL->y()+cityLL->height()/2;

        QPainter painter(this);
        painter.setPen(QPen(Qt::darkGreen,2));
        painter.drawLine(QPoint(provinceX,provinceY),QPoint(cityX,cityY));

        //draw the child num.
        QPixmap pixmapChildNum(":/icons/images/ChildNum.png");
        qint32 nChildNumX=cityLL->x()+cityLL->width()-pixmapChildNum.width()/2;
        qint32 nChildNumY=cityLL->y()-pixmapChildNum.height();
        QRect  rectChildNum(nChildNumX,nChildNumY,pixmapChildNum.width(),pixmapChildNum.height());
        painter.drawPixmap(rectChildNum,pixmapChildNum);

        //draw num.
        painter.setPen(QPen(Qt::black,2));
        QFont fontNum=painter.font();
        fontNum.setPixelSize(20);
        painter.setFont(fontNum);

        QString childNum=QString::number(this->m_nCinemaNumList.at(i),10);
        qint32 nNumX=rectChildNum.x()+painter.fontMetrics().width(childNum);
        qint32 nNumY=rectChildNum.y()+painter.fontMetrics().height()/2;
        qint32 nNumWidth=rectChildNum.width();
        qint32 nNumHeight=rectChildNum.height();
        QRect rectNum(nNumX,nNumY,nNumWidth,nNumHeight);
        painter.drawText(rectNum,childNum);
    }

    QFrame::paintEvent(event);
}
