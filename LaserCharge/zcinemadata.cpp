#include "zcinemadata.h"
#include <QHeaderView>
ZTreeWidget::ZTreeWidget()
{
    this->m_popupMenu=new QMenu;
    this->m_actAddDev=this->m_popupMenu->addAction(QIcon(":/icons/images/Add.png"),tr("新增设备"));
    this->m_actDelDev=this->m_popupMenu->addAction(QIcon(":/icons/images/Delete.png"),tr("删除设备"));
    this->m_popupMenu->addSeparator();
    this->m_actImportDev=this->m_popupMenu->addAction(QIcon(":/icons/images/Import.png"),tr("导入列表"));
    this->m_actExportDev=this->m_popupMenu->addAction(QIcon(":/icons/images/Export.png"),tr("导出列表"));
    this->m_popupMenu->addSeparator();
    this->m_actMoveDev=this->m_popupMenu->addAction(QIcon(":/icons/images/Move.png"),tr("迁移..."));
    this->m_popupMenu->addSeparator();
    this->m_actChargeDev=this->m_popupMenu->addAction(QIcon(":/icons/images/Charge.png"),tr("充值..."));

    connect(this->m_actAddDev,SIGNAL(triggered(bool)),this,SIGNAL(ZSigAddDevice()));
    connect(this->m_actDelDev,SIGNAL(triggered(bool)),this,SIGNAL(ZSigDelDevice()));

    connect(this->m_actImportDev,SIGNAL(triggered(bool)),this,SIGNAL(ZSigImportDev()));
    connect(this->m_actExportDev,SIGNAL(triggered(bool)),this,SIGNAL(ZSigExportDev()));

    connect(this->m_actMoveDev,SIGNAL(triggered(bool)),this,SIGNAL(ZSigMoveDev()));
    connect(this->m_actChargeDev,SIGNAL(triggered(bool)),this,SIGNAL(ZSigChargeDev()));
}
ZTreeWidget::~ZTreeWidget()
{
    delete this->m_actAddDev;
    delete this->m_actDelDev;
    delete this->m_actImportDev;
    delete this->m_actExportDev;
    delete this->m_actMoveDev;
    delete this->m_actChargeDev;
    delete this->m_popupMenu;
}
void ZTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    this->m_popupMenu->exec(QCursor::pos());
    event->accept();
}

ZCinemaData::ZCinemaData()
{
    this->m_llTips=new QLabel;
    this->m_llTips->setAlignment(Qt::AlignCenter);

    this->m_leIDFilter=new ZLineEdit;
    this->m_leIDFilter->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    this->m_leIDFilter->setMinimumWidth(200);
    this->m_leIDFilter->setMaximumHeight(24);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_llTips);
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_leIDFilter);

    this->m_tree=new ZTreeWidget;
    this->m_tree->setIconSize(QSize(24,24));
    this->m_tree->setColumnCount(4);
    QStringList labels;
    labels<<tr("设备编号");
    labels<<tr("累计充值时长");
    labels<<tr("增加日期");
    labels<<tr("修改日期");
    this->m_tree->setHeaderLabels(labels);
    this->m_tree->header()->setDefaultAlignment(Qt::AlignCenter);
    QFont fontHead=this->m_tree->header()->font();
    fontHead.setBold(true);
    this->m_tree->header()->setFont(fontHead);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addLayout(this->m_hLayout);
    this->m_vLayout->addWidget(this->m_tree);
    this->m_vLayout->setStretch(0,1);
    this->m_vLayout->setStretch(1,9);
    this->setLayout(this->m_vLayout);

    this->setObjectName("ZCinemaData");
    this->m_llTips->setObjectName("ZCinemaDataTips");
    this->m_tree->setObjectName("ZCinemaDataTree");
}
ZCinemaData::~ZCinemaData()
{
    delete this->m_llTips;
    delete this->m_leIDFilter;
    delete this->m_hLayout;
    delete this->m_tree;
    delete this->m_vLayout;
}
void ZCinemaData::ZSetCinema(QString cinemaAbbr,QString cinemaName)
{
    this->m_cinemaAbbr=cinemaAbbr;
    this->m_cinemaName=cinemaName;
}
void ZCinemaData::ZSetCinemaItem(QTreeWidgetItem *cinemaItem)
{
    this->m_tree->clear();
    for(qint32 i=0;i<cinemaItem->childCount();i++)
    {
        QTreeWidgetItem *devItem=cinemaItem->child(i);
        QTreeWidgetItem *newItem=new QTreeWidgetItem;
        newItem->setIcon(0,QIcon(":/icons/images/Device.png"));
        newItem->setText(0,devItem->text(0));
        newItem->setText(1,devItem->text(1));
        newItem->setText(2,devItem->text(2));
        newItem->setTextAlignment(0,Qt::AlignCenter);
        newItem->setTextAlignment(1,Qt::AlignCenter);
        newItem->setTextAlignment(2,Qt::AlignCenter);
        this->m_tree->addTopLevelItem(newItem);
    }
    for(qint32 i=0;i<this->m_tree->columnCount();i++)
    {
        this->m_tree->resizeColumnToContents(i);
    }
    this->m_llTips->setText(tr("[%1]共有[%2]台设备").arg(this->m_cinemaName).arg(QString::number(cinemaItem->childCount(),10)));
}
