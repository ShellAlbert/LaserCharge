#include "mainui.h"
#include <QMap>
#include "zdialog.h"
#include "resmanager.h"
#include "sql.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QTextCodec>
#include <QPropertyAnimation>
#include <stdio.h>
MainUI::MainUI(QWidget *parent): QWidget(parent)
{
    this->setWindowTitle(tr("Laser Charge [build on %1]").arg(__DATE__));
    this->setWindowIcon(QIcon(":/icons/images/Laser.png"));
    this->m_toolBar=new ZToolBar;

    /////////////////////////////////
    this->m_tbExpand=new QToolButton;
    this->m_tbExpand->setIcon(QIcon(":/icons/images/Expand.png"));
    this->m_tbExpand->setIconSize(QSize(16,16));
    this->m_tbExpand->setToolButtonStyle(Qt::ToolButtonIconOnly);
    this->m_tbInpand=new QToolButton;
    this->m_tbInpand->setIcon(QIcon(":/icons/images/Inpad.png"));
    this->m_tbInpand->setIconSize(QSize(16,16));
    this->m_tbInpand->setToolButtonStyle(Qt::ToolButtonIconOnly);

    this->m_tbAdd=new QToolButton;
    this->m_tbAdd->setIcon(QIcon(":/icons/images/Add2.png"));
    this->m_tbAdd->setIconSize(QSize(16,16));
    this->m_tbAdd->setToolButtonStyle(Qt::ToolButtonIconOnly);

    this->m_tbDel=new QToolButton;
    this->m_tbDel->setIcon(QIcon(":/icons/images/Delete2.png"));
    this->m_tbDel->setIconSize(QSize(16,16));
    this->m_tbDel->setToolButtonStyle(Qt::ToolButtonIconOnly);

    this->m_tbExport=new QToolButton;
    this->m_tbExport->setIcon(QIcon(":/icons/images/Export2.png"));
    this->m_tbExport->setIconSize(QSize(16,16));
    this->m_tbExport->setToolButtonStyle(Qt::ToolButtonIconOnly);

    this->m_hLayoutBtn=new QHBoxLayout;
    this->m_hLayoutBtn->addWidget(this->m_tbExpand);
    this->m_hLayoutBtn->addWidget(this->m_tbInpand);
    this->m_hLayoutBtn->addWidget(this->m_tbAdd);
    this->m_hLayoutBtn->addWidget(this->m_tbDel);
    this->m_hLayoutBtn->addWidget(this->m_tbExport);
    this->m_hLayoutBtn->addStretch(1);

    this->m_tbExpand->setObjectName("ZFrameTreeButton");
    this->m_tbInpand->setObjectName("ZFrameTreeButton");
    this->m_tbAdd->setObjectName("ZFrameTreeButton");
    this->m_tbDel->setObjectName("ZFrameTreeButton");
    this->m_tbExport->setObjectName("ZFrameTreeButton");

    this->m_tree=new QTreeWidget;
    this->m_tree->setContentsMargins(0,0,0,0);
    //this->m_tree->setIconSize(QSize(24,24));
    this->m_tree->setContextMenuPolicy(Qt::CustomContextMenu);
    //    QStringList heads;
    //    heads<<tr("设备列表");
    //    this->m_tree->setHeaderLabels(heads);
    //this->m_tree->setHeaderHidden(false);
    this->m_tree->setHeaderHidden(true);
    this->m_tree->setColumnCount(5);
#if 1
    for(qint32 i=1;i<5;i++)
    {
        this->m_tree->setColumnHidden(i,true);
    }
#endif

    this->m_frmTree=new QFrame;
    this->m_frmTree->setObjectName("ZFrameTree");
    this->m_vLayoutTree=new QVBoxLayout;
    this->m_vLayoutTree->setContentsMargins(0,0,0,0);
    this->m_vLayoutTree->setSpacing(0);
    this->m_vLayoutTree->addLayout(this->m_hLayoutBtn);
    this->m_vLayoutTree->addWidget(this->m_tree);
    this->m_frmTree->setLayout(this->m_vLayoutTree);


    this->m_menuTreePopup=new QMenu;
    this->m_actAddProvince=this->m_menuTreePopup->addAction(QIcon(":/icons/images/Add.png"),tr("新增省"));
    this->m_actAddCity=this->m_menuTreePopup->addAction(QIcon(":/icons/images/Add.png"),tr("新增市"));
    this->m_actAddCinema=this->m_menuTreePopup->addAction(QIcon(":/icons/images/Add.png"),tr("新增影院"));
    this->m_actAddDevice=this->m_menuTreePopup->addAction(QIcon(":/icons/images/Add.png"),tr("新增设备"));
    this->m_menuTreePopup->addSeparator();
    this->m_actDelete=this->m_menuTreePopup->addAction(QIcon(":/icons/images/Delete.png"),tr("移除"));

    this->m_province=new ZProvinceData;
    this->m_city=new ZCityData;
    this->m_cinema=new ZCinemaData;
    this->m_editor=new ZPropertyEditor;
    this->m_stack=new QStackedWidget;
    this->m_stack->addWidget(this->m_province);
    this->m_stack->addWidget(this->m_city);
    this->m_stack->addWidget(this->m_cinema);
    this->m_stack->addWidget(this->m_editor);

    this->m_statusBar=new ZStatusBar;

    this->m_vLayoutWorkArea=new QVBoxLayout;
    this->m_vLayoutWorkArea->setSpacing(0);
    this->m_vLayoutWorkArea->setContentsMargins(0,0,0,0);
    this->m_vLayoutWorkArea->addWidget(this->m_stack);
    this->m_vLayoutWorkArea->addWidget(this->m_statusBar);
    this->m_frmWorkArea=new QFrame;
    this->m_frmWorkArea->setLayout(this->m_vLayoutWorkArea);

    this->m_spliter=new QSplitter(Qt::Horizontal);
    this->m_spliter->setContentsMargins(0,0,0,0);
    this->m_spliter->addWidget(this->m_frmTree);
    this->m_spliter->addWidget(this->m_frmWorkArea);

    this->m_spliter->setStretchFactor(0,3);
    this->m_spliter->setStretchFactor(1,4);


    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->setContentsMargins(0,0,0,0);
    this->m_vLayoutMain->setSpacing(0);
    this->m_vLayoutMain->addWidget(this->m_toolBar);
    this->m_vLayoutMain->addWidget(this->m_spliter);
    this->m_vLayoutMain->setStretchFactor(this->m_toolBar,1);
    this->m_vLayoutMain->setStretchFactor(this->m_spliter,10);
    this->setLayout(this->m_vLayoutMain);

    //make connections.
    connect(this->m_tree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(ZSlotTreeItemClicked(QTreeWidgetItem*,qint32)));
    connect(this->m_tree,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ZSlotTreeContextMenu(QPoint)));

    //menu Actions.
    connect(this->m_toolBar,SIGNAL(ZSigAddProvince()),this,SLOT(ZSlotAddProvince()));
    connect(this->m_toolBar,SIGNAL(ZSigAddCity()),this,SLOT(ZSlotAddCity()));
    connect(this->m_toolBar,SIGNAL(ZSigAddCinema()),this,SLOT(ZSlotAddCinema()));
    connect(this->m_toolBar,SIGNAL(ZSigDelete()),this,SLOT(ZSlotDelete()));
    connect(this->m_actAddProvince,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddProvince()));
    connect(this->m_actAddCity,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddCity()));
    connect(this->m_actAddCinema,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddCinema()));
    connect(this->m_actAddDevice,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddDevice()));

    connect(this->m_toolBar,SIGNAL(ZSigAddDevice()),this,SLOT(ZSlotAddDevice()));
    connect(this->m_toolBar,SIGNAL(ZSigDelDevice()),this,SLOT(ZSlotDelDevice()));

    connect(this->m_toolBar,SIGNAL(ZSigChargeHour()),this,SLOT(ZSlotChargeHour()));
    connect(this->m_toolBar,SIGNAL(ZSigChargePeriod()),this,SLOT(ZSlotChargePeriod()));

    connect(this->m_toolBar,SIGNAL(ZSigExportAll()),this,SLOT(ZSlotExportAll()));
    connect(this->m_toolBar,SIGNAL(ZSigImportAll()),this,SLOT(ZSlotImportAll()));
    connect(this->m_toolBar,SIGNAL(ZSigRestorePoint()),this,SLOT(ZSlotRestorePoint()));
    connect(this->m_toolBar,SIGNAL(ZSigSysSetup()),this,SLOT(ZSlotSysSetup()));
    connect(this->m_toolBar,SIGNAL(ZSigLeftPanelShow(bool)),this,SLOT(ZSlotPanelShow(bool)));

    connect(this->m_editor,SIGNAL(ZSigChargeHour()),this,SLOT(ZSlotChargeHour()));
    connect(this->m_editor,SIGNAL(ZSigChargePeriod()),this,SLOT(ZSlotChargePeriod()));
    connect(this->m_editor,SIGNAL(ZSigChargeHistory()),this,SLOT(ZSlotChargeHistory()));

    //notify message.
    connect(this,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));


    QPropertyAnimation *animationStart=new QPropertyAnimation(this, "windowOpacity");
    animationStart->setDuration(1000);
    animationStart->setStartValue(0.0);
    animationStart->setEndValue(1.0);
    animationStart->start(QAbstractAnimation::DeleteWhenStopped);
}

MainUI::~MainUI()
{
    delete this->m_actAddProvince;
    delete this->m_actAddCity;
    delete this->m_actAddCinema;
    delete this->m_actAddDevice;
    delete this->m_actDelete;
    delete this->m_menuTreePopup;

    delete this->m_toolBar;

    delete this->m_province;
    delete this->m_city;
    delete this->m_cinema;
    delete this->m_editor;
    delete this->m_stack;

    delete this->m_tbExpand;
    delete this->m_tbInpand;
    delete this->m_tbAdd;
    delete this->m_tbDel;
    delete this->m_tbExport;

    delete this->m_hLayoutBtn;
    delete this->m_tree;
    delete this->m_frmTree;

    delete this->m_statusBar;
    delete this->m_vLayoutWorkArea;
    delete this->m_frmWorkArea;
    delete this->m_spliter;

    delete this->m_vLayoutMain;
}
QSize MainUI::sizeHint() const
{
    return QSize(800,400);
}
qint32 MainUI::ZCreateProvinceNodes(QStringList provinceList)
{
    for(qint32 i=0;i<provinceList.size();i++)
    {
        QStringList argList=provinceList.at(i).split("[,]");
        if(argList.size()!=3)
        {
            continue;//bypass invalid items.
        }
        QTreeWidgetItem *provinceItem=new QTreeWidgetItem;
        provinceItem->setIcon(0,QIcon(":/icons/images/Province.png"));
        provinceItem->setText(0,argList.at(1));
        provinceItem->setText(1,argList.at(0));
        provinceItem->setText(2,argList.at(2));
        provinceItem->setText(4,"province");
        this->m_tree->addTopLevelItem(provinceItem);

        ZResManager::ZGetInstance()->m_provinceNum++;
        this->m_statusBar->ZUpdateCounter();
    }
    return 0;
}
qint32 MainUI::ZCreateCityNodes(QStringList cityList)
{
    //generate a map.
    QMap<QString,qint32> provinceMap;
    for(qint32 i=0;i<this->m_tree->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=this->m_tree->topLevelItem(i);
        QString provinceName=item->text(0);
        QString provinceAbbr=item->text(1);
        provinceMap.insert(provinceAbbr,i);
    }

    for(qint32 i=0;i<cityList.size();i++)
    {
        QStringList argList=cityList.at(i).split("[,]");
        if(argList.size()!=4)
        {
            continue;
        }
        QString abbrProvince=argList.at(2);
        if(provinceMap.contains(abbrProvince))
        {
            QTreeWidgetItem *provinceItem=this->m_tree->topLevelItem(provinceMap.value(abbrProvince));
            QTreeWidgetItem *cityItem=new QTreeWidgetItem;
            cityItem->setIcon(0,QIcon(":/icons/images/City.png"));
            cityItem->setText(0,argList.at(1));
            cityItem->setText(1,argList.at(0));
            cityItem->setText(2,argList.at(3));
            cityItem->setText(4,"city");
            provinceItem->addChild(cityItem);

            ZResManager::ZGetInstance()->m_cityNum++;
            this->m_statusBar->ZUpdateCounter();
        }
    }
    return 0;
}
qint32 MainUI::ZCreateCinemaNodes(QStringList cinemaList)
{
    QMap<QString,QString> cityMap;
    //generate a map.
    for(qint32 i=0;i<this->m_tree->topLevelItemCount();i++)
    {
        QTreeWidgetItem *provinceItem=this->m_tree->topLevelItem(i);
        if(provinceItem->childCount()>0)
        {
            for(qint32 j=0;j<provinceItem->childCount();j++)
            {
                QTreeWidgetItem *cityItem=provinceItem->child(j);
                QString index=QString::number(i,10)+","+QString::number(j,10);
                cityMap.insert(cityItem->text(1),index);
            }
        }
    }
    for(qint32 i=0;i<cinemaList.size();i++)
    {
        QStringList argList=cinemaList.at(i).split("[,]");
        if(argList.size()!=4)
        {
            continue;//bypass invalid items.
        }
        if(cityMap.contains(argList.at(2)))
        {
            QString indexStr=cityMap.value(argList.at(2));
            QStringList indexList=indexStr.split(",");
            qint32 provinceIndex=indexList.at(0).toInt();
            qint32 cityIndex=indexList.at(1).toInt();
            QTreeWidgetItem *provinceItem=this->m_tree->topLevelItem(provinceIndex);
            QTreeWidgetItem *cityItem=provinceItem->child(cityIndex);
            QTreeWidgetItem *cinemaItem=new QTreeWidgetItem;
            cinemaItem->setIcon(0,QIcon(":/icons/images/Cinema.png"));
            cinemaItem->setText(0,argList.at(1));
            cinemaItem->setText(1,argList.at(0));
            cinemaItem->setText(2,argList.at(3));
            cinemaItem->setText(4,"cinema");
            cityItem->addChild(cinemaItem);

            ZResManager::ZGetInstance()->m_cinemaNum++;
            this->m_statusBar->ZUpdateCounter();
        }
    }
    return 0;
}
qint32 MainUI::ZCreateDeviceNodes(QStringList deviceList)
{
    //generate a map.
    QMap<QString,QString> cinemaMap;
    for(qint32 i=0;i<this->m_tree->topLevelItemCount();i++)
    {
        QTreeWidgetItem *provinceItem=this->m_tree->topLevelItem(i);
        for(qint32 j=0;j<provinceItem->childCount();j++)
        {
            QTreeWidgetItem *cityItem=provinceItem->child(j);
            for(qint32 k=0;k<cityItem->childCount();k++)
            {
                QTreeWidgetItem *cinemaItem=cityItem->child(k);
                QString indexStr=QString::number(i,10)+","+QString::number(j,10)+","+QString::number(k,10);
                cinemaMap.insert(cinemaItem->text(1),indexStr);
            }
        }
    }
    for(qint32 i=0;i<deviceList.size();i++)
    {
        QStringList argList=deviceList.at(i).split("[,]");
        if(argList.size()!=5)
        {
            continue;//bypass invalid item.
        }
        if(cinemaMap.contains(argList.at(1)))
        {
            QString indexStr=cinemaMap.value(argList.at(1));
            QStringList indexList=indexStr.split(",");
            if(indexList.size()!=3)
            {
                continue;//bypass invalid item.
            }

            QTreeWidgetItem *provinceItem=this->m_tree->topLevelItem(indexList.at(0).toInt());
            QTreeWidgetItem *cityItem=provinceItem->child(indexList.at(1).toInt());
            QTreeWidgetItem *cinemaItem=cityItem->child(indexList.at(2).toInt());
            QTreeWidgetItem *deviceItem=new QTreeWidgetItem;
            deviceItem->setIcon(0,QIcon(":/icons/images/Device.png"));
            deviceItem->setText(0,argList.at(0));
            deviceItem->setText(1,argList.at(2));
            deviceItem->setText(2,argList.at(4));
            deviceItem->setText(3,argList.at(3));
            deviceItem->setText(4,"device");
            cinemaItem->addChild(deviceItem);

            ZResManager::ZGetInstance()->m_deviceNum++;
            this->m_statusBar->ZUpdateCounter();
        }
    }
    this->m_tree->expandAll();

    //help to update the right section.
    if(this->m_tree->topLevelItemCount()>0)
    {
        emit this->m_tree->itemClicked(this->m_tree->topLevelItem(0),0);
    }
    return 0;
}
void MainUI::ZSlotTreeContextMenu(QPoint pt)
{
    this->m_menuTreePopup->popup(pt);
}
void MainUI::ZSlotTreeItemClicked(QTreeWidgetItem *item,qint32 column)
{
    Q_UNUSED(column);
    if(item->text(4)=="province")
    {
        QStringList  cityList;
        for(qint32 i=0;i<item->childCount();i++)
        {
            QTreeWidgetItem *cityItem=item->child(i);
            cityList.append(cityItem->text(0)+","+QString::number(cityItem->childCount(),10));
        }
        QString provinceName=item->text(0);
        QString addDate=item->text(2);
        this->m_province->ZSetData(provinceName,addDate);
        this->m_province->ZSetCityList(cityList);

        this->m_stack->setCurrentWidget(this->m_province);
    }else if(item->text(4)=="city"){
        QStringList cinemaList;
        for(qint32 i=0;i<item->childCount();i++)
        {
            cinemaList.append(item->child(i)->text(0));
        }

        this->m_city->ZSetCityData(item->text(0),cinemaList);

        this->m_stack->setCurrentWidget(this->m_city);
    }else if(item->text(4)=="cinema")
    {
        this->m_cinema->ZSetCinema(item->text(1),item->text(0));
        this->m_cinema->ZSetCinemaItem(item);

        this->m_stack->setCurrentWidget(this->m_cinema);
    }else if(item->text(4)=="device")
    {
        QString id=item->text(0);
        QString totalHours=item->text(1);
        QString addDate=item->text(2);
        QString memo=item->text(3);
        QString cinema=item->parent()->text(0);
        QString city=item->parent()->parent()->text(0);
        QString province=item->parent()->parent()->parent()->text(0);
        this->m_editor->ZSetDeviceID(id);
        this->m_editor->ZSetTotalHours(totalHours);
        this->m_editor->ZSetProvinceCityCinema(province,city,cinema);
        QString recentAction;
        recentAction+=addDate+","+"新增设备";
        this->m_editor->ZSetRecentAction(recentAction);
        this->m_stack->setCurrentWidget(this->m_editor);
    }
}
void MainUI::ZSlotAddProvince()
{
    ZDialogAddProvince dia(tr("新增省"));
    connect(&dia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
    if(dia.exec()==QDialog::Accepted)
    {
        QString provinceName=dia.ZGetProvinceName();
        QString provinceAbbr=dia.ZGetProvinceAbbr();
        QTreeWidgetItem *newItem=new QTreeWidgetItem;
        newItem->setIcon(0,QIcon(":/icons/images/Province.png"));
        newItem->setText(0,provinceName);
        newItem->setText(1,provinceAbbr);
        newItem->setText(4,"province");
        this->m_tree->addTopLevelItem(newItem);

        ZResManager::ZGetInstance()->m_provinceNum++;
        this->m_statusBar->ZUpdateCounter();
    }
    disconnect(&dia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
}
void MainUI::ZSlotAddCity()
{
    QTreeWidgetItem *provinceItem=NULL;
    QTreeWidgetItem *item=this->m_tree->currentItem();
    if(NULL==item)
    {
        return;
    }
    if(item->text(4)!="province" && item->text(4)!="city")
    {
        emit this->ZSigNotifyMsg(tr("请在一个省份下面添加市!"));
        return;
    }
    if(item->text(4)=="province")
    {
        provinceItem=item;
    }else if(item->text(4)=="city")
    {
        provinceItem=item->parent();
    }
    QString provinceName=provinceItem->text(0);
    QString provinceAbbr=provinceItem->text(1);
    ZDialogAddCity addCityDia(provinceName,provinceAbbr);
    connect(&addCityDia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
    if(addCityDia.exec()==QDialog::Accepted)
    {
        QString cityName=addCityDia.ZGetCityName();
        QString cityAbbr=addCityDia.ZGetCityAbbr();
        QTreeWidgetItem *newItem=new QTreeWidgetItem;
        newItem->setIcon(0,QIcon(":/icons/images/City.png"));
        newItem->setText(0,cityName);
        newItem->setText(1,cityAbbr);
        newItem->setText(4,"city");
        provinceItem->addChild(newItem);

        ZResManager::ZGetInstance()->m_cityNum++;
        this->m_statusBar->ZUpdateCounter();

        if(this->m_stack->currentWidget()==this->m_province)
        {
            QStringList cityList;
            for(qint32 i=0;i<provinceItem->childCount();i++)
            {
                cityList.append(provinceItem->child(i)->text(0)+","+QString::number(provinceItem->child(i)->childCount(),10));
            }
            this->m_province->ZSetCityList(cityList);
        }
    }
    disconnect(&addCityDia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
}
void MainUI::ZSlotAddCinema()
{
    QTreeWidgetItem *cityItem=NULL;
    QTreeWidgetItem *item=this->m_tree->currentItem();
    if(NULL==item)
    {
        return;
    }
    if(item->text(4)!="city" && item->text(4)!="cinema")
    {
        emit this->ZSigNotifyMsg(tr("请在一个市下面添加影院!"));
        return;
    }
    if(item->text(4)=="city")
    {
        cityItem=item;
    }else if(item->text(4)=="cinema")
    {
        cityItem=item->parent();
    }
    QString provinceName=cityItem->parent()->text(0);
    QString provinceAbbr=cityItem->parent()->text(1);
    QString cityName=cityItem->text(0);
    QString cityAbbr=cityItem->text(1);
    ZDialogAddCinema addDia(provinceName,provinceAbbr,cityName,cityAbbr);
    connect(&addDia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
    if(addDia.exec()==QDialog::Accepted)
    {
        QString cinemaName=addDia.ZGetCinemaName();
        QString cinemaAbbr=addDia.ZGetCinemaAbbr();
        QTreeWidgetItem *newItem=new QTreeWidgetItem;
        newItem->setIcon(0,QIcon(":/icons/images/Cinema.png"));
        newItem->setText(0,cinemaName);
        newItem->setText(1,cinemaAbbr);
        newItem->setText(4,"cinema");
        cityItem->addChild(newItem);

        ZResManager::ZGetInstance()->m_cinemaNum++;
        this->m_statusBar->ZUpdateCounter();
    }
    disconnect(&addDia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
}
void MainUI::ZSlotDelete()
{
    QTreeWidgetItem *item=this->m_tree->currentItem();
    if(NULL==item)
    {
        return;
    }

    if(item->text(4)=="province")
    {
        if(item->childCount()>0)
        {
            ZDialogErrMsg errDia(tr("无法删除!\n原因：省%1包含%2个市!").arg(item->text(0)).arg(item->childCount()));
            errDia.exec();
            return;
        }
        QString provinceName=item->text(0);
        ZDialogDelProvince dia(provinceName);
        connect(&dia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
        if(dia.exec()==QDialog::Accepted)
        {
            this->m_tree->takeTopLevelItem(this->m_tree->currentIndex().row());
            delete item;

            ZResManager::ZGetInstance()->m_provinceNum--;
            this->m_statusBar->ZUpdateCounter();
        }
        disconnect(&dia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
    }else if(item->text(4)=="city")
    {
        if(item->childCount()>0)
        {
            ZDialogErrMsg errDia(tr("无法删除!\n原因：市%1包含%2个影院!").arg(item->text(0)).arg(item->childCount()));
            errDia.exec();
            return;
        }
        QString cityName=item->text(0);
        ZDialogDelCity dia(cityName);
        connect(&dia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
        if(dia.exec()==QDialog::Accepted)
        {
            QTreeWidgetItem *provinceItem=item->parent();
            provinceItem->takeChild(provinceItem->indexOfChild(item));
            delete item;

            ZResManager::ZGetInstance()->m_cityNum--;
            this->m_statusBar->ZUpdateCounter();

            if(this->m_stack->currentWidget()==this->m_province)
            {
                QStringList cityList;
                for(qint32 i=0;i<provinceItem->childCount();i++)
                {
                    cityList.append(provinceItem->child(i)->text(0)+","+QString::number(provinceItem->child(i)->childCount(),10));
                }
                this->m_province->ZSetCityList(cityList);
            }
        }
        disconnect(&dia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
    }else if(item->text(4)=="cinema")
    {
        if(item->childCount()>0)
        {
            ZDialogErrMsg errDia(tr("无法删除!\n原因：影院%1包含%2个设备!").arg(item->text(0)).arg(item->childCount()));
            errDia.exec();
            return;
        }
        ZDialogDelCinema dia(item->text(0));
        connect(&dia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
        if(dia.exec()==QDialog::Accepted)
        {
            QTreeWidgetItem *cityItem=item->parent();
            cityItem->takeChild(cityItem->indexOfChild(item));
            delete item;

            ZResManager::ZGetInstance()->m_cinemaNum--;
            this->m_statusBar->ZUpdateCounter();
        }
        disconnect(&dia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
    }
}
void MainUI::ZSlotAddDevice()
{
    QTreeWidgetItem *cinemaItem=NULL;
    QTreeWidgetItem *item=this->m_tree->currentItem();
    if(NULL==item)
    {
        emit this->ZSigNotifyMsg(tr("请选择一个影院进行添加设备!"));
        return;
    }
    if(item->text(4)!="cinema" && item->text(4)!="device")
    {
        emit this->ZSigNotifyMsg(tr("请选择一个影院进行添加设备!"));
        return;
    }

    if(item->text(4)=="device")
    {
        cinemaItem=item->parent();

    }else if(item->text(4)=="cinema")
    {
        cinemaItem=item;
    }

    QString cinemaName=cinemaItem->text(0);
    QString cinemaAbbr=cinemaItem->text(1);
    QString cityName=cinemaItem->parent()->text(0);
    QString provinceName=cinemaItem->parent()->parent()->text(0);

    ZDialogAddDevice addDia(provinceName,cityName,cinemaName,cinemaAbbr);
    connect(&addDia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
    if(addDia.exec()==QDialog::Accepted)
    {
        QTreeWidgetItem *newItem=new QTreeWidgetItem;
        newItem->setIcon(0,QIcon(":/icons/images/Device.png"));
        newItem->setText(0,addDia.ZGetDevID());
        newItem->setText(1,"0.0");
        newItem->setText(2,addDia.ZGetAddDate());
        newItem->setText(3,addDia.ZGetMemo());
        newItem->setText(4,"device");
        cinemaItem->addChild(newItem);

        ZResManager::ZGetInstance()->m_deviceNum++;
        this->m_statusBar->ZUpdateCounter();

        if(this->m_stack->currentWidget()==this->m_editor)
        {
            emit this->m_tree->itemClicked(newItem,0);
        }
    }
    disconnect(&addDia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
}
void MainUI::ZSlotDelDevice()
{
    QTreeWidgetItem *item=this->m_tree->currentItem();
    if(NULL==item)
    {
        emit this->ZSigNotifyMsg(tr("请选择一个需要删除的设备!"));
        return;
    }
    if(item->text(4)!="device")
    {
        emit this->ZSigNotifyMsg(tr("请选中一个需要删除的设备!"));
        return;
    }
    ZDialogDelDevice delDia(item->text(0));
    connect(&delDia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
    if(delDia.exec()==QDialog::Accepted)
    {
        QTreeWidgetItem *cinemaItem=item->parent();
        cinemaItem->takeChild(cinemaItem->indexOfChild(item));
        delete item;

        if(cinemaItem->childCount()>0)
        {
            emit this->m_tree->itemClicked(cinemaItem->child(0),0);
        }else{
            emit this->m_tree->itemClicked(cinemaItem,0);
        }

        ZResManager::ZGetInstance()->m_deviceNum--;
        this->m_statusBar->ZUpdateCounter();
    }
    disconnect(&delDia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
}
void MainUI::ZSlotChargeHour()
{
    QString devID;
    QTreeWidgetItem *item=this->m_tree->currentItem();
    if(item && item->text(4)=="device")
    {
        devID=item->text(0);
    }
    if(devID.isEmpty())
    {
        return;
    }
    ZDialogChargeDev dia(devID);
    connect(&dia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
    if(dia.exec()==QDialog::Accepted)
    {
        qreal chargeHour=dia.ZGetChargeHour();
        qreal oldHours=item->text(1).toFloat();
        QString totalHour=QString::number(chargeHour+oldHours,'f',1);
        item->setText(1,totalHour);
        if(this->m_stack->currentWidget()==this->m_editor)
        {
            this->m_editor->ZSetTotalHours(totalHour);
        }
    }
    disconnect(&dia,SIGNAL(ZSigNotifyMsg(QString)),this->m_statusBar,SLOT(ZSlotShowMsg(QString)));
}
void MainUI::ZSlotChargePeriod()
{

}
void MainUI::ZSlotChargeHistory()
{
    QString devId=this->m_editor->ZGetDeviceID();
    ZDialogChargeHistory dia(devId);
    if(dia.exec()==QDialog::Accepted)
    {

    }
}
void MainUI::ZSlotExportAll()
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("保存至"),".",".xml");
    if(fileName.isEmpty())
    {
        return;
    }
    qDebug()<<fileName;
    QByteArray xmlData;
    QXmlStreamWriter xmlWrite(&xmlData);
    xmlWrite.setAutoFormatting(true);
    xmlWrite.setCodec(QTextCodec::codecForName("UTF-8"));
    xmlWrite.writeStartDocument();
    xmlWrite.writeStartElement("LaserCharge");
    xmlWrite.writeCharacters(" ");//to avoid missing </>.
    for(qint32 i=0;i<this->m_tree->topLevelItemCount();i++)
    {
        QTreeWidgetItem *provinceItem=this->m_tree->topLevelItem(i);
        xmlWrite.writeStartElement("Province");
        xmlWrite.writeAttribute("name",provinceItem->text(0));
        xmlWrite.writeAttribute("child",QString::number(provinceItem->childCount()));
        xmlWrite.writeEntityReference(QString("#x0A"));
        //xmlWrite.writeCharacters(" ");//to avoid missing </>.
        for(qint32 j=0;j<provinceItem->childCount();j++)
        {
            QTreeWidgetItem *cityItem=provinceItem->child(j);
            xmlWrite.writeStartElement("City");
            xmlWrite.writeAttribute("name",cityItem->text(0));
            xmlWrite.writeAttribute("child",QString::number(cityItem->childCount()));
            xmlWrite.writeCharacters(" ");//to avoid missing </>.
            for(qint32 k=0;k<cityItem->childCount();k++)
            {
                QTreeWidgetItem *cinemaItem=cityItem->child(k);
                xmlWrite.writeStartElement("Cinema");
                xmlWrite.writeAttribute("name",cinemaItem->text(0));
                xmlWrite.writeAttribute("child",QString::number(cinemaItem->childCount()));
                xmlWrite.writeCharacters(" ");//to avoid missing </>.
                for(qint32 l=0;l<cinemaItem->childCount();l++)
                {
                    QTreeWidgetItem *devItem=cinemaItem->child(l);
                    xmlWrite.writeStartElement("Device");
                    xmlWrite.writeAttribute("id",devItem->text(0));
                    xmlWrite.writeAttribute("hour",devItem->text(1));
                    xmlWrite.writeCharacters(" ");//to avoid missing </>.
                    xmlWrite.writeEndElement();//Device.
                }
                xmlWrite.writeEndElement();//Cinema.
            }
            xmlWrite.writeEndElement();//City.
        }
        xmlWrite.writeEndElement();//Province.
    }
    xmlWrite.writeEndElement();//LaserCharge.
    xmlWrite.writeEndDocument();

    QFile xmlFile(fileName);
    if(xmlFile.open(QIODevice::WriteOnly))
    {
        xmlFile.write(xmlData);
        xmlFile.close();
        emit this->ZSigNotifyMsg(tr("数据导出成功!"));
        return;
    }
    emit this->ZSigNotifyMsg(tr("数据导出失败!"));
}
void MainUI::ZSlotImportAll()
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("保存至"),".",".xml");
    if(fileName.isEmpty())
    {
        return;
    }
    qDebug()<<fileName;
}
void MainUI::ZSlotRestorePoint()
{
    ZDialogRestorePoint dia;
    dia.exec();
}
void MainUI::ZSlotSysSetup()
{

}
void MainUI::ZSlotPanelShow(bool bShow)
{
    if(bShow)//show.
    {
        QList<int> list;
        list<<this->m_splitList.at(0);
        list<<this->m_splitList.at(1);
        this->m_spliter->setSizes(list);
    }else{ //hide.
        //save width before hide.
        this->m_splitList.clear();
        this->m_splitList.append(this->m_tree->width());
        this->m_splitList.append(this->m_frmWorkArea->width());
        this->m_splitList.append(this->width());

        //resize.
        QList<int> list;
        list<<0;
        list<<this->width();
        this->m_spliter->setSizes(list);
    }
}

