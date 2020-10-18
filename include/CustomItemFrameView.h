#ifndef CUSTOMITEMFRAMEVIEW_H
#define CUSTOMITEMFRAMEVIEW_H

#include <QFrame>
#include <QVector>
#include "CustomItemClasses.h"

class QGridLayout;
class QVBoxLayout;
class QLabel;
class CustomItemFrame;

class CustomItemFrameView : public QFrame
{
    Q_OBJECT
public:
    CustomItemFrameView(QWidget* parent = Q_NULLPTR);
    ~CustomItemFrameView();

    void setItem(CustomItem* aRootItem);

signals:
    void signalItemSelected(CustomItem* apItem);

private:
    QVBoxLayout* mpVLayout;
    QLabel* mpLabelCaption;
    QVector<CustomItemFrame*> mWidgets;
    CustomItem* mpRootItem;

    void initialization();
    void deleteUI();
    void createUI();

};

#endif//CUSTOMITEMFRAMEVIEW_H
