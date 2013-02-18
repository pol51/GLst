#include <QtWidgets/QMessageBox>

#include <winListe.h>
#include <winBook.h>

#include <gestion/Book.h>
#include <gestion/Collection.h>

WinBook::WinBook(WinListe *ctrl, QWidget *parent) :
  QWidget(parent),
  _ctrl(ctrl), _modif(-1)
{
  _ui.setupUi(this);

  connect(_ui.cancelButton, &QPushButton::clicked, this, &WinBook::abandon);
  connect(_ui.okButton,     &QPushButton::clicked, this, &WinBook::confirm);

  resetFrm();

  //affectation des valeurs aux combobox
  _ui.cmbFormat->addItem("Papier");
  _ui.cmbFormat->addItem("E-Book");
}

void WinBook::resetFrm()
{
  _ui.cmbFormat->setCurrentIndex(0);
  _ui.txtAuteur->setFocus();
  _ui.txtAuteur->setText("");
  _ui.txtTitre->setText("");
  _ui.date->setDate(QDate::currentDate());
}

void WinBook::abandon()
{
  resetFrm();
  close();
}

void WinBook::confirm()
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
  Book *tmpB((_modif < 0)
             ? _ctrl->_listes.addBook()
             : (Book*)_ctrl->_listes[_modif]);
  tmpB->setAuthor(_ui.txtAuteur->text());
  tmpB->setTitle(_ui.txtTitre->text());
  tmpB->setFormat((Book::EBookFormat)_ui.cmbFormat->currentIndex());
  if (_modif < 0)
    tmpB->setNum(_ctrl->_listes.nextref(Media::eMTBook));
  tmpB->setDate(_ui.date->date().toString("yyyyMMdd"));

  //trie
  _ctrl->sortList();

  //sauvegarde
  _ctrl->save();

  //effacement et fermeture du formulaire
  abandon();
}

void WinBook::setVals(const int idn)
{
  //verif de l'id
  if ((idn < 0) or (idn >= _ctrl->_listes.size())) return;

  //recup des infos du media
  const Book &tmpB(*(Book*)_ctrl->_listes[idn]);
  _ui.txtAuteur->setText(tmpB.author());
  _ui.txtTitre->setText(tmpB.title());
  _ui.cmbFormat->setCurrentIndex(tmpB.format());
  _ui.date->setDate(QDate::fromString(tmpB.date(), "yyyyMMdd"));

  //definition du mode modif
  _modif = idn;
}

void WinBook::addTo(const int idn)
{
  //verif de l'id
  if ((idn < 0) or (idn >= _ctrl->_listes.size())) return;

  //recup des infos du media
  _ui.txtAuteur->setText(((Book*)_ctrl->_listes[idn])->author());

  // focus
  _ui.txtTitre->setFocus();
}
