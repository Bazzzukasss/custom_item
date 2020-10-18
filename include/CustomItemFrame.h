#ifndef CUSTOMITEMFRAME_H
#define CUSTOMITEMFRAME_H

#include <QFrame>
#include <QVector>
#include "CustomItemClasses.h"

class QGridLayout;
class QVBoxLayout;
class CustomItemFrameHeader;

class CustomItemFrame : public QFrame
{
    Q_OBJECT
public:
    CustomItemFrame(CustomItem* aRootItem,QWidget* parent = Q_NULLPTR);
    CustomItemFrame(QWidget* parent = Q_NULLPTR);

signals:
    void signalItemSelected(CustomItem* apItem);

private:
    CustomItem* mpRootItem;
    int mColumnCount;
    QVBoxLayout* mpVLayout;
    QGridLayout* mpGLayout;
    QFrame* mpContent;
    CustomItemFrameHeader* mpHeader;    

    void initialize();
    void createUI();
};

#endif//CUSTOMITEMFRAME_H
