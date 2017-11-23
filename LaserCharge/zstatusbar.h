#ifndef ZSTATUSBAR_H
#define ZSTATUSBAR_H

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
class ZStatusBar : public QFrame
{
    Q_OBJECT
public:
    ZStatusBar();
    ~ZStatusBar();
    void ZUpdateCounter();

public slots:
    void ZSlotShowMsg(QString msg);
private slots:
    void ZSlotResetMsg();
private:
    QLabel *m_llMsg;
    QLabel *m_llCounter;
    QHBoxLayout *m_hLayout;
};

#endif // ZSTATUSBAR_H
