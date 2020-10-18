#include "CustomItemFrame.h"
#include "CustomItemFrameWidget.h"
#include "CustomItemWidget.h"
#include "CustomItem.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include "CustomItemFrameHeader.h"
#include <QDebug>

CustomItemFrame::CustomItemFrame(CustomItem* aRootItem, QWidget *parent)
    : QFrame(parent)
    , mpRootItem(aRootItem)
    , mColumnCount(2)
{
    initialize();
}

CustomItemFrame::CustomItemFrame(QWidget *parent)
    : QFrame(parent)
    , mpRootItem(nullptr)
    , mColumnCount(2)
{
    initialize();
}

void CustomItemFrame::initialize()
{
    mpHeader = new CustomItemFrameHeader(mpRootItem,this);
    mpContent = new QFrame(this);
    mpVLayout = new QVBoxLayout(this);
    mpGLayout = new QGridLayout(mpContent);

    mpVLayout->addWidget(mpHeader);
    mpVLayout->addWidget(mpContent);

    mpContent->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    connect(mpHeader, &CustomItemFrameHeader::signalSwitchClicked, [&](bool aIsVisibile){ mpContent->setVisible(aIsVisibile); });

    createUI();
    mpContent->setVisible( mpHeader->getState() );
}

void CustomItemFrame::createUI()
{
    int y(0),x(0);
    for(CustomItem* pItem : mpRootItem->getItems())
        if(pItem->itemsCount() == 0)
        {
            int span = pItem->getProperty("span").mValue.toInt();
            if(span == 2)
            {
                y++;
                x=0;
            }
            else
                span = 1;
            auto pWidget = new CustomItemFrameWidget(pItem,mpContent);
            connect(pWidget, &CustomItemFrameWidget::signalItemSelected, this, &CustomItemFrame::signalItemSelected );

            mpGLayout->addWidget(pWidget,y,x++,1,span);
            if(x>=mColumnCount)
            {
                x=0;
                y++;
            }
        }
        else
        {
            auto pFrame = new CustomItemFrame(pItem,mpContent);
            mpGLayout->addWidget(pFrame,y,0,1,mColumnCount);
            connect(pFrame, &CustomItemFrame::signalItemSelected, this, &CustomItemFrame::signalItemSelected);
            x=0;
        }
}
