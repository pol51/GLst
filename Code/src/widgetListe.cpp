#include "widgetListe.h"

#include <winListe.h>
#include <winListeMenu.h>

#include <QMouseEvent>

void widgetListe::mousePressEvent(QMouseEvent *event)
{
  QListWidget::mousePressEvent(event);

  // partie spécifique
  if (!_ctrl) return;

  _ctrl->_menu->updateMenu();

  if (event->buttons() & Qt::RightButton)
    _ctrl->_menu->exec(event->globalPos());
}
