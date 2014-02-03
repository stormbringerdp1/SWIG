#ifndef MTELEMETRYTABWIDGETCHANNELS_H
#define MTELEMETRYTABWIDGETCHANNELS_H

#include <QTabWidget>

//============================================================================================
class MTelemetryTabWidgetChannels : public QTabWidget
{
    Q_OBJECT
public:
    explicit MTelemetryTabWidgetChannels(QWidget *parent = 0);

  QRect AddTabs();

signals:

public slots:

};
//============================================================================================

#endif // MTELEMETRYTABWIDGETCHANNELS_H
