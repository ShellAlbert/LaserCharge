#include "zdialog.h"
#include "resmanager.h"
#include "sql.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QDateTime>
#include <QDebug>
#include <QUuid>
#include <QHeaderView>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QApplication>

#include "sql.h"
#include "database/PinyinResource.h"
ZDialogErrMsg::ZDialogErrMsg(QString msg)
{
    this->setWindowTitle(tr("出错了"));

    this->m_llIcon=new QLabel;
    this->m_llIcon->setPixmap(QPixmap(":/icons/images/Error.png"));
    this->m_llIcon->setAlignment(Qt::AlignCenter);

    this->m_llMsg=new QLabel;
    this->m_llMsg->setText(msg);
    this->m_llMsg->setAlignment(Qt::AlignCenter);

    this->m_tbClose=new QToolButton;
    this->m_tbClose->setText(tr("知道了"));


    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_llIcon,0,Qt::AlignCenter);
    this->m_vLayout->addWidget(this->m_llMsg,1,Qt::AlignCenter);
    this->m_vLayout->addWidget(this->m_tbClose,0,Qt::AlignCenter);
    this->setLayout(this->m_vLayout);

    //make connections.
    connect(this->m_tbClose,SIGNAL(clicked(bool)),this,SLOT(reject()));

    this->setObjectName("ZDialogErrMsg");
    this->m_llMsg->setObjectName("ZDialogErrMsgMessage");
    this->m_tbClose->setObjectName("ZDialogErrMsgButton");
}
ZDialogErrMsg::~ZDialogErrMsg()
{
    delete this->m_llIcon;
    delete this->m_llMsg;
    delete this->m_tbClose;
    delete this->m_vLayout;
}
QSize ZDialogErrMsg::sizeHint() const
{
    return QSize(400,200);
}

ZDialogAskMsg::ZDialogAskMsg(QString msg)
{
    this->m_llIcon=new QLabel;
    this->m_llIcon->setPixmap(QPixmap(""));
    this->m_llIcon->setAlignment(Qt::AlignCenter);

    this->m_llMsg=new QLabel;
    this->m_llMsg->setText(msg);
    this->m_llMsg->setAlignment(Qt::AlignCenter);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_tbOkay);
    this->m_hLayout->addWidget(this->m_tbCancel);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_llIcon);
    this->m_vLayout->addWidget(this->m_llMsg);

    this->m_vLayout->addLayout(this->m_hLayout);

    this->setLayout(this->m_vLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));
}
ZDialogAskMsg::~ZDialogAskMsg()
{
    delete this->m_llIcon;
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayout;
    delete this->m_vLayout;
}
QSize ZDialogAskMsg::sizeHint() const
{
    return QSize(400,200);
}

ZDialogAddProvince::ZDialogAddProvince(QString title)
{
    this->setWindowTitle(title);

    this->m_llProvinceName=new QLabel(tr("省名称(*)"));
    this->m_leProvinceName=new QLineEdit;

    this->m_llProvincePinYin=new QLabel(tr("拼音(Auto)"));
    this->m_leProvincePinYin=new QLineEdit;
    this->m_leProvincePinYin->setFocusPolicy(Qt::NoFocus);

    this->m_llProvinceAbbr=new QLabel(tr("缩写(Auto)"));
    this->m_leProvinceAbbr=new QLineEdit;

    this->m_gLayout=new QGridLayout;
    this->m_gLayout->addWidget(this->m_llProvinceName,0,0,1,1);
    this->m_gLayout->addWidget(this->m_leProvinceName,0,1,1,1);

    this->m_gLayout->addWidget(this->m_llProvincePinYin,1,0,1,1);
    this->m_gLayout->addWidget(this->m_leProvincePinYin,1,1,1,1);


    this->m_gLayout->addWidget(this->m_llProvinceAbbr,2,0,1,1);
    this->m_gLayout->addWidget(this->m_leProvinceAbbr,2,1,1,1);


    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));
    this->m_tbOkay->setIconSize(QSize(32,32));
    this->m_tbOkay->setIcon(QIcon(":/icons/images/Okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));
    this->m_tbCancel->setIconSize(QSize(32,32));
    this->m_tbCancel->setIcon(QIcon(":/icons/images/Cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbOkay);
    this->m_hLayout->addWidget(this->m_tbCancel);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addLayout(this->m_gLayout);
    this->m_vLayout->addStretch(1);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    this->setObjectName("ZDialogAddProvince");
    this->m_llProvinceName->setObjectName("ZDialogAddProvinceLabelTips");
    this->m_llProvincePinYin->setObjectName("ZDialogAddProvinceLabelTips");
    this->m_llProvinceAbbr->setObjectName("ZDialogAddProvinceLabelTips");

    //make connections.
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    connect(this->m_leProvinceName,SIGNAL(textChanged(QString)),this,SLOT(ZSlotGetPinYin(QString)));
}
ZDialogAddProvince::~ZDialogAddProvince()
{
    delete this->m_llProvinceName;
    delete this->m_leProvinceName;

    delete this->m_llProvincePinYin;
    delete this->m_leProvincePinYin;

    delete this->m_llProvinceAbbr;
    delete this->m_leProvinceAbbr;

    delete this->m_gLayout;

    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayout;

    delete this->m_vLayout;
}
QSize ZDialogAddProvince::sizeHint() const
{
    return QSize(400,200);
}
void ZDialogAddProvince::ZSlotGetPinYin(QString str)
{
    QString pinyin=PinyinHelper::convertToPinyinString(str,"\n",PinyinFormat::WITHOUT_TONE);
    this->m_leProvincePinYin->setText(pinyin);

    QString abbr;
    QStringList pyList=pinyin.split("\n");
    for(qint32 i=0;i<pyList.size();i++)
    {
        abbr+=pyList.at(i).left(1);
    }
    this->m_leProvinceAbbr->setText(abbr);
}
void ZDialogAddProvince::ZSlotOkay()
{
    QString provinceName=this->m_leProvinceName->text().trimmed();
    QString provinceAbbr=this->m_leProvinceAbbr->text().trimmed();
    QSqlQuery query(ZResManager::ZGetInstance()->ZGetDB());
    //query.prepare(SQL_ADD_PROVINCE);
    query.prepare("INSERT INTO province (abbr, name, date) VALUES (:abbr, :name, :date)");
    query.bindValue(":abbr",provinceAbbr);
    query.bindValue(":name",provinceName);
    query.bindValue(":date",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(query.exec())
    {
        if(1==query.numRowsAffected())
        {
            emit this->ZSigNotifyMsg(tr("新增:%1成功!").arg(provinceName));
            this->accept();
            return;
        }
    }
    ZDialogErrMsg errDia(tr("新增:%1失败!").arg(provinceName));
    errDia.exec();
}

QString ZDialogAddProvince::ZGetProvinceName()
{
    return this->m_leProvinceName->text().trimmed();
}
QString ZDialogAddProvince::ZGetProvinceAbbr()
{
    return this->m_leProvinceAbbr->text().trimmed();
}


ZDialogDelProvince::ZDialogDelProvince(QString provinceName)
{
    this->setWindowTitle(tr("删除确认"));
    this->m_provinceName=provinceName;

    this->m_llMsg=new QLabel;
    this->m_llMsg->setText(tr("您确定要删除省%1吗?").arg(provinceName));

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("删除"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("取消"));


    this->m_gLayout=new QGridLayout;
    this->m_gLayout->addWidget(this->m_llMsg,0,0,1,2);
    this->m_gLayout->addWidget(this->m_tbOkay,1,0,1,1);
    this->m_gLayout->addWidget(this->m_tbCancel,1,1,1,1);

    this->setLayout(this->m_gLayout);

    //make connections.
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    this->setObjectName("ZDialogDelProvince");
    this->m_llMsg->setObjectName("ZDialogDelProvinceAskLabel");
}
ZDialogDelProvince::~ZDialogDelProvince()
{
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gLayout;
}
QSize ZDialogDelProvince::sizeHint() const
{
    return QSize(400,200);
}
void ZDialogDelProvince::ZSlotOkay()
{
    QSqlQuery query(ZResManager::ZGetInstance()->ZGetDB());
    query.prepare(SQL_DEL_PROVINCE);
    query.bindValue(":name",this->m_provinceName);
    if(query.exec())
    {
        if(1==query.numRowsAffected())
        {
            emit this->ZSigNotifyMsg(tr("删除省：%1成功!").arg(this->m_provinceName));
            this->accept();
            return;
        }
    }
    ZDialogErrMsg errDia(tr("删除省:%1失败!\n原因：%2!").arg(this->m_provinceName).arg(query.lastError().text()));
    errDia.exec();
}
ZDialogAddCity::ZDialogAddCity(QString provinceName,QString provinceAbbr)
{
    this->setWindowTitle(tr("新增市"));

    this->m_provinceAbbr=provinceAbbr;

    this->m_llProvinceNameTips=new QLabel(tr("省份"));
    this->m_llProvinceName=new QLabel(provinceName);

    this->m_llCityNameTips=new QLabel(tr("市(*)"));
    this->m_leCityName=new QLineEdit;

    this->m_llCityPyTips=new QLabel(tr("拼音(Auto)"));
    this->m_leCityPy=new QLineEdit;
    this->m_leCityPy->setFocusPolicy(Qt::NoFocus);

    this->m_llCityAbbrTips=new QLabel(tr("缩写(Auto)"));
    this->m_leCityAbbr=new QLineEdit;

    this->m_gLayout=new QGridLayout;
    this->m_gLayout->addWidget(this->m_llProvinceNameTips,0,0,1,1);
    this->m_gLayout->addWidget(this->m_llProvinceName,0,1,1,1);
    this->m_gLayout->addWidget(this->m_llCityNameTips,1,0,1,1);
    this->m_gLayout->addWidget(this->m_leCityName,1,1,1,1);
    this->m_gLayout->addWidget(this->m_llCityPyTips,2,0,1,1);
    this->m_gLayout->addWidget(this->m_leCityPy,2,1,1,1);
    this->m_gLayout->addWidget(this->m_llCityAbbrTips,3,0,1,1);
    this->m_gLayout->addWidget(this->m_leCityAbbr,3,1,1,1);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Add"));
    this->m_tbOkay->setIcon(QIcon(":/icons/images/Add.png"));
    this->m_tbOkay->setIconSize(QSize(32,32));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));
    this->m_tbCancel->setIcon(QIcon(":/icons/images/Cancel.png"));
    this->m_tbCancel->setIconSize(QSize(32,32));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbOkay);
    this->m_hLayout->addWidget(this->m_tbCancel);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addLayout(this->m_gLayout);
    this->m_vLayout->addStretch(1);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    connect(this->m_leCityName,SIGNAL(textChanged(QString)),this,SLOT(ZSlotGetPinYin(QString)));
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    this->setObjectName("ZDialogAddCity");
    this->m_llProvinceNameTips->setObjectName("ZDialogAddCityLabelTips");
    this->m_llProvinceName->setObjectName("ZDialogAddCityLabelTips");
    this->m_llCityNameTips->setObjectName("ZDialogAddCityLabelTips");
    this->m_llCityPyTips->setObjectName("ZDialogAddCityLabelTips");
    this->m_llCityAbbrTips->setObjectName("ZDialogAddCityLabelTips");
}
ZDialogAddCity::~ZDialogAddCity()
{
    delete this->m_llProvinceNameTips;
    delete this->m_llProvinceName;

    delete this->m_llCityNameTips;
    delete this->m_leCityName;

    delete this->m_llCityPyTips;
    delete this->m_leCityPy;

    delete this->m_llCityAbbrTips;
    delete this->m_leCityAbbr;

    delete this->m_gLayout;

    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayout;

    delete this->m_vLayout;
}
QSize ZDialogAddCity::sizeHint() const
{
    return QSize(400,200);
}
QString ZDialogAddCity::ZGetCityName()
{
    return this->m_leCityName->text().trimmed();
}
QString ZDialogAddCity::ZGetCityAbbr()
{
    return this->m_leCityAbbr->text().trimmed();
}
void ZDialogAddCity::ZSlotOkay()
{
    QSqlQuery query(ZResManager::ZGetInstance()->ZGetDB());
    query.prepare(SQL_ADD_CITY);
    query.bindValue(":abbr",this->m_leCityAbbr->text().trimmed());
    query.bindValue(":name",this->m_leCityName->text().trimmed());
    query.bindValue(":province",this->m_provinceAbbr);
    query.bindValue(":date",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(query.exec())
    {
        if(1==query.numRowsAffected())
        {
            emit this->ZSigNotifyMsg(tr("新增市：%1成功!").arg(this->m_leCityName->text().trimmed()));
            this->accept();
            return;
        }
    }
    ZDialogErrMsg errDia(tr("新增市:%1失败!\n原因:%2!").arg(this->m_leCityName->text().trimmed()).arg(query.lastError().text()));
    errDia.exec();
}
void ZDialogAddCity::ZSlotGetPinYin(QString str)
{
    QString pinyin=PinyinHelper::convertToPinyinString(str,"\n",PinyinFormat::WITHOUT_TONE);
    this->m_leCityPy->setText(pinyin);

    QString abbr;
    QStringList pyList=pinyin.split("\n");
    for(qint32 i=0;i<pyList.size();i++)
    {
        abbr+=pyList.at(i).left(1);
    }
    this->m_leCityAbbr->setText(abbr);
}
ZDialogDelCity::ZDialogDelCity(QString cityName)
{
    this->setWindowTitle(tr("删除<市>"));
    this->m_cityName=cityName;

    this->m_llMsg=new QLabel;
    this->m_llMsg->setText(tr("您确定要删除市<%1>吗?").arg(cityName));

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("删除"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("取消"));


    this->m_gLayout=new QGridLayout;
    this->m_gLayout->addWidget(this->m_llMsg,0,0,1,2);
    this->m_gLayout->addWidget(this->m_tbOkay,1,0,1,1);
    this->m_gLayout->addWidget(this->m_tbCancel,1,1,1,1);

    this->setLayout(this->m_gLayout);

    //make connections.
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    this->setObjectName("ZDialogDelCity");
    this->m_llMsg->setObjectName("ZDialogDelCityAskLabel");
}
ZDialogDelCity::~ZDialogDelCity()
{
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gLayout;
}
QSize ZDialogDelCity::sizeHint() const
{
    return QSize(400,200);
}
void ZDialogDelCity::ZSlotOkay()
{
    QSqlQuery query(ZResManager::ZGetInstance()->ZGetDB());
    query.prepare(SQL_DEL_CITY);
    query.bindValue(":name",this->m_cityName);
    if(query.exec())
    {
        if(1==query.numRowsAffected())
        {
            emit this->ZSigNotifyMsg(tr("删除市：%1成功!").arg(this->m_cityName));
            this->accept();
            return;
        }
    }
    ZDialogErrMsg errDia(tr("删除市:%1失败!\n原因：%2!").arg(this->m_cityName).arg(query.lastError().text()));
    errDia.exec();
}

ZDialogAddCinema::ZDialogAddCinema(QString provinceName,QString provinceAbbr,QString cityName,QString cityAbbr)
{
    this->setWindowTitle(tr("新增影院"));

    this->m_provinceAbbr=provinceAbbr;
    this->m_cityAbbr=cityAbbr;

    this->m_llProvinceNameTips=new QLabel(tr("省份"));
    this->m_llProvinceName=new QLabel(provinceName);

    this->m_llCityNameTips=new QLabel(tr("市"));
    this->m_llCityName=new QLabel(cityName);

    this->m_llCinemaNameTips=new QLabel(tr("影院(*)"));
    this->m_leCinemaName=new QLineEdit;

    this->m_llCinemaPyTips=new QLabel(tr("拼音(Auto)"));
    this->m_leCinemaPy=new QLineEdit;
    this->m_leCinemaPy->setFocusPolicy(Qt::NoFocus);

    this->m_llCinemaAbbrTips=new QLabel(tr("缩写(Auto)"));
    this->m_leCinemaAbbr=new QLineEdit;

    this->m_gLayout=new QGridLayout;
    this->m_gLayout->addWidget(this->m_llProvinceNameTips,0,0,1,1);
    this->m_gLayout->addWidget(this->m_llProvinceName,0,1,1,1);

    this->m_gLayout->addWidget(this->m_llCityNameTips,1,0,1,1);
    this->m_gLayout->addWidget(this->m_llCityName,1,1,1,1);

    this->m_gLayout->addWidget(this->m_llCinemaNameTips,2,0,1,1);
    this->m_gLayout->addWidget(this->m_leCinemaName,2,1,1,1);

    this->m_gLayout->addWidget(this->m_llCinemaPyTips,3,0,1,1);
    this->m_gLayout->addWidget(this->m_leCinemaPy,3,1,1,1);


    this->m_gLayout->addWidget(this->m_llCinemaAbbrTips,4,0,1,1);
    this->m_gLayout->addWidget(this->m_leCinemaAbbr,4,1,1,1);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Add"));
    this->m_tbOkay->setIcon(QIcon(":/icons/images/Add.png"));
    this->m_tbOkay->setIconSize(QSize(32,32));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));
    this->m_tbCancel->setIcon(QIcon(":/icons/images/Cancel.png"));
    this->m_tbCancel->setIconSize(QSize(32,32));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbOkay);
    this->m_hLayout->addWidget(this->m_tbCancel);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addLayout(this->m_gLayout);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    connect(this->m_leCinemaName,SIGNAL(textChanged(QString)),this,SLOT(ZSlotGetPinYin(QString)));
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    this->setObjectName("ZDialogAddCinema");
    this->m_llProvinceNameTips->setObjectName("ZDialogAddCinemaLabelTips");
    this->m_llProvinceName->setObjectName("ZDialogAddCinemaLabelTips");
    this->m_llCityNameTips->setObjectName("ZDialogAddCinemaLabelTips");
    this->m_llCityName->setObjectName("ZDialogAddCinemaLabelTips");
    this->m_llCinemaNameTips->setObjectName("ZDialogAddCinemaLabelTips");
    this->m_llCinemaPyTips->setObjectName("ZDialogAddCinemaLabelTips");
    this->m_llCinemaAbbrTips->setObjectName("ZDialogAddCinemaLabelTips");
}
ZDialogAddCinema::~ZDialogAddCinema()
{
    delete this->m_llProvinceNameTips;
    delete this->m_llProvinceName;

    delete this->m_llCityNameTips;
    delete this->m_llCityName;

    delete this->m_llCinemaNameTips;
    delete this->m_leCinemaName;

    delete this->m_llCinemaPyTips;
    delete this->m_leCinemaPy;

    delete this->m_llCinemaAbbrTips;
    delete this->m_leCinemaAbbr;

    delete this->m_gLayout;

    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayout;

    delete this->m_vLayout;
}
QSize ZDialogAddCinema::sizeHint() const
{
    return QSize(400,200);
}
QString ZDialogAddCinema::ZGetCinemaName()
{
    return this->m_leCinemaName->text().trimmed();
}
QString ZDialogAddCinema::ZGetCinemaAbbr()
{
    return this->m_leCinemaAbbr->text().trimmed();
}
void ZDialogAddCinema::ZSlotGetPinYin(QString str)
{
    QString pinyin=PinyinHelper::convertToPinyinString(str,"\n",PinyinFormat::WITHOUT_TONE);
    this->m_leCinemaPy->setText(pinyin);

    QString abbr;
    QStringList pyList=pinyin.split("\n");
    for(qint32 i=0;i<pyList.size();i++)
    {
        abbr+=pyList.at(i).left(1);
    }
    this->m_leCinemaAbbr->setText(abbr);
}
void ZDialogAddCinema::ZSlotOkay()
{
    QSqlQuery query(ZResManager::ZGetInstance()->ZGetDB());
    query.prepare(SQL_ADD_CINEMA);
    query.bindValue(":abbr",this->m_leCinemaAbbr->text().trimmed());
    query.bindValue(":name",this->m_leCinemaName->text().trimmed());
    query.bindValue(":city",this->m_cityAbbr);
    query.bindValue(":date",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(query.exec())
    {
        if(1==query.numRowsAffected())
        {
            emit this->ZSigNotifyMsg(tr("新增影院：%1成功!").arg(this->m_leCinemaName->text().trimmed()));
            this->accept();
            return;
        }
    }
    ZDialogErrMsg errDia(tr("新增影院:%1失败!\n原因:%2!").arg(this->m_leCinemaName->text().trimmed()).arg(query.lastError().text()));
    errDia.exec();
}

ZDialogDelCinema::ZDialogDelCinema(QString cinemaName)
{
    this->setWindowTitle(tr("删除<影院>"));
    this->m_cinemaName=cinemaName;

    this->m_llMsg=new QLabel;
    this->m_llMsg->setText(tr("您确定要删除影院<%1>吗?").arg(cinemaName));

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("删除"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("取消"));


    this->m_gLayout=new QGridLayout;
    this->m_gLayout->addWidget(this->m_llMsg,0,0,1,2);
    this->m_gLayout->addWidget(this->m_tbOkay,1,0,1,1);
    this->m_gLayout->addWidget(this->m_tbCancel,1,1,1,1);

    this->setLayout(this->m_gLayout);

    //make connections.
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    this->setObjectName("ZDialogDelCinema");
    this->m_llMsg->setObjectName("ZDialogDelCinemaAskLabel");
}
ZDialogDelCinema::~ZDialogDelCinema()
{
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gLayout;
}
QSize ZDialogDelCinema::sizeHint() const
{
    return QSize(400,200);
}
void ZDialogDelCinema::ZSlotOkay()
{
    QSqlQuery query(ZResManager::ZGetInstance()->ZGetDB());
    query.prepare(SQL_DEL_CINEMA);
    query.bindValue(":name",this->m_cinemaName);
    if(query.exec())
    {
        if(1==query.numRowsAffected())
        {
            emit this->ZSigNotifyMsg(tr("删除影院：%1成功!").arg(this->m_cinemaName));
            this->accept();
            return;
        }
    }
    ZDialogErrMsg errDia(tr("删除影院:%1失败!\n原因：%2!").arg(this->m_cinemaName).arg(query.lastError().text()));
    errDia.exec();
}
ZDialogAddDevice::ZDialogAddDevice(QString provinceName,QString cityName,QString cinemaName,QString cinemaAbbr)
{
    this->setWindowTitle(tr("新增设备"));

    this->m_cinemaAbbr=cinemaAbbr;

    this->m_llProvinceName=new QLabel(provinceName);
    this->m_llCityName=new QLabel(cityName);
    this->m_llCinemaName=new QLabel(cinemaName);
    this->m_hLayoutName=new QHBoxLayout;
    this->m_hLayoutName->addWidget(this->m_llProvinceName);
    this->m_hLayoutName->addWidget(this->m_llCityName);
    this->m_hLayoutName->addWidget(this->m_llCinemaName);


    this->m_llDevID=new QLabel(tr("设备ID"));
    this->m_leDevID=new QLineEdit;
    this->m_leDevID->setMaxLength(24);
    this->m_llDevIDTips=new QLabel(tr("(*)24字符长度"));
    this->m_hLayoutDevID=new QHBoxLayout;
    this->m_hLayoutDevID->addWidget(this->m_llDevID);
    this->m_hLayoutDevID->addWidget(this->m_leDevID);
    this->m_hLayoutDevID->addWidget(this->m_llDevIDTips);
    this->m_hLayoutDevID->setStretchFactor(this->m_llDevID,1);
    this->m_hLayoutDevID->setStretchFactor(this->m_leDevID,4);
    this->m_hLayoutDevID->setStretchFactor(this->m_llDevIDTips,1);
    this->m_teDevMemo=new QTextEdit;

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("添加"));
    this->m_tbOkay->setIcon(QIcon(":/icons/images/Add.png"));
    this->m_tbOkay->setIconSize(QSize(32,32));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("取消"));
    this->m_tbCancel->setIcon(QIcon(":/icons/images/Cancel.png"));
    this->m_tbCancel->setIconSize(QSize(32,32));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_hLayoutBtn=new QHBoxLayout;
    this->m_hLayoutBtn->addStretch(1);
    this->m_hLayoutBtn->addWidget(this->m_tbOkay);
    this->m_hLayoutBtn->addWidget(this->m_tbCancel);

    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->addLayout(this->m_hLayoutName);
    this->m_vLayoutMain->addLayout(this->m_hLayoutDevID);
    this->m_vLayoutMain->addWidget(this->m_teDevMemo);
    this->m_vLayoutMain->addLayout(this->m_hLayoutBtn);

    this->setLayout(this->m_vLayoutMain);

    //make connections.
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    /////////////////////////
    this->setObjectName("ZDialogAddDevice");
    this->m_llProvinceName->setObjectName("ZDialogAddDeviceLabel");
    this->m_llCityName->setObjectName("ZDialogAddDeviceLabel");
    this->m_llCinemaName->setObjectName("ZDialogAddDeviceLabel");
    this->m_llDevID->setObjectName("ZDialogAddDeviceLabelDevID");
    this->m_llDevIDTips->setObjectName("ZDialogAddDeviceLabelDevID");
}
ZDialogAddDevice::~ZDialogAddDevice()
{
    delete this->m_llProvinceName;
    delete this->m_llCityName;
    delete this->m_llCinemaName;
    delete this->m_hLayoutName;

    delete this->m_llDevID;
    delete this->m_leDevID;
    delete this->m_llDevIDTips;
    delete this->m_hLayoutDevID;
    delete this->m_teDevMemo;

    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayoutBtn;

    delete this->m_vLayoutMain;
}
void ZDialogAddDevice::ZSlotOkay()
{
    QString devID=this->m_leDevID->text().trimmed();
    if(devID.isEmpty())
    {
        return;
    }
    this->m_addDate=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QSqlQuery query(ZResManager::ZGetInstance()->ZGetDB());
    query.prepare(SQL_ADD_DEVICE);
    query.bindValue(":devID",devID);
    query.bindValue(":cinemaAbbr",this->m_cinemaAbbr);
    query.bindValue(":memo",this->m_teDevMemo->toPlainText());
    query.bindValue(":date",this->m_addDate);
    if(query.exec())
    {
        if(1==query.numRowsAffected())
        {
            emit this->ZSigNotifyMsg(tr("新增:%1成功!").arg(devID));
            this->accept();
            return;
        }
    }
    ZDialogErrMsg errDia(tr("新增:%1失败!\n原因:%2!").arg(devID).arg(query.lastError().text()));
    errDia.exec();
}
QString ZDialogAddDevice::ZGetDevID()
{
    return this->m_leDevID->text().trimmed();
}
QString ZDialogAddDevice::ZGetAddDate()
{
    return this->m_addDate;
}
QString ZDialogAddDevice::ZGetMemo()
{
    return this->m_teDevMemo->toPlainText().trimmed();
}
ZDialogDelDevice::ZDialogDelDevice(QString deviceName)
{
    this->setWindowTitle(tr("删除<设备>?"));
    this->m_deviceName=deviceName;

    this->m_llIcon=new QLabel;
    this->m_llIcon->setPixmap(QPixmap(":/icons/images/Question.png"));
    this->m_llIcon->setAlignment(Qt::AlignCenter);

    this->m_llMsg=new QLabel;
    this->m_llMsg->setText(tr("您确定要删除以下设备吗?\nID:%2\n\n该设备包含的所有数据都将被删除,且不可恢复!").arg(deviceName));
    this->m_llMsg->setAlignment(Qt::AlignCenter);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("删除"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("取消"));


    this->m_gLayout=new QGridLayout;
    this->m_gLayout->addWidget(this->m_llIcon,0,0,1,2);
    this->m_gLayout->addWidget(this->m_llMsg,1,0,1,2);
    this->m_gLayout->addWidget(this->m_tbOkay,2,0,1,1);
    this->m_gLayout->addWidget(this->m_tbCancel,2,1,1,1);

    this->setLayout(this->m_gLayout);

    //make connections.
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    this->setObjectName("ZDialogDelDevice");
    this->m_llMsg->setObjectName("ZDialogDelDeviceAskLabel");
}
ZDialogDelDevice::~ZDialogDelDevice()
{
    delete this->m_llIcon;
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gLayout;
}
QSize ZDialogDelDevice::sizeHint() const
{
    return QSize(400,200);
}
void ZDialogDelDevice::ZSlotOkay()
{
    QSqlDatabase db=ZResManager::ZGetInstance()->ZGetDB();
    db.transaction();
    QSqlQuery query(db);
    query.prepare(SQL_DEL_DEVICE);
    query.bindValue(":id",this->m_deviceName);
    if(query.exec())
    {
        if(1==query.numRowsAffected())
        {
            query.prepare(SQL_DEL_DATA);
            query.bindValue(":id",this->m_deviceName);
            if(query.exec())
            {
                if(query.numRowsAffected()>0)
                {
                    db.commit();
                    emit this->ZSigNotifyMsg(tr("删除设备：%1成功!").arg(this->m_deviceName));
                    this->accept();
                    return;
                }
            }
        }
    }
    db.rollback();
    ZDialogErrMsg errDia(tr("删除设备:%1失败!\n原因：%2!").arg(this->m_deviceName).arg(query.lastError().text()));
    errDia.exec();
}


ZDialogChargeDev::ZDialogChargeDev(QString devID)
{
    this->setWindowTitle(tr("充时长"));

    this->m_llDevID=new QLabel(devID);
    this->m_llDevID->setAlignment(Qt::AlignCenter);

    for(qint32 i=0;i<11;i++)
    {
        this->m_tbNum[i]=new QToolButton;
        if(i==10)
        {
            this->m_tbNum[i]->setText(tr("C"));
        }else{
            this->m_tbNum[i]->setText(QString::number(i,10));
        }
        connect(this->m_tbNum[i],SIGNAL(clicked(bool)),this,SLOT(ZSlotNumClicked()));
    }
    this->m_gLayoutNum=new QGridLayout;
    this->m_gLayoutNum->addWidget(this->m_tbNum[7],0,0,1,1);
    this->m_gLayoutNum->addWidget(this->m_tbNum[8],0,1,1,1);
    this->m_gLayoutNum->addWidget(this->m_tbNum[9],0,2,1,1);

    this->m_gLayoutNum->addWidget(this->m_tbNum[4],1,0,1,1);
    this->m_gLayoutNum->addWidget(this->m_tbNum[5],1,1,1,1);
    this->m_gLayoutNum->addWidget(this->m_tbNum[6],1,2,1,1);

    this->m_gLayoutNum->addWidget(this->m_tbNum[1],2,0,1,1);
    this->m_gLayoutNum->addWidget(this->m_tbNum[2],2,1,1,1);
    this->m_gLayoutNum->addWidget(this->m_tbNum[3],2,2,1,1);

    this->m_gLayoutNum->addWidget(this->m_tbNum[0],3,0,1,2);
    this->m_gLayoutNum->addWidget(this->m_tbNum[10],3,2,1,1);

    this->m_leChargeHours=new QLineEdit;
    this->m_leChargeHours->setAlignment(Qt::AlignCenter);
    this->m_leChargeHours->setFocusPolicy(Qt::NoFocus);
    this->m_leChargeHours->setObjectName("ZDialogChargeDevChargeHour");
    this->m_leChargeHours->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    this->m_llUUID=new QLabel(tr("唯一UUID"));
    this->m_leUUID=new QLineEdit;
    this->m_leUUID->setFocusPolicy(Qt::NoFocus);
    this->m_leUUID->setText(QUuid::createUuid().toString());
    this->m_tbUUID=new QToolButton;
    this->m_tbUUID->setText(tr("重新生成"));
    connect(this->m_tbUUID,SIGNAL(clicked(bool)),this,SLOT(ZSlotNewUUID()));

    this->m_llValidBefore=new QLabel(tr("在此之前有效"));
    this->m_leValidBefore=new QLineEdit;
    this->m_leValidBefore->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    this->m_tbValidBefore=new QToolButton;
    this->m_tbValidBefore->setText(tr("选择..."));


    this->m_gLayoutMore=new QGridLayout;
    this->m_gLayoutMore->addWidget(this->m_llUUID,0,0,1,1);
    this->m_gLayoutMore->addWidget(this->m_leUUID,0,1,1,1);
    this->m_gLayoutMore->addWidget(this->m_tbUUID,0,2,1,1);

    this->m_gLayoutMore->addWidget(this->m_llValidBefore,1,0,1,1);
    this->m_gLayoutMore->addWidget(this->m_leValidBefore,1,1,1,1);
    this->m_gLayoutMore->addWidget(this->m_tbValidBefore,1,2,1,1);


    this->m_tbMore=new QToolButton;
    this->m_tbMore->setText(tr("更多"));
    this->m_tbMore->setIcon(QIcon(":/icons/images/Down.png"));
    this->m_tbMore->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_tbMore,SIGNAL(clicked(bool)),this,SLOT(ZSlotShowMoreOptions()));

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("充值"));
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));

    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("取消"));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_tbMore);
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbOkay);
    this->m_hLayout->addWidget(this->m_tbCancel);

    this->m_gLayoutMain=new QGridLayout;
    this->m_gLayoutMain->addWidget(this->m_llDevID,0,0,1,2);
    this->m_gLayoutMain->addLayout(this->m_gLayoutNum,1,0,1,1);
    this->m_gLayoutMain->addWidget(this->m_leChargeHours,1,1,1,1);
    this->m_gLayoutMain->addLayout(this->m_gLayoutMore,2,0,1,2);
    this->m_gLayoutMain->addLayout(this->m_hLayout,3,0,1,2);

    this->setLayout(this->m_gLayoutMain);
    this->m_chargeHours=0.0f;
    this->m_leChargeHours->setText(QString::number(this->m_chargeHours,'f',1));

    this->setObjectName("ZDialogChargeDev");
    this->m_llDevID->setObjectName("ZDialogChargeDevID");
    for(qint32 i=0;i<11;i++)
    {
        if(this->m_tbNum[i]->text()=="0")
        {
            this->m_tbNum[i]->setObjectName("ZDialogChargeDevButton0");
        }else{
            this->m_tbNum[i]->setObjectName("ZDialogChargeDevButton");
        }
    }
    this->m_llUUID->setObjectName("ZDialogChargeDevUUID");
    this->m_leUUID->setObjectName("ZDialogChargeDevUUIDLineEdit");

    this->m_llValidBefore->setObjectName("ZDialogChargeDevUUID");
    this->m_leValidBefore->setObjectName("ZDialogChargeDevUUIDLineEdit");

    //hide more options.
    this->m_llUUID->setVisible(false);
    this->m_leUUID->setVisible(false);
    this->m_tbUUID->setVisible(false);

    this->m_llValidBefore->setVisible(false);
    this->m_leValidBefore->setVisible(false);
    this->m_tbValidBefore->setVisible(false);
}
ZDialogChargeDev::~ZDialogChargeDev()
{
    delete m_llDevID;
    for(qint32 i=0;i<11;i++)
    {
        delete this->m_tbNum[i];
    }

    delete this->m_gLayoutNum;

    delete this->m_leChargeHours;

    delete this->m_llUUID;
    delete this->m_leUUID;
    delete this->m_llValidBefore;
    delete this->m_leValidBefore;
    delete this->m_tbValidBefore;
    delete this->m_gLayoutMore;


    delete this->m_tbMore;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayout;

    delete this->m_gLayoutMain;
}
qreal ZDialogChargeDev::ZGetChargeHour()
{
    return this->m_chargeHours;
}
QSize ZDialogChargeDev::sizeHint() const
{
    return QSize(600,300);
}
void ZDialogChargeDev::ZSlotNewUUID()
{
    this->m_leUUID->setText(QUuid::createUuid().toString());
}
void ZDialogChargeDev::ZSlotNumClicked()
{
    QToolButton *tb=qobject_cast<QToolButton*>(this->sender());
    if(tb)
    {
        if(tb->text()=="C")
        {
            this->m_chargeHours=0.0f;
        }else{
            //0.0   320.0
            //0.3  3.2  32.0 320.0
            qint32 num=tb->text().toInt();
            this->m_chargeHours=this->m_chargeHours*10.0f+num/10.0f;
        }
        this->m_leChargeHours->setText(QString::number(this->m_chargeHours,'f',1));
    }
}
void ZDialogChargeDev::ZSlotOkay()
{
    QString devId=this->m_llDevID->text();
    QString uuid=this->m_leUUID->text();
    qreal chargeHour=this->m_leChargeHours->text().toFloat();
    QString validBefore=this->m_leValidBefore->text();
    QString memo;
    QSqlDatabase db=ZResManager::ZGetInstance()->ZGetDB();
    db.transaction();
    QSqlQuery query(db);
    query.prepare(SQL_ADD_DATA);
    query.bindValue(":id",devId);
    query.bindValue(":uuid",uuid);
    query.bindValue(":chargeHour",chargeHour);
    query.bindValue(":validBefore",validBefore);
    query.bindValue(":memo",memo);
    query.bindValue(":date",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(query.exec())
    {
        if(1==query.numRowsAffected())
        {
            //update device table.
            query.prepare(SQL_UPT_DATA);
            query.bindValue(":totalHour",chargeHour);
            query.bindValue(":id",devId);
            if(query.exec())
            {
                if(1==query.numRowsAffected())
                {
                    db.commit();
                    emit this->ZSigNotifyMsg(tr("%1充时长%2时").arg(devId).arg(chargeHour));
                    this->accept();
                    return;
                }
            }
        }
    }
    db.rollback();
    emit this->ZSigNotifyMsg(tr("%1充时长失败:%2").arg(devId).arg(query.lastError().text()));
}
void ZDialogChargeDev::ZSlotShowMoreOptions()
{
    if(this->m_llUUID->isVisible())
    {
        this->m_tbMore->setIcon(QIcon(":/icons/images/Down.png"));

        this->m_llUUID->setVisible(false);
        this->m_leUUID->setVisible(false);
        this->m_tbUUID->setVisible(false);

        this->m_llValidBefore->setVisible(false);
        this->m_leValidBefore->setVisible(false);
        this->m_tbValidBefore->setVisible(false);
    }else{

        this->m_tbMore->setIcon(QIcon(":/icons/images/Up.png"));

        this->m_llUUID->setVisible(true);
        this->m_leUUID->setVisible(true);
        this->m_tbUUID->setVisible(true);

        this->m_llValidBefore->setVisible(true);
        this->m_leValidBefore->setVisible(true);
        this->m_tbValidBefore->setVisible(true);
    }
}
ZDialogChargeHistory::ZDialogChargeHistory(QString devId)
{
    this->setWindowTitle(tr("充值历史-%1").arg(devId));
    this->m_devId=devId;

    this->m_llFilter=new QLabel(tr("依据"));
    this->m_llFilter->setAlignment(Qt::AlignCenter);
    this->m_cbFilter=new QComboBox;
    QStringList itemList;
    itemList<<tr("全部");
    itemList<<tr("根据日期");
    itemList<<tr("根据时长");
    this->m_cbFilter->addItems(itemList);

    this->m_llStart=new QLabel(tr("起始日期"));
    this->m_llStart->setAlignment(Qt::AlignCenter);
    this->m_deStart=new QDateEdit;
    this->m_deStart->setCalendarPopup(true);
    this->m_llEnd=new QLabel(tr("终止日期"));
    this->m_llEnd->setAlignment(Qt::AlignCenter);
    this->m_deEnd=new QDateEdit;
    this->m_deEnd->setCalendarPopup(true);
    this->m_tbFilter=new QToolButton;
    this->m_tbFilter->setText(tr("过滤"));
    this->m_tbFilter->setIcon(QIcon(":/icons/images/Filter.png"));
    this->m_tbFilter->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_llFilter);
    this->m_hLayout->addWidget(this->m_cbFilter);
    this->m_hLayout->addWidget(this->m_llStart);
    this->m_hLayout->addWidget(this->m_deStart);
    this->m_hLayout->addWidget(this->m_llEnd);
    this->m_hLayout->addWidget(this->m_deEnd);
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbFilter);

    this->m_tree=new QTreeWidget;
    this->m_tree->setColumnCount(4);
    QStringList labels;
    labels<<tr("充值日期");
    labels<<tr("UUID");
    labels<<tr("充值时长");
    labels<<tr("在此之前有效");
    this->m_tree->setHeaderLabels(labels);
    for(qint32 i=0;i<this->m_tree->columnCount();i++)
    {
        this->m_tree->headerItem()->setTextAlignment(i,Qt::AlignCenter);
    }
    this->m_tree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addLayout(this->m_hLayout);
    this->m_vLayout->addWidget(this->m_tree);
    this->setLayout(this->m_vLayout);


    this->m_llFilter->setObjectName("ZDialogChargeHistoryTipsLabel");
    this->m_llStart->setObjectName("ZDialogChargeHistoryTipsLabel");
    this->m_llEnd->setObjectName("ZDialogChargeHistoryTipsLabel");

    connect(this->m_tbFilter,SIGNAL(clicked(bool)),this,SLOT(ZSlotFilter()));
}
ZDialogChargeHistory::~ZDialogChargeHistory()
{
    delete this->m_llFilter;
    delete this->m_cbFilter;
    delete this->m_llStart;
    delete this->m_deStart;
    delete this->m_llEnd;
    delete this->m_deEnd;
    delete this->m_tbFilter;
    delete this->m_hLayout;

    delete this->m_tree;
    delete this->m_vLayout;
}

QSize ZDialogChargeHistory::sizeHint() const
{
    return QSize(800,400);
}
void ZDialogChargeHistory::ZSlotFilter()
{
    if(this->m_cbFilter->currentText()=="全部")
    {
        QSqlQuery query(ZResManager::ZGetInstance()->ZGetDB());
        query.prepare(SQL_FIL_HISTORY);
        query.bindValue(":id",this->m_devId);
        if(query.exec())
        {
            while(query.next())
            {
                QTreeWidgetItem *newItem=new QTreeWidgetItem;
                newItem->setText(0,query.value(0).toString());
                newItem->setText(1,query.value(1).toString());
                qreal chargeHours=query.value(2).toFloat();
                newItem->setText(2,QString::number(chargeHours,'f',1));
                newItem->setText(3,query.value(3).toString());

                newItem->setTextAlignment(0,Qt::AlignCenter);
                newItem->setTextAlignment(1,Qt::AlignCenter);
                newItem->setTextAlignment(2,Qt::AlignCenter);
                newItem->setTextAlignment(3,Qt::AlignCenter);

                this->m_tree->addTopLevelItem(newItem);
            }
        }
        for(qint32 i=0;i<this->m_tree->columnCount();i++)
        {
            this->m_tree->resizeColumnToContents(i);
        }
    }
}
ZDialogRestorePoint::ZDialogRestorePoint()
{
    this->setWindowTitle(tr("还原点"));

    this->m_frmWidget=new QFrame;
    this->m_scrollArea=new QScrollArea;
    this->m_scrollArea->setWidget(this->m_frmWidget);

    this->m_tbCreate=new QToolButton;
    this->m_tbCreate->setText(tr("创建还原点"));

    this->m_tbDelete=new QToolButton;
    this->m_tbDelete->setText(tr("删除还原点"));

    this->m_tbApply=new QToolButton;
    this->m_tbApply->setText(tr("应用还原点"));

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_tbCreate);
    this->m_hLayout->addWidget(this->m_tbDelete);
    this->m_hLayout->addWidget(this->m_tbApply);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_scrollArea);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbCreate,SIGNAL(clicked(bool)),this,SLOT(ZSlotCreateRestorePoint()));
    connect(this->m_tbDelete,SIGNAL(clicked(bool)),this,SLOT(ZSlotDeleteRestorePoint()));
    connect(this->m_tbApply,SIGNAL(clicked(bool)),this,SLOT(ZSlotApplyRestorePoint()));

    this->setObjectName("ZDialogRestorePoint");

    this->ZFuncLoadRestorePoints();
}
ZDialogRestorePoint::~ZDialogRestorePoint()
{
    for(qint32 i=0;i<this->m_llRPList.size();i++)
    {
        delete this->m_llRPList.at(i);
    }
    this->m_llRPList.clear();

    delete this->m_frmWidget;
    delete this->m_scrollArea;

    delete this->m_tbApply;
    delete this->m_tbCreate;
    delete this->m_tbDelete;
    delete this->m_hLayout;
    delete this->m_vLayout;
}
QSize ZDialogRestorePoint::sizeHint() const
{
    return QSize(800,400);
}

void ZDialogRestorePoint::ZSlotCreateRestorePoint()
{

}
void ZDialogRestorePoint::ZSlotDeleteRestorePoint()
{

}
void ZDialogRestorePoint::ZSlotApplyRestorePoint()
{

}
void ZDialogRestorePoint::ZFuncLoadRestorePoints()
{

}
ZDialogSysSetup::ZDialogSysSetup()
{

}
ZDialogSysSetup::~ZDialogSysSetup()
{

}
