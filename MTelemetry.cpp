#include "MTelemetry.h"
#include "MTelemetryTabChannel.h"
//#include "mainwindow.h"
#include "funcs.h"
#include "constants.h"

//#include <QCoreApplication>
#include <QMessageBox>
#include <QScrollArea>
#include <QApplication>
//#include <QGraphicsScene>
//#include <QGraphicsView>
#include <QtGlobal>

//  #include <QSlider>
//  #include <QGraphicsProxyWidget>

//============================================================================================

MTelemetry::MTelemetry(QWidget *parent) :
//    QWidget(parent)
  QSplitter(Qt::Vertical, parent)
{
  SMessageBoxTitle = QCoreApplication::instance()->applicationName()+":  Telemetry";

  Init();

  PFileReport = NULL;
  PStreamFileReport = NULL;
}
//--------------------------------------------------------------------------------------------
MTelemetry::~MTelemetry()
{
  if(PStreamFileReport) {
    PStreamFileReport->flush();  delete PStreamFileReport;
  }
  if(PFileReport) {
    if(PFileReport->isOpen()) PFileReport->close();
    delete PFileReport;
  }
}
//--------------------------------------------------------------------------------------------
void MTelemetry::Init()
{

//===  1) TelemetryChannels:

  QScrollArea* pScrollAreaTabs = new QScrollArea;
  pScrollAreaTabs->setObjectName(QStringLiteral("ScrollAreaTabs"));
//  pScrollAreaTabs->setGeometry(QRect(40, 70, 611, 111));
  pScrollAreaTabs->setWidgetResizable(true);

  QWidget* pScrollAreaTabsContents = new QWidget();
  pScrollAreaTabsContents->setObjectName(QStringLiteral("ScrollAreaTabsContents"));
//  pScrollAreaTabsContents->setGeometry(QRect(0, 0, 609, 109));
//  pScrollAreaTabsContents->setMinimumSize(609,109);

  QRect rect = FillTelemetryChannels(pScrollAreaTabsContents);
  pScrollAreaTabsContents->setMinimumSize(rect.right()+3,rect.bottom()+3);
  pScrollAreaTabs->setWidget(pScrollAreaTabsContents);


//==  2) TelemetryStates:

  QScrollArea* pScrollAreaState = new QScrollArea;
  pScrollAreaState->setObjectName(QStringLiteral("ScrollAreaState"));
//  pScrollAreaState->setGeometry(QRect(40, 70, 611, 111));
  pScrollAreaState->setWidgetResizable(true);

  QWidget* pScrollAreaStateContents = new QWidget();
//  PTabWidgetStates = new MTelemetryTabWidgetStates(pScrollAreaState, PTabWidgetChannels);
//  MTelemetryTabWidgetStates* pScrollAreaStateContents = PTabWidgetStates;
  pScrollAreaStateContents->setObjectName(QStringLiteral("ScrollAreaStateContents"));
//  pScrollAreaStateContents->setGeometry(QRect(0, 0, 609, 109));
//  pScrollAreaStateContents->setMinimumSize(609,109);

  rect = FillTelemetryStates(pScrollAreaStateContents);
  pScrollAreaStateContents->setMinimumSize(rect.right()+3,rect.bottom()+3);
  pScrollAreaState->setWidget(pScrollAreaStateContents);

//=====

  addWidget(pScrollAreaTabs);
  addWidget(pScrollAreaState);
  QList<int> list;    list << 550 << 450;    setSizes(list);

//== Button "Readiness":
  PPushButtonReadiness = new QPushButton(pScrollAreaState);//pScrollAreaStateContents);
  PPushButtonReadiness->setObjectName(QStringLiteral("PushButton"));
  PPushButtonReadiness->setGeometry(QRect(685, 10, 60, 30));
  PPushButtonReadiness->setAutoDefault(true);
//  PPushButtonReadiness->setDefault(true);
  PPushButtonReadiness->setText(QApplication::translate("MainWindow", "Readiness", 0));
  connect(PPushButtonReadiness, SIGNAL(clicked()), GetPMainWnd(), SLOT(SlotSwitchToReadiness()));

//=====
//  StartTelemetry();
  IsTelemetryStarted = false;
}
//--------------------------------------------------------------------------------------------
QRect MTelemetry::FillTelemetryChannels(QWidget* pScrollAreaChannelsContents)
{
//  CurrentIndexTabChannel = -1;
//  QRect rectTelemetryChannels;  QRect rect;
//  PTabWidgetChannels = new QTabWidget(pScrollAreaChannelsContents);

  PTabWidgetChannels = new MTelemetryTabWidgetChannels(pScrollAreaChannelsContents);
  PTabWidgetChannels->setObjectName(QStringLiteral("PTabWidgetChannels"));

  QRect rectTelemetryChannels = PTabWidgetChannels->AddTabs();
/*
  connect(PTabWidgetChannels->tabBar(), SIGNAL(currentChanged(int)), this, SLOT(SlotIndexTabChannelsChanged(int)));
//QSize size = PTabWidgetChannels->iconSize();
//QString s; s.sprintf("size.width() = %d,   size.height() = %d",size.width(),size.height()); // = 16x16
//QMessageBox msgBox;  msgBox.setText(s);   msgBox.exec();

  MTelemetryTabChannel* pTab; //  MPlot* pPlot;  //QWidget* pTab;
  int count = GetPMainWnd()->GetPListParamsTelemetryChannels()->count();
  for (int i = 0; i < count; i++) {  //    pTab = new QWidget();
    pTab = new MTelemetryTabChannel(PTabWidgetChannels, &(*GetPMainWnd()->GetPListParamsTelemetryChannels())[i]);
    rect = pTab->GetRectChannel(); // pTab->setGeometry(rect);
    if(i == 0)  rectTelemetryChannels = rect;
    else        rectTelemetryChannels |= rect;
    PTabWidgetChannels->addTab(pTab, QIcon((*GetPMainWnd()->GetPListParamsTelemetryChannels())[i][1]), (*GetPMainWnd()->GetPListParamsTelemetryChannels())[i][0]);
  }
//tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0));
//tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));
*/

//  rectTelemetryChannels.translate(-rectTelemetryChannels.left(), -rectTelemetryChannels.top());

//  rectTelemetryChannels.translate(3,0);
  rectTelemetryChannels.setTopLeft(QPoint(0,0));//.translate(-rectTelemetryChannels.left(), -rectTelemetryChannels.top());
//  rectTelemetryChannels.setBottom(rectTelemetryChannels.bottom() + PTabWidgetChannels->tabBar()->rect().height());
  rectTelemetryChannels.setBottomRight(QPoint(rectTelemetryChannels.right() + 15,
                                              rectTelemetryChannels.bottom() + 4 + PTabWidgetChannels->tabBar()->rect().height()));
  PTabWidgetChannels->setGeometry(rectTelemetryChannels);
//PTabWidgetChannels->setGeometry(0,0, 200,400);

  return rectTelemetryChannels;
}
//--------------------------------------------------------------------------------------------
/*
void MTelemetry::SlotIndexTabChannelsChanged(int newIndex)
{
  if(CurrentIndexTabChannel != newIndex) {
    QTabBar* pTabBar = PTabWidgetChannels->tabBar();
    if(0 <= CurrentIndexTabChannel) {
      pTabBar->setTabTextColor(CurrentIndexTabChannel, QColor(0,0,0));
    }
    pTabBar->setTabTextColor(newIndex, QColor(0,0,255));
    CurrentIndexTabChannel = newIndex;
  }
}
*/
//--------------------------------------------------------------------------------------------
QRect MTelemetry::FillTelemetryStates(QWidget* pScrollAreaStatesContents)
{
//  QRect rectTelemetryStates;
//  PTabWidgetStates = new QTabWidget(pScrollAreaStatesContents);
  PTabWidgetStates = new MTelemetryTabWidgetStates(pScrollAreaStatesContents, PTabWidgetChannels);
  PTabWidgetStates->setObjectName(QStringLiteral("PTabWidgetStates"));
//  PTabWidgetStates->setGeometry(QRect(0,0, 700,400));

  QRect rectTelemetryStates = PTabWidgetStates->AddTabs();

/*
  QList<QString> list;    list << "State" << "Report" << " ";

  QWidget* pTab; // MPlot* pPlot;
//  int count = list.count();
  for(int i = 0; i < list.count(); i++) {
//    pTab = new QWidget(PTabWidgetStates);
//    PTabWidgetStates->addTab(pTab, list[i]);
    if(i == 0) {
      pTab = new QWidget(PTabWidgetStates);
      PTabWidgetStates->addTab(pTab, list[i]);
//      QGraphicsScene* pSceneGyrohorizon = new QGraphicsScene(20.0, 20.0, 325.0, 325.0, pTab);
      QGraphicsScene* pSceneGyrohorizon = new QGraphicsScene(pTab);
      QGraphicsView* pViewGyrohorizon = new QGraphicsView(pSceneGyrohorizon, pTab);
      pViewGyrohorizon->setGeometry(20,20, 321,321);

//=================

QSlider* pSliderPitch = new QSlider(pTab);
pSliderPitch->setObjectName(QStringLiteral("verticalSlider"));
pSliderPitch->setOrientation(Qt::Vertical);
pSliderPitch->setGeometry(QRect(660, 3, 16, 350));
pSliderPitch->setMinimum(-360); //1080);
pSliderPitch->setMaximum(360); //1080);
pSliderPitch->setSingleStep(1);
pSliderPitch->setPageStep(36);
pSliderPitch->setValue(0);
pSliderPitch->setTickPosition(QSlider::TicksAbove);
//connect(pSliderPitch, SIGNAL(valueChanged(int)), PEkranoplanGLWidget, SLOT(SetPitchAngle(int)));
//connect(pSliderPitch, SIGNAL(valueChanged(int)), PGyrohorizon, SLOT(SetPitchAngle(int)));

QSlider* pSliderRoll = new QSlider(pTab);
pSliderRoll->setObjectName(QStringLiteral("horizontalSlider"));
pSliderRoll->setOrientation(Qt::Horizontal);
pSliderRoll->setGeometry(QRect(350, 170, 300, 16));
pSliderRoll->setMinimum(-360);
pSliderRoll->setMaximum(360);
pSliderRoll->setSingleStep(1);
pSliderRoll->setPageStep(36);
pSliderRoll->setValue(0);
pSliderRoll->setTickPosition(QSlider::TicksAbove);
//connect(pSliderRoll, SIGNAL(valueChanged(int)), PEkranoplanGLWidget, SLOT(SetRollAngle(int)));
//connect(pSliderRoll, SIGNAL(valueChanged(int)), PGyrohorizon, SLOT(SetRollAngle(int)));

//=================

//      PEkranoplanGLWidget = new MEkranoplanGLWidget(pViewGyrohorizon); // !


//      PGyrohorizon = new MGyrohorizon(pViewGyrohorizon, PEkranoplanGLWidget, pSliderPitch, pSliderRoll);
//+      PGyrohorizon = new MGyrohorizon(pViewGyrohorizon, pSliderPitch, pSliderRoll);
//+      PGyrohorizon->setGeometry(0,0, 320,320);
      PGyrohorizon = new MGyrohorizon(pTab, pSliderPitch, pSliderRoll);
      PGyrohorizon->setGeometry(20,20, 320,320);
//PGyrohorizon->setStyleSheet(QLatin1String("background: transparent;"));
//+      QGraphicsProxyWidget* pw = pSceneGyrohorizon->addWidget(PGyrohorizon);
//      pw->setRotation(10.0);
//pw->setOpacity(0.3);

//pViewGyrohorizon->rotate(30.0);

//      QGraphicsView* pViewGyrohorizonStatic = new QGraphicsView(pSceneGyrohorizon, pTab);
//      pViewGyrohorizonStatic->setGeometry(20,20, 321,321);

//pViewGyrohorizonStatic->rotate(30.0);

//  pViewGyrohorizon->setViewport(PEkranoplanGLWidget); // !

//PEkranoplanGLWidget = new MEkranoplanGLWidget(pViewGyrohorizon); // !
//      PEkranoplanGLWidget->setParent(pViewGyrohorizon);
//      QGraphicsProxyWidget* pw1 = pSceneGyrohorizon->addWidget(PEkranoplanGLWidget);


      PEkranoplanGL = new MEkranoplanGL(pViewGyrohorizon); // !
//      PEkranoplanGL = new MEkranoplanGL(PGyrohorizon); // !
//      PEkranoplanGL = new MEkranoplanGL(pSceneGyrohorizon); // !
//      PEkranoplanGL = new MEkranoplanGL(0); // !
//      PEkranoplanGLWidget->setWindowOpacity(0.0);
//PEkranoplanGLWidget->setStyleSheet(QLatin1String("background: transparent;"));

//PEkranoplanGLWidget->hide();
//PEkranoplanGLWidget->setVisible(false);

//+      QGraphicsProxyWidget* pw1 = pSceneGyrohorizon->addWidget(PEkranoplanGLWidget);
//  pViewGyrohorizon->setViewport(PEkranoplanGLWidget); // !
//pw1->setOpacity(0.3);

//QGraphicsProxyWidget* pw = pSceneGyrohorizon->addWidget(PGyrohorizon);


      PGyrohorizon->SetPEkranoplanGL(PEkranoplanGL);

//=================
connect(pSliderPitch, SIGNAL(valueChanged(int)), PEkranoplanGL, SLOT(SlotSetPitchAngle(int)));
connect(pSliderPitch, SIGNAL(valueChanged(int)), PGyrohorizon, SLOT(SlotSetPitchAngle(int)));
//connect(pSliderPitch, SIGNAL(sliderPressed()),  PGyrohorizon, SLOT(SliderPitchPressed()));
//connect(pSliderPitch, SIGNAL(sliderReleased()), PGyrohorizon, SLOT(SliderPitchReleased()));


connect(pSliderRoll, SIGNAL(valueChanged(int)), PEkranoplanGL, SLOT(SlotSetRollAngle(int)));
connect(pSliderRoll, SIGNAL(valueChanged(int)), PGyrohorizon, SLOT(SlotSetRollAngle(int)));
//=================

    }
    else if(i == 1) {
      MTelemetryTabReport* pTabReport = new MTelemetryTabReport(PTabWidgetStates);
//      pTabReport->setMouseTracking(true);
      PTabWidgetStates->addTab(pTabReport, list[i]);
//      pTabReport->setMouseTracking(true);

      MTelemetryTabChannel* pTabChannel;

      QString sNameChannel;   QString sNameParamChannel;
      QString sMinParamYNormalValue;  QString sMaxParamYNormalValue;

      int countParamsTelemetryChannels = GetPMainWnd()->GetPListParamsTelemetryChannels()->count();
      QList<QString>        listNamesChannels;
      QList<int>            listCountPlotsInChannels;
      QList<QList<QString>> listNameParamsInChannels;   QList<QString> list;

      for(int n = 0; n < countParamsTelemetryChannels; n++) {
        pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(n));
        Q_CHECK_PTR(pTabChannel);
        sNameChannel = PTabWidgetChannels->tabBar()->tabText(n);
        listNamesChannels << sNameChannel;
        listCountPlotsInChannels << pTabChannel->GetPListPlots()->count();

        for(int j = 0; j < pTabChannel->GetPListPlots()->count(); j++) {
          int m = GetPMainWnd()->GetIFirstItemListParamsTelemetry() + j*3; //GetPMainWnd()->GetDeltaNItemListParamsTelemetry();
          sNameParamChannel = (*pTabChannel->GetPListParamsTelemetryChannel())[m];
          sMinParamYNormalValue = (*pTabChannel->GetPListParamsTelemetryChannel())[m+1];
          sMaxParamYNormalValue = (*pTabChannel->GetPListParamsTelemetryChannel())[m+2];
          list << sNameParamChannel << sMinParamYNormalValue << sMaxParamYNormalValue;
        }
        listNameParamsInChannels << list;  list.clear();
      }

      QRect rectReport = FillTabReport(pTabReport, countParamsTelemetryChannels, listNamesChannels, listCountPlotsInChannels, listNameParamsInChannels, true);//isAssignCorrespondingReportPlot)
      rectTelemetryStates = rectReport;
    }
    else {
      pTab = new QWidget(PTabWidgetStates);
      int index = PTabWidgetStates->addTab(pTab, list[i]);
//      if(index == list.count()-1)  PTabWidgetStates ->setTabToolTip(index, "Open past report");
//      if(index == list.count()-1)  PTabWidgetStates ->setTabWhatsThis(index, "Open past report");
    }
  }
*/


  PTabWidgetStates->setGeometry(rectTelemetryStates);

  return rectTelemetryStates;
}
//--------------------------------------------------------------------------------------------
/*
QRect MTelemetry::FillTabReport(MTelemetryTabReport* pTabReport, int countParamsTelemetryChannels, QList<QString>& listNamesChannels,
                                QList<int>& listCountPlotsInChannels, QList<QList<QString>>& listNameParamsInChannels,
                                bool isAssignCorrespondingReportPlot)
{
  MTelemetryTabChannel* pTabChannel = NULL;
  QString sNameChannel;  QString sNameParam;
  QRect rectReport;  int yTopChannel = 0;
  QLineEdit* pLineEditNameChannel;  QRect rect;
  MPlot* pPlot;   QRect rectPlot(10,10, 321,321);

  int n = 0;
//      for (int n = 0; n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count(); n++) {
  while(n < countParamsTelemetryChannels) {

    yTopChannel += 10;

    pLineEditNameChannel = new QLineEdit(pTabReport);
    pLineEditNameChannel->setObjectName(QStringLiteral("LineEditNameChannel"));
    rect = QRect(285, yTopChannel, 100, 20);
    pLineEditNameChannel->setGeometry(rect);
    pLineEditNameChannel->setFrame(false);
    pLineEditNameChannel->setReadOnly(true);
    pLineEditNameChannel->setStyleSheet(QLatin1String("background: transparent;"));
    pLineEditNameChannel->setAlignment(Qt::AlignCenter);
//        sNameChannel = PTabWidgetChannels->tabBar()->tabText(n);
    sNameChannel = listNamesChannels[n];
    pLineEditNameChannel->setText(sNameChannel);

    if(n == 0)  rectReport = rect;
    else        rectReport |= rect;

    yTopChannel += 30;
    rectPlot.moveTop(yTopChannel);

    if(isAssignCorrespondingReportPlot) {
      pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(n));
      Q_CHECK_PTR(pTabChannel);
    }
    int j = 0;
//        for(int j = 0; j < pTabChannel->GetPListPlots()->count(); j ++) {
    while(j < listCountPlotsInChannels[n]) {
      Q_ASSERT(listNameParamsInChannels[n].count() == 3*2);
//      if(listNameParamsInChannels[n].count() != 3*2) {
//        QMessageBox msgBox(QMessageBox::Critical, "QRect MTelemetry::FillTabReport(...)",
//                                                  "if(listNameParamsInChannels[n].count() != 3*2) == TRUE (!)");   msgBox.exec();
//      }
      sNameParam = listNameParamsInChannels[n][j*3]; //GetPMainWnd()->GetDeltaNItemListParamsTelemetry()];
      pPlot = new MPlot(pTabReport, true, sNameParam.toStdString().c_str(), listNameParamsInChannels[n][j*3+1].toFloat(), listNameParamsInChannels[n][j*3+2].toFloat());
      pPlot->setGeometry(rectPlot);
      if(isAssignCorrespondingReportPlot)  pTabChannel->AssignCorrespondingReportPlot(pPlot);
      else                                 pTabReport->AddPlot(pPlot);
      rectReport |= rectPlot;
      rectPlot.translate(rectPlot.width()+10,0);
      j += 1;
    }

    yTopChannel += rectPlot.height()+20;
    rectPlot.moveTopLeft(QPoint(10,yTopChannel));

    n += 1;
  }

  rectReport.setTopLeft(QPoint(0,0));
  rectReport.setBottomRight(QPoint(rectReport.right() + 15,
                                   rectReport.bottom() + 4 + PTabWidgetStates->tabBar()->rect().height()));
  return rectReport;
}
*/
//--------------------------------------------------------------------------------------------
void MTelemetry::DoTelemetry()
{
  if(IsTelemetryStarted)  return;

  IsTelemetryStarted = true;

  QDateTime currentDataTime = QDateTime::currentDateTime();

  qint64 timeStartTelemetry = currentDataTime.toMSecsSinceEpoch();
  GetPMainWnd()->GetTimer().start(1000/12); // int msec
  GetPMainWnd()->SetTimeStartTelemetry(timeStartTelemetry);

  connect(&GetPMainWnd()->GetTimer(), SIGNAL(timeout()), this, SLOT(SlotTimerSignal()));

  PrepareFileReport(currentDataTime);

/*
 for(qreal dt = 0.0; dt < 21.0; dt++) {
  MTelemetryTabChannel* pTab = qobject_cast<MTelemetryTabChannel*>(PTabWidget->widget(0));
  (*pTab->GetPListPlots())[1]->AddValue(dt, ((qrand()*1.0)/RAND_MAX)*100.0);
 }
*/

  ICurrentChannel = -1;

  IsReadyNextChannel = true;
  IsReadyNextChannelParam = false;

//  SlotTimerSignal();
}
//--------------------------------------------------------------------------------------------
void MTelemetry::PrepareFileReport(QDateTime& currentDataTime)
{
  NameFileReport = "Report - ";  NameFileReport += currentDataTime.toString("dd.MMM.yyyy - HH.mm.ss");  NameFileReport += ".wig";
  PFileReport = new QFile(NameFileReport);
  if(PFileReport->open(QIODevice::WriteOnly | QIODevice::Text)) {
    PStreamFileReport = new QTextStream(PFileReport);
  }
  else {
    QMessageBox msgBox; msgBox.setText("Problem file \""+NameFileReport+"\"");   msgBox.exec();
  }

  *PStreamFileReport << ReportFileVersion;   *PStreamFileReport << "\n\n";

  ListLengthAllParams.clear();
  MTelemetryTabChannel* pTabChannel;  QString sNameChannel;  QString sNameParamChannel;

//= Calculation of the Channel Lengths:
  QList<int> listLengthChannels;  int lengthChannel;   int lengthNameParamChannel;
  for(int n = 0; n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count(); n++) {
    lengthChannel = 0;

    pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(n));
    Q_CHECK_PTR(pTabChannel);
    for(int j = 0; j < pTabChannel->GetPListPlots()->count(); j ++) {
//1), 3)
      lengthChannel += 8; // "T(sec)  "; // = 8 chs
      ListLengthAllParams << 8;
//2), 4)
      sNameParamChannel = (*pTabChannel->GetPListParamsTelemetryChannel())[GetPMainWnd()->GetIFirstItemListParamsTelemetry() + j*3]; //GetPMainWnd()->GetDeltaNItemListParamsTelemetry()];
      lengthNameParamChannel = qMax(sNameParamChannel.length(), 16);
//      lengthChannel += sNameParamChannel.length(); // "Rotation Speed (RPM)"
      lengthChannel += lengthNameParamChannel; // "Rotation Speed (RPM)"
                                               // "Power Consumption (W)"
      if(j < pTabChannel->GetPListPlots()->count()-1) {
//2)
        lengthChannel += 4; // "    "
        ListLengthAllParams << lengthNameParamChannel + 4;
      }
      else {
//4)
        if(n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count()-1) {
          lengthChannel += 3; //3+1+3; // to "   |   ":  3+1+3 chs
          ListLengthAllParams << lengthNameParamChannel + 3; // to  "   |   ": 3+1+3;
        }
        else {
          ListLengthAllParams << lengthNameParamChannel;
        }
      }
    }
    listLengthChannels << lengthChannel;
  }
  NAllWritingParams = ListLengthAllParams.count();
  IWritingParam = 0;

//= Writing the Channel Names:
  for(int n = 0; n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count(); n++) {
    sNameChannel = PTabWidgetChannels->tabBar()->tabText(n);
    sNameChannel = sNameChannel.leftJustified(listLengthChannels[n]);
    *PStreamFileReport << sNameChannel;
    if(n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count()-1) {
//5)
      *PStreamFileReport << "|   ";
    }
  }
  *PStreamFileReport << "\n";

//= Writing the Channel Params Names:
  int m = 0;  QString sParamX;  QString sParamY;
  for(int n = 0; n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count(); n++) {
    pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(n));
    Q_CHECK_PTR(pTabChannel);
    for(int j = 0; j < pTabChannel->GetPListPlots()->count(); j ++) {
      sParamX = "T(sec)";
      sParamX = sParamX.leftJustified(ListLengthAllParams[m]);  m += 1;
      *PStreamFileReport << sParamX;
      sParamY = (*pTabChannel->GetPListParamsTelemetryChannel())[GetPMainWnd()->GetIFirstItemListParamsTelemetry() + j*3]; //GetPMainWnd()->GetDeltaNItemListParamsTelemetry()];
      sParamY = sParamY.leftJustified(ListLengthAllParams[m]);  m += 1;
      *PStreamFileReport << sParamY;
    }
    if(n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count()-1) {
//5)
      *PStreamFileReport << "|   ";
    }
  }
  *PStreamFileReport << "\n";

//= Writing the Min and Max Normal Values:
  QString sMinNormalValue;  QString sMaxNormalValue;
  m = 0;  QString sRange;
  for(int n = 0; n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count(); n++) {
    pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(n));
    Q_CHECK_PTR(pTabChannel);
    for(int j = 0; j < pTabChannel->GetPListPlots()->count(); j ++) {
      sRange = " ";  sRange = sRange.leftJustified(ListLengthAllParams[m]);  m += 1;
      *PStreamFileReport << sRange;
      sMinNormalValue.sprintf("%.2f", (*pTabChannel->GetPListMinNormalValues())[j]);
      sMaxNormalValue.sprintf("%.2f", (*pTabChannel->GetPListMaxNormalValues())[j]);
      sRange = sMinNormalValue + " -- " + sMaxNormalValue;
      sRange = sRange.leftJustified(ListLengthAllParams[m]);  m += 1;
      *PStreamFileReport << sRange;
    }
    if(n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count()-1) {
      *PStreamFileReport << "|   ";
    }
  }
  *PStreamFileReport << "\n";
  PStreamFileReport->flush();
}
//--------------------------------------------------------------------------------------------
void MTelemetry::SlotTimerSignal()
{
  if(IsReadyNextChannel)  {
    IsReadyNextChannel = false;

    ICurrentChannel += 1;
    if(ICurrentChannel >= PTabWidgetChannels->count()) {
      PStreamFileReport->flush();
      ICurrentChannel = 0;
    }

    MTelemetryTabChannel* pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(ICurrentChannel));
    Q_CHECK_PTR(pTabChannel);
    connect(pTabChannel, SIGNAL(SignalChannelTelemetryDoneParam(qreal,float,bool)), this, SLOT(SlotChannelTelemetryDoneParam(qreal,float,bool)));

    pTabChannel->BeginGetArduinoValues();
  }
  else {
    if(IsReadyNextChannelParam) {  IsReadyNextChannelParam = false;

      MTelemetryTabChannel* pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(ICurrentChannel));
      Q_CHECK_PTR(pTabChannel);

      pTabChannel->GetNextArduinoValue();
    }
  }

/*
//   double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
//  QString time = QDateTime::toString("mm:ss.z");
//  pPlot->AddValue(1.0, 1.0); pPlot->AddValue(2.0, 2.0);

//  QDateTime dt;
//  ListTabPlots[0]->AddValue(QDateTime::currentDateTime().toString("mm.z"), ((qrand()*1.0)/RAND_MAX)*100.0);
qreal dt = (QDateTime::currentDateTime().toMSecsSinceEpoch()-TimeStart)/1000.0;

MTelemetryTabChannel* pTab = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(0));
(*pTab->GetPListPlots())[1]->AddValue(dt, ((qrand()*1.0)/RAND_MAX)*100.0);


  MTelemetryTabChannel* pTab;
  for(int i = 0; i < PTabWidgetChannels->count(); i++) {
    pTab = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(i));
    for(int n = 0; n < (*GetPMainWnd()->GetPListParamsTelemetryChannels())[i].count()-1; n++) {

   (*pTab->GetPListPlots())[1]->AddValue(dt, ((qrand()*1.0)/RAND_MAX)*100.0);

  }
*/

//QMessageBox msgBox;  msgBox.setText("1");   msgBox.exec();

}
//--------------------------------------------------------------------------------------------
void MTelemetry::SlotChannelTelemetryDoneParam(qreal dt, float value, bool isLastParamInChannel)
{
  WriteFileReportValue(dt, value, isLastParamInChannel);

//QMessageBox msgBox;  msgBox.setText("void MTelemetry::SlotChannelTelemetryDone()");   msgBox.exec();
  if(!isLastParamInChannel) {
    IsReadyNextChannelParam = true;
    return;
  }

  MTelemetryTabChannel* pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(ICurrentChannel));
  if(!disconnect(pTabChannel, SIGNAL(SignalChannelTelemetryDoneParam(qreal,float,bool)), this, SLOT(SlotChannelTelemetryDoneParam(qreal,float,bool)))) {
    QMessageBox msgBox(QMessageBox::Warning, SMessageBoxTitle,
                       "Problem::\n\ndisconnect(pTab, SIGNAL(SignalChannelTelemetryDone()), this, SLOT(SlotChannelTelemetryDone())) == false");
    msgBox.exec();
  }
  IsReadyNextChannel = true;
//  IsReadyNextChannelParam = true;
}
//--------------------------------------------------------------------------------------------
void MTelemetry::WriteFileReportValue(qreal dt, float value, bool isLastParamInChannel)
{
  if(PStreamFileReport)  {  QString s;
    if(IWritingParam >= NAllWritingParams)  IWritingParam = 0;
    s.sprintf("%.3f", dt);
    s = s.leftJustified(ListLengthAllParams[IWritingParam]);  IWritingParam += 1;
    *PStreamFileReport << s;
    s.sprintf("%.5f", value);
    s = s.leftJustified(ListLengthAllParams[IWritingParam]);  IWritingParam += 1;
    *PStreamFileReport << s;

    if(isLastParamInChannel) {
      if(ICurrentChannel < PTabWidgetChannels->count()-1)  s = "|   ";
      else                                                 s = "\n";
      *PStreamFileReport << s;
    }
  }
}
//--------------------------------------------------------------------------------------------
