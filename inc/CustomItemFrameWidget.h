#ifndef CUSTOMITEMFRAMEWIDGET_H
#define CUSTOMITEMFRAMEWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QLabel>
#include <QVBoxLayout>
#include "CustomItemClasses.h"

class CustomItemFrameWidget : public QFrame {
	Q_OBJECT

public:
    CustomItemFrameWidget(CustomItem* apItem, QWidget * parent = Q_NULLPTR);

signals:
    void signalItemSelected(CustomItem* apItem);

private:
    CustomItem* mpItem;
    CustomItemWidget* mpWidget;
    QLabel* mpLabelCaption;
    QLabel* mpLabelDescription;
    QVBoxLayout* mpLayout;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif//CUSTOMITEMFRAMEWIDGET_H
