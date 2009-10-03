#ifndef __WINLISTE_H
#define __WINLISTE_H

#include <ui_Liste.h>

#include <QtGui/QMainWindow>
#include <QtGui/QLabel>

class winFilm;
class winZik;
class winBook;
class winOptions;
class winListeMenu;
class widgetListe;

class Options;
class Collection;
class Acces;
class Acces_HTML;

#ifdef Q_OS_SYMBIAN
# define OPTIONS_FILE "E:/GLst/glst.cfg"
#else
# define OPTIONS_FILE "glst.cfg"
#endif

class winListe : public QMainWindow
{
  Q_OBJECT

  private:
    Ui_mwListe _ui;
    winZik *_frmZik;
    winFilm *_frmFilm;
    winBook *_frmBook;
    winOptions *_frmOptions;
    QLabel _lblStat;
    bool _moreInfo;
    int _currentType;

  public:
    Options *_opt;
    Collection *_listes;
    Acces *_listDE;
    Acces_HTML *_listHTML;
    winListeMenu *_menu;

  private:
    int selectedId() const;

  private slots:
    void showOptions();
    void showAdd();
    void showAddTo();
    void closeAll();
    void showMod();
    void delMedia();

  public:
    winListe(QWidget *parent = 0);
    bool canAddToItem() const;

  public slots:
    void updateLst(const int type);
    void updateLstFromMenu();
    void refreshLst();
    void sortList();
    void sortList(const int type);
    void changeStyle(const QString &styleName);
    void refreshStyle();
    void exportHTML();
    void save();
    void load();
    void displayMoreInfo(const bool value) { _moreInfo = value; refreshLst(); }
};

#endif
