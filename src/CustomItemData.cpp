#include "CustomItemData.h"
#include "CustomItemTypes.h"

CustomItemData::CustomItemData(){}

void CustomItemData::addProperty(const CustomItemProperty &property)
{
    if(!mIndexes.contains(property.mName))
    {
        mProperties.push_back( property );
        mIndexes[property.mName] = mPropertiesCount;
        ++mPropertiesCount;
    }
}

void CustomItemData::addProperty(const QString &aName, const QVariant &aValue, const Qt::ItemFlags& aFlags)
{
    addProperty(CustomItemProperty(aName,aValue,aFlags));
}

void CustomItemData::setProperty(const QString &aName, const QVariant &aValue, const Qt::ItemFlags& aFlags)
{
    if (mIndexes.contains(aName))
	{
        int index = mIndexes[aName];
        mProperties[index].mValue = aValue;
        mProperties[index].mFlags = aFlags;
	}
	else
        addProperty(aName, aValue, aFlags);
}

void CustomItemData::setProperty(int aIndex, const QVariant &aValue)
{
    if( (0 <= aIndex) && (aIndex < mPropertiesCount) )
        mProperties[aIndex].mValue = aValue;
}

void CustomItemData::setPropertyToDefault(int aIndex)
{
    if( (0 <= aIndex) && (aIndex < mPropertiesCount) )
        mProperties[aIndex].setToDefault();
}

void CustomItemData::resetPropertyValue(int aIndex)
{
    if( (0 <= aIndex) && (aIndex < mPropertiesCount) )
        mProperties[aIndex].resetValue();
}

int CustomItemData::getPropertiesCount() const
{
    return mPropertiesCount;
}

QStringList CustomItemData::getProperties() const
{
	QStringList list;
	for (auto& p : mProperties)
		list << p.mName;
    return list;
}




CustomItemProperty CustomItemData::getProperty(const QString &aName) const
{
    if(mIndexes.contains(aName))
    {
        int index = mIndexes[aName];
        return mProperties[index];
    }
    return CustomItemProperty();
}

CustomItemProperty CustomItemData::getProperty(int aIndex) const
{
    if( (0 <= aIndex) && (aIndex < mPropertiesCount) )
        return mProperties[aIndex];
    return CustomItemProperty();
}

int CustomItemData::getPropertyIndex(const QString &aName) const
{
    if(mIndexes.contains(aName))
        return mIndexes[aName];
    else
        return -1;
}

bool CustomItemData::isPropertyExists(const QString &aName) const
{
    return mIndexes.contains(aName);
}

void CustomItemProperty::setToDefault()
{
	switch (mValue.type())
	{
		case QVariant::Type::String:
		case QVariant::Type::Int:
		case QVariant::Type::Double:
		case QVariant::Type::Bool:
		default:
		{
			QString typeName(mValue.typeName());

			if (typeName == "SIInteger")
			{
				auto data = mValue.value<SIInteger>();
				data.setToDefault();
				mValue = QVariant().fromValue(data);
			}

			if (typeName == "SIDouble")
			{
				auto data = mValue.value<SIDouble>();
				data.setToDefault();
				mValue = QVariant().fromValue(data);
			}

			if (typeName == "SIBoolean")
			{
				auto data = mValue.value<SIBoolean>();
				data.setToDefault();
				mValue = QVariant().fromValue(data);
			}

			if (typeName == "SIString")
			{
				auto data = mValue.value<SIString>();
				data.setToDefault();
				mValue = QVariant().fromValue(data);
			}

			if (typeName == "SIText")
			{
				auto data = mValue.value<SIText>();
				data.setToDefault();
				mValue = QVariant().fromValue(data);
			}

			if (typeName == "SIStringList")
			{
				auto data = mValue.value<SIStringList>();
				data.setToDefault();
				mValue = QVariant().fromValue(data);
			}

			if (typeName == "SIBooleanList")
			{
				auto data = mValue.value<SIBooleanList>();
				data.setToDefault();
				mValue = QVariant().fromValue(data);
			}

			if (typeName == "SIProgress") {}
			if (typeName == "SILcd") {}
			if (typeName == "SIBars") {}
			if (typeName == "SIGraph") {}
			if (typeName == "SIImage") {}
		}
		break;
	}
}

void CustomItemProperty::resetValue()
{
	switch (mValue.type())
	{
	case QVariant::Type::String:
	case QVariant::Type::Int:
	case QVariant::Type::Double:
	case QVariant::Type::Bool:
		break;

	default:
	{
		QString typeName(mValue.typeName());

		if (typeName == "SIInteger")
		{
			auto data = mValue.value<SIInteger>();
			data.resetValue();
			mValue = QVariant().fromValue(data);
		}

		if (typeName == "SIDouble")
		{
			auto data = mValue.value<SIDouble>();
			data.resetValue();
			mValue = QVariant().fromValue(data);
		}

		if (typeName == "SIBoolean")
		{
			auto data = mValue.value<SIBoolean>();
			data.resetValue();
			mValue = QVariant().fromValue(data);
		}

		if (typeName == "SIString")
		{
			auto data = mValue.value<SIString>();
			data.resetValue();
			mValue = QVariant().fromValue(data);
		}

		if (typeName == "SIText")
		{
			auto data = mValue.value<SIText>();
			data.resetValue();
			mValue = QVariant().fromValue(data);
		}

		if (typeName == "SIStringList")
		{
			auto data = mValue.value<SIStringList>();
			data.resetValue();
			mValue = QVariant().fromValue(data);
		}

		if (typeName == "SIBooleanList")
		{
			auto data = mValue.value<SIBooleanList>();
			data.resetValue();
			mValue = QVariant().fromValue(data);
		}

		if (typeName == "SIProgress") {}
		if (typeName == "SILcd") {}
		if (typeName == "SIBars") {}
		if (typeName == "SIGraph") {}
		if (typeName == "SIImage") {}
	}
	break;
	}
}

QString CustomItemProperty::getValueAsText()
{
	switch (mValue.type())
	{
	case QVariant::Type::String:
	case QVariant::Type::Int:
	case QVariant::Type::Double:
	case QVariant::Type::Bool:
		return mValue.toString();
	break;

	default:
	{
		QString typeName(mValue.typeName());

		if (typeName == "SIInteger")
			return QString::number(mValue.value<SIInteger>().getValue()) + mValue.value<SIInteger>().getSuffix();

		if (typeName == "SIDouble")
			return QString::number(mValue.value<SIDouble>().getValue()) + mValue.value<SIDouble>().getSuffix();

		if (typeName == "SIBoolean")
		{
			if (mValue.value<SIBoolean>().getValue() == true)
				return "true";
			else
				return "false";
		}

		if (typeName == "SIString")
			return mValue.value<SIString>().getValue();

		if (typeName == "SIText")
			return mValue.value<SIText>().getValue();

		if (typeName == "SIStringList")
			return mValue.value<SIStringList>().getText();

		if (typeName == "SIBooleanList")
			return mValue.value<SIBooleanList>().getText();

		if (typeName == "SIProgress") return "";
		if (typeName == "SILcd") return "";
		if (typeName == "SIBars") return "";
		if (typeName == "SIGraph") return "";
		if (typeName == "SIImage") return "";
	}
		break;
	}
	
	return "";
}
