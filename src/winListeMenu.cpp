#include "winListeMenu.h"

#include <winListe.h>

#include <gestion/Options.h>

WinListeMenu::WinListeMenu(WinListe *parent) :
  QMenu(parent),
  _ctrl(parent)
{
  setTitle("Media");

  _actAdd   = addAction(QIcon(":/icons/button/add.svg"), "&Ajouter");
  _actAddTo = addAction(QIcon(":/icons/button/add.svg"), "A&jouter à  ...");
  _actMod   = addAction(QIcon(":/icons/button/edit.svg"), "&Modifier");
  _actDel   = addAction(QIcon(":/icons/button/remove.svg"), "&Supprimer");
  addSeparator();
  _actSortByNews = addAction("News");
  _actSortByNews->setCheckable(true);
  _actSortByNews->setChecked(_ctrl->_opt->get_sortType() == 2);
  _actDisplayMore = addAction("More Info");
  _actDisplayMore->setCheckable(true);

  connect(_actAdd,          &QAction::triggered, _ctrl, &WinListe::showAdd);
  connect(_actAddTo,        &QAction::triggered, _ctrl, &WinListe::showAddTo);
  connect(_actMod,          &QAction::triggered, _ctrl, &WinListe::showMod);
  connect(_actDel,          &QAction::triggered, _ctrl, &WinListe::delMedia);
  connect(_actSortByNews,   &QAction::triggered, this,  &WinListeMenu::sortListByNews);
  connect(_actDisplayMore,  &QAction::triggered, _ctrl, &WinListe::displayMoreInfo);
}

void WinListeMenu::updateMenu()
{
  _actAddTo->setVisible(_ctrl->canAddToItem());
}

void WinListeMenu::sortListByNews(bool more)
{
  _ctrl->sortList(more?2:1);
}
