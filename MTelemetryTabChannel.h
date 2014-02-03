#ifndef MTELEMETRYTABCHANNEL_H
#define MTELEMETRYTABCHANNEL_H

#include "MPlot.h"

#include <QWidget>
#include <QList>
//#include <QScrollBar>
#include <QLineEdit>
#include <QTimer>

//============================================================================================
class MTelemetryTabChannel : public QWidget
{
    Q_OBJECT
public:
    explicit MTelemetryTabChannel(QWidget* parent, QList<QString>* pListParamsTelemetryChannel);
  virtual ~MTelemetryTabChannel();

  QRect GetRectChannel() { return RectChannel; }

private:
  QList<QString>* PListParamsTelemetryChannel;
  int             IFirstItemListParamsTelemetry;
  int             DeltaNItemListParamsTelemetry;

  QList<float> ListMinNormalValues;   QList<float> ListMaxNormalValues;

  QRect RectChannel;

  QList<QLineEdit*> ListLineEditCurrentParams;

  QList<MPlot*> ListPlots;
  QList<MPlot*> ListCorrespondingReportPlots;

//  QScrollBar*   PScrollBar;

  int ICurrentParam;

  QTimer Timer;
  bool IsFlicker;            bool IsFlickerBrush;
  bool IsNonNormalMaxValue;  bool IsNonNormalMinValue;

//  QColor ColorBrushTabFlicker;

  void UpdateTabBar();

protected:
  virtual bool event(QEvent* event);
//  virtual void paintEvent(QPaintEvent* event);

public:
  const QList<MPlot*>* GetPListPlots() { return &ListPlots; }
  const QList<QString>* GetPListParamsTelemetryChannel() { return PListParamsTelemetryChannel; }

  const QList<float>* GetPListMinNormalValues() { return &ListMinNormalValues; }
  const QList<float>* GetPListMaxNormalValues() { return &ListMaxNormalValues; }


  void AssignCorrespondingReportPlot(MPlot* pCorrespondingReportPlot);

  void BeginGetArduinoValues();
  void GetNextArduinoValue();

  bool GetIsFlicker(bool& isColorBrushFlicker, bool& isNonNormalMinValue, bool& isNonNormalMaxValue);
  void StopFlicker();


signals:
  void SignalGetTelemetryValue(QString* psNameChannel, QString* psInputName);
  void SignalChannelTelemetryDoneParam(qreal dt, float value, bool isLastParamInChannel);
  void SignalUpdateTabBar();

public slots:
  void SlotResultGetTelemetryValue(float value);
  void SlotTimerSignal();

};
//============================================================================================
#endif // MTELEMETRYTABCHANNEL_H
