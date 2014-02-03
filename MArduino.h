#ifndef MARDUINO_H
#define MARDUINO_H

#include <QObject>
//#include <QThread>
#include <QString>

//============================================================================================
class MArduino : public QObject
{
    Q_OBJECT
public:
    explicit MArduino(QObject *parent = 0);

signals:
  void SignalResultTest(float result);
  void SignalResultGetTelemetryValue(float result);

public slots:
//  void SlotTest(const char* nameParam, float valueParam);
  void SlotTest(QString* psNameChannel, QString* psInputTestName, QString* psInputTestValue, QString* psOutputTestName);
  void SlotGetTelemetryValue(QString* psNameChannel, QString* psInputName);
};
//============================================================================================

#endif // MARDUINO_H
