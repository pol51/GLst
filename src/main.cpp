#include <QtWidgets/QApplication>

#include <winListe.h>

int main(int argc, char * argv[])
{
  QApplication myApp(argc,argv);

  WinListe *myListe = new WinListe();

  myListe->show();
  myListe->refreshStyle();
  myListe->load();
  myListe->sortList();

  return myApp.exec();
}
