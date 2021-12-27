#ifndef CUSTOMITEMPROPERTYWIDGET_H
#define CUSTOMITEMPROPERTYWIDGET_H

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include "CustomItemClasses.h"
#include "CustomItemData.h"

class CustomItemPropertyWidget : public QFrame {
	Q_OBJECT

public:
    CustomItemPropertyWidget(CustomItemData *aData, const QString &aPropertyName, QWidget * parent = Q_NULLPTR);

private:
    CustomItemData* mpData;
    QLabel* mpLabelCaption;
    CustomItemWidget* mpWidget;
    QHBoxLayout* mpLayout;
};

#endif // CUSTOMITEMPROPERTYWIDGET_H
