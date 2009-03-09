#ifndef __WINLISTEMENU_H
#define __WINLISTEMENU_H

#include <QMenu>

class winListe;

class winListeMenu : public QMenu
{
	Q_OBJECT
	private:
		winListe *ctrl;
		QAction *actAdd;
		QAction *actAddTo;
		QAction *actDel;
		QAction *actMod;
	
	public:
		winListeMenu(winListe *parent);
		virtual ~winListeMenu();
		void updateMenu();
		QAction *exec(const QPoint &p, QAction *action = 0);
};

#endif
