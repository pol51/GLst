#ifndef __WINLISTEMENU_H
#define __WINLISTEMENU_H

#include <QMenu>

class winListe;

class winListeMenu : public QMenu
{
  Q_OBJECT

  protected:
    winListe *ctrl;
    QAction *actAdd;
    QAction *actAddTo;
    QAction *actDel;
    QAction *actMod;
    QAction *actSortByNews;
    QAction *actDisplayMore;

  public:
    winListeMenu(winListe *parent);
    ~winListeMenu() {}
    void updateMenu();

  private slots:
    void sortListByNews(bool value);
};

#endif
