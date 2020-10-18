#include "CustomItemSortFilterProxyModel.h"
#include "CustomItemTreeModel.h"
#include "CustomItemTypes.h"
#include "CustomItemData.h"
#include <QDebug>

CustomItemSortFilterProxyModel::CustomItemSortFilterProxyModel(QObject *parent )
	:QSortFilterProxyModel(parent)
{

}

void CustomItemSortFilterProxyModel::refresh()
{
	emit dataChanged(QModelIndex(), QModelIndex());
}

void CustomItemSortFilterProxyModel::setIsShowAll(bool isShowAll)
{
	mIsShowAll = isShowAll;
	invalidateFilter();
}
void CustomItemSortFilterProxyModel::setIsEqual(bool isEqual)
{
	mIsEqual = isEqual;
	invalidateFilter();
}
void CustomItemSortFilterProxyModel::setFilterProperty(QPair<QString, QString> pairNameValue)
{
	mFilterPropertyName = pairNameValue.first;
	mFilterPropertyValue = pairNameValue.second;
	invalidateFilter();
}

void CustomItemSortFilterProxyModel::setSortingProperty(const QString& propertyName)
{
	mSortingPropertyName = propertyName;
	invalidateFilter();
}

bool CustomItemSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
	if (mIsShowAll)
		return true;

	const QModelIndex ind = sourceModel()->index(sourceRow, 0, sourceParent);
	//qDebug() << ind;
	const CustomItemData& cData = getCustomItemData(ind);
	bool res;

    if (cData.getProperty(mFilterPropertyName).mValue == mFilterPropertyValue)
		res = true;
	else
		res = false;

	if(!mIsEqual)
		res = !res;

	return res;
}

bool CustomItemSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const 
{
	int propertyNum = left.column();
	const CustomItemData& dataLeft = getCustomItemData(left);
	const CustomItemData& dataRight = getCustomItemData(right);

    const QVariant propertyLeft = dataLeft.getProperty(propertyNum).mValue;
    const QVariant propertyRight = dataRight.getProperty(propertyNum).mValue;
	
	QString typeName(propertyLeft.typeName());

	switch (propertyLeft.type())
	{
		case QVariant::Type::String:
			return propertyLeft.toString() < propertyRight.toString();
			break;

		case QVariant::Type::Double:
			return propertyLeft.toDouble() < propertyRight.toDouble();
			break;

		case QVariant::Type::Int:
			return propertyLeft.toInt() < propertyRight.toInt();
			break;

		case QVariant::Type::Bool:
			return propertyLeft.toBool() < propertyRight.toBool();
			break;

		default:

			if (typeName == "SIDouble")
				return propertyLeft.value<SIDouble>().getValue() < propertyRight.value<SIDouble>().getValue();

			if(typeName == "SIBoolean")
				return propertyLeft.value<SIBoolean>().getValue() < propertyRight.value<SIBoolean>().getValue();

			if ( (typeName == "SIProgress")||(typeName == "SILcd")||(typeName == "SIInteger") )
				return propertyLeft.value<SIProgress>().getValue() < propertyRight.value<SIProgress>().getValue();

			if (typeName == "SIBars")
				return propertyLeft.value<SIBars>().getValue() < propertyRight.value<SIBars>().getValue();

			if (typeName == "SIGraph")
				return propertyLeft.value<SIGraph>().getValue() < propertyRight.value<SIGraph>().getValue();

			if (typeName == "SIString")
				return propertyLeft.value<SIString>().getValue() < propertyRight.value<SIString>().getValue();

			if (typeName == "SIImage")
				return propertyLeft.value<SIImage>().getValue() < propertyRight.value<SIImage>().getValue();
			break;
	}

	return propertyLeft < propertyRight;
}

CustomItemData CustomItemSortFilterProxyModel::getCustomItemData(const QModelIndex & ind) const
{
	QVariant var = sourceModel()->data(ind);

	if (var.isValid())
		return var.value<CustomItemData>();
	else
		return CustomItemData();
}
