#include <QtGui>
#include <QMessageBox>

#include "winListe.h"
#include "winZik.h"

winZik::winZik(winListe *ctrl, QWidget *parent):QWidget(parent)
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
}

void winZik::resetFrm()
{
	this->modif = -1;
	this->ui.txtArtiste->setFocus();
	this->ui.txtArtiste->setText("");
	this->ui.txtTitre->setText("");
	this->ui.spinNbCd->setValue(1);
	this->ui.spinIdBoite->setValue(0);
	this->ui.date->setDate(QDate::currentDate());
}

void winZik::abandon()
{
	this->resetFrm();
	this->close();
}

void winZik::confirm()
{
	//test des valeurs
	if (Zik::test_artiste(this->ui.txtArtiste->text().toStdString()) == 0)
	{
		QMessageBox::information(0, "Erreur de saisie", "Artiste incorrect");
		this->ui.txtArtiste->setFocus();
		return;
	}
	if (Zik::test_titre(this->ui.txtTitre->text().toStdString()) == 0)
	{
		QMessageBox::information(0, "Erreur de saisie", "Titre incorrect");
		this->ui.txtTitre->setFocus();
		return;
	}
	if (Zik::test_nbCd(this->ui.spinNbCd->value()) == 0)
	{
		QMessageBox::information(0, "Erreur de saisie", "Nombre de CD incorrect");
		this->ui.spinNbCd->setFocus();
		return;
	}
	if (Media::test_date(this->ui.date->date().toString("yyyyMMdd").toStdString()) == 0)
	{
		QMessageBox::information(0, "Erreur de saisie", "Date incorrecte");
		this->ui.date->setFocus();
		return;
	}
	
	//affectation des valeurs
	Zik* tmpZ;
	if (this->modif < 0)
		tmpZ = (Zik*)this->ctrl->Listes->add_Zik();
	else
		tmpZ = (Zik*)this->ctrl->Listes->get_Media(modif);
	tmpZ->set_artiste(this->ui.txtArtiste->text().toStdString());
	tmpZ->set_titre(this->ui.txtTitre->text().toStdString());
	tmpZ->set_nbCd(this->ui.spinNbCd->value());
	tmpZ->set_idBoite(this->ui.spinIdBoite->value());
	if (this->modif < 0)
		tmpZ->set_num(this->ctrl->Listes->nextref_Media(TYPE_ZIK));
	tmpZ->set_date(this->ui.date->date().toString("yyyyMMdd").toStdString());

	//trie
	this->ctrl->sortList();
	
	//sauvegarde
    this->ctrl->save();
	
	//effacement et fermeture du formulaire
	this->abandon();
}

void winZik::setVals(int idn)
{
	//verif de l'id
	if ((idn < 0) or (idn >= this->ctrl->Listes->nb_Media())) return;
		
	//recup des infos du media
	Zik* tmpZ = (Zik*)this->ctrl->Listes->get_Media(idn);
	this->ui.txtArtiste->setText(tmpZ->get_artiste().c_str());
	this->ui.txtTitre->setText(tmpZ->get_titre().c_str());
	this->ui.spinNbCd->setValue(tmpZ->get_nbCd());
	this->ui.spinIdBoite->setValue(tmpZ->get_idBoite());
	QString date = tmpZ->get_date().c_str();
	this->ui.date->setDate(QDate::fromString(date, "yyyyMMdd"));
	
	//definition du mode modif
	this->modif = idn;
}

void winZik::addTo(int idn)
{
	//verif de l'id
	if ((idn < 0) or (idn >= this->ctrl->Listes->nb_Media())) return;
		
	//recup des infos du media
	Zik* tmpZ = (Zik*)this->ctrl->Listes->get_Media(idn);
	this->ui.txtArtiste->setText(tmpZ->get_artiste().c_str());

	// focus
	this->ui.txtTitre->setFocus();
}
