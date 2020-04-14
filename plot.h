#ifndef MYPLOT_H
#define MYPLOT_H

#include "datadefine.h"
#include <QMouseEvent>
#include <QHoverEvent>
#include <QCursor>
#include <qwt_plot.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <QGridLayout>
#include <qwt_plot_canvas.h>
#include <qwt_symbol.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_marker.h>

class QwtPlotCurve;
class QwtSymbol;

class Plot : public QwtPlot
{
    Q_OBJECT

public:
    Plot(QWidget *parent = nullptr);

    void SetSymbol(QwtSymbol *);

    void SetSamples(const QVector<QPointF> &samples);

    void SetPlotProperties(const S_DRAWDATA_PROPERTIES& properties);

    void SetCurveSamples(const QVector<QPointF> &samples, QColor qcolor, QSize qsize, const int YAxis, const QString& qcurvetitle);

    void ClearCurve();

    void SetLegend();

    void ModifyRange(double xstart,double xend,double ystart,double yend);

    void CreateLine(double min,double max);

    void UpdateLineMin(double value);

    void UpdateLineMax(double value);

    void UpdateLineValue(double min,double max);

    void CreateThresholdLine(double value);

    void UpdateTitle(QString title);

    void SetControlMode(E_CONTROLTYPE type);

    void SetPickerShow();

    QwtPlotMagnifier *magnifier;

private:
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    E_CONTROLTYPE m_curConMod;

    QwtPlotCanvas *m_canvas;
    QwtPlotCurve *m_curve;
    QwtPlotZoomer* m_zoomer;
    QwtPlotPanner* m_panner;
    QwtSymbol *m_symbol;
    QwtLegend *m_plengend;
    QwtPlotMarker *m_lineMin;
    QwtPlotMarker *m_lineMax;
    QwtPlotMarker *m_thresholdValueLine;
    QwtPlotPicker *m_picker;
    S_DATARANGE m_rangeValue;
    QwtText t;
};


#endif // MYPLOT_H
