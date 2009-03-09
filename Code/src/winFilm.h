#ifndef __WINFILM_H
#define __WINFILM_H
#include "ui_Film.h"
#include "./gestion/Film.h"

class winListe;

class winFilm : public QWidget
{
	Q_OBJECT
	private:
		Ui_dialogAjoutFilm ui;
		winListe *ctrl;
		int modif;
	public:
		winFilm(winListe *ctrl, QWidget *parent = 0);
	public slots:
		void resetFrm();
		void abandon();
		void confirm();
		void setVals(int idn);
};

#endif
