#ifndef ZTOOLBAR_H
#define ZTOOLBAR_H

#include <QFrame>
#include <QToolButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QAction>
class ZToolBar : public QFrame
{
    Q_OBJECT
public:
    ZToolBar();
    ~ZToolBar();
signals:
    void ZSigAddProvince();
    void ZSigAddCity();
    void ZSigAddCinema();
    void ZSigDelete();

    void ZSigAddDevice();
    void ZSigDelDevice();

    void ZSigChargeHour();
    void ZSigChargePeriod();

    void ZSigExportAll();
    void ZSigImportAll();

    void ZSigRestorePoint();
    void ZSigSysSetup();

    void ZSigLeftPanelShow(bool bShow);
private slots:
    void ZSlotPanelShow();
private:
    QLabel *m_llAppIcon;
    QLabel *m_llAppName;
    QToolButton *m_tbPlaceManage;
    QToolButton *m_tbDeviceManage;
    QToolButton *m_tbChargeManage;
    QToolButton *m_tbHistoryManage;
    QToolButton *m_tbSystemManage;
    QToolButton *m_tbPanelShow;

    QMenu *m_menuPlace;
    QAction *m_actAddProvince;
    QAction *m_actAddCity;
    QAction *m_actAddCinema;
    QAction *m_actDelete;

    QMenu *m_menuDevice;
    QAction *m_actAddDevice;
    QAction *m_actDelDevice;

    QMenu *m_menuCharge;
    QAction *m_actChargeHour;
    QAction *m_actChargePeriod;

    QMenu *m_menuSysSetup;
    QAction *m_actExportAll;
    QAction *m_actImportAll;
    QAction *m_actRestorePoint;
    QAction *m_actSysSetup;

    QHBoxLayout *m_hLayout;
private:
    bool m_bPanelShow;
};

#endif // ZTOOLBAR_H
