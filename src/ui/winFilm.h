#ifndef __WINFILM_H
#define __WINFILM_H

#include "winMedia.h"

#include <ui_Film.h>

#include <core/Film.h>

class WinListe;

class WinFilm : public WinMedia
{
  Q_OBJECT

  private:
    Ui_dialogAjoutFilm _ui;

  public:
    WinFilm(WinListe *ctrl, QWidget *parent = NULL);

  public slots:
    void resetFrm();
    void abandon();
    void confirm();
    void setVals(const int idn);
};

#endif
