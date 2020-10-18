#include "CustomItemTreeModel.h"
#include "CustomItemData.h"
#include "CustomItem.h"
#include <QDebug>
#include <QMimeData>

static const char* CustomItemMimeType = "CustomItemPointer";

CustomItemTreeModel::CustomItemTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}
CustomItemTreeModel::CustomItemTreeModel(CustomItem *rootItem, QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = rootItem;
}

CustomItemTreeModel::~CustomItemTreeModel()
{
	/*
	if (mRootItem != nullptr)
	{
		delete mRootItem;
		mRootItem = nullptr;
	}
	*/
}

QVariant CustomItemTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    CustomItem *item = getItem(index);

    if(item == 0)
        return QVariant();

    return QVariant().fromValue(item->getData());
}

bool CustomItemTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    CustomItem *item = getItem(index);
    if(item == 0)
        return false;

    CustomItemData data = value.value<CustomItemData>();
    item->setData(data);
    emit dataChanged(index, index);

    return true;
}

QVariant CustomItemTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		if (section >= mHeaders.size())
			section = mHeaders.size() - 1;
		return mHeaders[section];
	}

    return QVariant();
}

bool CustomItemTreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(value)
    Q_UNUSED(role)
    return false;
}

int CustomItemTreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return mHeaders.size();
}

Qt::ItemFlags CustomItemTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    Qt::ItemFlags flags = QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | mFlags;

    CustomItem* item = getItem(index);
    flags |= item->getProperty(index.column()).mFlags;

    return flags;
}

CustomItem *CustomItemTreeModel::getItem(const QModelIndex &index) const
{
    if(mRootItem == 0)
        return 0;

    if (!index.isValid())
        return mRootItem;

    CustomItem *item = static_cast<CustomItem*>(index.internalPointer());

    if (item)
        return item;
    else
        return 0;
}


CustomItem * CustomItemTreeModel::getRootItem() const
{
	return mRootItem;
}

QModelIndex CustomItemTreeModel::index(int row, int column, const QModelIndex &parent) const
{

    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    CustomItem *mParent = getItem(parent);

    if(!mParent)
        return QModelIndex();

    CustomItem *childItem = mParent->getItem(row);

    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex CustomItemTreeModel::parent(const QModelIndex &index) const
{

    if (!index.isValid())
        return QModelIndex();

    CustomItem *childItem = getItem(index);

    if(childItem == 0)
        return QModelIndex();

    CustomItem *mParent = childItem->getParent();

    if (mParent == mRootItem)
        return QModelIndex();

    return createIndex(mParent->getNumber(), 0, mParent);
}

int CustomItemTreeModel::rowCount(const QModelIndex &parent) const
{
    CustomItem *mParent = getItem(parent);
    if(mParent !=0)
        return mParent->itemsCount();
    else
        return 0;
}
void CustomItemTreeModel::updateItems(CustomItem* items)
{
    Q_UNUSED(items)
    refresh();
}

void CustomItemTreeModel::setItems(CustomItem* items)
{
    beginResetModel();
    if(mRootItem != nullptr )
        delete mRootItem;
    mRootItem = items;
    endResetModel();
}

void CustomItemTreeModel::setHeaders(const QStringList &headers)
{
	
	if (mHeaders.size() != headers.size())
	{
		beginResetModel();
		mHeaders = headers;
		endResetModel();
	}
	else
		mHeaders = headers;
    
	emit dataChanged(QModelIndex(), QModelIndex());
}

const QStringList& CustomItemTreeModel::getHeaders()
{
    return mHeaders;
}

void CustomItemTreeModel::refresh()
{
    emit dataChanged(QModelIndex(),QModelIndex());
}

void CustomItemTreeModel::setFlags(Qt::ItemFlags aFlags)
{
    mFlags = aFlags;
}

Qt::DropActions CustomItemTreeModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

QStringList CustomItemTreeModel::mimeTypes() const
{
    QStringList types;
    types << CustomItemMimeType;
    return types;
}

QMimeData *CustomItemTreeModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData* mimeData = new QMimeData();
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    QSet<CustomItem*> items;

    foreach(QModelIndex index, indexes)
        items.insert( getItem(index) );

    stream << items;
    qDebug() << "mimeData:"<< items;
    mimeData->setData(CustomItemMimeType, encodedData);
    return mimeData;
}

bool CustomItemTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    QSet<CustomItem*> items;
    Q_UNUSED(row);
    Q_UNUSED(column);
    Q_UNUSED(parent);
    if(action==Qt::IgnoreAction) return true;
    if(!data->hasFormat(CustomItemMimeType)) return false;
    if(action!=Qt::MoveAction) return true;
    //
    QByteArray encodedData = data->data(CustomItemMimeType);
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    stream >> items;
    qDebug() << "dropData:" << items <<" to: " << row << column << parent.row() << parent.column();
    return true;
}
