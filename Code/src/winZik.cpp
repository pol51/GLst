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
  if (Zik::test_artiste(_ui.txtArtiste->text()) == 0)
  {
    QMessageBox::information(0, "Erreur de saisie", "Artiste incorrect");
    _ui.txtArtiste->setFocus();
    return;
  }
  if (Zik::test_titre(_ui.txtTitre->text()) == 0)
  {
    QMessageBox::information(0, "Erreur de saisie", "Titre incorrect");
    _ui.txtTitre->setFocus();
    return;
  }
  if (Zik::test_nbCd(_ui.spinNbCd->value()) == 0)
  {
    QMessageBox::information(0, "Erreur de saisie", "Nombre de CD incorrect");
    _ui.spinNbCd->setFocus();
    return;
  }
  if (Media::test_date(_ui.date->date().toString("yyyyMMdd")) == 0)
  {
    QMessageBox::information(0, "Erreur de saisie", "Date incorrecte");
    _ui.date->setFocus();
    return;
  }

  //affectation des valeurs
  Zik* tmpZ;
  if (_modif < 0)
    tmpZ = _ctrl->Listes->add_Zik();
  else
    tmpZ = (Zik*)_ctrl->Listes->get_Media(_modif);
  tmpZ->set_artiste(_ui.txtArtiste->text());
  tmpZ->set_titre(_ui.txtTitre->text());
  tmpZ->set_nbCd(_ui.spinNbCd->value());
  tmpZ->set_idBoite(_ui.spinIdBoite->value());
  if (_modif < 0)
    tmpZ->set_num(_ctrl->Listes->nextref_Media(TYPE_ZIK));
  tmpZ->set_date(_ui.date->date().toString("yyyyMMdd"));

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
  if ((idn < 0) or (idn >= _ctrl->Listes->nb_Media())) return;

  //recup des infos du media
  Zik* tmpZ = (Zik*)_ctrl->Listes->get_Media(idn);
  _ui.txtArtiste->setText(tmpZ->get_artiste());
  _ui.txtTitre->setText(tmpZ->get_titre());
  _ui.spinNbCd->setValue(tmpZ->get_nbCd());
  _ui.spinIdBoite->setValue(tmpZ->get_idBoite());
  QString date = tmpZ->get_date();
  _ui.date->setDate(QDate::fromString(date, "yyyyMMdd"));

  //definition du mode modif
  _modif = idn;
}

void winZik::addTo(const int idn)
{
  //verif de l'id
  if ((idn < 0) or (idn >= _ctrl->Listes->nb_Media())) return;

  //recup des infos du media
  Zik* tmpZ = (Zik*)_ctrl->Listes->get_Media(idn);
  _ui.txtArtiste->setText(tmpZ->get_artiste());

  // focus
  _ui.txtTitre->setFocus();
}
