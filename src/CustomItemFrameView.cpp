#include "CustomItemFrameView.h"
#include "CustomItemFrame.h"
#include "CustomItem.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QVector>
#include <QDebug>

CustomItemFrameView::CustomItemFrameView(QWidget *parent)
    : QFrame(parent)
{
    initialization();
}

CustomItemFrameView::~CustomItemFrameView()
{
    deleteUI();
}

void CustomItemFrameView::setItem(CustomItem *aRootItem)
{
    deleteUI();
    mpRootItem = aRootItem;
    createUI();
}

void CustomItemFrameView::initialization()
{
    mpVLayout = new QVBoxLayout(this);
    mpLabelCaption = new QLabel("CustomItem Frame View",this);
    mpVLayout->addWidget(mpLabelCaption);
}

void CustomItemFrameView::deleteUI()
{
    for(auto pWidget : mWidgets)
    {
        mpVLayout->removeWidget(pWidget);
        delete pWidget;
    }
    mWidgets.clear();
}

void CustomItemFrameView::createUI()
{
    mpLabelCaption->setText( mpRootItem->getProperty("name").mValue.toString() );

    for(auto pItem : mpRootItem->getItems())
    {
        auto pFrame = new CustomItemFrame(pItem);
        mpVLayout->addWidget(pFrame);
        mWidgets.push_back(pFrame);
        connect(pFrame, &CustomItemFrame::signalItemSelected, this, &CustomItemFrameView::signalItemSelected);
    }
}
