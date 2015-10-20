#ifndef __WINFILM_H
#define __WINFILM_H

#include <ui_Film.h>

#include <core/Film.h>

class WinListe;

class WinFilm : public QWidget
{
  Q_OBJECT

  private:
    Ui_dialogAjoutFilm _ui;
    WinListe *_ctrl;
    int _modif;

  public:
    WinFilm(WinListe *ctrl, QWidget *parent = NULL);

  public slots:
    void resetFrm();
    void abandon();
    void confirm();
    void setVals(const int idn);
};

#endif
