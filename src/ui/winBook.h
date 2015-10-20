#ifndef __WINBOOK_H
#define __WINBOOK_H

#include <ui_Book.h>

#include <core/Book.h>

class WinListe;

class WinBook : public QWidget
{
  Q_OBJECT

  private:
    Ui_dialogAjoutBook _ui;
    WinListe *_ctrl;
    int _modif;

  public:
    WinBook(WinListe *ctrl, QWidget *parent = NULL);

  public slots:
    void resetFrm();
    void abandon();
    void confirm();
    void setVals(const int idn);
    void addTo(const int idn);
};

#endif
