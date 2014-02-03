#ifndef MTELEMETRYTABREPORT_H
#define MTELEMETRYTABREPORT_H

#include "MPlot.h"

#include <QWidget>
#include <QList>

//============================================================================================
class MTelemetryTabReport : public QWidget
{
    Q_OBJECT
public:
    explicit MTelemetryTabReport(QWidget *parent = 0);

private:
  QList<MPlot*> ListPlots;

public:
  void AddPlot(MPlot* pPlot) { ListPlots << pPlot; }
  MPlot* GetPPlot(int index) { return ListPlots[index]; }

signals:

public slots:

};
//============================================================================================

#endif // MTELEMETRYTABREPORT_H
