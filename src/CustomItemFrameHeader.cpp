#include "CustomItemFrameHeader.h"
#include "CustomItem.h"

CustomItemFrameHeader::CustomItemFrameHeader(CustomItem *aRootItem, QWidget *parent)
    : QFrame(parent)
    , mpRootItem(aRootItem)
{
    initialize();
}

CustomItemFrameHeader::CustomItemFrameHeader(QWidget *parent)
    : QFrame(parent)
    , mpRootItem(nullptr)
{
    initialize();
}

bool CustomItemFrameHeader::getState() const
{
    bool switchable = mpRootItem != nullptr ? mpRootItem->getProperty("switchable").mValue.toBool() : true;
    bool activated = mpRootItem != nullptr ? mpRootItem->getProperty("activated").mValue.toBool() : true;
    return switchable ? activated : true;
}

void CustomItemFrameHeader::initialize()
{
    QString caption = mpRootItem != nullptr ? mpRootItem->getProperty("name").mValue.toString() : "caption";
    bool switchable = mpRootItem != nullptr ? mpRootItem->getProperty("switchable").mValue.toBool() : true;
    bool activated = mpRootItem != nullptr ? mpRootItem->getProperty("activated").mValue.toBool() : true;

    mpLayout = new QHBoxLayout(this);
    mpLabelCaption = new QLabel(caption,this);
    mpLabelCaption->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    mpLayout->addWidget(mpLabelCaption);

    if(switchable)
    {
        mpButtonSwitch = new QPushButton(this);
        mpButtonSwitch->setCheckable(true);
        mpButtonSwitch->setChecked( activated );
        mpLayout->addWidget(mpButtonSwitch);
        connect(mpButtonSwitch, &QPushButton::clicked, [&](){
            bool state = mpButtonSwitch->isChecked();
            mpRootItem->setProperty("activated",state);
            emit signalSwitchClicked(state);
        });
    }

    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
}
