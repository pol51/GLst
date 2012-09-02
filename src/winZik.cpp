#include <QtGui>
#include <QMessageBox>

#include <winListe.h>
#include <winZik.h>

#include <gestion/Zik.h>
#include <gestion/Collection.h>

winZik::winZik(winListe *ctrl, QWidget *parent) :
  QWidget(parent),
  _ctrl(ctrl), _modif(-1)
{
  _ui.setupUi(this);

  connect(_ui.cancelButton, SIGNAL(clicked()),
          this, SLOT(abandon()));
  connect(_ui.okButton, SIGNAL(clicked()),
          this, SLOT(confirm()));

  resetFrm();
}

void winZik::resetFrm()
{
  _modif = -1;
  _ui.txtArtiste->setFocus();
  _ui.txtArtiste->setText("");
  _ui.txtTitre->setText("");
  _ui.spinNbCd->setValue(1);
  _ui.spinIdBoite->setValue(0);
  _ui.date->setDate(QDate::currentDate());
}

void winZik::abandon()
{
  resetFrm();
  close();
}

void winZik::confirm()
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
  Zik* TmpZ = (_modif < 0)
              ? _ctrl->_listes->add_Zik()
              : (Zik*)_ctrl->_listes->get_Media(_modif);
  TmpZ->set_artiste(_ui.txtArtiste->text());
  TmpZ->set_titre(_ui.txtTitre->text());
  TmpZ->set_nbCd(_ui.spinNbCd->value());
  TmpZ->set_idBoite(_ui.spinIdBoite->value());
  if (_modif < 0)
    TmpZ->set_num(_ctrl->_listes->nextref_Media(TYPE_ZIK));
  TmpZ->set_date(_ui.date->date().toString("yyyyMMdd"));

  //trie
  _ctrl->sortList();

  //sauvegarde
  _ctrl->save();

  //effacement et fermeture du formulaire
  abandon();
}

void winZik::setVals(const int idn)
{
  //verif de l'id
  if ((idn < 0) or (idn >= _ctrl->_listes->nb_Media())) return;

  //recup des infos du media
  Zik* TmpZ = (Zik*)_ctrl->_listes->get_Media(idn);
  _ui.txtArtiste->setText(TmpZ->get_artiste());
  _ui.txtTitre->setText(TmpZ->get_titre());
  _ui.spinNbCd->setValue(TmpZ->get_nbCd());
  _ui.spinIdBoite->setValue(TmpZ->get_idBoite());
  _ui.date->setDate(QDate::fromString(TmpZ->get_date(), "yyyyMMdd"));

  //definition du mode modif
  _modif = idn;
}

void winZik::addTo(const int idn)
{
  //verif de l'id
  if ((idn < 0) or (idn >= _ctrl->_listes->nb_Media())) return;

  //recup des infos du media
  _ui.txtArtiste->setText(((Zik*)_ctrl->_listes->get_Media(idn))->get_artiste());

  // focus
  _ui.txtTitre->setFocus();
}
