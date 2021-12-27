#include "CustomItemFrameWidget.h"
#include "CustomItemWidget.h"
#include "CustomItem.h"

CustomItemFrameWidget::CustomItemFrameWidget(CustomItem *apItem, QWidget * parent)
    : QFrame(parent)
    , mpItem(apItem)
{
    QString name = mpItem->getProperty("name").mValue.toString();
    QString description = mpItem->getProperty("description").mValue.toString();

    mpLayout = new QVBoxLayout(this);
    mpLabelCaption = new QLabel(name,this);
    mpLabelDescription = new QLabel(description,this);
    mpWidget = new CustomItemWidget(mpItem->getData(),1,true,this);

    mpLayout->addWidget(mpLabelCaption);
    mpLayout->addWidget(mpWidget);
    mpLayout->addWidget(mpLabelDescription);

    connect(mpWidget, &CustomItemWidget::signalEditingFinished, [&](const CustomItemData& aData){ mpItem->setData(aData); } );
    connect(mpWidget, &CustomItemWidget::signalSelected, [&](){ emit signalItemSelected(mpItem); } );
}


void CustomItemFrameWidget::mousePressEvent(QMouseEvent *event)
{
    QFrame::mousePressEvent(event);
    emit signalItemSelected(mpItem);
}
