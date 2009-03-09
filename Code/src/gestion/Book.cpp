
#include "Book.h"

//Constructeur
Book::Book()
{
	this->auteur = "";
	this->titre = "";
	this->format = FRT_PAPIER;
	this->type = TYPE_BOOK;
}
//Destructeur
Book::~Book()
{
	return;
}
//Accesseur en lecture sur l'auteur
const string Book::get_auteur() const
{
	return auteur;
}
//Accesseur en lecture sur le titre
const string Book::get_titre() const
{
	return titre;
}
//Accesseur en lecture sur le format
const int Book::get_format() const
{
	return format;
}
//Renvoie la première lettre caractéristique du média
char Book::get_firstLetter()
{
	return (this->auteur.c_str())[0];
}
//Accesseur en ecriture sur l'auteur
void Book::set_auteur(string value)
{
	auteur = value;
}
//Accesseur en ecriture sur le titre
void Book::set_titre(string value)
{
	titre = value;
}
//Accesseur en ecriture sur le format
void Book::set_format(int value)
{
	format = value;
}
//Operateur d'affectation
const Book* Book::operator=(const Book* book)
{
	this->auteur = book->auteur;
	this->titre = book->titre;
	this->format = book->format;
	this->num = book->num;
	this->date = book->date;
	this->idBoite = book->idBoite;
	this->type = book->type;
	return this;
}
//Test de l'auteur
const int Book::test_auteur(string auteur)
{
	if (auteur.size() == 0) return 0;
	
	return Utils::test_alpha(auteur);
}
//Test du titre
const int Book::test_titre(string titre)
{
	if (titre.size() == 0) return 0;
	
	return Utils::test_alpha(titre);
}
//Comparaison de 2 livres par leur auteur/titre
const int Book::cmp_alpha(const Book* book1, const Book* book2)
{
	if (Utils::str_compare(book1->get_auteur(), book2->get_auteur()) == 1)
		return 1;
	if (Utils::str_compare(book1->get_auteur(), book2->get_auteur()) == 0)
		return Utils::str_compare(book1->get_titre(), book2->get_titre());
	return -1;
}
