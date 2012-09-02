#include <QtGui>
#include <QMessageBox>

#include <winFilm.h>
#include <winListe.h>

#include <gestion/Film.h>
#include <gestion/Collection.h>

winFilm::winFilm(winListe *ctrl, QWidget *parent) :
  QWidget(parent),
  _ctrl(ctrl), _modif(-1)
{
  _ui.setupUi(this);

  connect(_ui.cancelButton, SIGNAL(clicked()),
          this, SLOT(abandon()));
  connect(_ui.okButton, SIGNAL(clicked()),
          this, SLOT(confirm()));

  resetFrm();

  //affectation des valeurs aux combobox
  _ui.cmbQualite->addItem("DvdRip");
  _ui.cmbQualite->addItem("Screener");
  _ui.cmbQualite->addItem("Dvd");
  _ui.cmbQualite->addItem("TVRip");
  _ui.cmbQualite->addItem("Publicitaire");
  _ui.cmbQualite->addItem("Dvd Screener");
  _ui.cmbQualite->addItem("Vcd");
  _ui.cmbGenre->addItem("Film");
  _ui.cmbGenre->addItem("Concert");
  _ui.cmbGenre->addItem("Spectacle");
  _ui.cmbGenre->addItem("Manga");
  _ui.cmbGenre->addItem("Dessin Animé");
  _ui.cmbGenre->addItem("Serie");
  _ui.cmbGenre->addItem("Documentaire");
}

void winFilm::resetFrm()
{
  _modif = -1;
  _ui.cmbQualite->setCurrentIndex(0);
  _ui.cmbGenre->setCurrentIndex(0);
  _ui.txtNom->setFocus();
  _ui.txtNom->setText("");
  _ui.spinNbCd->setValue(1);
  _ui.spinNbDvd->setValue(0);
  _ui.spinIdBoite->setValue(0);
  _ui.date->setDate(QDate::currentDate());
}

void winFilm::abandon()
{
  resetFrm();
  close();
}

void winFilm::confirm()
{
  //test des valeurs
  if (_ui.txtNom->text().isEmpty())
  {
    QMessageBox::information(0, "Erreur de saisie", "Nom incorrect");
    _ui.txtNom->setFocus();
    return;
  }

  //affectation des valeurs
  Film* TmpF = (_modif < 0)
               ? _ctrl->_listes->add_Film()
               : (Film*)_ctrl->_listes->get_Media(_modif);
  TmpF->set_nom(_ui.txtNom->text());
  TmpF->set_nbCd(_ui.spinNbCd->value());
  TmpF->set_nbDvd(_ui.spinNbDvd->value());
  TmpF->set_qualite((Film::EQualite)_ui.cmbQualite->currentIndex());
  TmpF->set_genre((Film::EGenre)_ui.cmbGenre->currentIndex());
  TmpF->set_idBoite(_ui.spinIdBoite->value());
  if (_modif < 0)
    TmpF->set_num(_ctrl->_listes->nextref_Media(TYPE_FILM));
  TmpF->set_date(_ui.date->date().toString("yyyyMMdd"));

    //trie
  _ctrl->sortList();

  //sauvegarde
  _ctrl->save();

  //effacement et fermeture du formulaire
  abandon();
}

void winFilm::setVals(const int idn)
{
  //verif de l'id
  if ((idn < 0) or (idn >= _ctrl->_listes->nb_Media())) return;

  //recup des infos du media
  Film* TmpF = (Film*)_ctrl->_listes->get_Media(idn);
  _ui.txtNom->setText(TmpF->get_nom());
  _ui.spinNbCd->setValue(TmpF->get_nbCd());
  _ui.spinNbDvd->setValue(TmpF->get_nbDvd());
  _ui.spinIdBoite->setValue(TmpF->get_idBoite());
  _ui.cmbQualite->setCurrentIndex(TmpF->get_qualite());
  _ui.cmbGenre->setCurrentIndex(TmpF->get_genre());
  _ui.date->setDate(QDate::fromString(TmpF->get_date(), "yyyyMMdd"));

  //definition du mode modif
  _modif = idn;
}
