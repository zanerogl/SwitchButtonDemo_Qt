#ifndef SWITCH_CONTROL
#define SWITCH_CONTROL

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class SwitchControl : public QWidget
{
    Q_OBJECT

public:
    SwitchControl(QWidget *parent = nullptr);
    ~SwitchControl();

    /**
     * @brief 设置背景颜色
     * @param QColor
     */
    void setBackgroundColor(QColor color);

    /**
     * @brief 设置关闭颜色
     * @param QColor
     */
    void setCloseColor(QColor color);

    /**
     * @brief 设置打开颜色
     * @param QColor
     */
    void setOpenColor(QColor color);

    /**
     * @brief 设置尺寸
     * @param QSize
     */
    void setSize(QSize size);

    /**
     * @brief 返回开关状态
     * @return 打开：true 关闭：false
     */
    bool isToggled() const;

    /**
     * @brief 设置开关状态
     * @param 打开：true 关闭：false
     */
    void setToggle(bool checked);

protected:
    /**
     * @brief 重写绘图事件
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief 重写尺寸事件
     */
    void resizeEvent(QResizeEvent *event) override;

    /**
     * @brief 重写鼠标释放事件，鼠标释放时开关状态改变
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    /**
     * @brief 状态改变时，发射信号
     */
    void toggled(bool checked);

private slots:
    /**
     * @brief 状态切换时，用于产生滑动效果
     */
    void onTimeout();

private:
    QColor m_background;            //背景颜色，不需要修改

    QColor m_closeColor;            //关闭颜色
    QColor m_openColor;             //打开颜色

    QTimer  m_timer;                //定时器

    qreal m_radius = 20;            // 圆角
    qint16 m_nMargin = 3;           // 外边距（边框与边框之间的距离），不需要修改
    bool m_bChecked = false;        // 是否选中，初始未被选中
    qreal m_nX;                     // 开关的x点坐标
    qreal m_nY;                     // 开关的y点坐标
//    qint16 m_nHeight =8;           // 高度

};
#endif // SWITCH_CONTROL
