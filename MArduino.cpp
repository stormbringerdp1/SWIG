#include "MArduino.h"

  #include <QThread>
//  #include <QApplication>

//============================================================================================
MArduino::MArduino(QObject *parent) :
    QObject(parent)
{
qsrand(1234578);
}
//--------------------------------------------------------------------------------------------
void MArduino::SlotTest(QString* psNameChannel, QString* psInputTestName, QString* psInputTestValue, QString* psOutputTestName)
{
//  wait(5000);
//  thread()->wait(5000);

// psInputTestValue->toStdString().c_str()

QThread::sleep(2); //unsigned long secs) [static]
  emit SignalResultTest(10.0);

//  moveToThread(QApplication::instance()->thread());
}
//--------------------------------------------------------------------------------------------
void MArduino::SlotGetTelemetryValue(QString* psNameChannel, QString* psInputName)
{

//QThread::sleep(1); //unsigned long secs) [static]
float value = ((qrand()*1.0)/RAND_MAX)*100.0;
  emit SignalResultGetTelemetryValue(value);

}
//--------------------------------------------------------------------------------------------
