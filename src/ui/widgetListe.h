#ifndef __WIDGETLISTE_H
#define __WIDGETLISTE_H

#include <QtWidgets/QListWidget>

class WinListe;

class WidgetListe : public QListWidget
{
  Q_OBJECT

  private:
    WinListe *_ctrl = NULL;

  public:
    WidgetListe(QWidget *parent = NULL) : QListWidget(parent) {}
    virtual ~WidgetListe() {}

    void setCtrl(WinListe *ctrl = NULL) { _ctrl = ctrl; }

  protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif
