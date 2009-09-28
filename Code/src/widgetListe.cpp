#include "widgetListe.h"

#include <winListe.h>
#include <winListeMenu.h>

#include <QMouseEvent>

widgetListe::widgetListe(QWidget *parent) :
  QListWidget(parent),
  _ctrl(NULL)
{
}

void widgetListe::mousePressEvent(QMouseEvent *event)
{
  QListWidget::mousePressEvent(event);

  // partie spécifique
  if (!_ctrl) return;

  _ctrl->Menu->updateMenu();

  if (event->buttons() & Qt::RightButton)
    _ctrl->Menu->exec(event->globalPos());
}
