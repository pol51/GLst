#include <QtWidgets/QMessageBox>

#include <winListe.h>
#include <winZik.h>

#include <gestion/Zik.h>
#include <gestion/Collection.h>

WinZik::WinZik(WinListe *ctrl, QWidget *parent) :
  QWidget(parent),
  _ctrl(ctrl), _modif(-1)
{
  _ui.setupUi(this);

  connect(_ui.cancelButton, &QPushButton::clicked, this, &WinZik::abandon);
  connect(_ui.okButton,     &QPushButton::clicked, this, &WinZik::confirm);

  resetFrm();
}

void WinZik::resetFrm()
{
  _modif = -1;
  _ui.txtArtiste->setFocus();
  _ui.txtArtiste->setText("");
  _ui.txtTitre->setText("");
  _ui.spinNbCd->setValue(1);
  _ui.spinIdBoite->setValue(0);
  _ui.date->setDate(QDate::currentDate());
}

void WinZik::abandon()
{
  resetFrm();
  close();
}

void WinZik::confirm()
{
  //test des valeurs
  if (_ui.txtArtiste->text().isEmpty())
  {
    QMessageBox::information(0, "Erreur de saisie", "Artiste incorrect");
    _ui.txtArtiste->setFocus();
    return;
  }
  if (_ui.txtTitre->text().isEmpty())
  {
    QMessageBox::information(0, "Erreur de saisie", "Titre incorrect");
    _ui.txtTitre->setFocus();
    return;
  }
  if (_ui.spinNbCd->value() < 1)
  {
    QMessageBox::information(0, "Erreur de saisie", "Nombre de CD incorrect");
    _ui.spinNbCd->setFocus();
    return;
  }

  //affectation des valeurs
  Zik *TmpZ((_modif < 0)
            ? _ctrl->_listes.addZik()
            : (Zik*)_ctrl->_listes[_modif]);
  TmpZ->setArtist(_ui.txtArtiste->text());
  TmpZ->setTitle(_ui.txtTitre->text());
  TmpZ->setNbCd(_ui.spinNbCd->value());
  TmpZ->setIdBoite(_ui.spinIdBoite->value());
  if (_modif < 0)
    TmpZ->setNum(_ctrl->_listes.nextref(Media::eMTZik));
  TmpZ->setDate(_ui.date->date().toString("yyyyMMdd"));

  //trie
  _ctrl->sortList();

  //sauvegarde
  _ctrl->save();

  //effacement et fermeture du formulaire
  abandon();
}

void WinZik::setVals(const int idn)
{
  //verif de l'id
  if ((idn < 0) or (idn >= _ctrl->_listes.size())) return;

  //recup des infos du media
  const Zik &TmpZ(*(Zik*)_ctrl->_listes[idn]);
  _ui.txtArtiste->setText(TmpZ.artist());
  _ui.txtTitre->setText(TmpZ.title());
  _ui.spinNbCd->setValue(TmpZ.nbCd());
  _ui.spinIdBoite->setValue(TmpZ.idBoite());
  _ui.date->setDate(QDate::fromString(TmpZ.date(), "yyyyMMdd"));

  //definition du mode modif
  _modif = idn;
}

void WinZik::addTo(const int idn)
{
  //verif de l'id
  if ((idn < 0) or (idn >= _ctrl->_listes.size())) return;

  //recup des infos du media
  _ui.txtArtiste->setText((*(Zik*)_ctrl->_listes[idn]).artist());

  // focus
  _ui.txtTitre->setFocus();
}
