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
  _ui.txtFilename->setText(_ctrl->Opt->get_liste());

  //recherche du nom du style dans la liste
  int i = _ui.cmbStyle->count();
  while ((_ui.cmbStyle->currentText() != _ctrl->Opt->get_style()) && (i >= 0))
    _ui.cmbStyle->setCurrentIndex(i--);
}

void winOptions::searchFile()
{
  _ui.txtFilename->setText(
    QFileDialog::getOpenFileName(this,
      QObject::tr("Listes"),
      _ctrl->Opt->get_liste(),
      QObject::tr("Fichiers listes (*.txt)")));
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
  _ctrl->Opt->set_style(_ui.cmbStyle->currentText());
  _ctrl->Opt->save();

  //fichier
  if (_ctrl->Opt->get_liste() != _ui.txtFilename->text())
  {
    _ctrl->save();
    _ctrl->Listes->clear();
    _ctrl->Opt->set_liste(_ui.txtFilename->text());
    _ctrl->load();
    _ctrl->sortList();
  }

  abandon();
}
