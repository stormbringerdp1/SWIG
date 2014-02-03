#ifndef MTELEMETRYTABBARSTATES_H
#define MTELEMETRYTABBARSTATES_H

#include <QTabBar>
#include <QMouseEvent>
#include <QEvent>

#include "MTelemetryTabReport.h"

//============================================================================================
class MTelemetryTabBarStates : public QTabBar
{
    Q_OBJECT
public:
    explicit MTelemetryTabBarStates(QWidget *parent = 0);

protected:
  virtual void mousePressEvent(QMouseEvent* event);
//  virtual void mouseReleaseEvent(QMouseEvent* event);
//  virtual void mouseMoveEvent(QMouseEvent* event);
//  virtual bool event(QEvent* e);

private:
  int CurrentIndex; // bool IsNewTab;

  bool InsertDataFromFileReport(MTelemetryTabReport* pTab, const QString& pathNameFileReport);

public:
  void CloseTab(QWidget* pTab);

signals:

public slots:
  void SlotIndexChanged(int newIndex);

};
//============================================================================================

#endif // MTELEMETRYTABBARSTATES_H
