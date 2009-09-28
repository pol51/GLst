#include <QApplication>

#include <winListe.h>

int main(int argc, char * argv[])
{
  QApplication myApp(argc,argv);

  winListe *myListe = new winListe();

  #ifdef Q_OS_SYMBIAN
  myListe->showMaximized();
  #else
  myListe->show();
  #endif
  myListe->refreshStyle();
  myListe->load();
  myListe->sortList();

  return myApp.exec();
}
