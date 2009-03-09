#ifndef _BOOK_H
#define _BOOK_H


#include "Media.h"
#include <string>
using namespace std;

#define TYPE_BOOK 3

typedef enum
{
	FRT_PAPIER,
	FRT_NUMERIC
} FRT;

//Item de livre
class Book : public Media
{
  protected:
	//Nom de l'auteur
	string auteur;
	//Titre du livre
	string titre;
	//Format du livre
	int format;

  public:
	//Constructeur
	Book();
	//Destructeur
	~Book();
	//Accesseur en lecture sur l'auteur
	const string get_auteur() const;
	//Accesseur en lecture sur le titre
	const string get_titre() const;
	//Accesseur en lecture sur le format
	const int get_format() const;
	//Renvoie la première lettre caractéristique du média
	virtual char get_firstLetter();
	//Accesseur en ecriture sur l'auteur
	void set_auteur(string value);
	//Accesseur en ecriture sur le titre
	void set_titre(string value);
	//Accesseur en ecriture sur le format
	void set_format(int value);
	//Operateur d'affectation
	const Book* operator=(const Book* book);
	//Test de l'auteur
	static const int test_auteur(string auteur);
	//Test du titre
	static const int test_titre(string titre);
	//Comparaison de 2 livres par leur auteur/titre
	static const int cmp_alpha(const Book* book1, const Book* book2);
};
#endif
