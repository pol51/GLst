#ifndef __WINLISTE_H
#define __WINLISTE_H
#include "ui_Liste.h"

class winFilm;
class winZik;
class winBook;
class winOptions;
class winListeMenu;
class widgetListe;

#include "./gestion/Options.h"
#include "./gestion/Collection.h"
#include "./gestion/Acces.h"
#include "./gestion/Acces_HTML.h"

#define OPTIONS_FILE "glst.cfg"

class winListe : public QWidget
{
	Q_OBJECT
	private:
		Ui_mwListe ui;
		winZik *frmZik;
		winFilm *frmFilm;
		winBook *frmBook;
		winOptions *frmOptions;
		int selectedId();
		QPalette originalPalette;
	public:
		Options *Opt;
		Collection *Listes;
		Acces *ListDE;
		Acces_HTML *ListHTML;
		winListeMenu *Menu;
	private slots:
		void showOptions();
		void showAdd();
		void showAddTo();
		void closeAll();
		void showMod();
		void delMedia();
	public:
		winListe(QWidget *parent = 0);
		bool canAddToItem();
	public slots:
		void updateLst(int type);
		void refreshLst();
		void sortList();
		void sortList(int type);
		void changeStyle(const QString &styleName);
		void refreshStyle();
		void exportHTML();
		void save();
		void load();
};

#endif
