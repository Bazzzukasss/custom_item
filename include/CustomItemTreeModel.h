#pragma once

#include <QAbstractItemModel>
#include "CustomItemClasses.h"

class CustomItemTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    CustomItemTreeModel(QObject *parent = 0);
    CustomItemTreeModel(CustomItem *rootItem,QObject *parent = 0);
    ~CustomItemTreeModel();

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    CustomItem *getItem(const QModelIndex &index) const;
	CustomItem *getRootItem()const;
    void setItems(CustomItem* items);
    void updateItems(CustomItem* items);
    void setHeaders(const QStringList& headers);
    const QStringList& getHeaders();
    void refresh();
    void setFlags(Qt::ItemFlags aFlags);

    Qt::DropActions supportedDropActions() const;
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

private:
	CustomItem* mRootItem{nullptr};
    QStringList mHeaders;
    Qt::ItemFlags mFlags;
};
