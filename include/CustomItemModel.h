#pragma once

#include <QStandardItemModel>
#include "CustomItemClasses.h"

class CustomItemModel : public QStandardItemModel
{
public:
    explicit CustomItemModel(QObject *parent = Q_NULLPTR);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    void setItems(CustomItem* rootItem);
    void updateItems(CustomItem* rootItem);
    void updateItem(CustomItem* customItem);
    void setHeaders(const QStringList& headers);
};
