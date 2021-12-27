#pragma once

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QSpinBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QLCDNumber>
#include <QProgressBar>
#include <QLabel>
#include <QPlainTextEdit>

#include "qcustomplot.h"
#include "CustomItemTypes.h"

//================================================================//
class QImageSI: public QLabel
{
    Q_OBJECT
public:
    QImageSI(QWidget* parent = 0);
    QImageSI(const QVariant& value,QWidget* parent = 0);
    void setValue(const QString& value);
    void setSIValue(const QVariant& value);
signals:
    void signalEdittingFinished(const QVariant& aValue);
    void signalSelected();
private:
    void init();
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QLabel::mousePressEvent(event);
        emit signalSelected();
    }
};

//================================================================//
class QLCDNumberSI : public QLCDNumber
{
    Q_OBJECT
public:
    QLCDNumberSI(QWidget* parent = 0);
    QLCDNumberSI(const QVariant& value,QWidget* parent = 0);
    void setValue(double value);
    void setSIValue(const QVariant& value);
signals:
    void signalEdittingFinished(const QVariant& aValue);
    void signalSelected();
private:
    void init();
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QLCDNumber::mousePressEvent(event);
        emit signalSelected();
    }
};

//================================================================//
class QProgressBarSI : public QProgressBar
{
    Q_OBJECT
public:
    QProgressBarSI(QWidget* parent = 0);
    QProgressBarSI(const QVariant& value,QWidget* parent = 0);
    void setSIValue(const QVariant& value);
signals:
    void signalEdittingFinished(const QVariant& aValue);
    void signalSelected();
private:
    void init();
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QProgressBar::mousePressEvent(event);
        emit signalSelected();
    }
};

//================================================================//
class QListWidgetSI : public QComboBox
{
    Q_OBJECT
public:
	QListWidgetSI(QWidget* parent = 0);
    QListWidgetSI(const QVariant& aValue, bool aEditMode = false, QWidget* parent = 0);
    void setValue(const QStringList& aValue);
    void setValue(int aValue);
    void setSIValue(const QVariant& aValue);
    QVariant getSIValue() const;
signals:
    void signalEdittingFinished(const QVariant& aValue);
    void signalSelected();
private:
	void init();
    SIStringList mData;
    bool mEditMode{false};

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QComboBox::mousePressEvent(event);
        emit signalSelected();
    }
};
//================================================================//
class QBooleanListWidgetSI : public QComboBox
{
	Q_OBJECT
public:
	QBooleanListWidgetSI(QWidget* parent = 0);
	QBooleanListWidgetSI(const QVariant& aValue, bool aEditMode = false, QWidget* parent = 0);
	void setValue(const QStringList& aValue);
	void setValue(int aValue);
	void setSIValue(const QVariant& aValue);
	QVariant getSIValue() const;
signals:
	void signalEdittingFinished(const QVariant& aValue);
    void signalSelected();
private:
	void init();
	SIBooleanList mData;
	bool mEditMode{ false };
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QComboBox::mousePressEvent(event);
        emit signalSelected();
    }
};
//================================================================//
class QLineEditSI : public QLineEdit//, virtual public signalsInterface
{
    Q_OBJECT
public:
    QLineEditSI(QWidget* parent = 0);
    QLineEditSI(const QVariant& aValue, bool aEditMode = false, QWidget* parent = 0);
    void setValue(const QString& aValue);
    void setSIValue(const QVariant& aValue);
    QVariant getSIValue() const;
signals:
    void signalEdittingFinished(const QVariant& aValue);
    void signalEdittingFinished(QString aValue);
    void signalSelected();
private:
    void init();
    SIString mData;
    bool mEditMode{false};
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QLineEdit::mousePressEvent(event);
        emit signalSelected();
    }
};

//================================================================//
class QTextEditSI : public QPlainTextEdit
{
    Q_OBJECT
public:
    QTextEditSI(QWidget* parent = 0);
    QTextEditSI(const QVariant& aValue, bool aEditMode = false, QWidget* parent = 0);
    void setValue(const QString& aValue);
    void setSIValue(const QVariant& aValue);
    QVariant getSIValue() const;
signals:
    void signalEdittingFinished(const QVariant& aValue);
    void signalEdittingFinished(QString aValue);
    void signalSelected();
private:
    void init();
    SIText mData;
    bool mEditMode{false};
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QPlainTextEdit::mousePressEvent(event);
        emit signalSelected();
    }
};

//================================================================//
class QSpinBoxSI : public QSpinBox
{
    Q_OBJECT
public:
    QSpinBoxSI(QWidget* parent = 0);
    QSpinBoxSI(const QVariant& aValue, bool aEditMode = false, QWidget* parent = 0);
    void setSIValue(const QVariant& aValue);
    QVariant getSIValue() const;
signals:
    void signalEdittingFinished(const QVariant& aValue);
    void signalEdittingFinished(int aValue);
    void signalSelected();
private:
    void init();
    SIInteger mData;
    bool mEditMode{false};
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QSpinBox::mousePressEvent(event);
        emit signalSelected();
    }
};

//================================================================//
class QDoubleSpinBoxSI : public QDoubleSpinBox
{
    Q_OBJECT
public:
    QDoubleSpinBoxSI(QWidget* parent = 0);
    QDoubleSpinBoxSI(const QVariant& aValue, bool aEditMode = false,QWidget* parent = 0);
    void setSIValue(const QVariant& aValue);
    QVariant getSIValue() const;
signals:
    void signalEdittingFinished(const QVariant& aValue);
    void signalEdittingFinished(double aValue);
    void signalSelected();
private:
    void init();
    SIDouble mData;
    bool mEditMode{false};
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QDoubleSpinBox::mousePressEvent(event);
        emit signalSelected();
    }
};

//================================================================//
class QRadioButtonSI : public QRadioButton
{
    Q_OBJECT
public:
    QRadioButtonSI(QWidget* parent = 0);
    QRadioButtonSI(const QVariant& aValue, bool aEditMode = false, QWidget* parent = 0);
    void setSIValue(const QVariant& aValue);
    QVariant getSIValue() const;
signals:
    void signalEdittingFinished(const QVariant& aValue);
    void signalEdittingFinished(bool aValue);
    void signalSelected();
private:
    void init();
    SIBoolean mData;
    bool mEditMode{false};
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QRadioButton::mousePressEvent(event);
        emit signalSelected();
    }
};

//================================================================//
class QCustomPlotSI : public QCustomPlot
{
    Q_OBJECT
public:
    QCustomPlotSI(QWidget* parent = 0);
    virtual void setData(const QVector<double>& xData,const QVector<double>& yData) = 0;
    virtual void setSIValue(const QVariant& value) = 0;
    void setYData(const QVector<double>& yData);
signals:
    void signalEdittingFinished(const QVariant& aValue);
    void signalSelected();
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QCustomPlot::mousePressEvent(event);
        emit signalSelected();
    }
};

//================================================================//
class QBarsPlotSI : public QCustomPlotSI
{
    Q_OBJECT
public:
    QBarsPlotSI(QWidget* parent = 0);
    QBarsPlotSI(const QVariant& value,QWidget* parent = 0);
    void setData(const QVector<double>& xData,const QVector<double>& yData);
    void setSIValue(const QVariant& value);
private:
    QCPBars *mBars;
    void init();
};

//================================================================//
class QGraphPlotSI : public QCustomPlotSI
{
    Q_OBJECT
public:
    QGraphPlotSI(QWidget* parent = 0);
    QGraphPlotSI(const QVariant& value,QWidget* parent = 0);
    void setData(const QVector<double>& xData,const QVector<double>& yData);
    void setSIValue(const QVariant& value);
private:
    QCPGraph *mGraph;
    void init();
};
