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
  Film* tmpF;
  if (_modif < 0)
    tmpF = _ctrl->Listes->add_Film();
  else
    tmpF = (Film*)_ctrl->Listes->get_Media(_modif);
  tmpF->set_nom(_ui.txtNom->text());
  tmpF->set_nbCd(_ui.spinNbCd->value());
  tmpF->set_nbDvd(_ui.spinNbDvd->value());
  tmpF->set_qualite(_ui.cmbQualite->currentIndex());
  tmpF->set_genre(_ui.cmbGenre->currentIndex());
  tmpF->set_idBoite(_ui.spinIdBoite->value());
  if (_modif < 0)
    tmpF->set_num(_ctrl->Listes->nextref_Media(TYPE_FILM));
  tmpF->set_date(_ui.date->date().toString("yyyyMMdd"));

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
  if ((idn < 0) or (idn >= _ctrl->Listes->nb_Media())) return;

  //recup des infos du media
  Film* tmpF = (Film*)_ctrl->Listes->get_Media(idn);
  _ui.txtNom->setText(tmpF->get_nom());
  _ui.spinNbCd->setValue(tmpF->get_nbCd());
  _ui.spinNbDvd->setValue(tmpF->get_nbDvd());
  _ui.spinIdBoite->setValue(tmpF->get_idBoite());
  _ui.cmbQualite->setCurrentIndex(tmpF->get_qualite());
  _ui.cmbGenre->setCurrentIndex(tmpF->get_genre());
  QString date = tmpF->get_date();
  _ui.date->setDate(QDate::fromString(date, "yyyyMMdd"));

  //definition du mode modif
  _modif = idn;
}
