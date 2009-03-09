
#include "Acces.h"
#include "Collection.h"
#include "Media.h"

//Constructeur
Acces::Acces(Collection * collection)
{
	this->collection = collection;
}
//Destructeur
Acces::~Acces()
{
	return;
}
//Chargement du fichier
const int Acces::load(string filename)
{
	char buffer[1024];
	string line;
	Media* med_src;
	Media* med_dest;
	
	fstream f(filename.c_str(), fstream::in);
	
	if (f == 0) return 0;
	
	while(!f.eof())
	{
		f.get(buffer, 1024);
		f.ignore();
		line = string(buffer);
		
		//récupération du résultat de la ligne
		med_src = decode(line);
		
		//test de ligne correcte
		if (med_src == NULL) break;
		
		//test de doublon
		if (collection->find_Media(med_src->get_num()) >= 0)
		{
			delete med_src;
			med_src = NULL;
			continue;
		}
		
		//ajout d'un media dans la collection
		switch (med_src->get_type())
		{
			case TYPE_ZIK:
				med_dest = (Zik*)collection->add_Zik();
				*((Zik*)med_dest) = *((Zik*)med_src);
				break;
			case TYPE_FILM:
				med_dest = (Film*)collection->add_Film();
				*((Film*)med_dest) = *((Film*)med_src);
				break;
			case TYPE_BOOK:
				med_dest = (Book*)collection->add_Book();
				*((Book*)med_dest) = *((Book*)med_src);
				break;
			default:
				delete med_src;
				med_dest = NULL;
				break;
		}
	}
	
	f.close();
	
	return 1;
}
//Sauvegarde du fichier
const int Acces::save(string filename)
{
	string line;
	
	fstream f(filename.c_str(), fstream::out);
	
	if (f == NULL) return 0;
	
	for (int i = 0; i < collection->nb_Media(); i++)
		f << code(collection->get_Media(i));
	
	f.close();
	
	return 1;
}
//Formatage d'une ligne
string Acces::code(const Media* media)
{
	ostringstream line;
	
	//type
	line << media->get_type();
	
	//num
	line << " " << media->get_num();
	
	//infos spécifiques
	switch (media->get_type())
	{
		case TYPE_ZIK:
			line << " " << Utils::sp2und(((Zik*)media)->get_artiste());
			line << " " << Utils::sp2und(((Zik*)media)->get_titre());
			line << " " << ((Zik*)media)->get_nbCd();
			break;
		case TYPE_FILM:
			line << " " << Utils::sp2und(((Film*)media)->get_nom());
			line << " " << ((Film*)media)->get_nbCd();
			line << " " << ((Film*)media)->get_nbDvd();
			line << " " << ((Film*)media)->get_qualite();
			line << " " << ((Film*)media)->get_genre();
			break;
		case TYPE_BOOK:
			line << " " << Utils::sp2und(((Book*)media)->get_auteur());
			line << " " << Utils::sp2und(((Book*)media)->get_titre());
			line << " " << ((Book*)media)->get_format();
			break;
		
	}
	
	//id boite
	line << " " << media->get_idBoite();
	
	//date
	line << " " << media->get_date();
	
	//eol
	line << "\n";
	
	return line.str();
}
//Décodage d'une ligne
Media* Acces::decode(string ligne)
{
	//variables tampons
	char nom[512];
	char artiste[512];
	char auteur[512];
	char titre[512];
	char num[NUM_SIZE];
	char date[512];
	int nbCd;
	int nbDvd;
	int type;
	int idBoite;
	int qualite;
	int genre;
	int format;
	
	Media* tmpMed;
	
	//test de la longueur de la ligne
	if (ligne.size() < 1)
		return NULL;
	
	switch (ligne.c_str()[0] - '0')
	{
		case TYPE_ZIK:
			//decoupe
			if (sscanf(ligne.c_str(), "%d %s %s %s %d %d %s",
				&type, num, artiste, titre, &nbCd, &idBoite, date) != 7)
				return NULL;
			//tests
			if (Media::test_num(string(num)) != 1)			return NULL;
			if (Zik::test_artiste(string(artiste)) != 1)	return NULL;
			if (Zik::test_titre(string(titre)) != 1)		return NULL;
			if (Media::test_date(string(date)) != 1)		return NULL;
			//création du media
			tmpMed = new Zik();
			//affectation des valeurs au media
			((Zik*)tmpMed)->set_artiste(Utils::und2sp(string(artiste)));
			((Zik*)tmpMed)->set_titre(Utils::und2sp(string(titre)));
			((Zik*)tmpMed)->set_nbCd(nbCd);
			((Zik*)tmpMed)->set_num(string(num));
			((Zik*)tmpMed)->set_idBoite(idBoite);
			((Zik*)tmpMed)->set_date(string(date));
			break;
		case TYPE_FILM:
			//decoupe
			if (sscanf(ligne.c_str(), "%d %s %s %d %d %d %d %d %s",
				&type, num, nom, &nbCd, &nbDvd, &qualite, &genre, &idBoite, date) != 9)
				return NULL;
			//tests
			if (Media::test_num(string(num)) != 1)			return NULL;
			if (Film::test_nom(string(nom)) != 1)			return NULL;
			if (Media::test_date(string(date)) != 1)		return NULL;
			//création du media
			tmpMed = new Film();
			//affectation des valeurs au media
			((Film*)tmpMed)->set_nom(Utils::und2sp(string(nom)));
			((Film*)tmpMed)->set_nbCd(nbCd);
			((Film*)tmpMed)->set_nbDvd(nbDvd);
			((Film*)tmpMed)->set_qualite(qualite);
			((Film*)tmpMed)->set_genre(genre);
			((Film*)tmpMed)->set_num(string(num));
			((Film*)tmpMed)->set_idBoite(idBoite);
			((Film*)tmpMed)->set_date(string(date));
			break;
		case TYPE_BOOK:
			//decoupe
			if (sscanf(ligne.c_str(), "%d %s %s %s %d %d %s",
				&type, num, auteur, titre, &format, &idBoite, date) != 7)
				return NULL;
			//tests
			if (Media::test_num(string(num)) != 1)			return NULL;
			if (Book::test_auteur(string(auteur)) != 1)		return NULL;
			if (Book::test_titre(string(titre)) != 1)		return NULL;
			if (Media::test_date(string(date)) != 1)		return NULL;
			//création du media
			tmpMed = new Book();
			//affectation des valeurs au media
			((Book*)tmpMed)->set_auteur(Utils::und2sp(string(auteur)));
			((Book*)tmpMed)->set_titre(Utils::und2sp(string(titre)));
			((Book*)tmpMed)->set_format(format);
			((Book*)tmpMed)->set_num(string(num));
			((Book*)tmpMed)->set_idBoite(idBoite);
			((Book*)tmpMed)->set_date(string(date));
			break;
		default:
			return NULL;
	}
	
	return tmpMed;
}
