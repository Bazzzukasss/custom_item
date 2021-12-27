#pragma once

#include <QObject>
#include <QFrame>
#include <QRadioButton>
#include <QVBoxLayout>
#include "CustomItemClasses.h"

class CustomItemTreeMonitor : public QFrame
{
    Q_OBJECT
public:
    CustomItemTreeMonitor(QWidget* parent = 0);
    void updateItems(CustomItem* rootItem);
    void setItems(CustomItem* rootItem);
    void setHeaders(const QStringList& headers);
    void setCaption(const QString& text);
    void setCaptionVisible(bool isVisible);
    void setAutoResizeToContents(bool isAutoResize);
    CustomItemTreeView *getView();
    void refresh();

public slots:
    void slotUpdateItems(CustomItem* rootItem);
    void slotSetItems(CustomItem* rootItem);
    void slotSetHeaders(const QStringList& headers);
    void slotResizeViewToContents();

signals:
    void signalCurrentChanged(CustomItem* item,int row, int column);
    void signalDoubleClicked(CustomItem* item,int row, int column);

private:
    CustomItemTreeView* mView;
    QRadioButton* mCaption;
    QVBoxLayout* mLayout;

    void build();
    void init();
};
