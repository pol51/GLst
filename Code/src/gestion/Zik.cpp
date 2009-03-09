
#include "Zik.h"

//Constructeur
Zik::Zik()
{
	this->artiste = "";
	this->titre = "";
	this->nbCd = 0;
	this->type = TYPE_ZIK;
}
//Destructeur
Zik::~Zik()
{
	return;
}
//Accesseur en lecture sur l'artiste
const string Zik::get_artiste() const
{
	  return artiste;
}
//Accesseur en lecture sur le titre
const string Zik::get_titre() const
{
	  return titre;
}
//Accesseur en lecture sur le nombre de cd
const int Zik::get_nbCd() const
{
	  return nbCd;
}
//Renvoie la première lettre caractéristique du média
char Zik::get_firstLetter()
{
	return (this->artiste.c_str())[0];
}
//Accesseur en ecriture sur l'artiste
void Zik::set_artiste(string value)
{
	  artiste = value;
}
//Accesseur en ecriture sur le titre
void Zik::set_titre(string value)
{
	  titre = value;
}
//Accesseur en ecriture sur le nombre de cd
void Zik::set_nbCd(int value)
{
	  nbCd = value;
}
//Operateur d'affectation
const Zik* Zik::operator=(const Zik* zik)
{
	this->artiste = zik->artiste;
	this->titre = zik->titre;
	this->nbCd = zik->nbCd;
	this->num = zik->num;
	this->date = zik->date;
	this->idBoite = zik->idBoite;
	this->type = zik->type;
	return this;
}
//Test de l'artiste
const int Zik::test_artiste(string artiste)
{
	if (artiste.size() == 0) return 0;
	
	return Utils::test_alpha(artiste);
}
//Test du titre
const int Zik::test_titre(string titre)
{
	if (titre.size() == 0) return 0;
	
	return Utils::test_alpha(titre);
}
//Test du nombre de cd
const int Zik::test_nbCd(int /*nbCd*/)
{
	return 1;
}
//Comparaison de 2 album par leur artiste/titre
const int Zik::cmp_alpha(const Zik* zik1, const Zik* zik2)
{
	if (Utils::str_compare(zik1->get_artiste(), zik2->get_artiste()) == 1)
		return 1;
	if (Utils::str_compare(zik1->get_artiste(), zik2->get_artiste()) == 0)
		return Utils::str_compare(zik1->get_titre(), zik2->get_titre());
	return -1;
}
