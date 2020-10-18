#pragma once

#include <QAbstractTableModel>
#include "CustomItemClasses.h"

class CustomItemTableModel : public QAbstractTableModel
{
public:
    explicit CustomItemTableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);

    bool insertRows(int row, int count, const QModelIndex &parent);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    CustomItem getItem(const QModelIndex &index) const;

    void setItems(CustomItem* rootItem);
    void setItems(const QList<CustomItem>& items);
    void setHeaders(const QStringList& headers);
    void refresh();
    void setFlags(Qt::ItemFlags aFlags);
private:
    QList<CustomItem> mItems;
    QStringList mHeaders;
    Qt::ItemFlags mFlags;
};
