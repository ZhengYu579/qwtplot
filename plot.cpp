#include "plot.h"

Plot::Plot(QWidget *parent):
    QwtPlot(parent),
    m_curve(nullptr),m_zoomer(nullptr),m_panner(nullptr)
{
    setMouseTracking(true);
    canvas()->setStyleSheet(
                "border: 2px solid Black;"
                "border-radius: 15px;"
                "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                "stop: 0 LemonChiffon, stop: 1 PaleGoldenrod);"
                );

    setAutoReplot(true);

    SetSymbol(nullptr);
}

void Plot::SetSymbol(QwtSymbol *symbol)
{
    if (m_curve!=nullptr)
    {
        m_curve->setSymbol(symbol);

        if (symbol == nullptr)
        {
            m_curve->setStyle(QwtPlotCurve::Dots);
        }
    }
}

void Plot::SetSamples(const QVector<QPointF> &samples)
{
    if (m_curve!=nullptr)
    {
        m_curve->setPaintAttribute(
                    QwtPlotCurve::ImageBuffer, samples.size() > 1000);

        m_curve->setSamples(samples);
    }
}

void Plot::SetCurveSamples(const QVector<QPointF> &samples, QColor qcolor, QSize qsize, const int YAxis, const QString& qcurvetitle)
{
    QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse, QBrush(Qt::white), QPen(qcolor, qsize.width()), qsize);//设置样本点的颜色、大小

    m_curve =new QwtPlotCurve();
    m_curve->setSymbol(symbol);//添加样本点形状

    m_curve->setYAxis(YAxis);
    m_curve->setTitle(qcurvetitle);
    m_curve->setSamples(samples);
    m_curve->setStyle(QwtPlotCurve::CurveStyle::NoCurve);//不连接成线
    m_curve->attach(this);
}

void Plot::SetLegend()
{
    if (m_plengend==nullptr)
    {
        m_plengend=new QwtLegend;
        this->insertLegend(m_plengend, QwtPlot::RightLegend);
    }
}

void Plot::ClearCurve()
{
    detachItems();
    replot();
}

void Plot::SetControlMode(E_CONTROLTYPE type)
{
    switch (type)
    {
    case noMode:
        m_curConMod = noMode;
        m_zoomer->setEnabled(false);
        m_panner->setEnabled(false);
        m_picker->setEnabled(true);
        break;
    case amplification:
        m_curConMod = amplification;
        m_zoomer->setEnabled(true);
        m_panner->setEnabled(false);
        m_picker->setEnabled(false);
        break;
    case drag:
        m_curConMod = drag;
        m_zoomer->setEnabled(false);
        m_panner->setEnabled(true);
        m_picker->setEnabled(false);
        break;
    default:
        break;
    }
}

void Plot::SetPickerShow()
{
    m_picker->setEnabled(true);
}

void Plot::mouseMoveEvent(QMouseEvent *e)
{
    QPoint mousepos = e->pos();

    //在坐标（0 ~ width，0 ~ height）范围内改变鼠标形状
    if(mousepos.rx() > m_canvas->x()
            && mousepos.rx() < m_canvas->width()
            && mousepos.ry() > m_canvas->y()
            && mousepos.ry() < m_canvas->height())
    {
        if(m_curConMod == amplification){
            QCursor *myCursor=new QCursor(QPixmap(":/new/prefix1/toolbarIcon/amplification_cursor.png"),-5,-5);    //-1,-1表示热点位于图片中心
            m_canvas->setCursor(*myCursor);
        }else if(m_curConMod == drag){
            m_canvas->setCursor(Qt::OpenHandCursor);
        }else{
            m_canvas->setCursor(Qt::CrossCursor);
        }
    }
    else
    {
        m_canvas->setCursor(Qt::ArrowCursor);      //范围之外变回原来形状
    }
}

void Plot::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton && m_curConMod != noMode){
        ModifyRange(m_rangeValue.xmin,m_rangeValue.xmax,m_rangeValue.ymin,m_rangeValue.ymax);
    }
}

/**
 * @brief Set properties of the plot
 * @param properties    The data for plot
 */
void Plot::SetPlotProperties(const S_DRAWDATA_PROPERTIES& properties)
{
    //set up Gridlines
    //    QwtPlotGrid* mGrid=new QwtPlotGrid;
    //    mGrid->enableX(true);
    //    mGrid->enableY(true);
    //    mGrid->setMajorPen(Qt::black, 0, Qt::DotLine);
    //    mGrid->attach(this);

    m_curConMod = noMode;

    /**this is for minimize the plot*/
    this->setMinimumWidth(30);
    this->setMinimumHeight(80);
    this->plotLayout()->setAlignCanvasToScales(true);
    ///设置网格线
    //-----------设置plot标题--------------//
    //设置标题名
    if (properties.BaseName != "")
    {
        t.setText("      " + properties.BaseName);
    }
    //设置字体
    QFont font(properties.TitleFontFamily, properties.TitileSize);
    //设置粗体
    font.setBold(false);
    t.setFont(font);
    //设置标题背景色
    //    QBrush brush(QColor(240, 240, 240));
    //    t.setBackgroundBrush(brush);
    this->setTitle(t);
    //-----------设置x，y坐标和范围--------------//

    //pdplot->setGeometry(400, 120, 850, 450);

    this->enableAxis(QwtPlot::yRight, true);

    QwtText tx;
    tx.setText(properties.XBottomAxisXTitle);
    QFont xfont(properties.AxisFontFamily, properties.AxisFontsize);
    xfont.setBold(false);
    tx.setFont(xfont);
    // tx.setFont(QFont("Regular", 10, 50));
    this->setAxisTitle(QwtPlot::xBottom, tx);
    this->setAxisScale(QwtPlot::xBottom, properties.XStart, properties.XEnd);

    QFont xaxisfont(properties.AxisFontFamily, properties.AxisFontsize);
    xaxisfont.setBold(false);
    this->setAxisFont(QwtPlot::xBottom, xaxisfont);

    QwtText tyl;
    tyl.setText(properties.YLeftAxisXTitle);
    tyl.setColor(properties.ylColor);

    QFont ylfont(properties.AxisFontFamily, properties.AxisFontsize);
    ylfont.setBold(false);
    tyl.setFont(ylfont);
    this->setAxisTitle(QwtPlot::yLeft, tyl);
    this->setAxisScale(QwtPlot::yLeft, properties.YLStart, properties.YLEnd);

    QFont ylaxisfont(properties.AxisFontFamily, properties.AxisFontsize);
    ylaxisfont.setBold(false);
    this->setAxisFont(QwtPlot::yLeft, ylaxisfont);

    QString m_strcoloryl = properties.ylColor.name();
    //this->axisWidget(QwtPlot::yLeft)->setStyleSheet(m_strcoloryl);
    this->axisWidget(QwtPlot::yLeft)->setStyleSheet("QWidget{color::green}");

    m_rangeValue.xmin = properties.XStart;
    m_rangeValue.xmax = properties.XEnd;
    m_rangeValue.ymin = properties.YLStart;
    m_rangeValue.ymax = properties.YLEnd;

    //if (properties.enableYRightAxis)
    {
        QwtText tyr;
        tyr.setText(properties.YRightAxisXTitle);
        QFont yrfont(properties.AxisFontFamily, properties.AxisFontsize);
        tyr.setFont(yrfont);
        tyr.setColor(properties.yrColor);
        this->setAxisTitle(QwtPlot::yRight, "");
        this->setAxisScale(QwtPlot::yRight, 0, 0);
        this->axisWidget(QwtPlot::yRight)->setStyleSheet("QWidget{color::black}");
    }

    m_canvas=new QwtPlotCanvas();
    m_canvas->setPalette(Qt::white);
    //canvas->setBorderRadius(10);
    setCanvas(m_canvas);
    m_canvas->setMouseTracking(true);

    magnifier = new QwtPlotMagnifier(m_canvas);
    magnifier->setMouseButton(Qt::NoButton);
    magnifier->setEnabled(false);

    axisWidget(QwtPlot::yLeft)->setMargin(0);
    axisWidget(QwtPlot::xBottom)->setMargin(0);
    axisWidget(QwtPlot::yRight)->setMargin(0);

    m_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
                                                 QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
                                                 this->canvas());
    m_picker->setStateMachine(new QwtPickerDragPointMachine());
    m_picker->setRubberBandPen(QColor(Qt::darkMagenta));
    m_picker->setRubberBand(QwtPicker::CrossRubberBand);
    m_picker->setTrackerMode(QwtPicker::ActiveOnly);//被激活时候显示
    m_picker->setTrackerPen(QColor(Qt::black));
    m_picker->setEnabled(false);

    //set up leftbutton to move the canvas
    m_panner = new QwtPlotPanner(m_canvas);
    m_panner->setMouseButton(Qt::LeftButton);
    m_panner->setEnabled(false);

    m_zoomer = new QwtPlotZoomer(m_canvas);
    m_zoomer->setZoomBase(false);
    m_zoomer->setEnabled(false);
}

void Plot::ModifyRange(double xstart,double xend,double ystart,double yend)
{
    this->setAxisScale(QwtPlot::xBottom, xstart, xend);
    this->setAxisScale(QwtPlot::yLeft, ystart, yend);
    setAxisMaxMajor(QwtPlot::xBottom, 5);
    setAxisMaxMajor(QwtPlot::yLeft, 5);
    m_rangeValue.xmin = xstart;
    m_rangeValue.xmax = xend;
    m_rangeValue.ymin = ystart;
    m_rangeValue.ymax = yend;
}

void Plot::CreateLine(double min,double max)
{
    m_lineMin = new QwtPlotMarker;
    m_lineMin->setLineStyle(QwtPlotMarker::VLine);
    m_lineMin->setLinePen(QColor(0, 100, 210), 1);
    m_lineMin->setXValue(min);
    m_lineMin->attach(this);

    m_lineMax = new QwtPlotMarker;
    m_lineMax->setLineStyle(QwtPlotMarker::VLine);
    m_lineMax->setLinePen(QColor(0, 100, 210), 1);
    m_lineMax->setXValue(max);
    m_lineMax->attach(this);

    setAxisScale(QwtPlot::xBottom, min - (max - min)/2, max + (max - min)/2);
    m_rangeValue.xmin = min - (max - min)/2;
    m_rangeValue.xmax = max + (max - min)/2;
}

void Plot::UpdateLineMin(double value)
{
    if (m_lineMin)
    {
        m_lineMin->setXValue(value);
    }
}

void Plot::UpdateLineMax(double value)
{
    if (m_lineMax)
    {
        m_lineMax->setXValue(value);
    }
}

void Plot::UpdateLineValue(double min, double max)
{
    if (m_lineMin)
    {
        m_lineMin->setXValue(min);
    }
    if (m_lineMax)
    {
        m_lineMax->setXValue(max);
    }
    setAxisScale(QwtPlot::xBottom, min - (max - min)/2, max + (max - min)/2);
}

void Plot::CreateThresholdLine(double value)
{
    m_thresholdValueLine = new QwtPlotMarker;
    m_thresholdValueLine->setLineStyle(QwtPlotMarker::HLine);
    m_thresholdValueLine->setLinePen(QColor(255, 0, 0), 1);
    m_thresholdValueLine->setYValue(value);
    m_thresholdValueLine->attach(this);
}

void Plot::UpdateTitle(QString title)
{
    t.setText(title);
    this->setTitle(t);
}
