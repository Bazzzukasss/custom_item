#pragma once

#include <QStyledItemDelegate>
#include "CustomItemClasses.h"

class CustomItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CustomItemDelegate(QObject* parent =0);

    ~CustomItemDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void setPropertyMask(const QStringList& mask);
    void setItemsSize(const QSize& size);

	void setStyleSheets(const QString& aEditModeStyleSheet, const QString& aShowModeStyleSheet);

public slots:
    void slotCommit();

private:
    CustomItemWidget* mWidget;
    QStringList mPropertyMask;
    QSize mItemSize;
	QString mEditModeStyleSheet;
	QString mShowModeStyleSheet;
};
