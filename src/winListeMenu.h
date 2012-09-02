#ifndef __WINLISTEMENU_H
#define __WINLISTEMENU_H

#include <QMenu>

class winListe;

class winListeMenu : public QMenu
{
  Q_OBJECT

  protected:
    winListe *_ctrl;
    QAction *_actAdd;
    QAction *_actAddTo;
    QAction *_actDel;
    QAction *_actMod;
    QAction *_actSortByNews;
    QAction *_actDisplayMore;

  public:
    winListeMenu(winListe *parent);
    virtual ~winListeMenu() {}

    void updateMenu();

  private slots:
    void sortListByNews(bool value);
};

#endif
