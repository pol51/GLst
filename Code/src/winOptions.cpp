#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>

#include "winOptions.h"
#include "winListe.h"

winOptions::winOptions(winListe *ctrl, QWidget *parent):QWidget(parent)
{
	this->ui.setupUi(this);
	this->ctrl = ctrl;
	
	//evenements
	QObject::connect(
		this->ui.btnCancel, SIGNAL(clicked()),
		this, SLOT(abandon()));
	QObject::connect(
		this->ui.btnOk, SIGNAL(clicked()),
		this, SLOT(confirm()));
	QObject::connect(
		this->ui.btnSearchFile, SIGNAL(clicked()),
		this, SLOT(searchFile()));
	QObject::connect(
		this->ui.cmbStyle, SIGNAL(activated(const QString &)),
		this->ctrl, SLOT(changeStyle(const QString &)));
	
	//affectation des valeurs aux éléments
	this->ui.cmbStyle->addItems(QStyleFactory::keys());
}

void winOptions::resetFrm()
{
	this->ui.tabOptions->setCurrentIndex(0);
	this->ui.txtFilename->setText(this->ctrl->Opt->get_liste().c_str());
	
	//recherche du nom du style dans la liste
	int i = this->ui.cmbStyle->count();
	while (
		(this->ui.cmbStyle->currentText() !=
		this->ctrl->Opt->get_style().c_str())
		and (i >= 0)
	)
		this->ui.cmbStyle->setCurrentIndex(i--);
}

void winOptions::searchFile()
{
	QString fileName = "";
	fileName = QFileDialog::getOpenFileName(this,
		QObject::tr("Listes"),
		this->ctrl->Opt->get_liste().c_str(),
		QObject::tr("Fichiers listes (*.txt)"));
	this->ui.txtFilename->setText(fileName);
}

void winOptions::abandon()
{
	this->resetFrm();
	this->ctrl->refreshStyle();
	this->close();
}

void winOptions::confirm()
{
	//style
	this->ctrl->Opt->set_style(this->ui.cmbStyle->currentText().toStdString());
	this->ctrl->Opt->save();
	
	//fichier
	if (strcmp(this->ctrl->Opt->get_liste().c_str(),
		this->ui.txtFilename->text().toStdString().c_str()) != 0)
	{
		this->ctrl->save();
		this->ctrl->Listes->clear();
		this->ctrl->Opt->set_liste(
			this->ui.txtFilename->text().toStdString().c_str());
		this->ctrl->load();
		this->ctrl->sortList();
	}
	
	this->abandon();
}
