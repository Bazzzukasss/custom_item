#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QStyleOptionViewItem>
#include "CustomItemClasses.h"
#include "CustomItemData.h"

class CustomItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomItemWidget(QWidget *parent = 0);
    explicit CustomItemWidget(CustomItemData data, QWidget *parent = 0);
    explicit CustomItemWidget(CustomItemData data, int propertyIndex, bool editMode, QWidget *parent = 0);
    ~CustomItemWidget();

    void setStyleOption(const QStyleOptionViewItem &option);
    void setData(CustomItemData data);
    CustomItemData getData() const;
    void setCurrentPropertyIndex(int propertyIndex);
    void setPropertyMask(const QStringList& mask);
    void setEditMode(bool aEditMode);
	void setStyleSheets(const QString& aEditModeStyleSheet,const QString& aShowModeStyleSheet);

signals:
    void signalCommit();
    void signalSelected();
    void signalEditingFinished(const CustomItemData& aData);

private slots:
    void slotEditingFinished(QVariant aValue);
    void slotEditingFinished(QString aValue);
    void slotEditingFinished(int aValue);
    void slotEditingFinished(double aValue);
    void slotEditingFinished(bool aValue);

private:
    CustomItemData mData;
    int mCurrentPropertyIndex;
    void build();
    void showValue(const CustomItemProperty &aProperty);
    void init();
    void clear();
	void applyStyleSheet(QWidget* aWidget);

    QVector<QWidget*> mWidgets;
    QVBoxLayout* mLayout;
    QStyleOptionViewItem mOption;
    QStringList mPropertyMask;
    bool mEditMode{false};
	QString mEditModeStyleSheet{};
	QString mShowModeStyleSheet{};

    void applyValue(QVariant aValue);
};
