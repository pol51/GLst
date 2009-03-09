#include "winListeMenu.h"

#include "winListe.h"

winListeMenu::winListeMenu(winListe *parent)
	:QMenu(parent)
{
	this->ctrl = parent;
	
	this->actAdd = this->addAction(
		QIcon(":/icons/button/add.svg"), "&Ajouter");
	this->actAddTo = this->addAction(
		QIcon(":/icons/button/add.svg"), "&Ajouter à ...");
	this->actMod = this->addAction(
		QIcon(":/icons/button/edit.svg"), "&Modifier");
	this->actDel = this->addAction(
		QIcon(":/icons/button/remove.svg"), "&Supprimer");
	
	QObject::connect(
		this->actAdd, SIGNAL(triggered()),
		this->ctrl, SLOT(showAdd()));
	QObject::connect(
		this->actAddTo, SIGNAL(triggered()),
		this->ctrl, SLOT(showAddTo()));
	QObject::connect(
		this->actMod, SIGNAL(triggered()),
		this->ctrl, SLOT(showMod()));
	QObject::connect(
		this->actDel, SIGNAL(triggered()),
		this->ctrl, SLOT(delMedia()));
}

winListeMenu::~winListeMenu()
{
	return;
}

void winListeMenu::updateMenu()
{
	if (this->ctrl->canAddToItem())
		this->actAddTo->setVisible(true);
	else
		this->actAddTo->setVisible(false);
}

QAction * winListeMenu::exec( const QPoint &p, QAction *action)
{
	this->updateMenu();
	return QMenu::exec(p, action);
}
