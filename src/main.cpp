#include <QtWidgets/QApplication>

#include <ui/winListe.h>

int main(int argc, char * argv[])
{
  QApplication App(argc,argv);
  App.setOrganizationName("PLab");
  App.setApplicationName("GLst");

  WinListe Liste;

  Liste.show();
  Liste.refreshStyle();
  Liste.load();
  Liste.sortList();

  return App.exec();
}
