#ifndef __WINOPTIONS_H
#define __WINOPTIONS_H

#include <ui_Options.h>

class winListe;

class winOptions : public QWidget
{
  Q_OBJECT

  private:
    Ui_dialogOptions _ui;
    winListe *_ctrl;

  public:
    winOptions(winListe *ctrl, QWidget *parent = 0);

  public slots:
    void searchFile();
    void resetFrm();
    void abandon();
    void confirm();
};

#endif
