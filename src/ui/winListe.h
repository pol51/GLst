#ifndef __WINLISTE_H
#define __WINLISTE_H

#include <ui_Liste.h>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>

#include <core/Collection.h>
#include <core/Acces_HTML.h>
#include <core/Options.h>

class WinFilm;
class WinZik;
class WinBook;
class WinOptions;
class WinListeMenu;
class WidgetListe;

#define OPTIONS_FILE "glst.cfg"

class WinListe : public QMainWindow
{
  Q_OBJECT

  private:
    Ui_mwListe _ui;
    WinZik *_frmZik;
    WinFilm *_frmFilm;
    WinBook *_frmBook;
    WinOptions *_frmOptions;
    QLabel _lblStat;
    bool _moreInfo;
    int _currentType;

  public:
    Options _opt;
    Collection _listes;
    Acces _listDE;
    Acces_HTML _listHTML;
    WinListeMenu *_menu;

  private:
    int selectedId() const;

  private slots:
    friend class WinListeMenu;
    void showOptions();
    void showAdd();
    void showAddTo();
    void closeAll();
    void showMod();
    void delMedia();

  public:
    WinListe(QWidget *parent = 0);
    bool canAddToItem() const;

  public slots:
    void updateLst(const int type);
    void updateLstFromMenu();
    void refreshLst() { updateLst(_currentType); }
    void sortList();
    void sortList(const Collection::ESortType type);
    void changeStyle(const QString &styleName);
    void refreshStyle();
    void exportHTML();
    void save();
    void load();
    void displayMoreInfo(const bool value) { _moreInfo = value; refreshLst(); }
};

#endif
