#ifndef MTELEMETRYTABWIDGETSTATES_H
#define MTELEMETRYTABWIDGETSTATES_H

#include "MTelemetryTabWidgetChannels.h"
#include "MEkranoplanGL.h"
#include "MGyrohorizon.h"
#include "MTelemetryTabReport.h"

#include <QTabWidget>

//============================================================================================
class MTelemetryTabWidgetStates : public QTabWidget
{
    Q_OBJECT
public:
    explicit MTelemetryTabWidgetStates(QWidget *parent, MTelemetryTabWidgetChannels *pTabWidgetChannels);

private:
  MTelemetryTabWidgetChannels *PTabWidgetChannels;

  MEkranoplanGL* PEkranoplanGL;
  MGyrohorizon*  PGyrohorizon;

public:
  QRect AddTabs();
  QRect FillTabReport(MTelemetryTabReport* pTabReport, int countParamsTelemetryChannels, QList<QString>& listNamesChannels,
                      QList<int>& listCountPlotsInChannels, QList<QList<QString>>& listNameParamsInChannels,
                      bool isAssignCorrespondingReportPlot);
signals:

public slots:

};
//============================================================================================

#endif // MTELEMETRYTABWIDGETSTATES_H
