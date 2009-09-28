#ifndef __WINFILM_H
#define __WINFILM_H

#include <ui_Film.h>
#include <gestion/Film.h>

class winListe;

class winFilm : public QWidget
{
  Q_OBJECT
  private:
    Ui_dialogAjoutFilm _ui;
    winListe *_ctrl;
    int _modif;

  public:
    winFilm(winListe *ctrl, QWidget *parent = NULL);

  public slots:
    void resetFrm();
    void abandon();
    void confirm();
    void setVals(const int idn);
};

#endif
