#include <QtWidgets/QStyleFactory>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <qt5/QtWidgets/QComboBox>

#include "winOptions.h"
#include "winListe.h"

#include <core/Options.h>
#include <core/Collection.h>

WinOptions::WinOptions(WinListe *ctrl, QWidget *parent) :
  QWidget(parent),
  _ctrl(ctrl)
{
  _ui.setupUi(this);

  //evenements
  connect(_ui.btnCancel,      &QPushButton::clicked, this,  &WinOptions::abandon);
  connect(_ui.btnOk,          &QPushButton::clicked, this,  &WinOptions::confirm);
  connect(_ui.btnSearchFile,  &QPushButton::clicked, this,  &WinOptions::searchFile);
  connect(_ui.cmbStyle,       static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::activated), _ctrl, &WinListe::changeStyle);

  //affectation des valeurs aux éléments
  _ui.cmbStyle->addItems(QStyleFactory::keys());
}

void WinOptions::resetFrm()
{
  _ui.tabOptions->setCurrentIndex(0);
  _ui.txtFilename->setText(_ctrl->_opt.liste());
  _ui.cmbStyle->setCurrentIndex(_ui.cmbStyle->findText(_ctrl->_opt.style()));
}

void WinOptions::searchFile()
{
  _ui.txtFilename->setText(
    QFileDialog::getOpenFileName(this, tr("Listes"),
                                 _ctrl->_opt.liste(),
                                 tr("Fichiers listes (*.txt)")));
}

void WinOptions::abandon()
{
  resetFrm();
  _ctrl->refreshStyle();
  close();
}

void WinOptions::confirm()
{
  //style
  _ctrl->_opt.setStyle(_ui.cmbStyle->currentText());
  _ctrl->_opt.save();

  //fichier
  if (_ctrl->_opt.liste() != _ui.txtFilename->text())
  {
    _ctrl->save();
    _ctrl->_listes.clear();
    _ctrl->_opt.setListe(_ui.txtFilename->text());
    _ctrl->load();
    _ctrl->sortList();
  }

  abandon();
}
