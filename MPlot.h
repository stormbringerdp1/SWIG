#ifndef MPLOT_H
#define MPLOT_H

#include "MPlot.h"

#include <QFrame>
#include <QEvent>
#include <QList>
#include <QScrollBar>

//============================================================================================
class MPlot : public QFrame
{
    Q_OBJECT
public:
    explicit MPlot(QWidget* pParent, const bool isReport, const char* cYAxisLabel, float minYNormalValue, float maxYNormalValue);

//                   const qreal& xLeft, const qreal& xRight);  //          1: X1 is fixedPlot, X2 changes
  virtual ~MPlot();                                                                  //          2: Plot moves to the left

private:
  bool IsReport;
  QString SYAxisLabel; // QString SXAxisLabel;
  float MinYNormalValue;  float MaxYNormalValue;

  qreal XStep;

//  qreal XLeft, XRight;
  int NYStroke, NXStroke;


  int  IxyOff, IxyOffStroke, IxyStrokeLength, IxyArrow;

  int NItemVisibleLeft;
  QScrollBar*   PScrollBar;   int  HScrollBar;
  int  PosSB;

  QRectF  RectCurve;

  QList<QPointF>  ListVisibleValues;   int NMaxVisibleCount;
  QList<QPointF>  ListAllValues;       int NAllCount;
  qreal YMinAllValue, YMaxAllValue;


//  qreal  XMinValue, XMaxValue, YMinValue, YMaxValue;

  void Draw(QPainter& painter);
//  void DrawAxes(QPainter& painter);
//  void DrawCurve(QPainter& painter);
//  void GetRangeValues(qreal& fx1, qreal& fx2, qreal& fy1, qreal& fy2);

protected:
  virtual bool event(QEvent* event);
  virtual void paintEvent(QPaintEvent* event);

public:
  void AddValue(const qreal &fx, const qreal &fy);
//  void AddValue(const QString& sx, const qreal &fy);

signals:
//  void SignalNotNormalValue(MPlot* pPlot);

public slots:
  void SliderMoved(int pos);
};
//============================================================================================
#endif // MPLOT_H
