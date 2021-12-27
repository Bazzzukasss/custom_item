#include "CustomItemTableView.h"
#include "CustomItemTableModel.h"
#include "CustomItemData.h"
#include "CustomItemDelegate.h"

CustomItemTableView::CustomItemTableView(QWidget *parent)
    :QTableView(parent)
{
    init();
}

void CustomItemTableView::setHeaders(const QStringList &headers)
{
    mModel->setHeaders(headers);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTableView::setItems(CustomItem *rootItem)
{
    mModel->setItems(rootItem);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTableView::setItems(const QList<CustomItem> &items)
{
    mModel->setItems(items);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTableView::updateItems(CustomItem *rootItem)
{
    mModel->setItems(rootItem);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTableView::updateItems(const QList<CustomItem> &items)
{
    mModel->setItems(items);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTableView::resizeViewToContents()
{
    resizeColumnsToContents();
    resizeRowsToContents();
}

void CustomItemTableView::setAutoResizeToContents(bool isResize)
{
    mIsAutoResizeToContents = isResize;
}

QItemSelectionModel *CustomItemTableView::getSelectionModel()
{
    return mSelectionModel;
}

CustomItemTableModel *CustomItemTableView::getModel()
{
    return mModel;
}


void CustomItemTableView::refresh()
{
	mModel->refresh();
}

void CustomItemTableView::slotCurrentChanged(QModelIndex currentIndex, QModelIndex previosIndex)
{
    Q_UNUSED(previosIndex)
    if(!currentIndex.isValid())
        return;

    QVariant var=currentIndex.model()->data(currentIndex);
    CustomItemData itemData=var.value<CustomItemData>();

    emit signalCurrentChanged(itemData, currentIndex.row(), currentIndex.column());
}

void CustomItemTableView::init()
{
    mModel = new CustomItemTableModel(this);
    mDelegate = new CustomItemDelegate(this);
    mSelectionModel = new QItemSelectionModel(mModel,this);

    setModel(mModel);
    setItemDelegate(mDelegate);
    setShowGrid(false);
    setSelectionModel(mSelectionModel);
    resizeViewToContents();

    connect(mSelectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)),   this,   SLOT(slotCurrentChanged(QModelIndex,QModelIndex)));
}
