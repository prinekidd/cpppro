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
 * ����ƶ�����
 * ����ʵʱ�޸Ĵ��ڵ�����
 */
void QLineEditEx::mouseMoveEvent(QMouseEvent* event)
{

}
/*
 * ����ͷź���
 */
void QLineEditEx::mouseReleaseEvent(QMouseEvent* event)
{

}

