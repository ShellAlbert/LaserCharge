#include "zcustomwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
ZDetailLabel::ZDetailLabel()
{
    this->m_bHitIt=false;
    this->m_popupMenu=new QMenu;
}
ZDetailLabel::~ZDetailLabel()
{
    delete this->m_popupMenu;
}
QAction* ZDetailLabel::ZAddAction(const QIcon &icon,const QString &text)
{
    QAction *act=this->m_popupMenu->addAction(icon,text);
    return act;
}
void ZDetailLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainter painter(this);
    if(this->m_bHitIt)
    {
        QPixmap pxpDetail(":/icons/images/DetailActive.png");
        QRect rect(2,2,30,30);
        painter.drawPixmap(rect,pxpDetail);
    }else{
        QPixmap pxpDetail(":/icons/images/Detail.png");
        QRect rect(2,2,20,20);
        painter.drawPixmap(rect,pxpDetail);
    }
}
void ZDetailLabel::mousePressEvent(QMouseEvent *ev)
{
    QRect rect(2,2,20,20);
    if(rect.contains(ev->x(),ev->y(),true))
    {
        this->setCursor(Qt::PointingHandCursor);
        this->m_bHitIt=true;
    }else{
        this->setCursor(Qt::ArrowCursor);
        this->m_bHitIt=false;
    }
    this->update();

    if(this->m_bHitIt)
    {
        QPoint pt(ev->x(),ev->y());
        this->m_popupMenu->popup(this->mapToGlobal(pt));
    }
}
void ZDetailLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    this->m_bHitIt=false;
    this->update();
}
ZLineEdit::ZLineEdit()
{
    this->m_leText=new QLineEdit;
    this->m_leText->setMaxLength(24);
    this->m_leText->setPlaceholderText(tr("请输入ID编号"));
    this->m_llIcon=new QLabel;
    this->m_llIcon->setPixmap(QPixmap(":/icons/images/Search.png").scaled(20,20));

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->setSpacing(0);
    this->m_hLayout->setContentsMargins(5,2,5,2);
    this->m_hLayout->addWidget(this->m_leText);
    this->m_hLayout->addWidget(this->m_llIcon);
    this->setLayout(this->m_hLayout);

    this->setObjectName("ZLineEdit");
    this->m_leText->setObjectName("ZLineEditData");
    this->m_llIcon->setObjectName("ZLineEditIcon");
}
ZLineEdit::~ZLineEdit()
{
    delete this->m_leText;
    delete this->m_llIcon;
    delete this->m_hLayout;
}
