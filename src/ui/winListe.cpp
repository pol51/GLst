#include "winListe.h"

#include "winFilm.h"
#include "winZik.h"
#include "winBook.h"
#include "winOptions.h"
#include "winListeMenu.h"
#include "widgetListe.h"

#include <core/Utils.h>
#include <core/Options.h>
#include <core/Acces.h>
#include <core/Acces_HTML.h>

#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStyleFactory>

WinListe::WinListe(QWidget *parent) :
  QMainWindow(parent),
  _moreInfo(false), _currentType(Media::eMTFilm),
  _opt(OPTIONS_FILE), _listDE(_listes), _listHTML(_listes)
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
  if (_opt.load() != NB_OPTIONS) _opt.save();

  //initialisation du menu des medias
  _menu = new WinListeMenu(this);
  _ui.menuBar->addMenu(_menu);

  //attribution du controlleur de ui.listM
  _ui.listM->setCtrl(this);

  //chargement du style
  refreshStyle();

  //evenements
  connect(_ui.listM, &QListWidget::itemDoubleClicked, this, &WinListe::showMod);

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
  _listDE.save(_opt.liste());
}

void WinListe::load()
{
  _lblStat.setText("Chargement...");
  _listDE.load(_opt.liste());
  refreshLst();
}

void WinListe::exportHTML()
{
  _listHTML.save("Listes.html");
  refreshLst();
}

void WinListe::changeStyle(const QString &styleName)
{
  QApplication::setStyle(QStyleFactory::create(styleName));
}

void WinListe::refreshStyle()
{
  QApplication::setStyle(QStyleFactory::create(_opt.style()));
}

void WinListe::showAdd()
{
  closeAll();
  QWidget *Form = NULL;
  switch (_currentType)
  {
    case Media::eMTFilm: Form = _frmFilm;  break;
    case Media::eMTZik:  Form = _frmZik;   break;
    case Media::eMTBook: Form = _frmBook;  break;
    default:             Form = NULL;      break;
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
    case Media::eMTZik:  _frmZik->addTo(Id);   break;
    case Media::eMTBook: _frmBook->addTo(Id);  break;
    default:                                   break;
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
    case Media::eMTFilm: _frmFilm->setVals(Id); break;
    case Media::eMTZik:  _frmZik->setVals(Id);  break;
    case Media::eMTBook: _frmBook->setVals(Id); break;
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
    _listes.remove(Id);
    refreshLst();
  }
  save();
}

int WinListe::selectedId() const
{
  const int Id = _ui.listM->currentRow();
  int Idn = _ui.listM->count();
  for (int i = _listes.size(); --i >= 0; )
    if (_listes[i]->type() == _currentType && --Idn == Id) return i;
  return -1;
}

bool WinListe::canAddToItem() const
{
  if (selectedId() < 0 || selectedId() >= _listes.size())
    return false;
  switch (_listes[selectedId()]->type())
  {
    case Media::eMTZik:
    case Media::eMTBook:
      return true;
    case Media::eMTFilm:
    default:
      return false;
  }
}

void WinListe::updateLst(const int type)
{
  _currentType = type;
  _ui.listM->clear();

  //checkbox behaviour as options :)
  _ui.actTypeFilms->setChecked(_currentType == Media::eMTFilm);
  _ui.actTypeZik->setChecked(_currentType == Media::eMTZik);
  _ui.actTypeBook->setChecked(_currentType == Media::eMTBook);

  _menu->updateMenu();

  foreach (const Media *TmpM, _listes)
    if (TmpM->type() == _currentType)
      _ui.listM->addItem(TmpM->displayable(_moreInfo));

  _menu->updateMenu();
  _lblStat.setText("Done!");
}

void WinListe::updateLstFromMenu()
{
  const QObject *Sender = sender();
  if (Sender == _ui.actTypeFilms)
    updateLst(Media::eMTFilm);
  if (Sender == _ui.actTypeZik)
    updateLst(Media::eMTZik);
  if (Sender == _ui.actTypeBook)
    updateLst(Media::eMTBook);
}

void WinListe::sortList()
{
  sortList(Collection::eSTUnsorted);
}

void WinListe::sortList(const Collection::ESortType type)
{
  const Collection::ESortType Type((type != Collection::eSTUnsorted) ? type : _opt.sortType());

  // trie de la liste
  _listes.sort(Type);
  refreshLst();

  //sauvegarde dans les options
  _opt.setSortType(Type);
  _opt.save();
}
