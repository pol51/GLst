#ifndef __WIDGETLISTE_H
#define __WIDGETLISTE_H

#include <QListWidget>

class winListe;

class widgetListe : public QListWidget
{
	Q_OBJECT
	private:
		winListe *ctrl;
	public:
		widgetListe(QWidget *parent = NULL);
		virtual ~widgetListe();
		void setCtrl(winListe *ctrl = NULL);
	protected:
		void mousePressEvent(QMouseEvent *event);
};

#endif
