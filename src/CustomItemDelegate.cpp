#include "CustomItem.h"
#include "CustomItemDelegate.h"
#include "CustomItemData.h"
#include "CustomItemWidget.h"
#include <QPainter>
#include <QDebug>
#include "CustomItemTreeModel.h"
#include <QSortFilterProxyModel>

CustomItemDelegate::CustomItemDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{
    mWidget=new CustomItemWidget();
}

CustomItemDelegate::~CustomItemDelegate()
{
    delete mWidget;
}

void CustomItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QColor selectColor(0, 0, 0x99, 20),overColor(0x99, 0x99, 0x99, 20);
    bool isCustomPaint(true);
    if(!index.isValid())
        return;

    mWidget->setCurrentPropertyIndex( index.column() );
    QVariant var=index.model()->data(index);

    if(var.isValid())
    {
        QString typeName(var.typeName());

        if(typeName == "CustomItemData")
        {
            CustomItemData data=var.value<CustomItemData>();
            QVariant value = data.getProperty(index.column()).mValue;

            if(mPropertyMask.isEmpty())
            {
                if( (value.type() == QVariant::Type::String)||(value.type() == QVariant::Type::Int)||(value.type() == QVariant::Type::Double) )
                {
                    if (option.state & QStyle::State_MouseOver)
                        painter->fillRect(option.rect, overColor);
                    if (option.state & QStyle::State_Selected)
                        painter->fillRect(option.rect, selectColor);

                    painter->drawText(option.rect,value.toString());
                    isCustomPaint = false;
                }
            }

            if(isCustomPaint == true)
            {
                mWidget->setStyleOption(option);
                mWidget->setData(data);
                mWidget->setFixedSize(option.rect.width(),option.rect.height());
                QPixmap pixmap(mWidget->size());
                mWidget->render(&pixmap);
                painter->drawPixmap(option.rect,pixmap);

				if (!mPropertyMask.isEmpty())
				{
					if (option.state & QStyle::State_MouseOver)
						painter->fillRect(option.rect, overColor);
					
					if (option.state & QStyle::State_Selected)
						painter->fillRect(option.rect, selectColor);
					else
					//if (option.state & QStyle::State_Enabled)
					{
                        QColor bgColor= QColor(data.getProperty("Color").mValue.value<QColor>());
						painter->fillRect(option.rect, bgColor);
					}
				}

            }
        }
        else
            QStyledItemDelegate::paint(painter,option,index);
    }
}

QSize CustomItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if ((mItemSize.isEmpty()) && index.isValid())
	{
        CustomItem *item;
		auto proxyModel = dynamic_cast<const QSortFilterProxyModel*>(index.model());
		if (proxyModel)
            item = static_cast<CustomItem*>(proxyModel->mapToSource(index).internalPointer());
		else
            item = static_cast<CustomItem*>(index.internalPointer());

		if (item)
		{
			auto size = item->getSize(index.column());
			if (!size.isEmpty())
				return size;
		}
    }
	else
		return mItemSize;
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *CustomItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    CustomItemWidget* pEditor=new CustomItemWidget(parent);
    pEditor->setEditMode(true);
	pEditor->setStyleSheets(mEditModeStyleSheet, mShowModeStyleSheet);
    connect(pEditor,SIGNAL(signalCommit()),this,SLOT(slotCommit()));
    return pEditor;
}

void CustomItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    CustomItemWidget* pEditor=qobject_cast<CustomItemWidget*>(editor);
    CustomItemData data = index.model()->data(index).value<CustomItemData>();
    pEditor->setCurrentPropertyIndex( index.column() );
    pEditor->setData(data);
}

void CustomItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    CustomItemWidget* pEditor=qobject_cast<CustomItemWidget*>(editor);
    model->setData(index,QVariant().fromValue(pEditor->getData()));
}

void CustomItemDelegate::setPropertyMask(const QStringList &mask)
{
    mWidget->setPropertyMask(mask);
    mPropertyMask = mask;
}

void CustomItemDelegate::setItemsSize(const QSize &size)
{
    mItemSize = size;
}


void CustomItemDelegate::setStyleSheets(const QString& aEditModeStyleSheet, const QString& aShowModeStyleSheet)
{
	mEditModeStyleSheet = aEditModeStyleSheet;
	mShowModeStyleSheet = aShowModeStyleSheet;
	//mWidget->setStyleSheets(aEditModeStyleSheet, aShowModeStyleSheet);
}

void CustomItemDelegate::slotCommit()
{
    QWidget* pEditor=qobject_cast<QWidget*>(sender());
    emit commitData(pEditor);
    emit closeEditor(pEditor);
}
