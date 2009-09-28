#ifndef __WINBOOK_H
#define __WINBOOK_H

#include <ui_Book.h>

#include <gestion/Book.h>

class winListe;

class winBook : public QWidget
{
  Q_OBJECT

  private:
    Ui_dialogAjoutBook _ui;
    winListe *_ctrl;
    int _modif;

  public:
    winBook(winListe *ctrl, QWidget *parent = NULL);

  public slots:
    void resetFrm();
    void abandon();
    void confirm();
    void setVals(const int idn);
    void addTo(const int idn);
};

#endif
