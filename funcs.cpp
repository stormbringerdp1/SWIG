#include "funcs.h"

#include <QMessageBox>
#include <QApplication>

//============================================================================================
MainWindow* GetPMainWnd()
{
  MainWindow* pMainWindow;
  foreach(QWidget* pwidget, QApplication::topLevelWidgets()) {
    pMainWindow = qobject_cast<MainWindow*>(pwidget);
    if(pMainWindow != NULL) break;
  }

//  MainWindow* pMainWindow = qobject_cast<MainWindow*>(parentWidget()->parentWidget());
  if(pMainWindow == NULL) {
//    QString s;  s.sprintf("ind = %d", ind);
    QMessageBox msgBox(QMessageBox::Critical, QCoreApplication::instance()->applicationName(), "GetPMainWnd() == NULL");   msgBox.exec();
  }
  return pMainWindow;
}
//--------------------------------------------------------------------------------------------
