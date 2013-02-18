#ifndef __WINLISTEMENU_H
#define __WINLISTEMENU_H

#include <QtWidgets/QMenu>

class WinListe;

class WinListeMenu : public QMenu
{
  Q_OBJECT

  protected:
    WinListe *_ctrl;
    QAction *_actAdd;
    QAction *_actAddTo;
    QAction *_actDel;
    QAction *_actMod;
    QAction *_actSortByNews;
    QAction *_actDisplayMore;

  public:
    WinListeMenu(WinListe *parent);
    virtual ~WinListeMenu() {}

    void updateMenu();

  private slots:
    void sortListByNews(bool on);
};

#endif
