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

#include <QtGui>
#include <QMessageBox>

winListe::winListe(QWidget *parent) :
  QMainWindow(parent),
  moreInfo(false), currentType(TYPE_FILM)
{
  ui.setupUi(this);

  setWindowTitle("GLst");

  //initialisation des dialogues de saisie
  frmZik = new winZik(this);
  frmFilm = new winFilm(this);
  frmBook = new winBook(this);

  //initialisation du dialogue d'optionss
  frmOptions = new winOptions(this);

  //initialisation des options
  Opt = new Options(OPTIONS_FILE);
  if (Opt->load() != NB_OPTIONS) Opt->save();

  //initaialisation de la collection et de son AccessDE
  Listes = new Collection();
  ListDE = new Acces(Listes);
  ListHTML = new Acces_HTML(Listes);

  //initialisation du menu des medias
  Menu = new winListeMenu(this);
  ui.menuBar->addMenu(Menu);

  //attribution du controlleur de ui.listM
  ui.listM->setCtrl(this);

  //chargement du style
  refreshStyle();

  //evenements
  connect(
    ui.listM, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
    this, SLOT(showMod()));

  //evenements du menu
  connect(
    ui.actOptions, SIGNAL(triggered()),
    this, SLOT(showOptions()));
  connect(
    ui.actExHTML, SIGNAL(triggered()),
    this, SLOT(exportHTML()));
  connect(
    ui.actTypeFilms, SIGNAL(triggered()),
    this, SLOT(updateLstFromMenu()));
  connect(
    ui.actTypeZik, SIGNAL(triggered()),
    this, SLOT(updateLstFromMenu()));
  connect(
    ui.actTypeBook, SIGNAL(triggered()),
    this, SLOT(updateLstFromMenu()));

  //initialisation de la status bar
  ui.statusBar->addWidget(&lblStat, 1);
  lblStat.setText("Chargement...");

  Menu->updateMenu();
}

void winListe::save()
{
  ListDE->save(Opt->get_liste());
}

void winListe::load()
{
  lblStat.setText("Chargement...");
  ListDE->load(Opt->get_liste());
  refreshLst();
}

void winListe::exportHTML()
{
  #ifdef Q_OS_SYMBIAN
  ListHTML->save("E:/GLst/Listes.html");
  #else
  ListHTML->save("Listes.html");
  #endif
  refreshLst();
}

void winListe::changeStyle(const QString &styleName)
{
  QApplication::setStyle(QStyleFactory::create(styleName));
}

void winListe::refreshStyle()
{
  QApplication::setStyle(QStyleFactory::create(Opt->get_style()));
}

void winListe::showAdd()
{
  closeAll();
  QWidget *Form = NULL;
  switch(currentType)
  {
    case TYPE_FILM: Form = frmFilm; break;
    case TYPE_ZIK:  Form = frmZik;  break;
    case TYPE_BOOK: Form = frmBook; break;
  }
  if (Form)
    #ifdef Q_OS_SYMBIAN
    Form->showMaximized();
    #else
    Form->show();
    #endif
}

void winListe::showAddTo()
{
  int id = selectedId();
  if (id < 0) return;
  switch(currentType)
  {
    case TYPE_ZIK:  frmZik->addTo(id);  break;
    case TYPE_BOOK: frmBook->addTo(id); break;
  }
  showAdd();
}

void winListe::showOptions()
{
  closeAll();
  frmOptions->resetFrm();
  #ifdef Q_OS_SYMBIAN
  frmOptions->showMaximized();
  #else
  frmOptions->show();
  #endif
}

void winListe::showMod()
{
  int id = selectedId();
  if (id < 0) return;

  switch(currentType)
  {
    case TYPE_FILM: frmFilm->setVals(id); break;
    case TYPE_ZIK:  frmZik->setVals(id);  break;
    case TYPE_BOOK: frmBook->setVals(id); break;
  }
  showAdd();
}

void winListe::closeAll()
{
  frmFilm->close();
  frmZik->close();
  frmBook->close();
  frmOptions->close();
}

void winListe::delMedia()
{
  int id = selectedId();
  if (id >= 0)
  {
    Listes->del_Media(id);
    refreshLst();
  }
  save();
}

int winListe::selectedId()
{
  int id;
  id = ui.listM->currentRow();
  int idn = 0;
  const int nb_Media = Listes->nb_Media();
  for (int i = 0; i < nb_Media; i++)
    if (Listes->get_Media(i)->get_type() == currentType)
    {
      if (idn == id) return i;
      idn++;
    }
  return -1;
}

void winListe::refreshLst()
{
  updateLst(currentType);
}

bool winListe::canAddToItem()
{
  Media *tmpMedia = Listes->get_Media(selectedId());
  if (tmpMedia == NULL)
    return false;
  switch (tmpMedia->get_type())
  {
    case TYPE_ZIK:
    case TYPE_BOOK:
      return true;
    case TYPE_FILM:
    default:
      return false;
  }
}

void winListe::updateLst(int type)
{
  currentType = type;
  int nb_Cd = 0;
  int nb_Dvd = 0;
  int nb_Elem = 0;
  QString status;
  Media* tmpM;
  ui.listM->clear();
  QString line;

  //checkbox behaviour as options :)
  ui.actTypeFilms->setChecked(currentType == TYPE_FILM);
  ui.actTypeZik->setChecked(currentType == TYPE_ZIK);
  ui.actTypeBook->setChecked(currentType == TYPE_BOOK);

  Menu->updateMenu();
  const int nb_Media = Listes->nb_Media();

  switch(currentType)
  {
    case TYPE_FILM:
      status.append("Film: ");
      for (int i = 0; i < nb_Media; i++)
      {
        tmpM = Listes->get_Media(i);
        if (tmpM->get_type() == TYPE_FILM)
        {
          nb_Elem++;
          nb_Cd += ((Film*)tmpM)->get_nbCd();
          nb_Dvd += ((Film*)tmpM)->get_nbDvd();
          line = ((Film*)tmpM)->get_nom();
          if (((Film*)tmpM)->get_nbCd() > 0)
            line.append(QString(" (%1CD)").
              arg(QString::number(((Film*)tmpM)->get_nbCd())));
          if (((Film*)tmpM)->get_nbDvd() > 0)
            line.append(QString(" (%1DVD)").
              arg(QString::number(((Film*)tmpM)->get_nbDvd())));
          if (moreInfo)
          {
            if (tmpM->get_idBoite() > 0)
              line.append(QString(" [#%1]").
                arg(QString::number(
                ((Film*)tmpM)->get_idBoite())));
            switch(((Film*)tmpM)->get_qualite())
            {
              case QLT_DVDRIP: line.append(" [DvdRip]"); break;
              case QLT_SCR:    line.append(" [Scr]");    break;
              case QLT_DVD:    line.append(" [Dvd]");    break;
              case QLT_TVRIP:  line.append(" [TvRip]");  break;
              case QLT_PUB:    line.append(" [Pub]");    break;
              case QLT_DVDSCR: line.append(" [DvdScr]"); break;
              case QLT_VCD:    line.append(" [Vcd]");    break;
            }
            switch(((Film*)tmpM)->get_genre())
            {
              case GNR_FILM:
                line.append(" <Film>");         break;
              case GNR_LIVE:
                line.append(" <Concert>");      break;
              case GNR_SPECTACLE:
                line.append(" <Spectacle>");    break;
              case GNR_MANGA:
                line.append(" <Manga>");        break;
              case GNR_DESSIN_A:
                line.append(" <Dessin Anime>"); break;
              case GNR_SERIE:
                line.append(" <Serie>");        break;
              case GNR_DOC:
                line.append(" <Documentaire>"); break;
            }
          }
          ui.listM->addItem(line);
        }
      }
      status.append(QString("%1 => %2CD + %3DVD").
        arg(QString::number(nb_Elem)).
        arg(QString::number(nb_Cd)).
        arg(QString::number(nb_Dvd)));
      lblStat.setText(status);
            break;
    case TYPE_ZIK:
      status.append("Zik: ");
      lblStat.setText("Zik: ");
      for (int i = 0; i < nb_Media; i++)
      {
        tmpM = Listes->get_Media(i);
        if (tmpM->get_type() == TYPE_ZIK)
        {
          nb_Elem++;
          nb_Cd += ((Zik*)tmpM)->get_nbCd();
          line = ((Zik*)tmpM)->get_artiste();
          line.append(" - ");
          line.append(((Zik*)tmpM)->get_titre());
          if (((Zik*)tmpM)->get_nbCd() > 0)
            line.append(QString(" (%1CD)").
              arg(QString::number(((Zik*)tmpM)->get_nbCd())));
          if (moreInfo && tmpM->get_idBoite() > 0)
            line.append(QString(" [#%1]").
              arg(QString::number(((Zik*)tmpM)->get_idBoite())));
          ui.listM->addItem(line);
        }
      }
      status.append(QString("%1 => %2CD").
        arg(QString::number(nb_Elem)).
        arg(QString::number(nb_Cd)));
      lblStat.setText(status);
            break;
    case TYPE_BOOK:
      status.append("Livres: ");
      lblStat.setText("Livres: ");
      for (int i = 0; i < nb_Media; i++)
      {
        tmpM = Listes->get_Media(i);
        if (tmpM->get_type() == TYPE_BOOK)
        {
          nb_Elem++;
          line = ((Book*)tmpM)->get_auteur();
          line.append(" - ");
          line.append(((Book*)tmpM)->get_titre());
          if (moreInfo)
            switch (((Book*)tmpM)->get_format())
            {
              case FRT_PAPIER:  line.append(" [papier]"); break;
              case FRT_NUMERIC: line.append(" [e-book]"); break;
            }
          ui.listM->addItem(line);
        }
      }
      status.append(QString::number(nb_Elem));
      lblStat.setText(status);
      break;
  }
  Menu->updateMenu();
}

void winListe::updateLstFromMenu()
{
  const QObject *Sender = sender();
  if (Sender == ui.actTypeFilms)
    updateLst(TYPE_FILM);
  if (Sender == ui.actTypeZik)
    updateLst(TYPE_ZIK);
  if (Sender == ui.actTypeBook)
    updateLst(TYPE_BOOK);
}

void winListe::sortList()
{
  sortList(-1);
}

void winListe::sortList(int type)
{
  if (type < 0)
    type = Opt->get_sortType();

  // trie de la liste
  Listes->sort_Media(type);
  refreshLst();

  //sauvegarde dans les options
  Opt->set_sortType(type);
  Opt->save();
}
