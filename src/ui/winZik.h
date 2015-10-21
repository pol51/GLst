#ifndef __WINZIK_H
#define __WINZIK_H

#include "winMedia.h"

#include <ui_Zik.h>

#include <core/Zik.h>

class WinListe;

class WinZik : public WinMedia
{
  Q_OBJECT

  private:
    Ui_dialogAjoutZik _ui;

  public:
    WinZik(WinListe *ctrl, QWidget *parent = NULL);

  public slots:
    void resetFrm();
    void abandon();
    void confirm();
    void setVals(const int idn);
    void addTo(const int idn);
};

#endif
