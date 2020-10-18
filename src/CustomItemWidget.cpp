#include "CustomItemWidget.h"
#include "CustomItemData.h"
#include "CustomItemWidgets.h"
#include "CustomItemTypes.h"

CustomItemWidget::CustomItemWidget(QWidget *parent)
    : QWidget(parent)
{
    init();
}

CustomItemWidget::CustomItemWidget(CustomItemData data, QWidget *parent)
    : QWidget(parent)
{
    init();
    setData(data);
}

CustomItemWidget::CustomItemWidget(CustomItemData data, int propertyIndex, bool editMode, QWidget *parent)
{
    init();
    setEditMode(editMode);
    setCurrentPropertyIndex(propertyIndex);
    setData(data);
}

CustomItemWidget::~CustomItemWidget()
{
    clear();
}

void CustomItemWidget::setStyleOption(const QStyleOptionViewItem &option)
{
    mOption = option;
}

void CustomItemWidget::setData(CustomItemData data)
{
    mData = data;
    build();
}

CustomItemData CustomItemWidget::getData() const
{
    return mData;
}

void CustomItemWidget::setCurrentPropertyIndex(int propertyIndex)
{
    mCurrentPropertyIndex = propertyIndex;
}

void CustomItemWidget::setPropertyMask(const QStringList &mask)
{
    mPropertyMask = mask;
}

void CustomItemWidget::setEditMode(bool aEditMode)
{
    mEditMode = aEditMode;
}

void CustomItemWidget::setStyleSheets(const QString& aEditModeStyleSheet, const QString& aShowModeStyleSheet)
{
	mEditModeStyleSheet = aEditModeStyleSheet;
	mShowModeStyleSheet = aShowModeStyleSheet;
}

void CustomItemWidget::applyValue(QVariant aValue)
{
    mData.setProperty(mCurrentPropertyIndex,aValue);
    //emit signalCommit();
    emit signalEditingFinished(mData);
}

void CustomItemWidget::slotEditingFinished(QVariant aValue)
{
    applyValue(aValue);
}

void CustomItemWidget::slotEditingFinished(QString aValue)
{
    applyValue(QVariant().fromValue(aValue));
}

void CustomItemWidget::slotEditingFinished(int aValue)
{
    applyValue(QVariant().fromValue(aValue));
}

void CustomItemWidget::slotEditingFinished(double aValue)
{
    applyValue(QVariant().fromValue(aValue));
}

void CustomItemWidget::slotEditingFinished(bool aValue)
{
    applyValue(QVariant().fromValue(aValue));
}

void CustomItemWidget::showValue(const CustomItemProperty &aProperty)
{
    QVariant value = aProperty.mValue;
    QString typeName(value.typeName());

    switch(value.type())
    {
        case QVariant::Type::String :
            {
                SIString si_string(value.toString());
                QLineEditSI* pWidget = new QLineEditSI(QVariant().fromValue(si_string),mEditMode);
				applyStyleSheet(pWidget);
                mWidgets.push_back(pWidget);
                connect(pWidget, SIGNAL(signalEdittingFinished(QString)),this,SLOT(slotEditingFinished(QString)));
                connect(pWidget, SIGNAL(signalSelected()),this,SIGNAL(signalSelected()));
            }
            break;

        case QVariant::Type::Int :
            {
                SIInteger si_integer(value.toInt());
                QSpinBoxSI* pWidget = new QSpinBoxSI(QVariant().fromValue(si_integer),mEditMode);
				applyStyleSheet(pWidget);
                mWidgets.push_back(pWidget);
                connect(pWidget, SIGNAL(signalEdittingFinished(int)),this,SLOT(slotEditingFinished(int)));
                connect(pWidget, SIGNAL(signalSelected()),this,SIGNAL(signalSelected()));
            }
            break;

        case QVariant::Type::Double :
            {
                SIDouble si_double(value.toDouble());
                QDoubleSpinBoxSI* pWidget = new QDoubleSpinBoxSI(QVariant().fromValue(si_double),mEditMode);
				applyStyleSheet(pWidget);
                mWidgets.push_back(pWidget);
                connect(pWidget, SIGNAL(signalEdittingFinished(double)),this,SLOT(slotEditingFinished(double)));
                connect(pWidget, SIGNAL(signalSelected()),this,SIGNAL(signalSelected()));
            }
            break;

        case QVariant::Type::Bool :
            {
                SIBoolean si_boolean(value.toBool());
                QRadioButtonSI* pWidget = new QRadioButtonSI(QVariant().fromValue(si_boolean),mEditMode);
				applyStyleSheet(pWidget);
                mWidgets.push_back(pWidget);
                connect(pWidget, SIGNAL(signalEdittingFinished(bool)),this,SLOT(slotEditingFinished(bool)));
                connect(pWidget, SIGNAL(signalSelected()),this,SIGNAL(signalSelected()));
            }
            break;

        default:
            if(typeName == "SIInteger")
            {
                auto pWidget = new QSpinBoxSI(value,mEditMode);
				applyStyleSheet(pWidget);
                mWidgets.push_back(pWidget);
                connect(pWidget, SIGNAL(signalEdittingFinished(QVariant)),this,SLOT(slotEditingFinished(QVariant)));
                connect(pWidget, SIGNAL(signalSelected()),this,SIGNAL(signalSelected()));
            }

            if(typeName == "SIDouble")
            {
                auto pWidget = new QDoubleSpinBoxSI(value,mEditMode);
				applyStyleSheet(pWidget);
                mWidgets.push_back(pWidget);
                connect(pWidget, SIGNAL(signalEdittingFinished(QVariant)),this,SLOT(slotEditingFinished(QVariant)));
                connect(pWidget, SIGNAL(signalSelected()),this,SIGNAL(signalSelected()));
            }

            if(typeName == "SIBoolean")
            {
                auto pWidget = new QRadioButtonSI(value,mEditMode);
				applyStyleSheet(pWidget);
                mWidgets.push_back(pWidget);
                connect(pWidget, SIGNAL(signalEdittingFinished(QVariant)),this,SLOT(slotEditingFinished(QVariant)));
                connect(pWidget, SIGNAL(signalSelected()),this,SIGNAL(signalSelected()));
            }

            if(typeName == "SIString")
            {
                auto pWidget = new QLineEditSI(value,mEditMode);
				applyStyleSheet(pWidget);
                mWidgets.push_back(pWidget);
                connect(pWidget, SIGNAL(signalEdittingFinished(QVariant)),this,SLOT(slotEditingFinished(QVariant)));
                connect(pWidget, SIGNAL(signalSelected()),this,SIGNAL(signalSelected()));
            }

            if(typeName == "SIText")
            {
                auto pWidget = new QTextEditSI(value,mEditMode);
				applyStyleSheet(pWidget);
                mWidgets.push_back(pWidget);
                connect(pWidget, SIGNAL(signalEdittingFinished(QVariant)),this,SLOT(slotEditingFinished(QVariant)));
                connect(pWidget, SIGNAL(signalSelected()),this,SIGNAL(signalSelected()));
            }

            if (typeName == "SIStringList")
            {
                auto pWidget = new QListWidgetSI(value,mEditMode);
				applyStyleSheet(pWidget);
                mWidgets.push_back(pWidget);
                connect(pWidget, SIGNAL(signalEdittingFinished(QVariant)),this,SLOT(slotEditingFinished(QVariant)));
                connect(pWidget, SIGNAL(signalSelected()),this,SIGNAL(signalSelected()));
            }

			if (typeName == "SIBooleanList")
			{
				auto pWidget = new QBooleanListWidgetSI(value, mEditMode);
				applyStyleSheet(pWidget);
				mWidgets.push_back(pWidget);
				connect(pWidget, SIGNAL(signalEdittingFinished(QVariant)), this, SLOT(slotEditingFinished(QVariant)));
                connect(pWidget, SIGNAL(signalSelected()),this,SIGNAL(signalSelected()));
			}

			if (typeName == "SIProgress")
			{
				auto pWidget = new QProgressBarSI(value);
				applyStyleSheet(pWidget);
				mWidgets.push_back(pWidget);
			}

			if (typeName == "SILcd")
			{
				auto pWidget = new QLCDNumberSI(value);
				applyStyleSheet(pWidget);
				mWidgets.push_back(pWidget);
			}

			if (typeName == "SIBars")
			{
				auto pWidget = new QBarsPlotSI(value);
				applyStyleSheet(pWidget);
				mWidgets.push_back(pWidget);
			}

			if (typeName == "SIGraph")
			{
				auto pWidget = new QGraphPlotSI(value);
				applyStyleSheet(pWidget);
				mWidgets.push_back(pWidget);
			}

			if (typeName == "SIImage")
			{
				auto pWidget = new QImageSI(value);
				applyStyleSheet(pWidget);
				mWidgets.push_back(pWidget);
			}
            break;
    }	
}

void CustomItemWidget::build()
{
    clear();

    if(mPropertyMask.isEmpty())
        showValue(mData.getProperty(mCurrentPropertyIndex));
    else
    {
        for(const QString& property : mPropertyMask)
            showValue(mData.getProperty(property));
    }

    for(auto widget : mWidgets)
        mLayout->addWidget(widget);
}

void CustomItemWidget::init()
{
    setStyleSheet("background-color:white;");
    mLayout = new QVBoxLayout(this);
    mLayout->setSpacing(0);
    mLayout->setMargin(1);
}

void CustomItemWidget::clear()
{
    for(auto w : mWidgets)
    {
        mLayout->removeWidget(w);
        delete w;
    }
    mWidgets.clear();
}

void CustomItemWidget::applyStyleSheet(QWidget* aWidget)
{
	/*
	if (mEditMode == true)
		aWidget->setStyleSheet(mEditModeStyleSheet);
	else
		aWidget->setStyleSheet(mShowModeStyleSheet);
		*/
}
