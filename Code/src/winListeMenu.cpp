#include "winListeMenu.h"

#include <winListe.h>

#include <gestion/Options.h>

winListeMenu::winListeMenu(winListe *parent) :
  QMenu(parent),
  _ctrl(parent)
{
  setTitle("Media");

  _actAdd = addAction(
    QIcon(":/icons/button/add.svg"), "&Ajouter");
  _actAddTo = addAction(
    QIcon(":/icons/button/add.svg"), "A&jouter à  ...");
  _actMod = addAction(
    QIcon(":/icons/button/edit.svg"), "&Modifier");
  _actDel = addAction(
    QIcon(":/icons/button/remove.svg"), "&Supprimer");
  _actSortByNews = addAction("News");
  _actSortByNews->setCheckable(true);
  _actSortByNews->setChecked(_ctrl->_opt->get_sortType() == 2);
  _actDisplayMore = addAction("More Info");
  _actDisplayMore->setCheckable(true);

  connect(_actAdd, SIGNAL(triggered()),
          _ctrl, SLOT(showAdd()));
  connect(_actAddTo, SIGNAL(triggered()),
          _ctrl, SLOT(showAddTo()));
  connect(_actMod, SIGNAL(triggered()),
          _ctrl, SLOT(showMod()));
  connect(_actDel, SIGNAL(triggered()),
          _ctrl, SLOT(delMedia()));
  connect(_actSortByNews, SIGNAL(triggered(bool)),
          this, SLOT(sortListByNews(bool)));
  connect(_actDisplayMore, SIGNAL(triggered(bool)),
          _ctrl, SLOT(displayMoreInfo(bool)));
}

void winListeMenu::updateMenu()
{
  _actAddTo->setVisible(_ctrl->canAddToItem());
}

void winListeMenu::sortListByNews(bool more)
{
  _ctrl->sortList(more?2:1);
}
