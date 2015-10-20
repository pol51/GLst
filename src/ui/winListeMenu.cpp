#include "winListeMenu.h"

#include "winListe.h"

#include <core/Options.h>

WinListeMenu::WinListeMenu(WinListe *parent) :
  QMenu(parent),
  _ctrl(parent)
{
  setTitle("Media");

  _actAdd   = addAction(QIcon(":/images/add.svg"), "&Ajouter");
  _actAddTo = addAction(QIcon(":/images/add.svg"), "A&jouter à  ...");
  _actMod   = addAction(QIcon(":/images/edit.svg"), "&Modifier");
  _actDel   = addAction(QIcon(":/images/remove.svg"), "&Supprimer");
  addSeparator();
  _actSortByNews = addAction("News");
  _actSortByNews->setCheckable(true);
  _actSortByNews->setChecked(_ctrl->_opt.sortType() == Collection::eSTAlpha);
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

void WinListeMenu::sortListByNews(bool on)
{
  _ctrl->sortList(on?Collection::eSTDate:Collection::eSTAlpha);
}
