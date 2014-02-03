#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MReadiness.h"
#include "MTelemetry.h"
#include "MArduino.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QString>
#include <QThread>

#include <QTimer>

//============================================================================================

namespace Ui {
class MainWindow;
}

//============================================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
//--
private:
  QSplitter* PMainSplitter;
  QList<int> ListMainSplitterSizes; //нужет для хранения сплитеров, так кути работает

  QGraphicsScene*       PSceneEkranoplan;
  QGraphicsView*        PViewEkranoplan;
  QGraphicsEllipseItem* PTestSpot;
  MReadiness*           PReadiness;
  MTelemetry*           PTelemetry;
//следующие переменные для нижней части полуэкрана для хранения листов
  QList<QString>        ListNamesEngines;
  QList<QString>        ListNamesSensors;
  QList<QString>        ListNamesServoMotors;

//  QList<QString>        ListTextTestChannels;
  QList<QList<QString>> ListParamsReadinessChannels;  int IFirstItemListParamsReadiness;  int DeltaNItemListParamsReadiness;
  QList<QList<QString>> ListParamsTelemetryChannels;  int IFirstItemListParamsTelemetry;//  int DeltaNItemListParamsTelemetry;

  QTimer Timer;
  qint64 TimeStartTelemetry;

  void Init();
  void InitLists(QString& sTextTest0);
  void SwitchSplitterFromTo(QWidget* pWidgetFrom, QWidget* pWidgetTo);


  MArduino* PArduino;
  QThread   ThreadArduino;

public:

  QList<QString>* GetPListNamesEngines() { return &ListNamesEngines; }
  QList<QString>* GetPListNamesSensors() { return &ListNamesSensors; }
  QList<QString>* GetPListNamesServoMotors() { return &ListNamesServoMotors; }

//  QList<QString>*        GetPListTextTestChannels() { return &ListTextTestChannels; }
  QList<QList<QString>>* GetPListParamsReadinessChannels() { return &ListParamsReadinessChannels; }
  QList<QList<QString>>* GetPListParamsTelemetryChannels() { return &ListParamsTelemetryChannels; }

  int GetIFirstItemListParamsReadiness() { return IFirstItemListParamsReadiness; }
  int GetDeltaNItemListParamsReadiness() { return DeltaNItemListParamsReadiness; }

  int GetIFirstItemListParamsTelemetry() { return IFirstItemListParamsTelemetry; }
//  int GetDeltaNItemListParamsTelemetry() { return DeltaNItemListParamsTelemetry; }

//  QGraphicsScene* GetPSceneEkranoplan() { return PSceneEkranoplan; }


//  QThread* GetPThreadArduino() { return &ThreadArduino; }
  const MArduino* GetPArduino() { return PArduino; }
//  void CreateArduinoObject(const QObject* pSenderReceiver, const char* signalThis, const char* slotArduino,
//                                                           const char* signalArduino, const char* slotThis);
//  void DestroyArduinoObject();

  MTelemetry* GetPTelemetry() { return PTelemetry; }

  QTimer& GetTimer() { return Timer; }

  void  SetTimeStartTelemetry(const qint64 timeStartTelemetry) { TimeStartTelemetry = timeStartTelemetry; }
  const qint64 GetTimeStartTelemetry()                          { return TimeStartTelemetry; }


protected:
  virtual bool event(QEvent* event);

public:

signals:

public slots:
  void SlotSwitchToReadiness();
  void SlotSwitchToTelemetry();
};
//============================================================================================
#endif // MAINWINDOW_H
