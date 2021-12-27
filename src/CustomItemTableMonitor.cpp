#include <QHeaderView>
#include "CustomItemTableMonitor.h"
#include "CustomItemTableView.h"
#include "CustomItemTableModel.h"

CustomItemTableMonitor::CustomItemTableMonitor(QWidget *parent)
    :QFrame(parent)
{
    init();
    build();
}

void CustomItemTableMonitor::init()
{
    mView = new CustomItemTableView(this);
    mCaption = new QRadioButton("Table Monitor",this);
    mLayout = new QVBoxLayout(this);

    connect(mView, SIGNAL(signalCurrentChanged(CustomItemData&,int,int)), this,   SIGNAL(signalCurrentChanged(CustomItemData&,int,int)));
}

void CustomItemTableMonitor::build()
{
    mLayout->setMargin(0);
    mLayout->setSpacing(0);
    mLayout->addWidget(mCaption);
    mLayout->addWidget(mView);
    mCaption->setChecked(false);
    mView->resizeViewToContents();
    mView->setAlternatingRowColors(true);
    mView->verticalHeader()->hide();
    mView->horizontalHeader()->setStretchLastSection(true);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    setHeaders({"NAME","VALUE","DESC","TEST"});
}

void CustomItemTableMonitor::setHeaders(const QStringList &headers)
{
    mView->setHeaders(headers);
}

void CustomItemTableMonitor::setCaptionVisible(bool isVisible)
{
    mCaption->setVisible(isVisible);
}

CustomItemTableView *CustomItemTableMonitor::getView()
{
    return mView;
}

void CustomItemTableMonitor::refresh()
{
    mView->refresh();
}

void CustomItemTableMonitor::setItems(CustomItem* rootItem)
{
    mView->setItems(rootItem);    
}

void CustomItemTableMonitor::setItems(const QList<CustomItem> &items)
{
    mView->setItems(items);
}
void CustomItemTableMonitor::updateItems(CustomItem* rootItem)
{
    mView->updateItems(rootItem);
}

void CustomItemTableMonitor::updateItems(const QList<CustomItem> &items)
{
    mView->updateItems(items);
}
//SLOTS
void CustomItemTableMonitor::slotSetHeaders(const QStringList &headers)
{
    setHeaders(headers);
}

void CustomItemTableMonitor::slotResizeViewToContents()
{
    mView->resizeViewToContents();
}

void CustomItemTableMonitor::setCaption(const QString &text)
{
	mCaption->setText(text);
}

void CustomItemTableMonitor::slotUpdateItems(CustomItem* rootItem)
{
    updateItems(rootItem);
    mCaption->setChecked( !mCaption->isChecked() );
}

void CustomItemTableMonitor::slotUpdateItems(const QList<CustomItem> &items)
{
    updateItems(items);
    mCaption->setChecked( !mCaption->isChecked() );
}
void CustomItemTableMonitor::slotSetItems(CustomItem* rootItem)
{
    setItems(rootItem);
}

void CustomItemTableMonitor::slotSetItems(const QList<CustomItem> &items)
{
    setItems(items);
}



