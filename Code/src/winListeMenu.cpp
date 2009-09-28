#include "winListeMenu.h"

#include <winListe.h>

#include <gestion/Options.h>

winListeMenu::winListeMenu(winListe *parent)
  :QMenu(parent)
{
  ctrl = parent;
  setTitle("Media");

  actAdd = addAction(
    QIcon(":/icons/button/add.svg"), "&Ajouter");
  actAddTo = addAction(
    QIcon(":/icons/button/add.svg"), "A&jouter à  ...");
  actMod = addAction(
    QIcon(":/icons/button/edit.svg"), "&Modifier");
  actDel = addAction(
    QIcon(":/icons/button/remove.svg"), "&Supprimer");
  actSortByNews = addAction("News");
  actSortByNews->setCheckable(true);
  actSortByNews->setChecked(ctrl->Opt->get_sortType() == 2);
  actDisplayMore = addAction("More Info");
  actDisplayMore->setCheckable(true);

  QObject::connect(
    actAdd, SIGNAL(triggered()),
    ctrl, SLOT(showAdd()));
  QObject::connect(
    actAddTo, SIGNAL(triggered()),
    ctrl, SLOT(showAddTo()));
  QObject::connect(
    actMod, SIGNAL(triggered()),
    ctrl, SLOT(showMod()));
  QObject::connect(
    actDel, SIGNAL(triggered()),
    ctrl, SLOT(delMedia()));
  QObject::connect(
    actSortByNews, SIGNAL(triggered(bool)),
    this, SLOT(sortListByNews(bool)));
  QObject::connect(
    actDisplayMore, SIGNAL(triggered(bool)),
    ctrl, SLOT(displayMoreInfo(bool)));
}

void winListeMenu::updateMenu()
{
  if (ctrl->canAddToItem())
    actAddTo->setVisible(true);
  else
    actAddTo->setVisible(false);
}

void winListeMenu::sortListByNews(bool more)
{
  ctrl->sortList(more?2:1);
}
