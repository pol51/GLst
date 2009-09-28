#ifndef __WINLISTE_H
#define __WINLISTE_H

#include "ui_Liste.h"

#include <QtGui/QMainWindow>
#include <QtGui/QLabel>

class winFilm;
class winZik;
class winBook;
class winOptions;
class winListeMenu;
class widgetListe;

#include <gestion/Options.h>
#include <gestion/Collection.h>
#include <gestion/Acces.h>
#include <gestion/Acces_HTML.h>

#ifdef Q_OS_SYMBIAN
# define OPTIONS_FILE "E:/GLst/glst.cfg"
#else
# define OPTIONS_FILE "glst.cfg"
#endif

class winListe : public QMainWindow
{
  Q_OBJECT

  private:
    Ui_mwListe ui;
    winZik *frmZik;
    winFilm *frmFilm;
    winBook *frmBook;
    winOptions *frmOptions;
    QLabel lblStat;
    bool moreInfo;
    int currentType;

  private:
    int selectedId();

  public:
    Options *Opt;
    Collection *Listes;
    Acces *ListDE;
    Acces_HTML *ListHTML;
    winListeMenu *Menu;

  private slots:
    void showOptions();
    void showAdd();
    void showAddTo();
    void closeAll();
    void showMod();
    void delMedia();

  public:
    winListe(QWidget *parent = 0);
    bool canAddToItem();

  public slots:
    void updateLst(int type);
    void updateLstFromMenu();
    void refreshLst();
    void sortList();
    void sortList(int type);
    void changeStyle(const QString &styleName);
    void refreshStyle();
    void exportHTML();
    void save();
    void load();
    void displayMoreInfo(const bool value) { moreInfo = value; refreshLst(); }
};

#endif
