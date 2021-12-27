#include "CustomItemModel.h"
#include "CustomItemData.h"
#include "CustomItem.h"

CustomItemModel::CustomItemModel(QObject *parent)
    :QStandardItemModel(parent)
{
}

Qt::ItemFlags CustomItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    return flags;
}

void CustomItemModel::setItems(CustomItem *rootItem)
{
    removeRows(0,rowCount());

    for(auto it : rootItem->getItems())
    {
        QList<QStandardItem *> row;
        for(int p = 0;p< it->getData().getPropertiesCount();++p)
        {
            auto item = new QStandardItem();
            item->setEditable(false);
            QVariant var = QVariant().fromValue(it->getData());
            item->setData(QVariant(var),Qt::DisplayRole);
            row << item;
            if(p == 0)
                it->setModelItem(item);
        }
        appendRow(row);        
    }
}

void CustomItemModel::updateItems(CustomItem *rootItem)
{
    for(auto it : rootItem->getItems())
        updateItem(it);
}

void CustomItemModel::updateItem(CustomItem *customItem)
{
    QStandardItem* pModelItem = customItem->getModelItem();

    if(pModelItem != nullptr)
    {
        int row = pModelItem->row();
        int colCount = qMin(customItem->getData().getPropertiesCount(),columnCount());

        for(int column = 0;column< colCount;++column)
        {
            QVariant var = QVariant().fromValue(customItem->getData());
            this->item(row,column)->setData(var,Qt::DisplayRole);
        }
    }
}

void CustomItemModel::setHeaders(const QStringList &headers)
{
    setHorizontalHeaderLabels(headers);
}
