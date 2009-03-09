#ifndef __WINBOOK_H
#define __WINBOOK_H
#include "ui_Book.h"
#include "./gestion/Book.h"

class winListe;

class winBook : public QWidget
{
	Q_OBJECT
	private:
		Ui_dialogAjoutBook ui;
		winListe *ctrl;
		int modif;
	public:
		winBook(winListe *ctrl, QWidget *parent = 0);
	public slots:
		void resetFrm();
		void abandon();
		void confirm();
		void setVals(int idn);
		void addTo(int idn);
};

#endif
