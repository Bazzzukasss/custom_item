#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include "CustomItemPropertiesView.h"
#include "CustomItemPropertyWidget.h"
#include "CustomItem.h"

CustomItemPropertiesViewHeader::CustomItemPropertiesViewHeader(const QString &aCaption, QWidget *parent)
    : QFrame(parent)
{
    mpLayout = new QHBoxLayout(this);
    mpLabelCaption = new QLabel(aCaption,this);
    mpButtonSwitch = new QPushButton(this);
    mpLayout->addWidget(mpLabelCaption);
    mpLayout->addWidget(mpButtonSwitch);

    mpButtonSwitch->setCheckable(true);
    mpButtonSwitch->setChecked(true);

    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    mpLabelCaption->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    connect(mpButtonSwitch, &QPushButton::clicked, this, &CustomItemPropertiesViewHeader::signalSwitchClicked);
}

void CustomItemPropertiesViewHeader::setCaption(const QString &aCaption){
    mpLabelCaption->setText(aCaption);
}


CustomItemPropertiesView::CustomItemPropertiesView(QWidget * parent)
    : QFrame(parent)
    , mpItem(nullptr)
{
    initialize();
}

CustomItemPropertiesView::~CustomItemPropertiesView()
{
    deleteUI();
}

void CustomItemPropertiesView::initialize()
{
    mpLayout = new QVBoxLayout(this);
    mpHeader = new CustomItemPropertiesViewHeader("OPTIONS",this);
    mpContent = new QFrame(this);
    mpContentLayout = new QVBoxLayout(mpContent);

    mpLayout->addWidget(mpHeader);
    mpLayout->addWidget(mpContent);

    connect(mpHeader, &CustomItemPropertiesViewHeader::signalSwitchClicked, [&](bool aIsVisibile){ mpContent->setVisible(aIsVisibile); } );

    mPropertyMask = QStringList({"Maximum","Minimum","Default","Precision","name","value","description"});
}

void CustomItemPropertiesView::setItem(CustomItem *aItem)
{
    deleteUI();
    mpItem = aItem;
    createUI();
}

void CustomItemPropertiesView::deleteUI()
{
    for(auto pWidget : mWidgets)
    {
        mpContentLayout->removeWidget(pWidget);
        delete pWidget;
    }
    mWidgets.clear();
}

void CustomItemPropertiesView::addWidget(CustomItemData *aData, const QString &aPropertyName)
{
    auto pWidget = new CustomItemPropertyWidget(aData,aPropertyName);
    mpContentLayout->addWidget(pWidget);
    mWidgets.push_back(pWidget);
}

void CustomItemPropertiesView::createUI()
{
    auto data = mpItem->getData();

    if(mPropertyMask.isEmpty())
    {
        for( auto propertyName : data.getProperties() )
            addWidget(&data, propertyName);
    }
    else
    {
        for( auto propertyName : mPropertyMask )
            if( data.isPropertyExists(propertyName) )
                addWidget(&data, propertyName);
    }
}

void CustomItemPropertiesView::setCaption(const QString &aCaption){
    mpHeader->setCaption(aCaption);
}

void CustomItemPropertiesView::setPropertyMask(const QStringList &aMask)
{
    mPropertyMask = aMask;
}

