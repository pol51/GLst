#include <QtGui>
#include <QMessageBox>

#include "winFilm.h"
#include "winListe.h"

winFilm::winFilm(winListe *ctrl, QWidget *parent):QWidget(parent)
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
	this->ui.cmbQualite->addItem("DvdRip");
	this->ui.cmbQualite->addItem("Screener");
	this->ui.cmbQualite->addItem("Dvd");
	this->ui.cmbQualite->addItem("TVRip");
	this->ui.cmbQualite->addItem("Publicitaire");
	this->ui.cmbQualite->addItem("Dvd Screener");
	this->ui.cmbQualite->addItem("Vcd");
	this->ui.cmbGenre->addItem("Film");
	this->ui.cmbGenre->addItem("Concert");
	this->ui.cmbGenre->addItem("Spectacle");
	this->ui.cmbGenre->addItem("Manga");
	this->ui.cmbGenre->addItem("Dessin Animé");
	this->ui.cmbGenre->addItem("Serie");
	this->ui.cmbGenre->addItem("Documentaire");
	
}

void winFilm::resetFrm()
{
	this->modif = -1;
	this->ui.cmbQualite->setCurrentIndex(0);
	this->ui.cmbGenre->setCurrentIndex(0);
	this->ui.txtNom->setFocus();
	this->ui.txtNom->setText("");
	this->ui.spinNbCd->setValue(1);
	this->ui.spinNbDvd->setValue(0);
	this->ui.spinIdBoite->setValue(0);
	this->ui.date->setDate(QDate::currentDate());
}

void winFilm::abandon()
{
	this->resetFrm();
	this->close();
}

void winFilm::confirm()
{
	//test des valeurs
	if (Film::test_nom(this->ui.txtNom->text().toStdString()) == 0)
	{
		QMessageBox::information(0, "Erreur de saisie", "Nom incorrect");
		this->ui.txtNom->setFocus();
		return;
	}
	if (Film::test_nbCd(this->ui.spinNbCd->value()) == 0)
	{
		QMessageBox::information(0, "Erreur de saisie", "Nombre de CD incorrect");
		this->ui.spinNbCd->setFocus();
		return;
	}
	if (Film::test_nbDvd(this->ui.spinNbDvd->value()) == 0)
	{
		QMessageBox::information(0, "Erreur de saisie", "Nombre de DVD incorrect");
		this->ui.spinNbDvd->setFocus();
		return;
	}
	if (Media::test_date(this->ui.date->date().toString("yyyyMMdd").toStdString()) == 0)
	{
		QMessageBox::information(0, "Erreur de saisie", "Date incorrecte");
		this->ui.date->setFocus();
		return;
	}
	
	//affectation des valeurs
	Film* tmpF;
	if (this->modif < 0)
		tmpF = (Film*)this->ctrl->Listes->add_Film();
	else
		tmpF = (Film*)this->ctrl->Listes->get_Media(modif);
	tmpF->set_nom(this->ui.txtNom->text().toStdString());
	tmpF->set_nbCd(this->ui.spinNbCd->value());
	tmpF->set_nbDvd(this->ui.spinNbDvd->value());
	tmpF->set_qualite(this->ui.cmbQualite->currentIndex());
	tmpF->set_genre(this->ui.cmbGenre->currentIndex());
	tmpF->set_idBoite(this->ui.spinIdBoite->value());
	if (this->modif < 0)
		tmpF->set_num(this->ctrl->Listes->nextref_Media(TYPE_FILM));
	tmpF->set_date(this->ui.date->date().toString("yyyyMMdd").toStdString());
    
    //trie
	this->ctrl->sortList();
	
	//sauvegarde
    this->ctrl->save();

	//effacement et fermeture du formulaire
	this->abandon();
}

void winFilm::setVals(int idn)
{
	//verif de l'id
	if ((idn < 0) or (idn >= this->ctrl->Listes->nb_Media())) return;
		
	//recup des infos du media
	Film* tmpF = (Film*)this->ctrl->Listes->get_Media(idn);
	this->ui.txtNom->setText(tmpF->get_nom().c_str());
	this->ui.spinNbCd->setValue(tmpF->get_nbCd());
	this->ui.spinNbDvd->setValue(tmpF->get_nbDvd());
	this->ui.spinIdBoite->setValue(tmpF->get_idBoite());
	this->ui.cmbQualite->setCurrentIndex(tmpF->get_qualite());
	this->ui.cmbGenre->setCurrentIndex(tmpF->get_genre());
	QString date = tmpF->get_date().c_str();
	this->ui.date->setDate(QDate::fromString(date, "yyyyMMdd"));
	
	//definition du mode modif
	this->modif = idn;
}
