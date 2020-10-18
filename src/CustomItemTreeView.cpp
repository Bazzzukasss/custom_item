#include "CustomItemTreeView.h"
#include "CustomItemTreeModel.h"
#include "CustomItemDelegate.h"
#include <QHeaderView>
#include <QSortFilterProxyModel>
#include <QDebug>

CustomItemTreeView::CustomItemTreeView(QWidget *parent)
    :QTreeView(parent)
{
    init();
}

void CustomItemTreeView::setHeaders(const QStringList &headers)
{
    mModel->setHeaders(headers);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTreeView::setItems(CustomItem *rootItem)
{
    mModel->setItems(rootItem);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTreeView::updateItems(CustomItem *rootItem)
{
    mModel->setItems(rootItem);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTreeView::resizeViewToContents()
{
	for (int i = 0; i < mModel->getHeaders().size(); i++)
		resizeColumnToContents(i);
}

void CustomItemTreeView::setAutoResizeToContents(bool isResize)
{
    mIsAutoResizeToContents = isResize;
}

QItemSelectionModel* CustomItemTreeView::getSelectionModel()
{
	return mSelectionModel;
}

void CustomItemTreeView::changeSelectionModel(QItemSelectionModel *aSelectionModel)
{
	disconnect(mSelectionModel, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(slotCurrentChanged(QModelIndex, QModelIndex)));
	if (mSelectionModel)
		delete mSelectionModel;
	mSelectionModel = aSelectionModel;
	setSelectionModel(mSelectionModel);
	connect(mSelectionModel, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(slotCurrentChanged(QModelIndex, QModelIndex)));
}

CustomItemTreeModel* CustomItemTreeView::getModel()
{
	return mModel;
}


void CustomItemTreeView::refresh()
{
	mModel->refresh();
}


void CustomItemTreeView::setDelegateStyleSheets(const QString& aEditModeStyleSheet,const QString& aShowModeStyleSheet)
{
	mDelegate->setStyleSheets(aEditModeStyleSheet, aShowModeStyleSheet);
}

void CustomItemTreeView::slotCurrentChanged(const QModelIndex& currentIndex, const QModelIndex& previosIndex)
{
    Q_UNUSED(previosIndex)
    if(!currentIndex.isValid())
        return;

    QModelIndex localIndex;
	const QAbstractItemModel *localModel;
	if (!currentIndex.isValid())
		return;
	auto proxyModel = dynamic_cast<const QSortFilterProxyModel*>(currentIndex.model());
	if (proxyModel)
	{
        localIndex = proxyModel->mapToSource(currentIndex);
		localModel = proxyModel->sourceModel();
	}
	else
	{
        localIndex = currentIndex;
		localModel = currentIndex.model();
	}
	auto model = dynamic_cast<const CustomItemTreeModel*>(localModel);
	if (model)
	{
        CustomItem* item = model->getItem(localIndex);
		if (item)
		{
            emit signalCurrentChanged(item, localIndex.row(), localIndex.column());
		}
	}
}

void CustomItemTreeView::slotDoubleClicked(const QModelIndex &currentIndex)
{
    QModelIndex localIndex;
	const QAbstractItemModel *localModel;
    if(!currentIndex.isValid())
        return;
	auto proxyModel = dynamic_cast<const QSortFilterProxyModel*>(currentIndex.model());
	if (proxyModel)
	{
        localIndex = proxyModel->mapToSource(currentIndex);
		localModel = proxyModel->sourceModel();
	}
	else
	{
        localIndex = currentIndex;
		localModel = currentIndex.model();
	}
	auto model = dynamic_cast<const CustomItemTreeModel*>(localModel);
	if (model)
	{
        CustomItem* item = model->getItem(localIndex);
		if (item)
            emit signalDoubleClicked(item, localIndex.row(), localIndex.column());
	}
}


void CustomItemTreeView::slotExpanded(const QModelIndex& currentIndex)
{
    Q_UNUSED(currentIndex)
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTreeView::slotColapsed(const QModelIndex& currentIndex)
{
    Q_UNUSED(currentIndex)
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTreeView::init()
{
    mModel = new CustomItemTreeModel(this);
    mDelegate = new CustomItemDelegate(this);
    mSelectionModel = new QItemSelectionModel(mModel,this);

    setModel(mModel);
    setItemDelegate(mDelegate);
    setSelectionModel(mSelectionModel);
    resizeViewToContents();

    connect(mSelectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)),   this,   SLOT(slotCurrentChanged(QModelIndex,QModelIndex)));
	connect(this, SIGNAL(expanded(QModelIndex)), this, SLOT(slotExpanded(QModelIndex)));
    connect(this, SIGNAL(collapsed(QModelIndex)), this, SLOT(slotColapsed(QModelIndex)));
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotDoubleClicked(QModelIndex)));
}

void CustomItemTreeView::stashExpandStatus()
{
    mExpandStatus.clear();
    for (auto a = model()->index(0, 0); a.isValid(); a = indexBelow(a))
        mExpandStatus.push_back(isExpanded(a));
}

void CustomItemTreeView::applyExpandStatus()
{
    auto it = mExpandStatus.begin();
    for (auto a = model()->index(0, 0); a.isValid() && it != mExpandStatus.end(); a = indexBelow(a))
    {
        if (*it == true)
            expand(a);
        it++;
    }
}
