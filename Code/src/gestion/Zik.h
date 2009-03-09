#ifndef _ZIK_H
#define _ZIK_H


#include "Media.h"
#include <string>
using namespace std;

#define TYPE_ZIK 2

//Item de musique
class Zik : public Media
{
  protected:
	//Nom de l'artiste
	string artiste;
	//Titre de l'album
	string titre;
	//Nombre de cd
	int nbCd;

  public:
	//Constructeur
	Zik();
	//Destructeur
	virtual ~Zik();
	//Accesseur en lecture sur l'artiste
	const string get_artiste() const;
	//Accesseur en lecture sur le titre
	const string get_titre() const;
	//Accesseur en lecture sur le nombre de cd
	const int get_nbCd() const;
	//Renvoie la première lettre caractéristique du média
	virtual char get_firstLetter();
	//Accesseur en ecriture sur l'artiste
	void set_artiste(string value);
	//Accesseur en ecriture sur le titre
	void set_titre(string value);
	//Accesseur en ecriture sur le nombre de cd
	void set_nbCd(int value);
	//Operateur d'affectation
	virtual const Zik* operator=(const Zik* zik);
	//Test de l'artiste
	static const int test_artiste(string artiste);
	//Test du titre
	static const int test_titre(string titre);
	//Test du nombre de cd
	static const int test_nbCd(int /*nbCd*/);
	//Comparaison de 2 album par leur artiste/titre
	static const int cmp_alpha(const Zik* zik1, const Zik* zik2);
};
#endif
