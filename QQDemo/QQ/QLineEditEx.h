#pragma once

#include <QLineEdit>
#include <QEvent>
class QLineEditEx : public QLineEdit
{
	Q_OBJECT

public:
	QLineEditEx(QWidget *parent);
	~QLineEditEx();

protected:
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
public:signals:
	void  Hovered(QWidget *sender);
	void  Leaved(QWidget* sender);
};
