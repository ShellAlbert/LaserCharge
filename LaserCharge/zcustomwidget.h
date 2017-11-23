#ifndef ZCUSTOMWIDGET_H
#define ZCUSTOMWIDGET_H

#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QHBoxLayout>
#include <QLineEdit>
class ZDetailLabel:public QLabel
{
    Q_OBJECT
public:
    ZDetailLabel();
    ~ZDetailLabel();
    QAction* ZAddAction(const QIcon &icon,const QString &text);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    bool m_bHitIt;
    QMenu *m_popupMenu;
};

class ZLineEdit:public QFrame
{
    Q_OBJECT
public:
    ZLineEdit();
    ~ZLineEdit();
private:
    QLineEdit *m_leText;
    QLabel *m_llIcon;
    QHBoxLayout *m_hLayout;
};
#endif // ZCUSTOMWIDGET_H
