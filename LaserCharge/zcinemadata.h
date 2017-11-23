#ifndef ZCINEMADATA_H
#define ZCINEMADATA_H

#include <QFrame>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QContextMenuEvent>
#include "zcustomwidget.h"
class ZTreeWidget:public QTreeWidget
{
    Q_OBJECT
public:
    ZTreeWidget();
    ~ZTreeWidget();
signals:
    void ZSigAddDevice();
    void ZSigDelDevice();

    void ZSigImportDev();
    void ZSigExportDev();

    void ZSigMoveDev();

    void ZSigChargeDev();
protected:
    void contextMenuEvent(QContextMenuEvent *event);
private:
    QMenu *m_popupMenu;
    QAction *m_actAddDev;
    QAction *m_actDelDev;

    QAction *m_actImportDev;
    QAction *m_actExportDev;

    QAction *m_actMoveDev;

    QAction *m_actChargeDev;
};
class ZCinemaData : public QFrame
{
    Q_OBJECT
public:
    ZCinemaData();
    ~ZCinemaData();

    void ZSetCinema(QString cinemaAbbr,QString cinemaName);
    void ZSetCinemaItem(QTreeWidgetItem *cinemaItem);
private:
    QLabel *m_llTips;
    ZLineEdit *m_leIDFilter;
    QHBoxLayout *m_hLayout;
    ZTreeWidget *m_tree;
    QVBoxLayout *m_vLayout;
private:
    QString m_cinemaAbbr;
    QString m_cinemaName;
};

#endif // ZCINEMADATA_H
