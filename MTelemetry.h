#ifndef MTELEMETRY_H
#define MTELEMETRY_H

#include "MTelemetryTabWidgetChannels.h"
#include "MTelemetryTabWidgetStates.h"
//#include "MTelemetryTabReport.h"
//#include "MEkranoplanGL.h"
//#include "MGyrohorizon.h"

#include <QSplitter>
//#include <QTabWidget>
#include <QPushButton>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

class MainWindow;
//============================================================================================

class MTelemetry : public QSplitter
{
    Q_OBJECT
public:
    explicit MTelemetry(QWidget *parent = 0);
  virtual ~MTelemetry();

private:
  QString SMessageBoxTitle;

//  QTabWidget* PTabWidgetChannels;   int CurrentIndexTabChannel;
//  QTabWidget* PTabWidgetStates;
  MTelemetryTabWidgetChannels* PTabWidgetChannels;
  MTelemetryTabWidgetStates*   PTabWidgetStates;

//  QList<MPlot*> ListTabPlots;

//  MEkranoplanGL* PEkranoplanGL;
//  MGyrohorizon*  PGyrohorizon;

  bool   IsTelemetryStarted;
//  qint64 TimeStartTelemetry;
  int    ICurrentChannel;
  bool   IsReadyNextChannel;
  bool   IsReadyNextChannelParam;


  QPushButton* PPushButtonReadiness;

  void Init();

  QRect FillTelemetryChannels(QWidget* pScrollAreaChannelsContents);
  QRect FillTelemetryStates(QWidget* pScrollAreaStatesContents);

  QString      NameFileReport;
  QFile*       PFileReport;
  QTextStream* PStreamFileReport;
  QList<int> ListLengthAllParams;
  int        IWritingParam;
  int        NAllWritingParams;

  void PrepareFileReport(QDateTime& currentDataTime);
  void WriteFileReportValue(qreal dt, float value, bool isLastParamInChannel);

public:
  void DoTelemetry();
//  QRect FillTabReport(MTelemetryTabReport* pTabReport, int countParamsTelemetryChannels, QList<QString>& listNamesChannels,
//                      QList<int>& listCountPlotsInChannels, QList<QList<QString>>& listNameParamsInChannels,
//                      bool isAssignCorrespondingReportPlot);
  const QString* GetCurrentPNameFileReport() { return &NameFileReport; }

signals:

public slots:
//  void SlotIndexTabChannelsChanged(int newIndex);
  void SlotTimerSignal();
  void SlotChannelTelemetryDoneParam(qreal dt, float value, bool isLastParamInChannel);
};
//============================================================================================
#endif // MTELEMETRY_H
