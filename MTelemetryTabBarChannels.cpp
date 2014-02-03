#include "MTelemetryTabBarChannels.h"
#include "MTelemetryTabWidgetChannels.h"
#include "MTelemetryTabChannel.h"

#include <QPainter>
  #include <QMessageBox>
#include <QtGlobal>

//============================================================================================
MTelemetryTabBarChannels::MTelemetryTabBarChannels(QWidget *parent)
                        : QTabBar(parent)
{
  CurrentIndex = 0;//-1;
  connect(this, SIGNAL(currentChanged(int)), SLOT(SlotCurrentChanged(int)));
  connect(this, SIGNAL(tabBarClicked(int)), SLOT(SlotTabBarClicked(int)));
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabBarChannels::SlotTabBarClicked(int clickedIndex)
{
  MTelemetryTabWidgetChannels* pTabWidgetChannels = qobject_cast<MTelemetryTabWidgetChannels*>(parent());
  Q_ASSERT(pTabWidgetChannels != NULL); // Q_CHECK_PTR(pTabWidgetChannels);

  MTelemetryTabChannel* pTabChannel = qobject_cast<MTelemetryTabChannel*>(pTabWidgetChannels->widget(clickedIndex));
  Q_ASSERT(pTabChannel != NULL); // Q_CHECK_PTR(pTabChannel);
  bool isColorBrushFlicker;  bool isNonNormalMinValue;  bool isNonNormalMaxValue;
  if(pTabChannel->GetIsFlicker(isColorBrushFlicker, isNonNormalMinValue, isNonNormalMaxValue))  pTabChannel->StopFlicker();
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabBarChannels::SlotCurrentChanged(int newIndex)
{
//  if(CurrentIndex != newIndex) {
//  if(0 <= CurrentIndex) {
  setTabTextColor(CurrentIndex, QColor(0,0,0));
//  }
  setTabTextColor(newIndex, QColor(0,0,255));
  CurrentIndex = newIndex;
//  }
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabBarChannels::paintEvent(QPaintEvent* event)
{
  QTabBar::paintEvent(event);
//--
  //create a QPainter and pass a pointer to the device.
  //A paint device can be a QWidget, a QPixmap or a QImage
  QPainter painter(this);

  painter.setPen(Qt::NoPen);

  MTelemetryTabWidgetChannels* pTabWidgetChannels = qobject_cast<MTelemetryTabWidgetChannels*>(parent());
  Q_ASSERT(pTabWidgetChannels != NULL); // Q_CHECK_PTR(pTabWidget);

  MTelemetryTabChannel* pTabChannel;  //  QColor* pColorBrushTab;
  bool isColorBrushFlicker;  bool isNonNormalMinValue;  bool isNonNormalMaxValue;
  for(int i = 0; i < pTabWidgetChannels->count(); i++) {
    pTabChannel = qobject_cast<MTelemetryTabChannel*>(pTabWidgetChannels->widget(i));
    Q_ASSERT(pTabChannel != NULL); // Q_CHECK_PTR(pTabChannel);

//    if(pTabChannel->GetIsFlicker(pColorBrushTab) && pColorBrushTab != NULL) {
    if(pTabChannel->GetIsFlicker(isColorBrushFlicker, isNonNormalMinValue, isNonNormalMaxValue)) {
      if(isColorBrushFlicker) {
        painter.setBrush(QBrush(QColor(255,0,0, 100)));
        QRect rect= tabRect(i);
        if(currentIndex() != i) {
          rect.setTopLeft(rect.topLeft()+=QPoint(1,2));
          rect.setBottomRight(rect.bottomRight()+=QPoint(-1,0));
        }
        else {
          rect.setTopLeft(rect.topLeft()+=QPoint(-1,0));
          rect.setBottomRight(rect.bottomRight()+=QPoint(1,0));
        }

        if(!isNonNormalMaxValue) rect.setTop(rect.top()+rect.height()/2);
        if(!isNonNormalMinValue) rect.setBottom(rect.bottom()-rect.height()/2);

        painter.drawRect(rect);
      }
    }
  }
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabBarChannels::SlotUpdateTabBar()
{
  update();
}
//--------------------------------------------------------------------------------------------
