#pragma once

#include <QObject>
#include <QFrame>
#include <QRadioButton>
#include <QVBoxLayout>
#include "CustomItemClasses.h"

class CustomItemTableMonitor : public QFrame
{
    Q_OBJECT
public:
    CustomItemTableMonitor(QWidget* parent = 0);
    void updateItems(CustomItem* rootItem);
    void updateItems(const QList<CustomItem>& items);
    void setItems(CustomItem* rootItem);
    void setItems(const QList<CustomItem>& items);
    void setHeaders(const QStringList& headers);
	void setCaptionVisible(bool isVisible);
    CustomItemTableView *getView();
    void refresh();

public slots:
    void slotUpdateItems(CustomItem* rootItem);
    void slotUpdateItems(const QList<CustomItem>& items);
    void slotSetItems(CustomItem* rootItem);
    void slotSetItems(const QList<CustomItem>& items);
    void slotSetHeaders(const QStringList& headers);
    void slotResizeViewToContents();
	void setCaption(const QString &text);

signals:
    void signalCurrentChanged(CustomItemData& data,int row, int column);

private:
    CustomItemTableView* mView;
    QRadioButton* mCaption;
    QVBoxLayout* mLayout;    

    void build();
    void init();
};
