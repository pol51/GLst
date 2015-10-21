#ifndef __WINLISTE_H
#define __WINLISTE_H

#include <ui_Liste.h>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>

#include <core/Collection.h>
#include <core/Options.h>

class WinMedia;
class WinOptions;
class WinListeMenu;
class WidgetListe;

class WinListe : public QMainWindow
{
  Q_OBJECT

  private:
    Ui_mwListe _ui;
    WinMedia *_frm[Media::eMTMax];
    WinOptions *_frmOptions;
    QLabel _lblStat;
    bool _moreInfo   = false;

  public:
    Options _opt;
    Collection _listes;
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
    WinListe(QWidget *parent = NULL);
    bool canAddToItem() const;

  public slots:
    void updateLst(const Media::EMediaType type);
    void updateLstFromMenu();
    void refreshLst() { updateLst(_opt.mediaType()); }
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
