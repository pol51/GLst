#ifndef _FILM_H
#define _FILM_H


#include "Media.h"
#include <string>
using namespace std;

#define TYPE_FILM 1

typedef enum
{
	QLT_DVDRIP,
	QLT_SCR,
	QLT_DVD,
	QLT_TVRIP,
	QLT_PUB,
	QLT_DVDSCR,
	QLT_VCD
} QLT;

typedef enum
{
	GNR_FILM,
	GNR_LIVE,
	GNR_SPECTACLE,
	GNR_MANGA,
	GNR_DESSIN_A,
	GNR_SERIE,
	GNR_DOC
} GNR;

//Item de film
class Film : public Media
{
  protected:
	//Nom du film
	string nom;
	//Nombre de cd
	int nbCd;
	//Nombre de dvd
	int nbDvd;
	//Qualité du film
	int qualite;
	//Genre du film
	int genre;

  public:
	//Constructeur
	Film();
	//Destructeur
	virtual ~Film();
	//Accesseur en lecture sur le nom
	const string get_nom() const;
	//Accesseur en lecture sur le nombre de cd
	const int get_nbCd() const;
	//Accesseur en lecture sur le nombre de dvd
	const int get_nbDvd() const;
	//Accesseur en lecture sur la qualité
	const int get_qualite() const;
	//Accesseur en lecture sur le genre
	const int get_genre() const;
	//Renvoie la première lettre caractéristique du média
	virtual char get_firstLetter();
	//Accesseur en ecriture sur le nom
	void set_nom(string value);
	//Accesseur en ecriture sur le nombre de cd
	void set_nbCd(int value);
	//Accesseur en ecriture sur le nombre de dvd
	void set_nbDvd(int value);
	//Accesseur en ecriture sur la qualité
	void set_qualite(int value);
	//Accesseur en ecriture sur le genre
	void set_genre(int value);
	//Operateur d'affectation
	virtual const Film* operator=(const Film* film);
	//Test du nom
	static const int test_nom(string nom);
	//Test du nombre de cd
	static const int test_nbCd(int /*nbCd*/);
	//Test du nombre de dvd
	static const int test_nbDvd(int /*nbCd*/);
	//Comparaison de 2 films par leur nom
	static const int cmp_alpha(const Film* film1, const Film* film2);
};
#endif
