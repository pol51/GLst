#include "winListe.h"

#include <winFilm.h>
#include <winZik.h>
#include <winBook.h>
#include <winOptions.h>
#include <winListeMenu.h>
#include <widgetListe.h>

#include <gestion/Utils.h>
#include <gestion/Options.h>
#include <gestion/Collection.h>
#include <gestion/Acces.h>
#include <gestion/Acces_HTML.h>

#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStyleFactory>

WinListe::WinListe(QWidget *parent) :
  QMainWindow(parent),
  _moreInfo(false), _currentType(TYPE_FILM)
{
  _ui.setupUi(this);

  setWindowTitle("GLst");

  //initialisation des dialogues de saisie
  _frmZik = new WinZik(this);
  _frmFilm = new WinFilm(this);
  _frmBook = new WinBook(this);

  //initialisation du dialogue d'optionss
  _frmOptions = new WinOptions(this);

  //initialisation des options
  _opt = new Options(OPTIONS_FILE);
  if (_opt->load() != NB_OPTIONS) _opt->save();

  //initaialisation de la collection et de son AccessDE
  _listes = new Collection();
  _listDE = new Acces(_listes);
  _listHTML = new Acces_HTML(_listes);

  //initialisation du menu des medias
  _menu = new WinListeMenu(this);
  _ui.menuBar->addMenu(_menu);

  //attribution du controlleur de ui.listM
  _ui.listM->setCtrl(this);

  //chargement du style
  refreshStyle();

  //evenements
  connect(_ui.listM, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
          this, SLOT(showMod()));

  _ui.actFind->setVisible(false);

  //evenements du menu
  connect(_ui.actOptions,   &QAction::triggered,  this, &WinListe::showOptions);
  connect(_ui.actExHTML,    &QAction::triggered,  this, &WinListe::exportHTML);
  connect(_ui.actTypeFilms, &QAction::triggered,  this, &WinListe::updateLstFromMenu);
  connect(_ui.actTypeZik,   &QAction::triggered,  this, &WinListe::updateLstFromMenu);
  connect(_ui.actTypeBook,  &QAction::triggered,  this, &WinListe::updateLstFromMenu);

  //initialisation de la status bar
  _ui.statusBar->addWidget(&_lblStat, 1);
  _lblStat.setText("Chargement...");

  _menu->updateMenu();
}

void WinListe::save()
{
  _listDE->save(_opt->get_liste());
}

void WinListe::load()
{
  _lblStat.setText("Chargement...");
  _listDE->load(_opt->get_liste());
  refreshLst();
}

void WinListe::exportHTML()
{
  _listHTML->save("Listes.html");
  refreshLst();
}

void WinListe::changeStyle(const QString &styleName)
{
  QApplication::setStyle(QStyleFactory::create(styleName));
}

void WinListe::refreshStyle()
{
  QApplication::setStyle(QStyleFactory::create(_opt->get_style()));
}

void WinListe::showAdd()
{
  closeAll();
  QWidget *Form = NULL;
  switch (_currentType)
  {
    case TYPE_FILM: Form = _frmFilm;  break;
    case TYPE_ZIK:  Form = _frmZik;   break;
    case TYPE_BOOK: Form = _frmBook;  break;
    default:        Form = NULL;      break;
  }
  if (Form)
    #ifdef Q_OS_SYMBIAN
    Form->showMaximized();
    #else
    Form->show();
    #endif
}

void WinListe::showAddTo()
{
  int Id = selectedId();
  if (Id < 0) return;
  switch (_currentType)
  {
    case TYPE_ZIK:  _frmZik->addTo(Id);   break;
    case TYPE_BOOK: _frmBook->addTo(Id);  break;
    default:                              break;
  }
  showAdd();
}

void WinListe::showOptions()
{
  closeAll();
  _frmOptions->resetFrm();
  #ifdef Q_OS_SYMBIAN
  _frmOptions->showMaximized();
  #else
  _frmOptions->show();
  #endif
}

void WinListe::showMod()
{
  int Id = selectedId();
  if (Id < 0) return;

  switch (_currentType)
  {
    case TYPE_FILM: _frmFilm->setVals(Id); break;
    case TYPE_ZIK:  _frmZik->setVals(Id);  break;
    case TYPE_BOOK: _frmBook->setVals(Id); break;
  }
  showAdd();
}

void WinListe::closeAll()
{
  _frmFilm->close();
  _frmZik->close();
  _frmBook->close();
  _frmOptions->close();
}

void WinListe::delMedia()
{
  int Id = selectedId();
  if (Id >= 0)
  {
    _listes->del_Media(Id);
    refreshLst();
  }
  save();
}

int WinListe::selectedId() const
{
  const int Id = _ui.listM->currentRow();
  int Idn = _ui.listM->count();
  for (int i = _listes->nb_Media(); --i >= 0; )
    if (_listes->get_Media(i)->get_type() == _currentType && --Idn == Id) return i;
  return -1;
}

bool WinListe::canAddToItem() const
{
  Media *TmpMedia = _listes->get_Media(selectedId());
  if (TmpMedia == NULL)
    return false;
  switch (TmpMedia->get_type())
  {
    case TYPE_ZIK:
    case TYPE_BOOK:
      return true;
    case TYPE_FILM:
    default:
      return false;
  }
}

void WinListe::updateLst(const int type)
{
  _currentType = type;
  int Nb_Cd = 0;
  int Nb_Dvd = 0;
  int Nb_Elem = 0;
  QString Status;
  QString Line;
  _ui.listM->clear();

  //checkbox behaviour as options :)
  _ui.actTypeFilms->setChecked(_currentType == TYPE_FILM);
  _ui.actTypeZik->setChecked(_currentType == TYPE_ZIK);
  _ui.actTypeBook->setChecked(_currentType == TYPE_BOOK);

  _menu->updateMenu();
  const int Nb_Media = _listes->nb_Media();

  switch (_currentType)
  {
    case TYPE_FILM:
      {
        Film *TmpFilm;
        Status.append("Film: ");
        for (int i = 0; i < Nb_Media; i++)
        {
          TmpFilm = (Film*)_listes->get_Media(i);
          if (TmpFilm->get_type() == TYPE_FILM)
          {
            Nb_Elem++;
            Nb_Cd += TmpFilm->get_nbCd();
            Nb_Dvd += TmpFilm->get_nbDvd();
            Line = TmpFilm->get_nom();
            if (TmpFilm->get_nbCd() > 0)
              Line.append(QString(" (%1CD)").
                arg(QString::number(TmpFilm->get_nbCd())));
            if (TmpFilm->get_nbDvd() > 0)
              Line.append(QString(" (%1DVD)").
                arg(QString::number(TmpFilm->get_nbDvd())));
            if (_moreInfo)
            {
              if (TmpFilm->get_idBoite() > 0)
                Line.append(QString(" [#%1]").
                  arg(QString::number(
                  TmpFilm->get_idBoite())));
              switch (TmpFilm->get_qualite())
              {
                case Film::eDVDRip:       Line.append(" [DvdRip]"); break;
                case Film::eScreener:     Line.append(" [Scr]");    break;
                case Film::eDVD:          Line.append(" [Dvd]");    break;
                case Film::eTVRip:        Line.append(" [TvRip]");  break;
                case Film::ePub:          Line.append(" [Pub]");    break;
                case Film::eDVDScreener:  Line.append(" [DvdScr]"); break;
                case Film::eVCD:          Line.append(" [Vcd]");    break;
              }
              switch (TmpFilm->get_genre())
              {
                case Film::eFilm:
                  Line.append(" <Film>");         break;
                case Film::eLive:
                  Line.append(" <Concert>");      break;
                case Film::eSpectacle:
                  Line.append(" <Spectacle>");    break;
                case Film::eManga:
                  Line.append(" <Manga>");        break;
                case Film::eAnime:
                  Line.append(" <Dessin Anime>"); break;
                case Film::eSerie:
                  Line.append(" <Serie>");        break;
                case Film::eDocumentaire:
                  Line.append(" <Documentaire>"); break;
              }
            }
            _ui.listM->addItem(Line);
          }
        }
        Status.append(QString("%1 => %2CD + %3DVD").
          arg(QString::number(Nb_Elem)).
          arg(QString::number(Nb_Cd)).
          arg(QString::number(Nb_Dvd)));
        _lblStat.setText(Status);
      }
      break;
    case TYPE_ZIK:
      {
        Zik *TmpZik;
        Status.append("Zik: ");
        _lblStat.setText("Zik: ");
        for (int i = 0; i < Nb_Media; i++)
        {
          TmpZik = (Zik*)_listes->get_Media(i);
          if (TmpZik->get_type() == TYPE_ZIK)
          {
            Nb_Elem++;
            Nb_Cd += TmpZik->get_nbCd();
            Line = TmpZik->get_artiste();
            Line.append(" - ");
            Line.append(TmpZik->get_titre());
            if (TmpZik->get_nbCd() > 0)
              Line.append(QString(" (%1CD)").
                arg(QString::number(TmpZik->get_nbCd())));
            if (_moreInfo && TmpZik->get_idBoite() > 0)
              Line.append(QString(" [#%1]").
                arg(QString::number(TmpZik->get_idBoite())));
            _ui.listM->addItem(Line);
          }
        }
        Status.append(QString("%1 => %2CD").
          arg(QString::number(Nb_Elem)).
          arg(QString::number(Nb_Cd)));
        _lblStat.setText(Status);
      }
      break;
    case TYPE_BOOK:
      {
        Book *TmpBook;
        Status.append("Livres: ");
        _lblStat.setText("Livres: ");
        for (int i = 0; i < Nb_Media; i++)
        {
          TmpBook = (Book*)_listes->get_Media(i);
          if (TmpBook->get_type() == TYPE_BOOK)
          {
            Nb_Elem++;
            Line = TmpBook->get_auteur();
            Line.append(" - ");
            Line.append(TmpBook->get_titre());
            if (_moreInfo)
              switch (TmpBook->get_format())
              {
                case Book::ePapier:  Line.append(" [papier]"); break;
                case Book::eNumeric: Line.append(" [e-book]"); break;
              }
            _ui.listM->addItem(Line);
          }
        }
        Status.append(QString::number(Nb_Elem));
        _lblStat.setText(Status);
      }
      break;
    default:
      break;
  }
  _menu->updateMenu();
}

void WinListe::updateLstFromMenu()
{
  const QObject *Sender = sender();
  if (Sender == _ui.actTypeFilms)
    updateLst(TYPE_FILM);
  if (Sender == _ui.actTypeZik)
    updateLst(TYPE_ZIK);
  if (Sender == _ui.actTypeBook)
    updateLst(TYPE_BOOK);
}

void WinListe::sortList()
{
  sortList(-1);
}

void WinListe::sortList(const int type)
{
  const int Type = (type >= 0) ? type : _opt->get_sortType();

  // trie de la liste
  _listes->sort_Media(Type);
  refreshLst();

  //sauvegarde dans les options
  _opt->set_sortType(Type);
  _opt->save();
}
