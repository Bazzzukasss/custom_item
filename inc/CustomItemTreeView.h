#pragma once

#include <QObject>
#include <QTreeView>
#include "CustomItemClasses.h"

class CustomItemTreeView : public QTreeView
{
    Q_OBJECT
public:
    CustomItemTreeView(QWidget *parent = Q_NULLPTR);
    void setHeaders(const QStringList& headers);
    void setItems(CustomItem* rootItem);
    void updateItems(CustomItem* rootItem);
    void resizeViewToContents();
    void setAutoResizeToContents(bool isResize);
	void changeSelectionModel(QItemSelectionModel *aSelectionModel);
	QItemSelectionModel* getSelectionModel();
    CustomItemTreeModel* getModel();
	void refresh();
	void setDelegateStyleSheets(const QString& aEditModeStyleSheet, const QString& aShowModeStyleSheet);
    void stashExpandStatus();
    void applyExpandStatus();
public slots:
    void slotCurrentChanged(const QModelIndex& currentIndex,const QModelIndex& previosIndex);
    void slotDoubleClicked(const QModelIndex& currentIndex);
	void slotExpanded(const QModelIndex& currentIndex);
    void slotColapsed(const QModelIndex& currentIndex);

signals:
    void signalCurrentChanged(CustomItem* item,int row, int column);
    void signalDoubleClicked(CustomItem* item,int row, int column);

private:
    CustomItemTreeModel* mModel;
    CustomItemDelegate* mDelegate;
    QItemSelectionModel* mSelectionModel;
    QVector<bool> mExpandStatus;
    bool mIsAutoResizeToContents{true};
    void init();
};
