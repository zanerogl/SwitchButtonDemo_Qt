#include "SwitchControl.h"

SwitchControl::SwitchControl(QWidget *parent)
    : QWidget(parent)
{

    setBackgroundColor(QColor(Qt::blue));
    setCloseColor(QColor(Qt::red));
    setOpenColor(QColor(Qt::green));

    this->setFixedSize(50,100);

//    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    connect(&m_timer, &QTimer::timeout, this, &SwitchControl::onTimeout);
}

SwitchControl::~SwitchControl()
{

}

void SwitchControl::setBackgroundColor(QColor color)
{
    m_background = color;
}

void SwitchControl::setCloseColor(QColor color)
{
    m_closeColor = color;
}

void SwitchControl::setOpenColor(QColor color)
{
    m_openColor = color;
}

void SwitchControl::setSize(QSize size)
{
    Q_UNUSED(size);
}

bool SwitchControl::isToggled() const
{
    return m_bChecked;
}

void SwitchControl::setToggle(bool checked)
{
    m_bChecked = checked;
}

void SwitchControl::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QColor background = m_background;
    QColor openColor = m_openColor;
    QColor setCloseColor = m_closeColor;

    /*初始化画家类*/
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  //抗锯齿
    painter.setBrush(background);                   //设置画刷
    painter.setOpacity(0.6);                        //不透明度

    /*绘制背景*/
    QPainterPath path;  //一个用来画线的类
    path.addRoundedRect(QRectF(m_nMargin, m_nMargin, width()-(m_nMargin*2), height()-(m_nMargin*2)) ,m_radius, m_radius);   //QRectF是一个可以接受float型的类似QRect的类
    painter.drawPath(path.simplified());    //画path设置的线

    /*判断状态，绘制开关*/
    if(m_bChecked)  //打开->关闭
    {
        painter.setBrush(m_closeColor);
    }
    else            //关闭->打开
    {
        painter.setBrush(m_openColor);
    }
    painter.setOpacity(1.0);
//    painter.drawEllipse(QRectF(m_nX - (m_nHeight / 2), m_nY - (m_nHeight / 2), this->width(),  this->width()));
    qDebug()<<m_nX<<m_nY;
    painter.drawEllipse(QRectF(m_nX, m_nY, this->width(), this->width()));
//    painter.drawEllipse(QRectF());
//    painter.drawEllipse(QRectF(0, this->height() - this->width(), this->width(), this->width()));
//    painter.drawEllipse(QRectF(m_nX - (m_nHeight / 2), m_nY - (m_nHeight / 2) + this->height() - this->width(), this->width(),  this->width()));

}

void SwitchControl::resizeEvent(QResizeEvent *event)
{
    m_nX = 0;
    m_nY = 0;
//    m_nX = m_nHeight / 2;
//    m_nY = m_nHeight / 2;
    QWidget::resizeEvent(event);
}


void SwitchControl::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->type() == QMouseEvent::MouseButtonRelease) && (event->button() == Qt::LeftButton))
    {
        event->accept();
        m_bChecked = !m_bChecked;
        emit toggled(m_bChecked);
        m_timer.start(10);
    } else {
        event->ignore();
    }
}

// 切换状态 - 滑动
void SwitchControl::onTimeout()
{
    if (m_bChecked)
    {
        m_nY += 1;
        if (m_nY >= this->height() - this->width())
        {
            m_timer.stop();
        }

    }
    else
    {
        m_nY -= 1;
        if (m_nY <= 0)
        {
            m_timer.stop();
            qDebug()<<m_nX<<m_nY;
        }

    }
    update();
}








