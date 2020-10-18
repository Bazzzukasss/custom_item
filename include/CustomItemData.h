#pragma once

#include <QMap>
#include <QString>
#include <QVariant>
#include <QVector>
#include <QList>

struct CustomItemProperty
{
    CustomItemProperty(const QString& name, const QVariant& value,const Qt::ItemFlags& aFlags = Qt::NoItemFlags)
        :mName(name),mValue(value),mFlags(aFlags)
    {}
    CustomItemProperty(){}

    void setToDefault();
    void resetValue();
	QString getValueAsText();

    QString     mName;
    QVariant    mValue;
    Qt::ItemFlags mFlags;
};

class CustomItemData
{
public:
    CustomItemData();
    void addProperty(const CustomItemProperty& property);
    void addProperty(const QString& aName, const QVariant& aValue, const Qt::ItemFlags& aFlags = Qt::NoItemFlags);

    void setProperty(const QString& aName, const QVariant& aValue, const Qt::ItemFlags& aFlags = Qt::NoItemFlags);
    void setProperty(int aIndex, const QVariant& aValue);
    void setPropertyToDefault(int aIndex);
    void resetPropertyValue(int aIndex);

    int getPropertiesCount() const;
	QStringList getProperties() const;
    CustomItemProperty getProperty(const QString& aName) const;
    CustomItemProperty getProperty(int aIndex) const;
    int getPropertyIndex(const QString& aName) const;
    bool isPropertyExists(const QString& aName) const;

private:
    QVector<CustomItemProperty> mProperties;
    QMap<QString,int> mIndexes;
    int mPropertiesCount{0};
};

Q_DECLARE_METATYPE(CustomItemData)
Q_DECLARE_METATYPE(CustomItemData*)
