#pragma once

#include <QStandardItem>
#include "CustomItemData.h"

class CustomItem
{
public:
    enum TargetMode{ForSelf,ForALL,ForChildren};
    CustomItem();
    ~CustomItem();
    explicit CustomItem(const QString& name,const QVariant& value,const QString& description = "",const Qt::ItemFlags& aFlags = Qt::NoItemFlags);
    explicit CustomItem(CustomItem *parent);
    explicit CustomItem(const CustomItem *item, CustomItem *parent = 0);

    CustomItem& operator=(const CustomItem& item);

    void addProperty(const CustomItemProperty& property);
    void addProperty(const QString& propertyName, const QVariant& propertyValue,const Qt::ItemFlags& aFlags = Qt::NoItemFlags);
    void setProperty(const QString& propertyName, const QVariant& propertyValue,const Qt::ItemFlags& aFlags = Qt::NoItemFlags);
    CustomItemProperty getProperty(const QString& propertyName) const;
    CustomItemProperty getProperty(int propertyIndex) const;
    QVariant getPropertyValue(int propertyIndex) const;
	QVariant getPropertyValue(const QString& propertyName) const;
    void setPropertyToDefault(int propertyIndex,TargetMode aMode = ForSelf);
    void resetPropertyValue(int propertyIndex,TargetMode aMode = ForSelf);

    const CustomItemData& getData() const;
    void setData(const CustomItemData& data);

    CustomItem *getParent() const;
    void setParent(CustomItem *parent);

    CustomItem *getItem(int getNumber);
    const QList<CustomItem*>& getItems() const;
    void clearItems();

    int getNumber() const;
    CustomItem* addItem(CustomItem* item);
    int itemsCount() const;
    int columnCount() const;

    void setModelItem(QStandardItem* modelItem);
    QStandardItem* getModelItem();

    void setSizes(const QMap<int,QSize>& aSizes,TargetMode aMode = ForALL);
    QSize getSize(int aColumn) const;



private:
    CustomItemData mData;
    QList<CustomItem*> mItems;
	CustomItem* mParent{nullptr};
    QStandardItem* mModelItem;
    QMap<int,QSize> mSizes;

    void clone(const CustomItem   *item);
    void init();
};

extern CustomItem* operator<<(CustomItem* dstItem, CustomItemProperty property);
extern QDataStream& operator<< (QDataStream& stream, const CustomItem* item);
extern QDataStream& operator>> (QDataStream& stream, CustomItem*& item);

Q_DECLARE_METATYPE(CustomItem)
Q_DECLARE_METATYPE(CustomItem*)
