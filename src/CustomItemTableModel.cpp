#include "CustomItemTableModel.h"
#include "CustomItemData.h"
#include "CustomItem.h"

CustomItemTableModel::CustomItemTableModel(QObject *parent)
    :QAbstractTableModel(parent)
{
}

int CustomItemTableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid()?0:mItems.count();
}

int CustomItemTableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid()?0:mHeaders.count();
}

bool CustomItemTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()||role!=Qt::EditRole)
        return false;
    if( index.row()<0 || index.row()>mItems.count() || index.column()<0 || index.column()>mHeaders.count()-1)
        return false;

    CustomItemData data=value.value<CustomItemData>();
    mItems[index.row()].setData(data);

    emit dataChanged(index,index);
    return true;
}

bool CustomItemTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(value)
    Q_UNUSED(role)
    return false;
}

bool CustomItemTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    beginInsertRows(QModelIndex(),row,row+count-1);
    for(int i=0;i<count;i++)
        mItems.insert(0,CustomItem());
    endInsertRows();
    return true;
}

Qt::ItemFlags CustomItemTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    Qt::ItemFlags flags = QAbstractItemModel::flags(index) | mFlags;

    return flags;
}

QVariant CustomItemTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if( index.row()<0 || index.row()>mItems.count() || index.column()<0 || index.column()>mHeaders.count()-1)
        return false;

    if( role != Qt::DisplayRole && role!= Qt::EditRole)
        return QVariant();

    CustomItemData data = mItems.at(index.row()).getData();
    QVariant value = data.getProperty(index.column()).mValue;
    switch(value.type())
    {
        case QVariant::Type::String :
        case QVariant::Type::Int :
        case QVariant::Type::Double :
            return value;
        break;
        default:
            return QVariant().fromValue(data);
        break;
    }

}

QVariant CustomItemTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role!=Qt::DisplayRole)
        return QVariant();
    if(orientation==Qt::Horizontal)
        return mHeaders[section];
    else
        return section+1;
    return QVariant();
}

CustomItem CustomItemTableModel::getItem(const QModelIndex &index) const
{
    if(!index.isValid())
        return CustomItem();

    if( index.row()<0 || index.row()>mItems.count() || index.column()<0 || index.column()>mHeaders.count()-1)
        return CustomItem();


    return mItems.at(index.row());
}

void CustomItemTableModel::setItems(CustomItem* rootItem)
{
    beginResetModel();
    mItems.clear();

    for(auto it : rootItem->getItems())
    {
        CustomItem item;
        item.setData(it->getData());
        mItems.append(item);
    }
    endResetModel();
    if(rootItem != 0 )
        delete rootItem;
}

void CustomItemTableModel::setItems(const QList<CustomItem> &items)
{
    beginResetModel();
    mItems = items;
    endResetModel();
}

void CustomItemTableModel::setHeaders(const QStringList &headers)
{
    mHeaders = headers;
}

void CustomItemTableModel::refresh()
{
    emit dataChanged(QModelIndex(),QModelIndex());
}
