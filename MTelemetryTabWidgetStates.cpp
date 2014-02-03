#include "MTelemetryTabWidgetStates.h"
#include "MTelemetryTabBarStates.h"
#include "MTelemetryTabChannel.h"
#include "funcs.h"

#include <QList>
#include <QSlider>
#include <QGraphicsScene>
#include <QGraphicsView>

//============================================================================================
MTelemetryTabWidgetStates::MTelemetryTabWidgetStates(QWidget *parent, MTelemetryTabWidgetChannels* pTabWidgetChannels)
                         : QTabWidget(parent), PTabWidgetChannels(pTabWidgetChannels)
{
  MTelemetryTabBarStates* pTabBar = new MTelemetryTabBarStates(this);
  setTabBar(pTabBar);
}
//--------------------------------------------------------------------------------------------
QRect MTelemetryTabWidgetStates::AddTabs()
{
  QList<QString> listNameTabs;    listNameTabs << "State" << "Report" << "";

  QRect rectTelemetryStates;

  QWidget* pTab; // MPlot* pPlot;
//  int count = list.count();
  for(int i = 0; i < listNameTabs.count(); i++) {
//    pTab = new QWidget(PTabWidgetStates);
//    PTabWidgetStates->addTab(pTab, list[i]);
    if(i == 0) {
      pTab = new QWidget(this);
      addTab(pTab, listNameTabs[i]);
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
      MTelemetryTabReport* pTabReport = new MTelemetryTabReport(this);
//      pTabReport->setMouseTracking(true);
      addTab(pTabReport, listNameTabs[i]);
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
      pTab = new QWidget(this);
      int index = addTab(pTab, listNameTabs[i]);
//      if(index == listNameTabs.count()-1) {
//        setTabToolTip(index, "Open past report");
//        tabBar()->setToolTipDuration(2000); //(int msec)
//      }
//      if(index == list.count()-1)  PTabWidgetStates ->setTabWhatsThis(index, "Open past report");
    }
  }
  return rectTelemetryStates;
}
//--------------------------------------------------------------------------------------------
QRect MTelemetryTabWidgetStates::FillTabReport(MTelemetryTabReport* pTabReport, int countParamsTelemetryChannels, QList<QString>& listNamesChannels,
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
                                   rectReport.bottom() + 4 + tabBar()->rect().height()));
  return rectReport;
}
//--------------------------------------------------------------------------------------------
