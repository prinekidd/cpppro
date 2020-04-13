#include "QLineEditEx.h"

QLineEditEx::QLineEditEx(QWidget *parent)
	: QLineEdit(parent)
{
}

QLineEditEx::~QLineEditEx()
{
}

void QLineEditEx::enterEvent(QEvent* event)
{
    emit Hovered(this);
}
void QLineEditEx::leaveEvent(QEvent* event)
{
    emit Leaved(this);
}
/*
 * 鼠标移动函数
 * 这里实时修改窗口的坐标
 */
void QLineEditEx::mouseMoveEvent(QMouseEvent* event)
{

}
/*
 * 鼠标释放函数
 */
void QLineEditEx::mouseReleaseEvent(QMouseEvent* event)
{

}

