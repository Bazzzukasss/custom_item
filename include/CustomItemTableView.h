#pragma once

#include <QObject>
#include <QTableView>
#include "CustomItemClasses.h"

class CustomItemTableView : public QTableView
{
    Q_OBJECT
public:
    CustomItemTableView(QWidget *parent = Q_NULLPTR);
    void setHeaders(const QStringList& headers);
    void setItems(CustomItem* rootItem);
    void setItems(const QList<CustomItem>& items);
    void updateItems(CustomItem* rootItem);
    void updateItems(const QList<CustomItem>& items);
    void resizeViewToContents();
    void setAutoResizeToContents(bool isResize);
    QItemSelectionModel* getSelectionModel();
    CustomItemTableModel* getModel();
	void refresh();

public slots:
    void slotCurrentChanged(QModelIndex currentIndex,QModelIndex previosIndex);

signals:
    void signalCurrentChanged(CustomItemData& data,int row, int column);
    void signalCurrentChanged(CustomItem* item,int row, int column);

private:
    CustomItemTableModel* mModel;
    CustomItemDelegate* mDelegate;
    QItemSelectionModel* mSelectionModel;
    bool mIsAutoResizeToContents{true};
    void init();
};
