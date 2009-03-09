#ifndef _COLLECTION_H
#define _COLLECTION_H


#include <vector>
using namespace std;
#include <string>
using namespace std;

class Media;

#include <math.h>

#include "Media.h"
#include "Zik.h"
#include "Book.h"
#include "Film.h"

#define SORT_ALPHA	1
#define SORT_DATE	2

//Gestionnaire de la collection de medias
class Collection
{
  protected:
	//Etat du trie de la collection
	int sort;
	vector<Media*> vMedia;

  public:
	//Constructeur
	Collection();
	//Destructeur
	virtual ~Collection();
	//Permet de savoir si la collection est actuellement tri�e de cette mani�re.
	bool isSorted(int type);
	void setUnsorted();
	void clear();
	//Ajout d'un album dans la collection
	Media* add_Zik();
	//Ajout d'un film dans la collection
	Media* add_Film();
	//Ajout d'un livre dans la collection
	Media* add_Book();
	//Suppresision d'unmedia de la collection
	int del_Media(int id);
	//Recup�re un media dans la collection
	Media* get_Media(int id);
	//Recherche l'id d'un media par sa r�f�rence
	const int find_Media(string num);
	//Renvoie le nombre de media dans la collection
	const int nb_Media();
	//Renvoie le nombre de media d'un type donn� dans la collection
	const int nb_Media(int type);
	//Renvoie le prochain nombre attribuable � un media de type donn�
	const int nextref_Media(int type);
	//Trie la collection (par fusion)
	//SORT_ALPHA  -> trie alphab�tique
	//SORT_DATE -> trie par date (news)
	void sort_Media(int type);

  protected:
	//Utilis�e par le trie fusion alphab�tique
	void fusionAlpha(Media** vTmp, int de1, int vers1, int de2, int vers2, int count, int posInB);
	//Utilis�e par le trie fusion par date
	void fusionDate(Media** vTmp, int de1, int vers1, int de2, int vers2, int count, int posInB);
};
#endif
