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
  QMainWindow(parent)
{
  _ui.setupUi(this);

  setWindowTitle("GLst");

  // init media forms
  _frm[Media::eMTUnknown] = NULL;
  _frm[Media::eMTZik]   = new WinZik(this);
  _frm[Media::eMTFilm]  = new WinFilm(this);
  _frm[Media::eMTBook]  = new WinBook(this);

  // init settings form
  _frmOptions = new WinOptions(this);

  // init media menu
  _menu = new WinListeMenu(this);
  _ui.menuBar->addMenu(_menu);

  // set list controler
  _ui.listM->setCtrl(this);

  // load style
  refreshStyle();

  // group media type menu actions
  QActionGroup *CurrentMediaActionGroup = new QActionGroup(this);
  CurrentMediaActionGroup->addAction(_ui.actTypeFilms);
  CurrentMediaActionGroup->addAction(_ui.actTypeZik);
  CurrentMediaActionGroup->addAction(_ui.actTypeBook);

  // check the current media type
  switch (_opt.mediaType())
  {
    case Media::eMTFilm:  _ui.actTypeFilms->setChecked(true); break;
    case Media::eMTZik:   _ui.actTypeZik->setChecked(true); break;
    case Media::eMTBook:  _ui.actTypeBook->setChecked(true); break;
  }

  // events
  connect(_ui.listM, &QListWidget::itemDoubleClicked, this, &WinListe::showMod);

  // menu events
  connect(_ui.actOptions,   &QAction::triggered,  this, &WinListe::showOptions);
  connect(_ui.actExHTML,    &QAction::triggered,  this, &WinListe::exportHTML);
  connect(_ui.actTypeFilms, &QAction::triggered,  this, &WinListe::updateLstFromMenu);
  connect(_ui.actTypeZik,   &QAction::triggered,  this, &WinListe::updateLstFromMenu);
  connect(_ui.actTypeBook,  &QAction::triggered,  this, &WinListe::updateLstFromMenu);

  // update menu
  _menu->updateMenu();
}

void WinListe::save()
{
  Acces(_listes).save(_opt.filename());
}

void WinListe::load()
{
  Acces(_listes).load(_opt.filename());
  refreshLst();
}

void WinListe::exportHTML()
{
  Acces_HTML(_listes).save("Listes.html");
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
  emit closeChildWin();
  _frm[_opt.mediaType()]->show();
}

void WinListe::showAddTo()
{
  const int Id = selectedId();
  if (Id < 0) return;

  _frm[_opt.mediaType()]->addTo(Id);
  showAdd();
}

void WinListe::showOptions()
{
  emit closeChildWin();
  _frmOptions->resetFrm();
  _frmOptions->show();
}

void WinListe::showMod()
{
  int Id = selectedId();
  if (Id < 0) return;

  _frm[_opt.mediaType()]->setVals(Id);
  showAdd();
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
    if (_listes[i]->type() == _opt.mediaType() && --Idn == Id) return i;
  return -1;
}

bool WinListe::canAddToItem() const
{
  if (selectedId() < 0 || selectedId() >= _listes.size())
    return false;
  return ((1<<_listes[selectedId()]->type()) & ((1<<Media::eMTZik) | (1<<Media::eMTBook)));
}

void WinListe::updateLst(const Media::EMediaType type)
{
  _opt.setMediaType(type);
  _ui.listM->clear();

  _menu->updateMenu();

  foreach (const Media *TmpM, _listes)
    if (TmpM->type() == type)
      _ui.listM->addItem(TmpM->displayable(_moreInfo));

  _menu->updateMenu();
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
  sortList(_opt.sortType());
}

void WinListe::sortList(const Collection::ESortType type)
{
  const Collection::ESortType Type((type != Collection::eSTUnsorted) ? type : _opt.sortType());

  // trie de la liste
  _listes.sort(Type);
  refreshLst();

  _opt.setSortType(Type);
}
