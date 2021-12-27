#ifndef CUSTOMITEMFRAMEHEADER_H
#define CUSTOMITEMFRAMEHEADER_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

class CustomItem;

class CustomItemFrameHeader : public QFrame
{
    Q_OBJECT
public:
    CustomItemFrameHeader(CustomItem* aRootItem, QWidget* parent = Q_NULLPTR);
    CustomItemFrameHeader(QWidget* parent = Q_NULLPTR);
    bool getState() const;

signals:
    void signalSwitchClicked(bool aIsVisibile);

private:
    QHBoxLayout* mpLayout;
    QLabel* mpLabelCaption;
    QPushButton* mpButtonSwitch;
    CustomItem* mpRootItem;

    void initialize();
};

#endif //CUSTOMITEMFRAMEHEADER_H
