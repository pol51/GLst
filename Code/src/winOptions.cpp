#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>

#include <winOptions.h>
#include <winListe.h>

#include <gestion/Options.h>
#include <gestion/Collection.h>

winOptions::winOptions(winListe *ctrl, QWidget *parent) :
  QWidget(parent),
  _ctrl(ctrl)
{
  _ui.setupUi(this);

  //evenements
  connect(_ui.btnCancel, SIGNAL(clicked()),
          this, SLOT(abandon()));
  connect(_ui.btnOk, SIGNAL(clicked()),
          this, SLOT(confirm()));
  connect(_ui.btnSearchFile, SIGNAL(clicked()),
          this, SLOT(searchFile()));
  connect(_ui.cmbStyle, SIGNAL(activated(const QString &)),
          _ctrl, SLOT(changeStyle(const QString &)));

  //affectation des valeurs aux éléments
  _ui.cmbStyle->addItems(QStyleFactory::keys());
}

void winOptions::resetFrm()
{
  _ui.tabOptions->setCurrentIndex(0);
  _ui.txtFilename->setText(_ctrl->_opt->get_liste());

  //recherche du nom du style dans la liste
  int i = _ui.cmbStyle->count();
  while ((_ui.cmbStyle->currentText() != _ctrl->_opt->get_style()) && (i >= 0))
    _ui.cmbStyle->setCurrentIndex(i--);
}

void winOptions::searchFile()
{
  _ui.txtFilename->setText(
    QFileDialog::getOpenFileName(this, tr("Listes"),
                                 _ctrl->_opt->get_liste(),
                                 tr("Fichiers listes (*.txt)")));
}

void winOptions::abandon()
{
  resetFrm();
  _ctrl->refreshStyle();
  close();
}

void winOptions::confirm()
{
  //style
  _ctrl->_opt->set_style(_ui.cmbStyle->currentText());
  _ctrl->_opt->save();

  //fichier
  if (_ctrl->_opt->get_liste() != _ui.txtFilename->text())
  {
    _ctrl->save();
    _ctrl->_listes->clear();
    _ctrl->_opt->set_liste(_ui.txtFilename->text());
    _ctrl->load();
    _ctrl->sortList();
  }

  abandon();
}
