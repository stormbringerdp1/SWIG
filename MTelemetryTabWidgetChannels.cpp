#include "MTelemetryTabWidgetChannels.h"
#include "MTelemetryTabBarChannels.h"

#include "MTelemetryTabChannel.h"
#include "funcs.h"

//============================================================================================
MTelemetryTabWidgetChannels::MTelemetryTabWidgetChannels(QWidget *parent) :
    QTabWidget(parent)
{
  MTelemetryTabBarChannels* pTabBar = new MTelemetryTabBarChannels(this);
  pTabBar->setIconSize(QSize(16,11));

  setTabBar(pTabBar);
}
//--------------------------------------------------------------------------------------------
QRect MTelemetryTabWidgetChannels::AddTabs()
{
  QRect rectTelemetryChannels;  QRect rect;

//QSize size = PTabWidgetChannels->iconSize();
//QString s; s.sprintf("size.width() = %d,   size.height() = %d",size.width(),size.height()); // = 16x16
//QMessageBox msgBox;  msgBox.setText(s);   msgBox.exec();

  MTelemetryTabBarChannels* pTabBar = qobject_cast<MTelemetryTabBarChannels*>(tabBar());
  Q_CHECK_PTR(pTabBar);

  MTelemetryTabChannel* pTabChannel; //  MPlot* pPlot;  //QWidget* pTab;
  int count = GetPMainWnd()->GetPListParamsTelemetryChannels()->count();
  for (int i = 0; i < count; i++) {  //    pTabChannel = new QWidget();
    pTabChannel = new MTelemetryTabChannel(this, &(*GetPMainWnd()->GetPListParamsTelemetryChannels())[i]);
    rect = pTabChannel->GetRectChannel(); // pTab->setGeometry(rect);
    if(i == 0)  rectTelemetryChannels = rect;
    else        rectTelemetryChannels |= rect;
    addTab(pTabChannel, QIcon((*GetPMainWnd()->GetPListParamsTelemetryChannels())[i][1]), (*GetPMainWnd()->GetPListParamsTelemetryChannels())[i][0]);

    connect(pTabChannel, SIGNAL(SignalUpdateTabBar()), pTabBar, SLOT(SlotUpdateTabBar()));
  }
//tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0));
//tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));

  return rectTelemetryChannels;
}
//--------------------------------------------------------------------------------------------
