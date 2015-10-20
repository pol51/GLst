#include <QtWidgets/QApplication>

#include <ui/winListe.h>

int main(int argc, char * argv[])
{
  QApplication myApp(argc,argv);

  WinListe myListe;

  myListe.show();
  myListe.refreshStyle();
  myListe.load();
  myListe.sortList();

  return myApp.exec();
}
