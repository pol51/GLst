#ifndef _ACCES_H
#define _ACCES_H


#include <string>
using namespace std;

class Collection;
class Media;

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Zik.h"
#include "Film.h"
#include "Book.h"
#include "Media.h"

//Acces aux données externes
class Acces
{
  protected:
	//Collection
	Collection * collection;

  public:
	//Constructeur
	Acces(Collection * collection);
	//Destructeur
	virtual ~Acces();
	//Chargement du fichier
	const int load(string filename);
	//Sauvegarde du fichier
	const int save(string filename);
	//Formatage d'une ligne
	string code(const Media* media);
	//Décodage d'une ligne
	Media* decode(string ligne);
};
#endif
