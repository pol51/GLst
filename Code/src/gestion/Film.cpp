
#include "Film.h"

//Constructeur
Film::Film()
{
	this->nom = "";
	this->nbCd = 0;
	this->nbDvd = 0;
	this->qualite = QLT_DVDRIP;
	this->genre = GNR_FILM;
	this->type = TYPE_FILM;
}
//Destructeur
Film::~Film()
{
	return;
}
//Accesseur en lecture sur le nom
const string Film::get_nom() const
{
	  return nom;
}
//Accesseur en lecture sur le nombre de cd
const int Film::get_nbCd() const
{
	  return nbCd;
}
//Accesseur en lecture sur le nombre de dvd
const int Film::get_nbDvd() const
{
	  return nbDvd;
}
//Accesseur en lecture sur la qualité
const int Film::get_qualite() const
{
	  return qualite;
}
//Accesseur en lecture sur le genre
const int Film::get_genre() const
{
	  return genre;
}
//Renvoie la première lettre caractéristique du média
char Film::get_firstLetter()
{
	return (this->nom.c_str())[0];
}
//Accesseur en ecriture sur le nom
void Film::set_nom(string value)
{
	  nom = value;
}
//Accesseur en ecriture sur le nombre de cd
void Film::set_nbCd(int value)
{
	  nbCd = value;
}
//Accesseur en ecriture sur le nombre de dvd
void Film::set_nbDvd(int value)
{
	  nbDvd = value;
}
//Accesseur en ecriture sur la qualité
void Film::set_qualite(int value)
{
	  qualite = value;
}
//Accesseur en ecriture sur le genre
void Film::set_genre(int value)
{
	  genre = value;
}
//Operateur d'affectation
const Film* Film::operator=(const Film* film)
{
	this->nom = film->nom;
	this->nbCd = film->nbCd;
	this->nbDvd = film->nbDvd;
	this->num = film->num;
	this->date = film->date;
	this->idBoite = film->idBoite;
	this->qualite = film->qualite;
	this->genre = film->genre;
	this->type = film->type;
	return this;
}
//Test du nom
const int Film::test_nom(string nom)
{
	if (nom.size() == 0) return 0;
	
	return Utils::test_alpha(nom);
}
//Test du nombre de cd
const int Film::test_nbCd(int /*nbCd*/)
{
	return 1;
}
//Test du nombre de dvd
const int Film::test_nbDvd(int /*nbCd*/)
{
	return 1;
}
//Comparaison de 2 films par leur nom
const int Film::cmp_alpha(const Film* film1, const Film* film2)
{
	return Utils::str_compare(film1->get_nom(), film2->get_nom());
}
