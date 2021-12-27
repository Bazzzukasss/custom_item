#ifndef CUSTOMITEMPROPERTIESVIEW_H
#define CUSTOMITEMPROPERTIESVIEW_H

#include <QFrame>
#include <QStringList>
#include <QVector>
#include "CustomItemClasses.h"

class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLabel;

class CustomItemPropertiesViewHeader : public QFrame {
    Q_OBJECT
public:
    CustomItemPropertiesViewHeader(const QString &aCaption, QWidget * parent = Q_NULLPTR);

    void setCaption(const QString& aCaption);

signals:
    void signalSwitchClicked(bool aIsVisibile);

private:
    QLabel* mpLabelCaption;
    QPushButton* mpButtonSwitch;
    QHBoxLayout* mpLayout;
};


class CustomItemPropertiesView : public QFrame {
	Q_OBJECT

public:
	CustomItemPropertiesView(QWidget * parent = Q_NULLPTR);
    ~CustomItemPropertiesView();

    void setItem(CustomItem* aItem);
    void setCaption(const QString& aCaption);
    void setPropertyMask(const QStringList& aMask);

private:
    CustomItem* mpItem;
    CustomItemPropertiesViewHeader* mpHeader;
    QFrame* mpContent;
    QVBoxLayout* mpLayout;
    QVBoxLayout* mpContentLayout;
    QStringList mPropertyMask;

    QVector<QWidget*> mWidgets;

    void initialize();
    void createUI();
    void deleteUI();
    void addWidget(CustomItemData* aData, const QString& aPropertyName);
};

#endif //CUSTOMITEMPROPERTIESVIEW_H
