#ifndef __WINOPTIONS_H
#define __WINOPTIONS_H

#include <ui_Options.h>

class WinListe;

class WinOptions : public QWidget
{
  Q_OBJECT

  private:
    Ui_dialogOptions _ui;
    WinListe *_ctrl;

  public:
    WinOptions(WinListe *ctrl, QWidget *parent = NULL);

  public slots:
    void searchFile();
    void resetFrm();
    void abandon();
    void confirm();
};

#endif
