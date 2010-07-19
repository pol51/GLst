#include <QApplication>

#include <winListe.h>

int main(int argc, char * argv[])
{
  QApplication myApp(argc,argv);

  winListe *myListe = new winListe();

  #if defined Q_WS_S60 || defined Q_WS_MAEMO_5
  myListe->showMaximized();
  #else
  myListe->show();
  #endif
  myListe->refreshStyle();
  myListe->load();
  myListe->sortList();

  return myApp.exec();
}
