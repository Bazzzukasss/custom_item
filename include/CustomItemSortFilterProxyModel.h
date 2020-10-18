#pragma once

#include <QSortFilterProxyModel>
#include "CustomItemClasses.h"

class CustomItemSortFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	CustomItemSortFilterProxyModel(QObject *parent = 0);
	void refresh();
	
	void setIsShowAll(bool isShowAll);
	void setIsEqual(bool isEqual);
	void setFilterProperty(QPair<QString, QString> pairNameValue);
	void setSortingProperty(const QString& propertyName);

protected:
	bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
	bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;

private:
	QString mSortingPropertyName{ "Alias" };
	QString mFilterPropertyName{ "Group" };
	QString mFilterPropertyValue{ "gr1" };
	bool mIsShowAll{ true };
	bool mIsEqual{ true };

	CustomItemData getCustomItemData(const QModelIndex & ind) const;
};

