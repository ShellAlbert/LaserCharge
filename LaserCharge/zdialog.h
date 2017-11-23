#ifndef ZDIALOG_H
#define ZDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QGridLayout>
#include <QTextEdit>
#include <QTreeWidget>
#include <QDateEdit>
#include <QTimeEdit>
#include <QComboBox>
#include <QScrollArea>
#include <QFrame>
class ZDialogErrMsg:public QDialog
{
    Q_OBJECT
public:
    ZDialogErrMsg(QString msg);
    ~ZDialogErrMsg();
protected:
    QSize sizeHint() const;
private:
    QVBoxLayout *m_vLayout;
    QLabel *m_llIcon;
    QLabel *m_llMsg;
    QToolButton *m_tbClose;
};
class ZDialogAskMsg:public QDialog
{
    Q_OBJECT
public:
    ZDialogAskMsg(QString msg);
    ~ZDialogAskMsg();
protected:
    QSize sizeHint() const;
private:

    QLabel *m_llIcon;
    QLabel *m_llMsg;
    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayout;

    QVBoxLayout *m_vLayout;
};
class ZDialogAddProvince:public QDialog
{
    Q_OBJECT
public:
    ZDialogAddProvince(QString title);
    ~ZDialogAddProvince();

    QString ZGetProvinceName();
    QString ZGetProvinceAbbr();
protected:
    QSize sizeHint() const;
signals:
    void ZSigNotifyMsg(QString msg);
private slots:
    void ZSlotGetPinYin(QString str);
    void ZSlotOkay();
private:
    QLabel *m_llProvinceName;
    QLineEdit *m_leProvinceName;


    QLabel *m_llProvincePinYin;
    QLineEdit *m_leProvincePinYin;

    QLabel *m_llProvinceAbbr;
    QLineEdit *m_leProvinceAbbr;

    QGridLayout *m_gLayout;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayout;

    QVBoxLayout *m_vLayout;
};

class ZDialogDelProvince:public QDialog
{
    Q_OBJECT
public:
    ZDialogDelProvince(QString provinceName);
    ~ZDialogDelProvince();

protected:
    QSize sizeHint() const;
signals:
    void ZSigNotifyMsg(QString msg);
private slots:
    void ZSlotOkay();
private:
    QLabel *m_llMsg;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;

    QGridLayout *m_gLayout;
    QString m_provinceName;
};
class ZDialogAddCity:public QDialog
{
    Q_OBJECT
public:
    ZDialogAddCity(QString provinceName,QString provinceAbbr);
    ~ZDialogAddCity();

    QString ZGetCityName();
    QString ZGetCityAbbr();
protected:
    QSize sizeHint() const;
signals:
    void ZSigNotifyMsg(QString msg);
private slots:
    void ZSlotGetPinYin(QString str);
    void ZSlotOkay();
private:
    QLabel *m_llProvinceNameTips;
    QLabel *m_llProvinceName;

    QLabel *m_llCityNameTips;
    QLineEdit *m_leCityName;

    QLabel *m_llCityPyTips;
    QLineEdit *m_leCityPy;

    QLabel *m_llCityAbbrTips;
    QLineEdit *m_leCityAbbr;

    QGridLayout *m_gLayout;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayout;

    QVBoxLayout *m_vLayout;

    QString m_provinceAbbr;
};
class ZDialogDelCity:public QDialog
{
    Q_OBJECT
public:
    ZDialogDelCity(QString cityName);
    ~ZDialogDelCity();

protected:
    QSize sizeHint() const;
signals:
    void ZSigNotifyMsg(QString msg);
private slots:
    void ZSlotOkay();
private:
    QLabel *m_llMsg;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;

    QGridLayout *m_gLayout;
    QString m_cityName;
};

class ZDialogAddCinema:public QDialog
{
    Q_OBJECT
public:
    ZDialogAddCinema(QString provinceName,QString provinceAbbr,QString cityName,QString cityAbbr);
    ~ZDialogAddCinema();

    QString ZGetCinemaName();
    QString ZGetCinemaAbbr();
protected:
    QSize sizeHint() const;
signals:
    void ZSigNotifyMsg(QString msg);
private slots:
    void ZSlotGetPinYin(QString str);
    void ZSlotOkay();
private:
    QLabel *m_llProvinceNameTips;
    QLabel *m_llProvinceName;

    QLabel *m_llCityNameTips;
    QLabel *m_llCityName;

    QLabel *m_llCinemaNameTips;
    QLineEdit *m_leCinemaName;

    QLabel *m_llCinemaPyTips;
    QLineEdit *m_leCinemaPy;

    QLabel *m_llCinemaAbbrTips;
    QLineEdit *m_leCinemaAbbr;

    QGridLayout *m_gLayout;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayout;

    QVBoxLayout *m_vLayout;
private:
    QString m_provinceAbbr;
    QString m_cityAbbr;
};
class ZDialogDelCinema:public QDialog
{
    Q_OBJECT
public:
    ZDialogDelCinema(QString cinemaName);
    ~ZDialogDelCinema();

protected:
    QSize sizeHint() const;
signals:
    void ZSigNotifyMsg(QString msg);
private slots:
    void ZSlotOkay();
private:
    QLabel *m_llMsg;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;

    QGridLayout *m_gLayout;
    QString m_cinemaName;
};

class ZDialogAddDevice:public QDialog
{
    Q_OBJECT
public:
    ZDialogAddDevice(QString provinceName,QString cityName,QString cinemaName,QString cinemaAbbr);
    ~ZDialogAddDevice();

    QString ZGetDevID();
    QString ZGetAddDate();
    QString ZGetMemo();
protected:
signals:
    void ZSigNotifyMsg(QString msg);
private slots:
    void ZSlotOkay();
private:
    QLabel *m_llProvinceName;
    QLabel *m_llCityName;
    QLabel *m_llCinemaName;
    QHBoxLayout *m_hLayoutName;

    QLabel *m_llDevID;
    QLineEdit *m_leDevID;
    QLabel *m_llDevIDTips;
    QHBoxLayout *m_hLayoutDevID;
    QTextEdit *m_teDevMemo;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayoutBtn;

    QVBoxLayout *m_vLayoutMain;
private:
    QString m_cinemaAbbr;
    QString m_addDate;
};

class ZDialogDelDevice:public QDialog
{
    Q_OBJECT
public:
    ZDialogDelDevice(QString deviceName);
    ~ZDialogDelDevice();

protected:
    QSize sizeHint() const;
signals:
    void ZSigNotifyMsg(QString msg);
private slots:
    void ZSlotOkay();
private:
    QLabel *m_llIcon;
    QLabel *m_llMsg;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;

    QGridLayout *m_gLayout;
    QString m_deviceName;
};


////////////////////////////////////////////
class ZDialogChargeDev:public QDialog
{
    Q_OBJECT
public:
    ZDialogChargeDev(QString devID);
    ~ZDialogChargeDev();

    qreal ZGetChargeHour();

protected:
    QSize sizeHint() const;
signals:
    void ZSigNotifyMsg(QString msg);
private slots:
    void ZSlotNumClicked();
    void ZSlotNewUUID();
    void ZSlotShowMoreOptions();
    void ZSlotOkay();
private:
    QLabel *m_llDevID;
    QToolButton *m_tbNum[11];
    QGridLayout *m_gLayoutNum;

    QLineEdit *m_leChargeHours;

    QLabel *m_llUUID;
    QLineEdit *m_leUUID;
    QToolButton *m_tbUUID;
    QLabel *m_llValidBefore;
    QLineEdit *m_leValidBefore;
    QToolButton *m_tbValidBefore;
    QGridLayout *m_gLayoutMore;

    QToolButton *m_tbMore;
    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayout;

    QGridLayout *m_gLayoutMain;

private:
    qreal m_chargeHours;
};

class ZDialogChargeHistory:public QDialog
{
Q_OBJECT
public:
    ZDialogChargeHistory(QString devId);
    ~ZDialogChargeHistory();
protected:
    QSize sizeHint() const;
private slots:
    void ZSlotFilter();
private:
    QLabel *m_llFilter;
    QComboBox *m_cbFilter;
    QLabel *m_llStart;
    QDateEdit *m_deStart;
    QLabel *m_llEnd;
    QDateEdit *m_deEnd;
    QToolButton *m_tbFilter;
    QHBoxLayout *m_hLayout;

    QTreeWidget *m_tree;
    QVBoxLayout *m_vLayout;
private:
    QString m_devId;
};

class ZDialogRestorePoint:public QDialog
{
Q_OBJECT
public:
    ZDialogRestorePoint();
    ~ZDialogRestorePoint();
protected:
    QSize sizeHint() const;
private slots:
    void ZSlotCreateRestorePoint();
    void ZSlotDeleteRestorePoint();
    void ZSlotApplyRestorePoint();
private:
    void ZFuncLoadRestorePoints();
private:
    QList<QLabel*> m_llRPList;
    QFrame *m_frmWidget;
    QScrollArea *m_scrollArea;

    QToolButton *m_tbCreate;
    QToolButton *m_tbDelete;
    QToolButton *m_tbApply;
    QHBoxLayout *m_hLayout;
    QVBoxLayout *m_vLayout;
};
class ZDialogSysSetup:public QDialog
{
    Q_OBJECT
public:
    ZDialogSysSetup();
    ~ZDialogSysSetup();
private:
};
#endif // ZDIALOG_H
