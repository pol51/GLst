#include "winListe.h"

#include "winFilm.h"
#include "winZik.h"
#include "winBook.h"
#include "winOptions.h"
#include "winListeMenu.h"
#include "./gestion/Utils.h"
#include "widgetListe.h"

#include <QtGui>
#include <QMessageBox>

winListe::winListe(QWidget *parent):QWidget(parent)
{
	this->ui.setupUi(this);
	
	//initialisation des dialogues de saisie
	frmZik = new winZik(this);
	frmFilm = new winFilm(this);
	frmBook = new winBook(this);
	
	//initialisation du dialogue d'optionss
	frmOptions = new winOptions(this);
	
	//initialisation des options
	Opt = new Options(string(OPTIONS_FILE));
	if (Opt->load() != NB_OPTIONS) Opt->save();
	
	//initaialisation de la collection et de son AccessDE
	Listes = new Collection();
	ListDE = new Acces(Listes);
	ListHTML = new Acces_HTML(Listes);
	
	//initialisation du menu
	Menu = new winListeMenu(this);
	
	//attribution du controlleur de this->ui.listM
	this->ui.listM->setCtrl(this);
	
	//chargement du style
	this->refreshStyle();
	
	//evenements
	QObject::connect(
		this->ui.btnAjout, SIGNAL(clicked()),
		this, SLOT(showAdd()));
	QObject::connect(
		this->ui.btnQuit, SIGNAL(clicked()),
		this, SLOT(closeAll()));
	QObject::connect(
		this->ui.comboType, SIGNAL(activated(int)),
		this, SLOT(updateLst(int)));
	QObject::connect(
		this->ui.btnSuppr, SIGNAL(clicked()),
		this, SLOT(delMedia()));
	QObject::connect(
		this->ui.btnModif, SIGNAL(clicked()),
		this, SLOT(showMod()));
	QObject::connect(
		this->ui.listM, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
		this, SLOT(showMod()));
	QObject::connect(
		this->ui.chkNews, SIGNAL(stateChanged(int)),
		this, SLOT(sortList(int)));
	QObject::connect(
		this->ui.chkInfo, SIGNAL(stateChanged(int)),
		this, SLOT(refreshLst()));
	QObject::connect(
		this->ui.btnOptions, SIGNAL(clicked()),
		this, SLOT(showOptions()));
	QObject::connect(
		this->ui.btnExHTML, SIGNAL(clicked()),
		this, SLOT(exportHTML()));
	
	//affectation des valeurs aux lments
	originalPalette = QApplication::palette();
	this->ui.comboType->addItem("Film");
	this->ui.comboType->addItem("Zik");
	this->ui.comboType->addItem("Livres");
	this->ui.lblStat->setText("Chargement...");
	if (Opt->get_sortType() == SORT_DATE)
		this->ui.chkNews->setCheckState(Qt::Checked);
}

void winListe::save()
{
	this->ListDE->save(Opt->get_liste().c_str());
}

void winListe::load()
{
	this->ui.lblStat->setText("Chargement...");
	this->ListDE->load(Opt->get_liste().c_str());
	this->refreshLst();
}

void winListe::exportHTML()
{
	this->ListHTML->save("Listes.html");
	this->refreshLst();
	this->ui.chkNews->setCheckState(Qt::Unchecked);
}

void winListe::changeStyle(const QString &styleName)
{
	QApplication::setStyle(QStyleFactory::create(styleName));
//	QApplication::setPalette(QApplication::style()->standardPalette());
}

void winListe::refreshStyle()
{
    QApplication::setStyle(QStyleFactory::create(Opt->get_style().c_str()));
    //QApplication::setPalette(QApplication::style()->standardPalette());
}

void winListe::showAdd()
{
	closeAll();
	switch(this->ui.comboType->currentIndex() + 1)
	{
		case TYPE_FILM:
			this->frmFilm->show();
			break;
		case TYPE_ZIK:
			this->frmZik->show();
			break;
		case TYPE_BOOK:
			this->frmBook->show();
			break;
	}
}

void winListe::showAddTo()
{
	closeAll();
	int id = this->selectedId();
	switch(this->ui.comboType->currentIndex() + 1)
	{
		case TYPE_ZIK:
			this->frmZik->addTo(id);
			this->frmZik->show();
			break;
		case TYPE_BOOK:
			this->frmBook->addTo(id);
			this->frmBook->show();
			break;
	}
}

void winListe::showOptions()
{
	closeAll();
	this->frmOptions->resetFrm();
	this->frmOptions->show();
}

void winListe::showMod()
{
	int id = this->selectedId();
	if (id >= 0)
	{
		closeAll();
		switch(this->ui.comboType->currentIndex() + 1)
		{
			case TYPE_FILM:
				this->frmFilm->setVals(id);
				this->frmFilm->show();
				break;
			case TYPE_ZIK:
				this->frmZik->setVals(id);
				this->frmZik->show();
				break;
			case TYPE_BOOK:
				this->frmBook->setVals(id);
				this->frmBook->show();
				break;
		}
	}
}

void winListe::closeAll()
{
	this->frmFilm->close();
	this->frmZik->close();
	this->frmBook->close();
	this->frmOptions->close();
}

void winListe::delMedia()
{
    int id = this->selectedId();
	if (id >= 0)
	{
		this->Listes->del_Media(id);
		this->refreshLst();
	}
	this->save();
}

int winListe::selectedId()
{
	int id;
	id = this->ui.listM->currentRow();
	int idn = 0;
	Media* tmpM;
	for (int i = 0; i < Listes->nb_Media(); i++)
	{
		tmpM = Listes->get_Media(i);
		if (tmpM->get_type() == (this->ui.comboType->currentIndex() + 1))
			if (idn == id)
				return i;
			else
				idn++;
	}
	return -1;
}

void winListe::refreshLst()
{
	this->updateLst(this->ui.comboType->currentIndex());
}

bool winListe::canAddToItem()
{
	Media * tmpMedia = Listes->get_Media(this->selectedId());
	if (tmpMedia == NULL)
		return false;
	switch (tmpMedia->get_type())
	{
		case TYPE_ZIK:
		case TYPE_BOOK:
			return true;
		case TYPE_FILM:
		default:
			return false;
	}
}

void winListe::updateLst(int type)
{
	int info = 0;
	if (this->ui.chkInfo->checkState()  == Qt::Checked)
		info = 1;
	int nb_Cd = 0;
	int nb_Dvd = 0;
	int nb_Elem = 0;
	ostringstream status;
	type++;
	Media* tmpM;
	this->ui.listM->clear();
	QString line;
	switch(type)
	{
		case TYPE_FILM:
			status << "Film: ";
			for (int i = 0; i < Listes->nb_Media(); i++)
			{
				tmpM = Listes->get_Media(i);
				if (tmpM->get_type() == TYPE_FILM)
				{
					nb_Elem++;
					line = QString(((Film*)tmpM)->get_nom().c_str());
					if (((Film*)tmpM)->get_nbCd() > 0)
					{
						ostringstream tmp;
						tmp << (((Film*)tmpM)->get_nbCd());
						nb_Cd += (((Film*)tmpM)->get_nbCd());
						line += " (";
						line += tmp.str().c_str();
						line += "CD)";
					}
					if (((Film*)tmpM)->get_nbDvd() > 0)
					{
						ostringstream tmp;
						tmp << (((Film*)tmpM)->get_nbDvd());
						nb_Dvd += (((Film*)tmpM)->get_nbDvd());
						line += " (";
						line += tmp.str().c_str();
						line += "DVD)";
					}
					if (info > 0)
					{
						if (tmpM->get_idBoite() > 0)
						{
							ostringstream tmp;
							tmp << (tmpM->get_idBoite());
							line += " [#";
							line += tmp.str().c_str();
							line += "]";
						}
						switch(((Film*)tmpM)->get_qualite())
						{
							case QLT_DVDRIP:	line += " [DvdRip]";	break;
							case QLT_SCR:		line += " [Scr]";		break;
							case QLT_DVD:		line += " [Dvd]";		break;
							case QLT_TVRIP:		line += " [TvRip]";		break;
							case QLT_PUB:		line += " [Pub]";		break;
							case QLT_DVDSCR:	line += " [DvdScr]";	break;
							case QLT_VCD:		line += " [Vcd]";		break;
						}
						switch(((Film*)tmpM)->get_genre())
						{
							case GNR_FILM:		line += " <Film>";			break;
							case GNR_LIVE:		line += " <Concert>";		break;
							case GNR_SPECTACLE:	line += " <Spectacle>";		break;
							case GNR_MANGA:		line += " <Manga>";			break;
							case GNR_DESSIN_A:	line += " <Dessin Anim>";	break;
							case GNR_SERIE:		line += " <Srie>";			break;
							case GNR_DOC:		line += " <Documentaire>";	break;
						}
					}
					this->ui.listM->addItem(line);
				}
			}
			status << nb_Elem << " => " << nb_Cd << "CD + " << nb_Dvd << "DVD";
			this->ui.lblStat->setText(status.str().c_str());
            break;
		case TYPE_ZIK:
			status << "Zik: ";
			this->ui.lblStat->setText("Zik: ");
			for (int i = 0; i < Listes->nb_Media(); i++)
			{
				tmpM = Listes->get_Media(i);
				if (tmpM->get_type() == TYPE_ZIK)
				{
					nb_Elem++;
					line = QString(((Zik*)tmpM)->get_artiste().c_str());
					line += " - ";
					line += QString(((Zik*)tmpM)->get_titre().c_str());
					if (((Zik*)tmpM)->get_nbCd() > 0)
					{
						ostringstream tmp;
						tmp << (((Zik*)tmpM)->get_nbCd());
						nb_Cd += (((Zik*)tmpM)->get_nbCd());
						line += " (";
						line += tmp.str().c_str();
						line += "CD)";
					}
					if (info > 0)
						if (tmpM->get_idBoite() > 0)
						{
							ostringstream tmp;
							tmp << (tmpM->get_idBoite());
							line += " [#";
							line += tmp.str().c_str();
							line += "]";
						}
					this->ui.listM->addItem(line);
				}
			}
			status << nb_Elem << " => " << nb_Cd << "CD";
			this->ui.lblStat->setText(status.str().c_str());
            break;
		case TYPE_BOOK:
			status << "Livres: ";
			this->ui.lblStat->setText("Livres: ");
			for (int i = 0; i < Listes->nb_Media(); i++)
			{
				tmpM = Listes->get_Media(i);
				if (tmpM->get_type() == TYPE_BOOK)
				{
					nb_Elem++;
					line = QString(((Book*)tmpM)->get_auteur().c_str());
					line += " - ";
					line += QString(((Book*)tmpM)->get_titre().c_str());
					if (info > 0)
						switch (((Book*)tmpM)->get_format())
						{
							case FRT_PAPIER:
								line += QString(" [papier]");
								break;
							case FRT_NUMERIC:
								line += QString(" [e-book]");
								break;
						}
					this->ui.listM->addItem(line);
				}
			}
			status << nb_Elem;
			this->ui.lblStat->setText(status.str().c_str());
            break;
	}
}

void winListe::sortList()
{
	sortList(-1);
}

void winListe::sortList(int type)
{
	if (type != SORT_ALPHA && type != SORT_DATE);
		type = this->ui.chkNews->checkState();
	
	if (type == Qt::Checked)
		type = SORT_DATE;
	else
		type = SORT_ALPHA;
	
	// trie de la liste
	this->Listes->sort_Media(type);
	this->refreshLst();
	
	//sauvegarde dans les options
	this->Opt->set_sortType(type);
	this->Opt->save();
}
