#include <QtGui>
#include <QMessageBox>

#include "winListe.h"
#include "winBook.h"

winBook::winBook(winListe *ctrl, QWidget *parent):QWidget(parent)
{
	this->ui.setupUi(this);
	this->ctrl = ctrl;
	QObject::connect(
		this->ui.cancelButton, SIGNAL(clicked()),
		this, SLOT(abandon()));
	QObject::connect(
		this->ui.okButton, SIGNAL(clicked()),
		this, SLOT(confirm()));
	this->resetFrm();
	
	//affectation des valeurs aux combobox
	this->ui.cmbFormat->addItem("Papier");
	this->ui.cmbFormat->addItem("E-Book");
}

void winBook::resetFrm()
{
	this->modif = -1;
	this->ui.cmbFormat->setCurrentIndex(0);
	this->ui.txtAuteur->setFocus();
	this->ui.txtAuteur->setText("");
	this->ui.txtTitre->setText("");
	this->ui.date->setDate(QDate::currentDate());
}

void winBook::abandon()
{
	this->resetFrm();
	this->close();
}

void winBook::confirm()
{
	//test des valeurs
	if (Book::test_auteur(this->ui.txtAuteur->text().toStdString()) == 0)
	{
		QMessageBox::information(0, "Erreur de saisie", "Auteur incorrect");
		this->ui.txtAuteur->setFocus();
		return;
	}
	if (Book::test_titre(this->ui.txtTitre->text().toStdString()) == 0)
	{
		QMessageBox::information(0, "Erreur de saisie", "Titre incorrect");
		this->ui.txtTitre->setFocus();
		return;
	}
	if (Media::test_date(this->ui.date->date().toString("yyyyMMdd").toStdString()) == 0)
	{
		QMessageBox::information(0, "Erreur de saisie", "Date incorrecte");
		this->ui.date->setFocus();
		return;
	}
	
	//affectation des valeurs
	Book* tmpB;
	if (this->modif < 0)
		tmpB = (Book*)this->ctrl->Listes->add_Book();
	else
		tmpB = (Book*)this->ctrl->Listes->get_Media(modif);
	tmpB->set_auteur(this->ui.txtAuteur->text().toStdString());
	tmpB->set_titre(this->ui.txtTitre->text().toStdString());
	tmpB->set_format(this->ui.cmbFormat->currentIndex());
	if (this->modif < 0)
		tmpB->set_num(this->ctrl->Listes->nextref_Media(TYPE_BOOK));
	tmpB->set_date(this->ui.date->date().toString("yyyyMMdd").toStdString());
	
	//trie
	this->ctrl->sortList();
	
	//sauvegarde
    this->ctrl->save();

	//effacement et fermeture du formulaire
	this->abandon();
}

void winBook::setVals(int idn)
{
	//verif de l'id
	if ((idn < 0) or (idn >= this->ctrl->Listes->nb_Media())) return;
	
	//recup des infos du media
	Book* tmpB = (Book*)this->ctrl->Listes->get_Media(idn);
	this->ui.txtAuteur->setText(tmpB->get_auteur().c_str());
	this->ui.txtTitre->setText(tmpB->get_titre().c_str());
	this->ui.cmbFormat->setCurrentIndex(tmpB->get_format());
	QString date = tmpB->get_date().c_str();
	this->ui.date->setDate(QDate::fromString(date, "yyyyMMdd"));
	
	//definition du mode modif
	this->modif = idn;
}

void winBook::addTo(int idn)
{
	//verif de l'id
	if ((idn < 0) or (idn >= this->ctrl->Listes->nb_Media())) return;
	
	//recup des infos du media
	Book* tmpB = (Book*)this->ctrl->Listes->get_Media(idn);
	this->ui.txtAuteur->setText(tmpB->get_auteur().c_str());
	
	// focus
	this->ui.txtTitre->setFocus();
}
