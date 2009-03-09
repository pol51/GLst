#ifndef __WINZIK_H
#define __WINZIK_H
#include "ui_Zik.h"
#include "./gestion/Zik.h"

class winListe;

class winZik : public QWidget
{
	Q_OBJECT
	private:
		Ui_dialogAjoutZik ui;
		winListe *ctrl;
		int modif;
	public:
		winZik(winListe *ctrl, QWidget *parent = 0);
	public slots:
		void resetFrm();
		void abandon();
		void confirm();
		void setVals(int idn);
		void addTo(int idn);
};

#endif
