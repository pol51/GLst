#ifndef _ACCES_HTML_H
#define _ACCES_HTML_H


#include "Acces.h"
#include <string>
using namespace std;

class Collection;
class Media;

//Export au format HTML
class Acces_HTML : public Acces
{
  public:
	//Constructeur
	Acces_HTML(Collection * collection);
	//Destructeur
	virtual ~Acces_HTML();
	//Chargement du fichier
	const int load(string /*filename*/);
	//Sauvegarde du fichier
	const int save(string filename);
	//Formatage d'une ligne
	string code(const Media* media);
	//Décodage d'une ligne
	Media* decode(string /*ligne*/);
};
#endif
