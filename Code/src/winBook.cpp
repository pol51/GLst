#include <QtGui>
#include <QMessageBox>

#include <winListe.h>
#include <winBook.h>

#include <gestion/Book.h>
#include <gestion/Collection.h>

winBook::winBook(winListe *ctrl, QWidget *parent) :
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
  _ui.cmbFormat->addItem("Papier");
  _ui.cmbFormat->addItem("E-Book");
}

void winBook::resetFrm()
{
  _ui.cmbFormat->setCurrentIndex(0);
  _ui.txtAuteur->setFocus();
  _ui.txtAuteur->setText("");
  _ui.txtTitre->setText("");
  _ui.date->setDate(QDate::currentDate());
}

void winBook::abandon()
{
  resetFrm();
  close();
}

void winBook::confirm()
{
  //test des valeurs
  if (_ui.txtAuteur->text().isEmpty())
  {
    QMessageBox::information(0, "Erreur de saisie", "Auteur incorrect");
    _ui.txtAuteur->setFocus();
    return;
  }
  if (_ui.txtTitre->text().isEmpty())
  {
    QMessageBox::information(0, "Erreur de saisie", "Titre incorrect");
    _ui.txtTitre->setFocus();
    return;
  }

  //affectation des valeurs
  Book* tmpB;
  if (_modif < 0)
    tmpB = _ctrl->Listes->add_Book();
  else
    tmpB = (Book*)_ctrl->Listes->get_Media(_modif);
  tmpB->set_auteur(_ui.txtAuteur->text());
  tmpB->set_titre(_ui.txtTitre->text());
  tmpB->set_format(_ui.cmbFormat->currentIndex());
  if (_modif < 0)
    tmpB->set_num(_ctrl->Listes->nextref_Media(TYPE_BOOK));
  tmpB->set_date(_ui.date->date().toString("yyyyMMdd"));

  //trie
  _ctrl->sortList();

  //sauvegarde
  _ctrl->save();

  //effacement et fermeture du formulaire
  abandon();
}

void winBook::setVals(const int idn)
{
  //verif de l'id
  if ((idn < 0) or (idn >= _ctrl->Listes->nb_Media())) return;

  //recup des infos du media
  Book* tmpB = (Book*)_ctrl->Listes->get_Media(idn);
  _ui.txtAuteur->setText(tmpB->get_auteur());
  _ui.txtTitre->setText(tmpB->get_titre());
  _ui.cmbFormat->setCurrentIndex(tmpB->get_format());
  QString date = tmpB->get_date();
  _ui.date->setDate(QDate::fromString(date, "yyyyMMdd"));

  //definition du mode modif
  _modif = idn;
}

void winBook::addTo(const int idn)
{
  //verif de l'id
  if ((idn < 0) or (idn >= _ctrl->Listes->nb_Media())) return;

  //recup des infos du media
  Book* tmpB = (Book*)_ctrl->Listes->get_Media(idn);
  _ui.txtAuteur->setText(tmpB->get_auteur());

  // focus
  _ui.txtTitre->setFocus();
}
