#include "zstatusbar.h"
#include "resmanager.h"
#include <QTimer>
ZStatusBar::ZStatusBar()
{
    this->m_llMsg=new QLabel;
    this->m_llCounter=new QLabel;
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->setContentsMargins(5,0,5,0);
    this->m_hLayout->addWidget(this->m_llMsg);
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_llCounter);
    this->setLayout(this->m_hLayout);

    this->ZUpdateCounter();
    this->ZSlotResetMsg();

    this->setObjectName("ZStatusBar");
    this->m_llMsg->setObjectName("ZStatusBarNotifyMsg");
    this->m_llCounter->setObjectName("ZStatusBarNotifyMsg");
}
ZStatusBar::~ZStatusBar()
{
    delete this->m_llMsg;
    delete this->m_llCounter;
    delete this->m_hLayout;
}
void ZStatusBar::ZSlotShowMsg(QString msg)
{
    this->m_llMsg->setText(msg);
    QTimer::singleShot(2000,this,SLOT(ZSlotResetMsg()));
}
void ZStatusBar::ZUpdateCounter()
{
    QString dispStr("共有");
    dispStr+=QString::number(ZResManager::ZGetInstance()->m_provinceNum,10)+"省";
    dispStr+=QString::number(ZResManager::ZGetInstance()->m_cityNum,10)+"市";
    dispStr+=QString::number(ZResManager::ZGetInstance()->m_cinemaNum,10)+"影院";
    dispStr+=QString::number(ZResManager::ZGetInstance()->m_deviceNum,10)+"设备";
    this->m_llCounter->setText(dispStr);
}
void ZStatusBar::ZSlotResetMsg()
{
    this->m_llMsg->setText(tr("就续"));
}
