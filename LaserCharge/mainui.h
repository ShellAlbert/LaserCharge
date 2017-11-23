#ifndef MAINUI_H
#define MAINUI_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QTimer>

#include "ztoolbar.h"
#include "zpropertyeditor.h"
#include "zprovincedata.h"
#include "zcitydata.h"
#include "zcinemadata.h"
#include "zstatusbar.h"
class MainUI : public QWidget
{
    Q_OBJECT

public:
    MainUI(QWidget *parent = 0);
    ~MainUI();

    qint32 ZCreateProvinceNodes(QStringList provinceList);
    qint32 ZCreateCityNodes(QStringList cityList);
    qint32 ZCreateCinemaNodes(QStringList cinemaList);
    qint32 ZCreateDeviceNodes(QStringList deviceList);
protected:
    QSize sizeHint() const;

signals:
    void ZSigNotifyMsg(QString msg);
private slots:

    void ZSlotAddProvince();
    void ZSlotAddCity();
    void ZSlotAddCinema();
    void ZSlotDelete();

    void ZSlotAddDevice();
    void ZSlotDelDevice();

    void ZSlotChargeHour();
    void ZSlotChargePeriod();
    void ZSlotChargeHistory();

    void ZSlotExportAll();
    void ZSlotImportAll();
    void ZSlotRestorePoint();
    void ZSlotSysSetup();
    void ZSlotPanelShow(bool bShow);
    void ZSlotTreeItemClicked(QTreeWidgetItem *item,qint32 column);
    void ZSlotTreeContextMenu(QPoint pt);


private:
    ZToolBar *m_toolBar;

    QFrame *m_frmTree;
    QToolButton *m_tbExpand;
    QToolButton *m_tbInpand;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDel;
    QToolButton *m_tbExport;
    QHBoxLayout *m_hLayoutBtn;
    QTreeWidget *m_tree;
    QVBoxLayout *m_vLayoutTree;


    QStackedWidget *m_stack;
    ZProvinceData *m_province;
    ZCityData *m_city;
    ZCinemaData *m_cinema;
    ZPropertyEditor *m_editor;

    QFrame *m_frmWorkArea;
    ZStatusBar *m_statusBar;
    QVBoxLayout *m_vLayoutWorkArea;

    QSplitter *m_spliter;


    QVBoxLayout *m_vLayoutMain;
private:
    QMenu *m_menuTreePopup;
    QAction *m_actAddProvince;
    QAction *m_actAddCity;
    QAction *m_actAddCinema;
    QAction *m_actAddDevice;
    QAction *m_actDelete;

private:
    QList<qint32> m_splitList;
};

#endif // MAINUI_H
