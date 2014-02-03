#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSplitter>
#include <QScrollBar>
  #include <QMessageBox>
//#include <QtSerialPort/QtSerialPort>

//============================================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//--
  ListMainSplitterSizes << 500 << 1000; //разделение один к двум

  Init();
//--
}
//--------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
  if(PMainSplitter->isWindow()) {
    QMessageBox msgBox;
    msgBox.setText("MainWindow::~MainWindow()\nPMainSplitter->isWindow() == true   <<===  Correct!");
    msgBox.exec();
  }
  if(PTelemetry->isWindow()) {
    QMessageBox msgBox;
    msgBox.setText("MainWindow::~MainWindow()\nPTelemetry->isWindow() == true   <<===  Correct!");
    msgBox.exec();
  }
  if(PReadiness->isWindow()) { //   PReadiness->close();
    QMessageBox msgBox;
    msgBox.setText("MainWindow::~MainWindow()\nPReadiness->isWindow() == true   <<===  Correct!");
    msgBox.exec();
//    delete PReadiness;
//    if(PReadiness->isWindow()) {    QMessageBox msgBox;  msgBox.setText("2 PReadiness->isWindow()");  msgBox.exec(); }
//    PReadiness = NULL;
  }
//  delete PSceneEkranoplan;
  if(PViewEkranoplan->isWindow()) {
    QMessageBox msgBox;
    msgBox.setText("MainWindow::~MainWindow()\nPViewEkranoplan->isWindow() == true   <<===  Correct!");
    msgBox.exec();
  }
//Ардуин ждёт бесконечно долго. когда поток закрыт, ардуин прекращает ждать и закрывается
  ThreadArduino.quit();    ThreadArduino.wait();
//--
    delete ui;
}
//--------------------------------------------------------------------------------------------
bool MainWindow::event(QEvent* event)
{
  //следующие действие: при закрытии материнского окна, если один из классов не был его частью, то зделать его частью
  //материнского окна и закрыть без патери памяти и утечек.
  if(event->type() == QEvent::Close) {
    if(PReadiness->parentWidget() == NULL)  PReadiness->setParent(this); //  PReadiness->close();
    if(PTelemetry->parentWidget() == NULL)  PTelemetry->setParent(this); //  PTelemetry->close();
  }
//--

  bool b = QMainWindow::event(event); //catch different events

//--
  if(event->type() == QEvent::Polish) {//Polish is caught
//    Init();
//    SlotSwitchToReadiness();

//    setScaledContents(true);
//    FrameRectOrig = frameGeometry();//save dimensions
//    FontPointSizeOrg = font().pointSize();
//QString s; s.sprintf("font :-: %dpt", font().pointSize());
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();
  }
//--
  return b;
}
//--------------------------------------------------------------------------------------------
void MainWindow::Init()
{
  QString sTextTest0("   State of Execution\n");
  InitLists(sTextTest0);

//=======
  PMainSplitter = new QSplitter(Qt::Horizontal, this); //&w);
  //PMainSplitter = new QSplitter(Qt::Vertical, this); //&w);
  setCentralWidget(PMainSplitter); // правила назначения в qt


//===####  I: Left (Ekranoplan):  ####===
  PSceneEkranoplan = new QGraphicsScene(PMainSplitter);  //    scene.addText("Hello, world!");
  PSceneEkranoplan->addPixmap(QPixmap(":/Ekranoplan.png"));
    //scene.setSceneRect(0,0, 100,100);

  PViewEkranoplan = new QGraphicsView(PSceneEkranoplan);
    //view.setBaseSize(200,500);
  PMainSplitter->addWidget(PViewEkranoplan);//добавляет слева на право

//int ind = psplitter->indexOf(&view);
//QString s;  s.sprintf("ind = %d", ind);
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();

    //psplitter->handle(0)->setFixedWidth(100);
    //psplitter->handle(0)->setMaximumWidth(100);
    //psplitter->setHandleWidth(50);
    //psplitter->resize(1200,500);


//  InitReadiness(this, pSplitter);

//    scene.addEllipse(QRectF(180,360, 40,40),QPen(),QBrush(QColor(255,0,0,255)));
    int xc = 200;  int yc = 380;  int rc = 25; //xc - xcenter
    QRadialGradient radialGradTestSpot(QPointF(xc, yc), rc);
//    radialGradTestSpot.setColorAt(0, Qt::red);
    radialGradTestSpot.setColorAt(0, QColor(255, 0, 0, 155)); // 255
    radialGradTestSpot.setColorAt(0.5, QColor(0, 0, 255, 155));
//    radialGradTestSpot.setColorAt(1, Qt::green);
    radialGradTestSpot.setColorAt(1, QColor(0, 255, 0, 155));

//radialGradTestSpot.setColorAt(0, QColor(20, 255, 180, 255)); // 255
//radialGradTestSpot.setColorAt(0.6, QColor(180, 255, 180, 155)); // 255
//radialGradTestSpot.setColorAt(1, QColor(220, 0, 0, 100)); // 255

    PTestSpot = PSceneEkranoplan->addEllipse(QRectF(xc-rc,yc-rc, 2*rc,2*rc),QPen(Qt::NoPen),QBrush(radialGradTestSpot));



//===####  II: 1) Right (Readiness):  ####===

//  QSplitter* pSplitterReadiness = new QSplitter(Qt::Vertical, pSplitter);
  PReadiness = new MReadiness;//(pSplitter);//создали правое полуокно в готовности


//===####  III: 1) Right (Telemetry):  ####===
  PTelemetry = new MTelemetry;//(pSplitter); //создали правое полуокно в телеметрии

//===####    ####===

//  pSplitter->addWidget(PReadiness);
//  PMainSplitter->addWidget(PTelemetry);

  SlotSwitchToReadiness();// переключение полуокон\
   //PMainSplitter->addWidget(PReadiness);
   //PMainSplitter->addWidget(PTelemetry);

//  QList<int> list;  list << 500 << 1000;    PMainSplitter->setSizes(list);   list.clear();

//======

//  PArduino = NULL;
  PArduino = new MArduino;
  PArduino->moveToThread(&ThreadArduino);
  connect(&ThreadArduino, &QThread::finished, PArduino, &QObject::deleteLater);
  ThreadArduino.start();
//--
}
//--------------------------------------------------------------------------------------------
void MainWindow::InitLists(QString& sTextTest0)
{
  QString sTextTest;// то что это бражается в черном квадрате
  QString sNameChannel;     QString sNameChannelPixmapFile;
  QString sInputTestName1;  QString sInputTestValue1;  QString sOutputTestName1;
  QString sInputTestName2;  QString sInputTestValue2;  QString sOutputTestName2;
  QString sParam1;      QString sParam2;
  QList<QString> list;


// == 1) Engines:  ===
//начало первого канала
  sTextTest = sTextTest0;
sNameChannel = "Right Engine";  sNameChannelPixmapFile = ":/Engine.png";
  sInputTestName1 = "Min Voltage (V)";
  sTextTest += sInputTestName1 + ":\t\t"; //5\n";
  sInputTestValue1 = "5";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "RPM";
//  sParam1 = "    " + sOutputTestName1 + ":\t\t\t\t\t\t\t";
  sParam1 = "    ";  sParam1 += sOutputTestName1;  sParam1 += ":\t\t\t\t\t\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Voltage (V)";
  sTextTest += sInputTestName2 + ":\t\t"; //20\n";
  sInputTestValue2 = "20";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "RPM";
  sParam2 = "    " + sOutputTestName2 + ":\t\t\t\t\t\t\t";
  sTextTest += sParam2;

  //sTextTest.insert(0, sTextTest0); //вставить первую строку в нулевую позицию
  //Присвоение значений каналу
  ListNamesEngines << sNameChannel;//лист моторов в нижнем окне

//лисп параметров верхнего полуокна
//        0               1                         2
  list << sNameChannel << sNameChannelPixmapFile << sTextTest
 //       3                  4                   5                   6          7        8
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "8"   << "12"
//        9                  10                  11                  12         13       14
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "400" << "600";
  IFirstItemListParamsReadiness = 6;  //  number of "sParam1"
  DeltaNItemListParamsReadiness = 6;  // = 12-6: distance between "sParam1" and "sParam2"
  ListParamsReadinessChannels << list;   list.clear();

//формирование листа на телеметрию
//        0               1
  list << sNameChannel << sNameChannelPixmapFile //формирование табов на верху телеметрии
//        2                         3        4
       << "Rotation Speed (RPM)" << "0.5" << "99.5" //  "2.0 - 98.0"  is the the Range of the "Rotation Speed (RPM)"
//        5                          6        7
       << "Power Consumption (W)" << "0.5" << "99.5"; //  "2.0 - 98.0"  is the the Range of the "Power Consumption (W)"
  IFirstItemListParamsTelemetry = 2; // number of the first param
//  DeltaNItemListParamsTelemetry = 3;  // = 5-2: distance between param1 ("Rotation Speed (RPM)") and param2 ("Power Consumption (W)")
  ListParamsTelemetryChannels << list;   list.clear();
//конец первого канала

sNameChannel = "Left Engine";  sNameChannelPixmapFile = ":/Engine.png";
  sInputTestName1 = "Min Voltage (V)";
  sTextTest = sInputTestName1 + ":\t\t"; //5\n";
  sInputTestValue1 = "5";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "RPM";
  sParam1 = "    " + sOutputTestName1 + ":\t\t\t\t\t\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Voltage (V)";
  sTextTest += sInputTestName2 + ":\t\t"; //20\n";
  sInputTestValue2 = "20";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "RPM";
  sParam2 = "    " + sOutputTestName2 + ":\t\t\t\t\t\t\t";
  sTextTest += sParam2;

  sTextTest.insert(0, sTextTest0);

  ListNamesEngines << sNameChannel;

  list << sNameChannel << sNameChannelPixmapFile << sTextTest
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "8"   << "12"
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "400" << "600";
  ListParamsReadinessChannels << list;   list.clear();

  list << sNameChannel << sNameChannelPixmapFile
       << "Rotation Speed (RPM)" << "0.5" << "99.5"
       << "Power Consumption (W)" << "0.5" << "99.5";
  ListParamsTelemetryChannels << list;   list.clear();


// == 2) Sensors:  ===

sNameChannel = "Right Sensor";  sNameChannelPixmapFile = ":/Engine.png";
  sInputTestName1 = "Min Angle (°)";
  sTextTest = sInputTestName1 + ":\t\t"; //1\n";
  sInputTestValue1 = "1";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "Voltage (V)";
  sParam1 = "    " + sOutputTestName1 + ":\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Angle (°)";
  sTextTest += sInputTestName2 + ":\t\t"; //10\n";
  sInputTestValue2 = "10";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "Voltage (V)";
  sParam2 = "    " + sOutputTestName2 + ":\t\t";
  sTextTest += sParam2;

  sTextTest.insert(0, sTextTest0);

  ListNamesSensors << sNameChannel;

  list << sNameChannel << sNameChannelPixmapFile << sTextTest
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "4.5" << "5.5"
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "19"  << "21";
  ListParamsReadinessChannels << list;   list.clear();

  list << sNameChannel << sNameChannelPixmapFile
       << "Voltage (V)" << "20.0" << "80.0"
       << "Power Consumption (W)" << "0.5" << "99.5";
  ListParamsTelemetryChannels << list;   list.clear();


sNameChannel = "Left Sensor";  sNameChannelPixmapFile = ":/Engine.png";
  sInputTestName1 = "Min Angle (°)";
  sTextTest = sInputTestName1 + ":\t\t"; //1\n";
  sInputTestValue1 = "1";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "Voltage (V)";
  sParam1 = "    " + sOutputTestName1 + ":\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Angle (°)";
  sTextTest += sInputTestName2 + ":\t\t"; //10\n";
  sInputTestValue2 = "10";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "Voltage (V)";
  sParam2 = "    " + sOutputTestName2 + ":\t\t";
  sTextTest += sParam2;

  sTextTest.insert(0, sTextTest0);

  ListNamesSensors << sNameChannel;

  list << sNameChannel << sNameChannelPixmapFile << sTextTest
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "9.5" << "10.5"   //  "4.5" << "5.5"
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "9.5" << "10.5";  //  "19"  << "21";
  ListParamsReadinessChannels << list;   list.clear();

  list << sNameChannel << sNameChannelPixmapFile
       << "Voltage (V)" << "0.5" << "99.5"
       << "Power Consumption (W)" << "0.5" << "99.5";
  ListParamsTelemetryChannels << list;   list.clear();


// == 3) ServoMotors:  ===

sNameChannel = "Right ServoMotor";  sNameChannelPixmapFile = ":/Engine.png";
  sInputTestName1 = "Min Voltage (V)";
  sTextTest = sInputTestName1 +":\t\t"; //5\n";
  sInputTestValue1 = "5";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "Angle (°)";
  sParam1 = "    " + sOutputTestName1 + ":\t\t\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Voltage (V)";
  sTextTest += sInputTestName2 + ":\t\t"; //20\n";
  sInputTestValue2 = "20";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "Angle (°)";
  sParam2 = "    " + sOutputTestName2 + ":\t\t\t\t";
  sTextTest += sParam2;

  sTextTest.insert(0, sTextTest0);

  ListNamesServoMotors << sNameChannel;

  list << sNameChannel << sNameChannelPixmapFile << sTextTest
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "0.8" << "1.2"
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "9.5" << "10.5";
  ListParamsReadinessChannels << list;   list.clear();

  list << sNameChannel << sNameChannelPixmapFile
       << "Angle (°)" << "0.5" << "99.5"
       << "Power Consumption (W)" << "0.5" << "99.5";
  ListParamsTelemetryChannels << list;   list.clear();


sNameChannel = "Left ServoMotor";  sNameChannelPixmapFile = ":/Engine.png";
  sInputTestName1 = "Min Voltage (V)";
  sTextTest = sInputTestName1 +":\t\t"; //5\n";
  sInputTestValue1 = "5";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "Angle (°)";
  sParam1 = "    " + sOutputTestName1 + ":\t\t\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Voltage (V)";
  sTextTest += sInputTestName2 + ":\t\t"; //20\n";
  sInputTestValue2 = "20";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "Angle (°)";
  sParam2 = "    " + sOutputTestName2 + ":\t\t\t\t";
  sTextTest += sParam2;

  sTextTest.insert(0, sTextTest0);

  ListNamesServoMotors << sNameChannel;

  list << sNameChannel << sNameChannelPixmapFile << sTextTest
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "0.8" << "1.2"
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "9.5" << "10.5";
  ListParamsReadinessChannels << list;   list.clear();

  list << sNameChannel << sNameChannelPixmapFile
       << "Angle (°)" << "0.5" << "99.5"
       << "Power Consumption (W)" << "0.5" << "99.5";
  ListParamsTelemetryChannels << list;   list.clear();
}
//--------------------------------------------------------------------------------------------
void MainWindow::SlotSwitchToReadiness()
{
  SwitchSplitterFromTo(PTelemetry, PReadiness);
/*
//QString s;  s.sprintf("ind = %d", PMainSplitter->indexOf(PTelemetry));
//QMessageBox msgBox; msgBox.setText(s);   msgBox.exec();

//int x = PViewAirplane->horizontalScrollBar()->value();
//int y = PViewAirplane->verticalScrollBar()->value();
//QString s;  s.sprintf("x = %d   y = %d", x,y);
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();

  int x, y;
  int index = PMainSplitter->indexOf(PTelemetry);
  if(index >= 0) {
    x = PViewAirplane->horizontalScrollBar()->value();
    y = PViewAirplane->verticalScrollBar()->value();
    ListMainSplitterSizes = PMainSplitter->sizes();
    PMainSplitter->widget(index)->setParent(NULL);
  }
  PMainSplitter->addWidget(PReadiness);
//  if(index < 0)  {
//    QList<int> list;  list << 500 << 1000;    PMainSplitter->setSizes(list);   list.clear();
  PMainSplitter->setSizes(ListMainSplitterSizes);//  ListMainSplitterSizes.clear();
//  }
  if(index >= 0) {  //  PViewAirplane->scroll(x,y);
    PViewAirplane->horizontalScrollBar()->setValue(x);
    PViewAirplane->verticalScrollBar()->setValue(y);
  }
*/
}
//--------------------------------------------------------------------------------------------
void MainWindow::SlotSwitchToTelemetry()
{
  SwitchSplitterFromTo(PReadiness, PTelemetry);

  PTelemetry->DoTelemetry();

/*
//int x = PViewAirplane->horizontalScrollBar()->value();
//int y = PViewAirplane->verticalScrollBar()->value();
//QString s;  s.sprintf("x = %d   y = %d", x,y);
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();

  int x, y;
  int index = PMainSplitter->indexOf(PReadiness);

  if(index >= 0) {
    x = PViewAirplane->horizontalScrollBar()->value();
    y = PViewAirplane->verticalScrollBar()->value();
    ListMainSplitterSizes = PMainSplitter->sizes();
    PMainSplitter->widget(index)->setParent(NULL);
  }
  PMainSplitter->addWidget(PTelemetry);


//  if(index < 0)  {
//    QList<int> list;  list << 500 << 1000;    PMainSplitter->setSizes(list);   list.clear();
  PMainSplitter->setSizes(ListMainSplitterSizes);//  ListMainSplitterSizes.clear();
//  }
  if(index >= 0) {  //  PViewAirplane->scroll(x,y);
    PViewAirplane->horizontalScrollBar()->setValue(x);
    PViewAirplane->verticalScrollBar()->setValue(y);
  }
*/
}
//--------------------------------------------------------------------------------------------
void MainWindow::SwitchSplitterFromTo(QWidget* pWidgetFrom, QWidget* pWidgetTo)
{
//QString s;  s.sprintf("ind = %d", PMainSplitter->indexOf(PTelemetry));
//QMessageBox msgBox; msgBox.setText(s);   msgBox.exec();

//int x = PViewAirplane->horizontalScrollBar()->value();
//int y = PViewAirplane->verticalScrollBar()->value();
//QString s;  s.sprintf("x = %d   y = %d", x,y);
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();

  int x, y;

  int index = PMainSplitter->indexOf(pWidgetFrom);
  if(index >= 0) {
    x = PViewEkranoplan->horizontalScrollBar()->value();
    y = PViewEkranoplan->verticalScrollBar()->value();
    ListMainSplitterSizes = PMainSplitter->sizes();
    PMainSplitter->widget(index)->setParent(NULL);
  }

  PMainSplitter->addWidget(pWidgetTo);
//pWidgetTo->setParent(PMainSplitter);

//  if(index < 0)  {
//    QList<int> list;  list << 500 << 1000;    PMainSplitter->setSizes(list);   list.clear();
  PMainSplitter->setSizes(ListMainSplitterSizes);//  ListMainSplitterSizes.clear();
//  }
  if(index >= 0) {  //  PViewAirplane->scroll(x,y);
    PViewEkranoplan->horizontalScrollBar()->setValue(x);
    PViewEkranoplan->verticalScrollBar()->setValue(y);
  }

//QString s; s.sprintf("PMainSplitter->count()   = %d",PMainSplitter->count());
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();
}
//--------------------------------------------------------------------------------------------
/*
void MainWindow::CreateArduinoObject(const QObject* pSenderReceiver, const char *signalThis, const char *slotArduino,
                                                                     const char *signalArduino, const char *slotThis)
{
//  if(PArduino == NULL)  {
  PArduino = new MArduino;
  PArduino->moveToThread(&ThreadArduino);
  connect(&ThreadArduino, &QThread::finished, PArduino, &QObject::deleteLater);
//  }
  connect(pSenderReceiver, signalThis, PArduino, slotArduino);
  connect(PArduino, signalArduino, pSenderReceiver, slotThis);
//  if(!ThreadArduino.isRunning())
  ThreadArduino.start(); // ThreadTest.wait(5000);
}
//--------------------------------------------------------------------------------------------
void MainWindow::DestroyArduinoObject()
{
  ThreadArduino.quit();    ThreadArduino.wait();
}
*/
//--------------------------------------------------------------------------------------------
