#include "CustomItem.h"
#include <QDebug>

CustomItem::CustomItem()
{
}

CustomItem::~CustomItem()
{
	if(!mItems.isEmpty())
		qDeleteAll(mItems);
	mItems.clear();
}

CustomItem::CustomItem(const QString &name, const QVariant &value, const QString &description,const Qt::ItemFlags& aFlags)
{
    addProperty("name",name);
    addProperty("value",value,aFlags);
    addProperty("description",description);
}

CustomItem::CustomItem(CustomItem *parent)
{
    mParent = parent;
}

CustomItem::CustomItem(const CustomItem *item, CustomItem *parent)
{
    mParent = parent;
    clone(item);
}

CustomItem &CustomItem::operator=(const CustomItem &item)
{
    clone(&item);
    return *this;
}

void CustomItem::addProperty(const CustomItemProperty &property)
{
    mData.addProperty(property);
}

void CustomItem::addProperty(const QString &propertyName, const QVariant &propertyValue, const Qt::ItemFlags &aFlags)
{
    mData.addProperty(propertyName,propertyValue,aFlags);
}

void CustomItem::setProperty(const QString &propertyName, const QVariant &propertyValue, const Qt::ItemFlags &aFlags)
{
    mData.setProperty(propertyName,propertyValue,aFlags);
}

CustomItemProperty CustomItem::getProperty(const QString &propertyName) const
{
    return mData.getProperty(propertyName);
}

CustomItemProperty CustomItem::getProperty(int propertyIndex) const
{
    return mData.getProperty(propertyIndex);
}

QVariant CustomItem::getPropertyValue(int propertyIndex) const
{
    return mData.getProperty(propertyIndex).mValue;
}

QVariant CustomItem::getPropertyValue(const QString& propertyName) const
{
	return mData.getProperty(propertyName).mValue;
}

void CustomItem::setPropertyToDefault(int propertyIndex, TargetMode aMode)
{
    if((aMode == ForSelf) || (aMode == ForALL))
        mData.setPropertyToDefault(propertyIndex);

    if((aMode == ForALL) || (aMode == ForChildren))
        for(auto& it : mItems)
            it->setPropertyToDefault(propertyIndex,ForALL);
}

void CustomItem::resetPropertyValue(int propertyIndex, TargetMode aMode)
{
    if((aMode == ForSelf) || (aMode == ForALL))
        mData.resetPropertyValue(propertyIndex);

    if((aMode == ForALL) || (aMode == ForChildren))
        for(auto& it : mItems)
            it->resetPropertyValue(propertyIndex,ForALL);
}

const CustomItemData &CustomItem::getData() const
{
    return mData;
}

void CustomItem::setData(const CustomItemData &data)
{
    mData = data;
}

CustomItem *CustomItem::getParent() const
{
    return mParent;
}

void CustomItem::setParent(CustomItem *parent)
{
    mParent = parent;
}

CustomItem *CustomItem::getItem(int getNumber)
{
    return mItems.value(getNumber);
}

const QList<CustomItem *> &CustomItem::getItems() const
{
    return mItems;
}

void CustomItem::clearItems()
{
    mItems.clear();
}

int CustomItem::getNumber() const
{
    if (mParent)
        return mParent->mItems.indexOf(const_cast<CustomItem*>(this));

    return 0;
}

CustomItem* CustomItem::addItem(CustomItem *item)
{
    item->setParent(this);
    mItems.append(item);
    return item;
}

int CustomItem::itemsCount() const
{
    return mItems.count();
}

int CustomItem::columnCount() const
{
    return mData.getPropertiesCount();
}

void CustomItem::setModelItem(QStandardItem *modelItem)
{
    mModelItem = modelItem;
}

QStandardItem *CustomItem::getModelItem()
{
    return mModelItem;
}

void CustomItem::setSizes(const QMap<int, QSize> &aSizes, TargetMode aMode)
{
    if((aMode == ForSelf) || (aMode == ForALL))
        mSizes = aSizes;

    if((aMode == ForALL) || (aMode == ForChildren))
        for(auto& it : mItems)
            it->setSizes(aSizes,ForALL);
}

QSize CustomItem::getSize(int aColumn) const
{
    if(mSizes.contains(aColumn))
        return mSizes[aColumn];
    else
        return QSize();
}

void CustomItem::clone(const CustomItem *item)
{
    mData = item->mData;
    for(auto it : mItems)
        delete it;
    mItems.clear();

    for(auto& it : item->mItems)
    {
        CustomItem* subItem = new CustomItem(it,this);
        mItems.append(subItem);
    }
}

QDataStream& operator<< (QDataStream& stream, const CustomItem* item)
{
    stream << item;
    return stream;
}

QDataStream& operator>> (QDataStream& stream, CustomItem*& item)
{
    int pIt;
    stream >> pIt;
    item = (CustomItem*)pIt;
    return stream;
}

CustomItem *operator<<(CustomItem *item, CustomItemProperty property){
    item->addProperty(property);
    return item;
}
