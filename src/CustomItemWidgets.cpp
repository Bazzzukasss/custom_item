#include "CustomItemWidgets.h"
#include "CustomItemTypes.h"

//================================================================SILCDNumber
QLCDNumberSI::QLCDNumberSI(QWidget *parent)
    :QLCDNumber(parent)
{
    init();
}

QLCDNumberSI::QLCDNumberSI(const QVariant &value, QWidget *parent)
    :QLCDNumber(parent)
{
    init();
    setSIValue(value);
}

void QLCDNumberSI::setValue(double value)
{
    display(value);
}

void QLCDNumberSI::setSIValue(const QVariant &value)
{
    blockSignals(true);
    SILcd data = value.value<SILcd>();
    setMode(static_cast<QLCDNumber::Mode>( data.getDisplayMode()));
    setValue( data.getValue() );
    blockSignals(false);
}

void QLCDNumberSI::init()
{
    setFrameShape(QLCDNumber::NoFrame);
    setSegmentStyle(QLCDNumber::Flat);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

//================================================================SIProgressBar
QProgressBarSI::QProgressBarSI(QWidget *parent)
    :QProgressBar(parent)
{
    init();
}

QProgressBarSI::QProgressBarSI(const QVariant &value, QWidget *parent)
    :QProgressBar(parent)
{
    init();
    setSIValue(value);
}

void QProgressBarSI::setSIValue(const QVariant &value)
{
    blockSignals(true);
    SIProgress data = value.value<SIProgress>();
    auto val = data.getValue();
    auto min = data.getMinimum();
    auto max = data.getMaximum();
	auto format = data.getFormat();
    if( val > max ) val = max;
    if( val < min ) val = min;

    setMinimum(min);
    setMaximum(max);
    setValue(val);
	setFormat(format);
    blockSignals(false);
}

void QProgressBarSI::init()
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setAlignment(Qt::AlignHCenter);
}

//================================================================QListWidgetSI
QListWidgetSI::QListWidgetSI(QWidget *parent)
    :QComboBox(parent)
{
	init();
}

QListWidgetSI::QListWidgetSI(const QVariant &aValue, bool aEditMode, QWidget *parent) :
    QComboBox(parent),mEditMode(aEditMode)
{
	init();
    setSIValue(aValue);
}

void QListWidgetSI::setValue(const QStringList &aValue)
{
    if(currentIndex()<aValue.size()) setCurrentIndex(aValue.size());
    clear();
    addItems(aValue);
}

void QListWidgetSI::setValue(int aValue)
{
    blockSignals(true);
    if(aValue < 0) aValue = 0;
    if(aValue >= count()) aValue = count() - 1;

    setCurrentIndex(aValue);
    blockSignals(false);
}

void QListWidgetSI::setSIValue(const QVariant &aValue)
{
    blockSignals(true);
    mData = aValue.value<SIStringList>();
	clear();
    addItems(mData.getList());
    setValue(mData.getValue());
    blockSignals(false);
}

QVariant QListWidgetSI::getSIValue() const
{
    return QVariant().fromValue(mData);
}

void QListWidgetSI::init()
{
    if(!mEditMode)
    {
        setFrame(false);
		setStyleSheet("QListWidgetSI::drop-down { width: 0px;}QListWidgetSI {  border: 0px solid }");
    }

    connect(this,static_cast<void (QListWidgetSI::*)(int)>(&QListWidgetSI::currentIndexChanged),[=](){
        mData.setValue(currentIndex());
        qDebug()<<"QListWidgetSI:"<<currentIndex() << " StyleSheet: " << styleSheet();
        emit signalEdittingFinished(QVariant().fromValue(mData));
    });

}
//================================================================QBooleanListWidgetSI
QBooleanListWidgetSI::QBooleanListWidgetSI(QWidget *parent)
	:QComboBox(parent)
{
	init();
}

QBooleanListWidgetSI::QBooleanListWidgetSI(const QVariant &aValue, bool aEditMode, QWidget *parent) :
	QComboBox(parent), mEditMode(aEditMode)
{
	init();
	setSIValue(aValue);
}

void QBooleanListWidgetSI::setValue(const QStringList &aValue)
{
	if (currentIndex() < aValue.size()) setCurrentIndex(aValue.size());
	clear();
	addItems(aValue);
}

void QBooleanListWidgetSI::setValue(int aValue)
{
	blockSignals(true);
	if (aValue < 0) aValue = 0;
	if (aValue >= count()) aValue = count() - 1;

	setCurrentIndex(aValue);
	blockSignals(false);
}

void QBooleanListWidgetSI::setSIValue(const QVariant &aValue)
{
	blockSignals(true);
	mData = aValue.value<SIBooleanList>();
	clear();
	addItems(mData.getList());
	setValue(mData.getValue());
	blockSignals(false);
}

QVariant QBooleanListWidgetSI::getSIValue() const
{
	return QVariant().fromValue(mData);
}

void QBooleanListWidgetSI::init()
{
	if (!mEditMode)
	{
		setFrame(false);
		setStyleSheet("QBooleanListWidgetSI::drop-down { width: 0px;}QBooleanListWidgetSI {  border: 0px solid }");
	}

	connect(this, static_cast<void (QBooleanListWidgetSI::*)(int)>(&QBooleanListWidgetSI::currentIndexChanged), [=]() {
		mData.setValue(currentIndex());
		qDebug() << "QBooleanListWidgetSI:" << currentIndex()<<" StyleSheet: "<<styleSheet();
		emit signalEdittingFinished(QVariant().fromValue(mData));
	});

}
//================================================================SILineEdit
QLineEditSI::QLineEditSI(QWidget *parent)
    :QLineEdit(parent)
{
    init();
}

QLineEditSI::QLineEditSI(const QVariant &aValue, bool aEditMode, QWidget *parent):
    QLineEdit(parent),mEditMode(aEditMode)
{
    init();
    setSIValue(aValue);
}

void QLineEditSI::setValue(const QString &aValue)
{
    setText(aValue);
}

void QLineEditSI::setSIValue(const QVariant &aValue)
{
    blockSignals(true);
    mData = aValue.value<SIString>();
    setText( mData.getValue() );
    blockSignals(false);
}

QVariant QLineEditSI::getSIValue() const
{
    return QVariant().fromValue(mData);
}

void QLineEditSI::init()
{
    setFrame(mEditMode);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(this,&QLineEditSI::textChanged,[=](){
        mData.setValue(text());
        qDebug()<<"QLineEditSI:"<<text();
        emit signalEdittingFinished(QVariant().fromValue(mData));
        emit signalEdittingFinished(mData.getValue());
    });
}

//================================================================SITextEdit
QTextEditSI::QTextEditSI(QWidget *parent)
    :QPlainTextEdit(parent)
{
    init();
}

QTextEditSI::QTextEditSI(const QVariant &aValue, bool aEditMode, QWidget *parent):
    QPlainTextEdit(parent),mEditMode(aEditMode)
{
    init();
    setSIValue(aValue);
}

void QTextEditSI::setValue(const QString &aValue)
{
    setPlainText(aValue);
}

void QTextEditSI::setSIValue(const QVariant &aValue)
{
    blockSignals(true);
    mData = aValue.value<SIText>();
    setPlainText( mData.getValue() );
    blockSignals(false);
}

QVariant QTextEditSI::getSIValue() const
{
    return QVariant().fromValue(mData);
}

void QTextEditSI::init()
{
    if(!mEditMode)
    {
        setFrameShape(QFrame::NoFrame);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(this,&QTextEditSI::textChanged,[=](){
        mData.setValue(toPlainText());
        qDebug()<<"QLineEditSI:"<<toPlainText();
        emit signalEdittingFinished(QVariant().fromValue(mData));
        emit signalEdittingFinished(mData.getValue());
    });
}

//================================================================SISpinBox
QSpinBoxSI::QSpinBoxSI(QWidget *parent)
    :QSpinBox(parent)
{
    init();
}

QSpinBoxSI::QSpinBoxSI(const QVariant &aValue, bool aEditMode, QWidget *parent)
    :QSpinBox(parent),mEditMode(aEditMode)
{
    init();
    setSIValue(aValue);
}

void QSpinBoxSI::setSIValue(const QVariant &aValue)
{
    blockSignals(true);
    mData = aValue.value<SIInteger>();
    auto val = mData.getValue();
    auto min = mData.getMinimum();
    auto max = mData.getMaximum();
	auto suffix = mData.getSuffix();
    if( val > max ) val = max;
    if( val < min ) val = min;

    setMinimum(min);
    setMaximum(max);
    setValue(val);
	setSuffix(suffix);
    specialValueText();
    blockSignals(false);
}

QVariant QSpinBoxSI::getSIValue() const
{
    return QVariant().fromValue( mData );
}

void QSpinBoxSI::init()
{
    if(!mEditMode)
    {
        setFrame(false);
        setButtonSymbols(QSpinBox::NoButtons);
    }
    setMaximum(std::numeric_limits<int>::max());
    setMinimum(std::numeric_limits<int>::min());
    //setSpecialValueText(locale().toString(std::numeric_limits<int>::quiet_NaN()));
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    connect(this,static_cast<void (QSpinBox::*)(int)>(&QSpinBoxSI::valueChanged),[=](){
        mData.setValue(value());
        qDebug()<<"QSpinBoxSI:"<<value();
        emit signalEdittingFinished(QVariant().fromValue(mData));
        emit signalEdittingFinished(mData.getValue());
    });
}

//================================================================SIDoubleSpinBox
QDoubleSpinBoxSI::QDoubleSpinBoxSI(QWidget *parent)
    :QDoubleSpinBox(parent)
{
    init();
}

QDoubleSpinBoxSI::QDoubleSpinBoxSI(const QVariant &aValue, bool aEditMode, QWidget *parent)
    :QDoubleSpinBox(parent),mEditMode(aEditMode)
{
    init();
    setSIValue(aValue);
}

void QDoubleSpinBoxSI::setSIValue(const QVariant &aValue)
{
    blockSignals(true);
    mData = aValue.value<SIDouble>();
    auto val = mData.getValue();
    auto min = mData.getMinimum();
    auto max = mData.getMaximum();
	auto precision = mData.getPrecision();
	auto suffix = mData.getSuffix();
    if( val > max ) val = max;
    if( val < min ) val = min;

    setMinimum(min);
    setMaximum(max);
	setDecimals(precision);
    setValue(val);
	setSuffix(suffix);
    specialValueText();
    blockSignals(false);
}

QVariant QDoubleSpinBoxSI::getSIValue() const
{
    return QVariant().fromValue(mData);
}

void QDoubleSpinBoxSI::init()
{
    if(!mEditMode)
    {
        setFrame(false);
        setButtonSymbols(QSpinBox::NoButtons);
    }
    setMaximum(std::numeric_limits<double>::max());
    setMinimum(std::numeric_limits<double>::min());
    //setSpecialValueText(locale().toString(std::numeric_limits<double>::quiet_NaN()));
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    connect(this,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBoxSI::valueChanged),[=](){
        qDebug()<<"QDoubleSpinBoxSI:"<<value();
        mData.setValue(value());
        emit signalEdittingFinished(QVariant().fromValue(mData));
        emit signalEdittingFinished(mData.getValue());
    });
}

//================================================================SIRadioButton
QRadioButtonSI::QRadioButtonSI(QWidget *parent)
    :QRadioButton(parent)
{
    init();
}

QRadioButtonSI::QRadioButtonSI(const QVariant &aValue, bool aEditMode, QWidget *parent)
    :QRadioButton(parent),mEditMode(aEditMode)
{
    init();
    setSIValue(aValue);
}

void QRadioButtonSI::setSIValue(const QVariant &aValue)
{
    blockSignals(true);
    mData = aValue.value<SIBoolean>();
    setChecked( mData.getValue() );
    blockSignals(false);
}

QVariant QRadioButtonSI::getSIValue() const
{
    return QVariant().fromValue(mData);
}

void QRadioButtonSI::init()
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(this,&QRadioButtonSI::toggled,[=](){
        mData.setValue(isChecked());
        qDebug()<<"QRadioButtonSI:"<<isChecked();
        emit signalEdittingFinished(QVariant().fromValue(mData));
        emit signalEdittingFinished(mData.getValue());
    });
}

//================================================================SICustomPlot
QCustomPlotSI::QCustomPlotSI(QWidget *parent)
    :QCustomPlot(parent)
{
    xAxis->setTicks(false);
    yAxis->setTicks(false);
    axisRect()->setupFullAxesBox();
    axisRect()->setAutoMargins(QCP::msNone);
    axisRect()->setMargins(QMargins(1,1,1,1));
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}


void QCustomPlotSI::setYData(const QVector<double> &yData)
{
    QVector<double> xData(yData.size());
    for(int i = 0;i<xData.size();i++)
        xData[i]=i;
    setData(xData, yData);
}

//================================================================SIBarsPlot
QBarsPlotSI::QBarsPlotSI(QWidget *parent)
    :QCustomPlotSI(parent)
{
    init();
}

QBarsPlotSI::QBarsPlotSI(const QVariant &value, QWidget *parent):
    QCustomPlotSI(parent)
{
    init();
    setSIValue(value);
}

void QBarsPlotSI::setData(const QVector<double> &xData, const QVector<double> &yData)
{
    mBars->setData(xData,yData);
    mBars->rescaleValueAxis(true);
    xAxis->setRange(0,xData.size());
}

void QBarsPlotSI::setSIValue(const QVariant &value)
{
    SIBars data = value.value<SIBars>();
    setYData(data.getValue());
}

void QBarsPlotSI::init()
{
    mBars = new QCPBars(xAxis, yAxis);
    addPlottable(mBars);
    mBars->rescaleAxes(true);
    mBars->setWidth(1);
    mBars->setPen(Qt::NoPen);
    mBars->setBrush(QColor(0x99, 0x99, 0x99, 160));
}

//================================================================SIGraphPlot
QGraphPlotSI::QGraphPlotSI(QWidget *parent)
    :QCustomPlotSI(parent)
{
    init();
}

QGraphPlotSI::QGraphPlotSI(const QVariant &value, QWidget *parent)
    :QCustomPlotSI(parent)
{
    init();
    setSIValue(value);
}

void QGraphPlotSI::setData(const QVector<double> &xData, const QVector<double> &yData)
{
    mGraph->setData(xData,yData);
    mGraph->rescaleValueAxis(true);
    xAxis->setRange(0,xData.size());
}

void QGraphPlotSI::setSIValue(const QVariant &value)
{
    SIGraph data = value.value<SIGraph>();
    setYData(data.getValue());
}

void QGraphPlotSI::init()
{
    mGraph = addGraph(xAxis, yAxis);
    mGraph->rescaleAxes(true);
    mGraph->setPen(QPen( QColor(0x66, 0x66, 0x66) ));
}

//================================================================QImageSI
QImageSI::QImageSI(QWidget *parent)
    :QLabel(parent)
{
    init();
}

QImageSI::QImageSI(const QVariant &value, QWidget *parent)
    :QLabel(parent)
{
    setSIValue(value);
}

void QImageSI::setValue(const QString &value)
{
    setPixmap(QPixmap(value));
}

void QImageSI::setSIValue(const QVariant &value)
{
    SIImage data = value.value<SIImage>();
    setValue(data.getValue());
}

void QImageSI::init()
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}
