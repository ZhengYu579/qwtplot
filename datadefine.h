#ifndef DATADEFINE_H
#define DATADEFINE_H

#include <QColor>

/**  Draw Data Properties*/
typedef struct DRAWDATA_PROPERTIES
{
    int XStart;
    int XEnd;
    int XStep;
    double YLStart;
    double YLEnd;
    double YLStep;
    double YRStart;
    double YREnd;
    double YRStep;

    QColor ylColor;
    QColor yrColor;

    int DataType;
    QColor color;
    QString BaseName;
    QString XBottomAxisXTitle;
    QString YLeftAxisXTitle;
    QString YRightAxisXTitle;
    bool enableYRightAxis;
    int IndexofRow;
    int IndexofColumn;
    int TotalPlots;
    int axis;

    QString TitleFontFamily;
    int TitileSize;
    QString AxisFontFamily;
    int AxisFontsize;

    int PlotWidth;
    int PlotHeight;
    bool bhasMap=false;

}S_DRAWDATA_PROPERTIES;

typedef enum CONTROLTYPE{
    noMode,             ///<Mouse drag and drop no function, click to display coordinates
    amplification,      ///<Drag and drop the mouse to select the box. Release the mouse to enlarge the selected area
    drag,               ///<Mouse drag causes the canvas to move
}E_CONTROLTYPE;

/**  Data Range*/
typedef struct DATARANGE
{
    double xmax;    ///<The maximum value of the X-axis at adaptive time
    double xmin;    ///<The minimum value of the Y-axis at adaptive time
    double ymax;    ///<The maximum value of the X-axis at adaptive time
    double ymin;    ///<The minimum value of the Y-axis at adaptive time
}S_DATARANGE;

#endif // DATADEFINE_H
