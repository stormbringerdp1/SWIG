#include "MTelemetryTabChannel.h"
#include "MTelemetryTabWidgetChannels.h"
#include "MTelemetryTabBarChannels.h"
#include "MArduino.h"
#include "funcs.h"

//#include <QTabWidget>
#include <QtGlobal>
#include <QDateTime>
#include <QMessageBox>

//============================================================================================
MTelemetryTabChannel::MTelemetryTabChannel(QWidget* parent, QList<QString>* pListParamsTelemetryChannel) :
    QWidget(parent), PListParamsTelemetryChannel(pListParamsTelemetryChannel)
{
  MTelemetryTabWidgetChannels* pTabWidgetChannels = qobject_cast<MTelemetryTabWidgetChannels*>(parent);
  Q_ASSERT(pTabWidgetChannels != NULL); // Q_CHECK_PTR(pTabWidgetChannels);
  MTelemetryTabBarChannels* pTabBarChannels = qobject_cast<MTelemetryTabBarChannels*>(pTabWidgetChannels->tabBar());
  Q_ASSERT(pTabBarChannels != NULL); // Q_CHECK_PTR(pTabBarChannels);

  IsFlicker = false;            IsFlickerBrush = false;
  IsNonNormalMaxValue = false;  IsNonNormalMinValue = false;

//  ColorBrushTabFlicker = QColor(255,0,0, 100);

  MPlot* pPlot;    QString s;
  int yTopName = pTabBarChannels->rect().height();// + 10;
  QRect rectPlot(10,yTopName+10, 321,321);
  int xLeftName = rectPlot.left() + rectPlot.width()/2 - 30;

  IFirstItemListParamsTelemetry = GetPMainWnd()->GetIFirstItemListParamsTelemetry();
//  DeltaNItemListParamsTelemetry = GetPMainWnd()->GetDeltaNItemListParamsTelemetry();

  for(int i = IFirstItemListParamsTelemetry; i < PListParamsTelemetryChannel->count(); i += 3) { //DeltaNItemListParamsTelemetry) {
/*
    pLineEditNameParam = new QLineEdit(parent);
    pLineEditNameParam->setObjectName(QStringLiteral("LineEditNameParam"));
//    rect = QRect(xLeftName, yTopName, 100, 20);
    pLineEditNameParam->setGeometry(QRect(xLeftName, yTopName, 300, 20));
    pLineEditNameParam->setFrame(false);
    pLineEditNameParam->setReadOnly(true);
    pLineEditNameParam->setStyleSheet(QLatin1String("background: transparent;"));
    pLineEditNameParam->setAlignment(Qt::AlignCenter);
    s = "Current Value of ";  s = (*PListParamsChannel)[i];
    pLineEditNameParam->setText(s);
*/
    xLeftName += rectPlot.width()+10;

    float minValue = (*PListParamsTelemetryChannel)[i+1].toFloat();   ListMinNormalValues << minValue;
    float maxValue = (*PListParamsTelemetryChannel)[i+2].toFloat();   ListMaxNormalValues << maxValue;
//    pPlot = new MPlot(this, false, (*PListParamsTelemetryChannel)[i].toStdString().c_str());//,0.0, 10.0);
    pPlot = new MPlot(this, false, (*PListParamsTelemetryChannel)[i].toStdString().c_str(), minValue, maxValue);
    pPlot->setGeometry(rectPlot);

//    connect(this, SIGNAL(SignalNotNormalValue()), pTabBar, SLOT(SlotNotNormalValue()));

    ListPlots << pPlot;
    RectChannel |= rectPlot;

    if(i == 1)  RectChannel = rectPlot;
    else        RectChannel |= rectPlot;

    rectPlot.translate(rectPlot.width()+10,0);
  }
//  RectChannel.setRight(RectChannel.right()+15);

  connect(&Timer, SIGNAL(timeout()), this, SLOT(SlotTimerSignal()));

}
//--------------------------------------------------------------------------------------------
MTelemetryTabChannel::~MTelemetryTabChannel()
{
}
//--------------------------------------------------------------------------------------------
bool MTelemetryTabChannel::event(QEvent* event)
{
  bool b = QWidget::event(event); //catch different events
//--
  if(event->type() == QEvent::Polish) {//Polish is caught

    int xLeftName = 20;
    QLineEdit* pLineEditNameParam;  QLineEdit* pLineEditCurrentParam;
    for(int i = 0; i < ListPlots.count(); i++) {
      pLineEditNameParam = new QLineEdit(ListPlots[i]->parentWidget());
      pLineEditNameParam->setObjectName(QStringLiteral("LineEditNameParam"));
      pLineEditNameParam->setGeometry(QRect(xLeftName, 15, 300, 20));
      pLineEditNameParam->setFrame(false);
      pLineEditNameParam->setReadOnly(true);
      pLineEditNameParam->setStyleSheet(QLatin1String("background: transparent;"));
      pLineEditNameParam->setAlignment(Qt::AlignLeft);//Center);
      pLineEditNameParam->setText("Current Value of "
                                 + (*PListParamsTelemetryChannel)[IFirstItemListParamsTelemetry + i*3] //DeltaNItemListParamsTelemetry]
                                 + ":");

      pLineEditCurrentParam = new QLineEdit(ListPlots[i]->parentWidget());
      pLineEditCurrentParam->setObjectName(QStringLiteral("LineEditNameParam"));
      pLineEditCurrentParam->setGeometry(QRect(xLeftName+245, 15, 50, 20));
      pLineEditCurrentParam->setFrame(false);
      pLineEditCurrentParam->setReadOnly(true);
      pLineEditCurrentParam->setStyleSheet(QLatin1String("background: transparent;"));
      pLineEditCurrentParam->setAlignment(Qt::AlignRight);//Center);
      ListLineEditCurrentParams << pLineEditCurrentParam;

      xLeftName += 330;
    }

/*
    setObjectName(QStringLiteral("TelemetryTabChannel")); //tab"));

    MPlot* pPlot;  QRect rect(20,120, 321,321);
    for(int i = 0; i < PListParamsChannel->count(); i++) {
      pPlot = new MPlot(this, false, (*PListParamsChannel)[i], "t (sec)", 0.0, 10.0); // Plot moves to the left
      pPlot->setGeometry(rect);
      ListPlots << pPlot;
      if(i ==0)  RectChannel = rect;
      else       RectChannel |= rect;
      rect.translate(rect.width()+10,0);
    }

//    pPlot = new MPlot(this, true, "YAxisLabel", "XAxisLabel", 0.0, 10.0); // Plot does not move
//    pPlot->setGeometry(QRect(360, 120, 321, 321));
//    ListPlots << pPlot;


//    QRect rect = pPlot->geometry();
//    PScrollBar = new QScrollBar(this);
//    PScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
//    PScrollBar->setGeometry(QRect(rect.left(), rect.bottom()+1, rect.width(), 16));
//    PScrollBar->setOrientation(Qt::Horizontal);

*/
  }
  return b;
}
//--------------------------------------------------------------------------------------------
/*
void MTelemetryTabChannel::paintEvent(QPaintEvent* event)
{
  QWidget::paintEvent(event);
  return;
}
*/
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::AssignCorrespondingReportPlot(MPlot* pCorrespondingReportPlot)
{
  ListCorrespondingReportPlots << pCorrespondingReportPlot;
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::BeginGetArduinoValues()
{
  ICurrentParam = -1;

//  GetPMainWnd()->CreateArduinoObject(this, SIGNAL(SignalGetTelemetryValue(QString*,QString*)), SLOT(SlotGetTelemetryValue(QString*,QString*)),
//                                           SIGNAL(SignalResultGetTelemetryValue(float)), SLOT(SlotResultGetTelemetryValue(float)));
  connect(this, SIGNAL(SignalGetTelemetryValue(QString*,QString*)), GetPMainWnd()->GetPArduino(), SLOT(SlotGetTelemetryValue(QString*,QString*)));
  connect(GetPMainWnd()->GetPArduino(), SIGNAL(SignalResultGetTelemetryValue(float)), this, SLOT(SlotResultGetTelemetryValue(float)));
  GetNextArduinoValue();

}
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::GetNextArduinoValue()
{
  ICurrentParam += 1;
/*
  if(ICurrentParam < ListPlots.count()) {
    emit SignalGetTelemetryValue(&(*PListParamsChannel)[0], &(*PListParamsChannel)[ICurrentParam+1]);
  }
  else {
//    GetPMainWnd()->DestroyArduinoObject();
    if(!disconnect(this, SIGNAL(SignalGetTelemetryValue(QString*,QString*)), GetPMainWnd()->GetPArduino(), SLOT(SlotGetTelemetryValue(QString*,QString*)))) {
      QMessageBox msgBox(QMessageBox::Warning, "void MTelemetryTabChannel::GetNextArduinoValue()",
                         "Problem::\n\ndisconnect(this, SIGNAL(SignalGetTelemetryValue(QString*,QString*)), GetPMainWnd()->GetPArduino(), SLOT(SlotGetTelemetryValue(QString*,QString*))) == false");
      msgBox.exec();
    }
    if(!disconnect(GetPMainWnd()->GetPArduino(), SIGNAL(SignalResultGetTelemetryValue(float)), this, SLOT(SlotResultGetTelemetryValue(float)))) {
      QMessageBox msgBox(QMessageBox::Warning, "void MTelemetryTabChannel::GetNextArduinoValue()",
                         "Problem::\n\ndisconnect(GetPMainWnd()->GetPArduino(), SIGNAL(SignalResultGetTelemetryValue(float)), this, SLOT(SlotResultGetTelemetryValue(float))) == false");
      msgBox.exec();
    }
    emit SignalChannelTelemetryDoneParam(true);
  }
*/

  emit SignalGetTelemetryValue(&(*PListParamsTelemetryChannel)[0],
                               &(*PListParamsTelemetryChannel)[IFirstItemListParamsTelemetry + ICurrentParam*3]); //DeltaNItemListParamsTelemetry]);
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::SlotResultGetTelemetryValue(float value)
{
//QMessageBox msgBox;  msgBox.setText("void MTelemetryTabChannel::SlotResultGetTelemetryValue(float value)");   msgBox.exec();

  qreal dt = (QDateTime::currentDateTime().toMSecsSinceEpoch()-GetPMainWnd()->GetTimeStartTelemetry())/1000.0;

  QString s; s.sprintf("%.1f",value);
  ListLineEditCurrentParams[ICurrentParam]->setText(s);

  ListPlots[ICurrentParam]->AddValue(dt, value);
  Q_ASSERT(ICurrentParam < ListCorrespondingReportPlots.count());
  ListCorrespondingReportPlots[ICurrentParam]->AddValue(dt, value);

  if(value < ListMinNormalValues[ICurrentParam] || ListMaxNormalValues[ICurrentParam] < value) {
    if(value < ListMinNormalValues[ICurrentParam])  IsNonNormalMinValue = true;
    else                                            IsNonNormalMaxValue = true;

    if(!Timer.isActive()) {
      IsFlicker = true;  IsFlickerBrush = true; //!IsFlickerBrush;
      Timer.start(500); // int msec
      UpdateTabBar();
    }
  }

  bool isLastParamInChannel;
//  GetNextArduinoValue();
//  ICurrentParam += 1;

  if(ICurrentParam < ListPlots.count()-1)  isLastParamInChannel = false;
  else {                                   isLastParamInChannel = true;
//    GetPMainWnd()->DestroyArduinoObject();
    if(!disconnect(this, SIGNAL(SignalGetTelemetryValue(QString*,QString*)), GetPMainWnd()->GetPArduino(), SLOT(SlotGetTelemetryValue(QString*,QString*)))) {
      QMessageBox msgBox(QMessageBox::Warning, "void MTelemetryTabChannel::SlotResultGetTelemetryValue(float value)",
                         "Problem::\n\ndisconnect(this, SIGNAL(SignalGetTelemetryValue(QString*,QString*)), GetPMainWnd()->GetPArduino(), SLOT(SlotGetTelemetryValue(QString*,QString*))) == false");
      msgBox.exec();
    }
    if(!disconnect(GetPMainWnd()->GetPArduino(), SIGNAL(SignalResultGetTelemetryValue(float)), this, SLOT(SlotResultGetTelemetryValue(float)))) {
      QMessageBox msgBox(QMessageBox::Warning, "void MTelemetryTabChannel::SlotResultGetTelemetryValue(float value)",
                         "Problem::\n\ndisconnect(GetPMainWnd()->GetPArduino(), SIGNAL(SignalResultGetTelemetryValue(float)), this, SLOT(SlotResultGetTelemetryValue(float))) == false");
      msgBox.exec();
    }
  }

  emit SignalChannelTelemetryDoneParam(dt, value, isLastParamInChannel);
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::SlotTimerSignal()
{
  IsFlickerBrush = !IsFlickerBrush;
  UpdateTabBar();
}
//--------------------------------------------------------------------------------------------
bool MTelemetryTabChannel::GetIsFlicker(bool& isColorBrushFlicker, bool& isNonNormalMinValue, bool& isNonNormalMaxValue)
{
  if(IsFlicker) {
    if(IsFlickerBrush)  isColorBrushFlicker = true; //&ColorBrushTabFlicker;
    else                isColorBrushFlicker = false; //NULL;
    isNonNormalMinValue = IsNonNormalMinValue;  isNonNormalMaxValue = IsNonNormalMaxValue;
  }
  return IsFlicker;
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::StopFlicker()
{
  IsFlicker = false;            IsFlickerBrush = false;
  IsNonNormalMaxValue = false;  IsNonNormalMinValue = false;
  if(Timer.isActive())  Timer.stop();
  UpdateTabBar();
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::UpdateTabBar()
{
  emit SignalUpdateTabBar();
//return;
//  MTelemetryTabWidgetChannels* pTabWidget = qobject_cast<MTelemetryTabWidgetChannels*>(parentWidget());
//  MTelemetryTabWidgetChannels* pTabWidget = qobject_cast<MTelemetryTabWidgetChannels*>(parentWidget());
//  MTelemetryTabWidgetChannels* pTabWidget = (MTelemetryTabWidgetChannels*)parentWidget();
//if(pTabWidget == NULL)   {
//  QMessageBox msgBox; msgBox.setText("void MTelemetryTabChannel::UpdateTabBar()");  msgBox.exec();
//}
//  Q_CHECK_PTR(pTabWidget);

//  pTabWidget->tabBar()->update();
//  MTelemetryTabBarChannels* pTabBar = qobject_cast<MTelemetryTabBarChannels*>(pTabWidget->tabBar());
//  MTelemetryTabBarChannels* pTabBar = (MTelemetryTabBarChannels*)pTabWidget->tabBar();
//  Q_CHECK_PTR(pTabBar);
//  pTabBar->update();
}
//--------------------------------------------------------------------------------------------
