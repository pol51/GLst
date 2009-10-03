#ifndef __WIDGETLISTE_H
#define __WIDGETLISTE_H

#include <QListWidget>

class winListe;

class widgetListe : public QListWidget
{
  Q_OBJECT

  private:
    winListe *_ctrl;

  public:
    widgetListe(QWidget *parent = NULL) : QListWidget(parent), _ctrl(NULL) {}
    virtual ~widgetListe() {}

    void setCtrl(winListe *ctrl = NULL) { _ctrl = ctrl; }

  protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif
