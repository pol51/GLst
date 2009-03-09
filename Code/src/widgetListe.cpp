#include "widgetListe.h"

#include "winListe.h"
#include "winListeMenu.h"
#include <QMouseEvent>

widgetListe::widgetListe(QWidget *parent)
	:QListWidget(parent)
{
	this->ctrl = NULL;
}

widgetListe::~widgetListe()
{
}

void widgetListe::setCtrl(winListe *ctrl)
{
	this->ctrl = ctrl;
}

void widgetListe::mousePressEvent(QMouseEvent *event)
{
	QListWidget::mousePressEvent(event);
	
	// partie spécifique
	if (ctrl == NULL) return;
	
	if (event->buttons() & Qt::RightButton)
		this->ctrl->Menu->exec(event->globalPos());
}
