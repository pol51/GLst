#include <QtWidgets/QMessageBox>

#include <winFilm.h>
#include <winListe.h>

#include <gestion/Film.h>
#include <gestion/Collection.h>

WinFilm::WinFilm(WinListe *ctrl, QWidget *parent) :
  QWidget(parent),
  _ctrl(ctrl), _modif(-1)
{
  _ui.setupUi(this);

  connect(_ui.cancelButton, &QPushButton::clicked, this, &WinFilm::abandon);
  connect(_ui.okButton,     &QPushButton::clicked, this, &WinFilm::confirm);

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

void WinFilm::resetFrm()
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

void WinFilm::abandon()
{
  resetFrm();
  close();
}

void WinFilm::confirm()
{
  //test des valeurs
  if (_ui.txtNom->text().isEmpty())
  {
    QMessageBox::information(0, "Erreur de saisie", "Nom incorrect");
    _ui.txtNom->setFocus();
    return;
  }

  //affectation des valeurs
  Film *TmpF((_modif < 0)
             ? _ctrl->_listes.addFilm()
             : (Film*)_ctrl->_listes[_modif]);
  TmpF->setName(_ui.txtNom->text());
  TmpF->setNbCd(_ui.spinNbCd->value());
  TmpF->setNbDvd(_ui.spinNbDvd->value());
  TmpF->setQuality((Film::EQualite)_ui.cmbQualite->currentIndex());
  TmpF->setGender((Film::EGenre)_ui.cmbGenre->currentIndex());
  TmpF->setIdBoite(_ui.spinIdBoite->value());
  if (_modif < 0)
    TmpF->setNum(_ctrl->_listes.nextref(Media::eMTFilm));
  TmpF->setDate(_ui.date->date().toString("yyyyMMdd"));

    //trie
  _ctrl->sortList();

  //sauvegarde
  _ctrl->save();

  //effacement et fermeture du formulaire
  abandon();
}

void WinFilm::setVals(const int idn)
{
  //verif de l'id
  if ((idn < 0) or (idn >= _ctrl->_listes.size())) return;

  //recup des infos du media
  const Film &TmpF(*(Film*)_ctrl->_listes[idn]);
  _ui.txtNom->setText(TmpF.name());
  _ui.spinNbCd->setValue(TmpF.nbCd());
  _ui.spinNbDvd->setValue(TmpF.nbDvd());
  _ui.spinIdBoite->setValue(TmpF.idBoite());
  _ui.cmbQualite->setCurrentIndex(TmpF.quality());
  _ui.cmbGenre->setCurrentIndex(TmpF.gender());
  _ui.date->setDate(QDate::fromString(TmpF.date(), "yyyyMMdd"));

  //definition du mode modif
  _modif = idn;
}
