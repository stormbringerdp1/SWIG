#include "MLabelCloseTab.h"
#include "MTelemetryTabBarStates.h"

  #include <QMessageBox>
//  #include <QToolTip>

//============================================================================================
MLabelCloseTab::MLabelCloseTab(QWidget* parent, QWidget* pTab) :
    QLabel(parent), PTab(pTab)
{
  setPixmap(QPixmap(QString::fromUtf8(":/RemoveTabInactive.ico")));
  setAttribute(Qt::WA_Hover, true);
}
//--------------------------------------------------------------------------------------------
bool MLabelCloseTab::event(QEvent* event)
{
  bool b = QLabel::event(event);
//--
  if(event->type() == QEvent::HoverEnter) {
//QMessageBox msgBox;  msgBox.setText("QEvent::HoverEnter");   msgBox.exec();
    setPixmap(QPixmap(QString::fromUtf8(":/RemoveTabActive.ico")));
//    QToolTip::showText(QPoint(10,10), QString("Xe-Xe"), this, geometry(), 3000); //int msecDisplayTime)
  }
  if(event->type() == QEvent::HoverLeave) {
//QMessageBox msgBox;  msgBox.setText("QEvent::HoverLeave");   msgBox.exec();
    setPixmap(QPixmap(QString::fromUtf8(":/RemoveTabInactive.ico")));
  }

  return b;
}
//--------------------------------------------------------------------------------------------
void MLabelCloseTab::mousePressEvent(QMouseEvent* event)
{
  QLabel::mousePressEvent(event);
//--
//QString s; s.sprintf("margin() = %d",margin()); // = 0
//QMessageBox msgBox;  msgBox.setText(s);   msgBox.exec();

  if(event->button() == Qt::LeftButton) {
    MTelemetryTabBarStates* pTabBar = qobject_cast<MTelemetryTabBarStates*>(parent());
    Q_CHECK_PTR(pTabBar);
    pTabBar->CloseTab(PTab);
//QMessageBox msgBox;  msgBox.setText("event->button() == Qt::LeftButton");   msgBox.exec();
  }
}
//--------------------------------------------------------------------------------------------
