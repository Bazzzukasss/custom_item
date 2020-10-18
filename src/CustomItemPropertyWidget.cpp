#include "CustomItemPropertyWidget.h"
#include "CustomItemWidget.h"
#include <QLabel>
#include <QHBoxLayout>

CustomItemPropertyWidget::CustomItemPropertyWidget(CustomItemData* aData, const QString& aPropertyName, QWidget * parent)
    : QFrame(parent)
    , mpData(aData)
{
    mpLayout = new QHBoxLayout(this);
    mpLabelCaption = new QLabel(aPropertyName,this);
    mpWidget = new CustomItemWidget(*mpData,mpData->getPropertyIndex(aPropertyName),true,this);

    mpLayout->addWidget(mpLabelCaption);
    mpLayout->addWidget(mpWidget);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    connect(mpWidget, &CustomItemWidget::signalEditingFinished, [&](const CustomItemData& aData){ *mpData = aData; } );
}
