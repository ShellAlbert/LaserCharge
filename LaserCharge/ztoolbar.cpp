#include "ztoolbar.h"

ZToolBar::ZToolBar()
{
    this->m_llAppIcon=new QLabel;
    this->m_llAppIcon->setPixmap(QPixmap(":/icons/images/AppName.png").scaled(48,48));

    this->m_llAppName=new QLabel;
    this->m_llAppName->setText(tr("激光租赁充值管理"));
    this->m_llAppName->setAlignment(Qt::AlignCenter);

    this->m_tbPlaceManage=new QToolButton;
    this->m_tbPlaceManage->setText(tr("地域管理"));
    this->m_tbPlaceManage->setIconSize(QSize(32,32));
    this->m_tbPlaceManage->setIcon(QIcon(":/icons/images/PlaceManage.png"));
    this->m_tbPlaceManage->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_tbPlaceManage->setPopupMode(QToolButton::InstantPopup);
    this->m_tbPlaceManage->setAutoRaise(true);
    this->m_menuPlace=new QMenu;
    this->m_actAddProvince=this->m_menuPlace->addAction(QIcon(":/icons/images/Add.png"),tr("新增省"));
    this->m_menuPlace->addSeparator();
    this->m_actAddCity=this->m_menuPlace->addAction(QIcon(":/icons/images/Add.png"),tr("新增市"));
    this->m_menuPlace->addSeparator();
    this->m_actAddCinema=this->m_menuPlace->addAction(QIcon(":/icons/images/Add.png"),tr("新增影院"));
    this->m_menuPlace->addSeparator();
    this->m_actDelete=this->m_menuPlace->addAction(QIcon(":/icons/images/Delete.png"),tr("移除"));
    this->m_tbPlaceManage->setMenu(this->m_menuPlace);


    this->m_tbDeviceManage=new QToolButton;
    this->m_tbDeviceManage->setText(tr("设备管理"));
    this->m_tbDeviceManage->setIconSize(QSize(32,32));
    this->m_tbDeviceManage->setIcon(QIcon(":/icons/images/DeviceManage.png"));
    this->m_tbDeviceManage->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_tbDeviceManage->setPopupMode(QToolButton::InstantPopup);
    this->m_tbDeviceManage->setAutoRaise(true);
    this->m_menuDevice=new QMenu;
    this->m_actAddDevice=this->m_menuDevice->addAction(QIcon(":/icons/images/Add.png"),tr("新增设备"));
    this->m_actDelDevice=this->m_menuDevice->addAction(QIcon(":/icons/images/Delete.png"),tr("移除设备"));
    this->m_tbDeviceManage->setMenu(this->m_menuDevice);


    this->m_tbChargeManage=new QToolButton;
    this->m_tbChargeManage->setText(tr("授权充值"));
    this->m_tbChargeManage->setIconSize(QSize(32,32));
    this->m_tbChargeManage->setIcon(QIcon(":/icons/images/Charge.png"));
    this->m_tbChargeManage->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_tbChargeManage->setPopupMode(QToolButton::InstantPopup);
    this->m_tbChargeManage->setAutoRaise(true);
    this->m_menuCharge=new QMenu;
    this->m_actChargeHour=this->m_menuCharge->addAction(QIcon(":/icons/images/Add.png"),tr("充时长"));
    this->m_actChargePeriod=this->m_menuCharge->addAction(QIcon(":/icons/images/Delete.png"),tr("充时段"));
    this->m_tbChargeManage->setMenu(this->m_menuCharge);

    this->m_tbHistoryManage=new QToolButton;
    this->m_tbHistoryManage->setText(tr("历史日志"));
    this->m_tbHistoryManage->setIconSize(QSize(32,32));
    this->m_tbHistoryManage->setIcon(QIcon(":/icons/images/HistoryRecord.png"));
    this->m_tbHistoryManage->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_tbHistoryManage->setPopupMode(QToolButton::InstantPopup);
    this->m_tbHistoryManage->setAutoRaise(true);


    this->m_tbSystemManage=new QToolButton;
    this->m_tbSystemManage->setText(tr("系统设置"));
    this->m_tbSystemManage->setIconSize(QSize(32,32));
    this->m_tbSystemManage->setIcon(QIcon(":/icons/images/SystemManage.png"));
    this->m_tbSystemManage->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_tbSystemManage->setPopupMode(QToolButton::InstantPopup);
    this->m_tbSystemManage->setAutoRaise(true);
    this->m_menuSysSetup=new QMenu;
    this->m_actExportAll=this->m_menuSysSetup->addAction(QIcon(":/icons/images/Export.png"),tr("设备导出"));
    this->m_actImportAll=this->m_menuSysSetup->addAction(QIcon(":/icons/images/Import.png"),tr("设备导入"));
    this->m_actRestorePoint=this->m_menuSysSetup->addAction(QIcon(":/icons/images/Import.png"),tr("还原点"));
    this->m_actSysSetup=this->m_menuSysSetup->addAction(QIcon(":/icons/images/Import.png"),tr("个性设置"));
    this->m_tbSystemManage->setMenu(this->m_menuSysSetup);

    this->m_tbPanelShow=new QToolButton;
    this->m_tbPanelShow->setText(tr("侧边栏"));
    this->m_tbPanelShow->setIconSize(QSize(32,32));
    this->m_tbPanelShow->setIcon(QIcon(":/icons/images/SystemManage.png"));
    this->m_tbPanelShow->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_tbPanelShow->setPopupMode(QToolButton::InstantPopup);
    this->m_tbPanelShow->setAutoRaise(true);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->setContentsMargins(10,5,10,0);
    this->m_hLayout->addWidget(this->m_tbPanelShow);
    this->m_hLayout->addWidget(this->m_tbPlaceManage);
    this->m_hLayout->addWidget(this->m_tbDeviceManage);
    this->m_hLayout->addWidget(this->m_tbChargeManage);
    this->m_hLayout->addWidget(this->m_tbHistoryManage);
    this->m_hLayout->addWidget(this->m_tbSystemManage);
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_llAppName);
    this->m_hLayout->addWidget(this->m_llAppIcon);
    this->setLayout(this->m_hLayout);

    this->setObjectName("ZToolBar");
    this->m_llAppName->setObjectName("ZToolBarAppName");
    this->m_tbPlaceManage->setObjectName("ZToolBarButton");
    this->m_tbDeviceManage->setObjectName("ZToolBarButton");
    this->m_tbChargeManage->setObjectName("ZToolBarButton");
    this->m_tbHistoryManage->setObjectName("ZToolBarButton");
    this->m_tbSystemManage->setObjectName("ZToolBarButton");
    this->m_tbPanelShow->setObjectName("ZToolBarButton");

    //make connections.
    connect(this->m_actAddProvince,SIGNAL(triggered(bool)),this,SIGNAL(ZSigAddProvince()));
    connect(this->m_actAddCity,SIGNAL(triggered(bool)),this,SIGNAL(ZSigAddCity()));
    connect(this->m_actAddCinema,SIGNAL(triggered(bool)),this,SIGNAL(ZSigAddCinema()));
    connect(this->m_actDelete,SIGNAL(triggered(bool)),this,SIGNAL(ZSigDelete()));


    connect(this->m_actAddDevice,SIGNAL(triggered(bool)),this,SIGNAL(ZSigAddDevice()));
    connect(this->m_actDelDevice,SIGNAL(triggered(bool)),this,SIGNAL(ZSigDelDevice()));

    connect(this->m_actChargeHour,SIGNAL(triggered(bool)),this,SIGNAL(ZSigChargeHour()));
    connect(this->m_actChargePeriod,SIGNAL(triggered(bool)),this,SIGNAL(ZSigChargePeriod()));

    connect(this->m_actExportAll,SIGNAL(triggered(bool)),this,SIGNAL(ZSigExportAll()));
    connect(this->m_actImportAll,SIGNAL(triggered(bool)),this,SIGNAL(ZSigImportAll()));
    connect(this->m_actRestorePoint,SIGNAL(triggered(bool)),this,SIGNAL(ZSigRestorePoint()));
    connect(this->m_actSysSetup,SIGNAL(triggered(bool)),this,SIGNAL(ZSigSysSetup()));

    connect(this->m_tbPanelShow,SIGNAL(clicked(bool)),this,SLOT(ZSlotPanelShow()));

    this->m_bPanelShow=true;
}
ZToolBar::~ZToolBar()
{
    delete this->m_llAppIcon;
    delete this->m_llAppName;


    delete this->m_actAddProvince;
    delete this->m_actAddCity;
    delete this->m_actAddCinema;
    delete this->m_actDelete;
    delete this->m_menuPlace;


    delete this->m_actAddDevice;
    delete this->m_actDelDevice;
    delete this->m_menuDevice;

    delete this->m_actChargeHour;
    delete this->m_actChargePeriod;
    delete this->m_menuCharge;

    delete this->m_actExportAll;
    delete this->m_actImportAll;
    delete this->m_actRestorePoint;
    delete this->m_actSysSetup;
    delete this->m_menuSysSetup;

    delete this->m_tbPlaceManage;
    delete this->m_tbDeviceManage;
    delete this->m_tbChargeManage;
    delete this->m_tbHistoryManage;
    delete this->m_tbSystemManage;
    delete this->m_tbPanelShow;

    delete this->m_hLayout;
}
void ZToolBar::ZSlotPanelShow()
{
    this->m_bPanelShow=!this->m_bPanelShow;
    emit this->ZSigLeftPanelShow(this->m_bPanelShow);
}
