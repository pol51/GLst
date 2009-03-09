
#include "Collection.h"
#include "Media.h"

//Constructeur
Collection::Collection()
{
	this->sort = -1;
	return;
}
//Destructeur
Collection::~Collection()
{
	this->clear();
}
//Permet de savoir si la collection est actuellement triée de cette manière.
bool Collection::isSorted(int type)
{
	if (type == this->sort)
		return true;
	return false;
}
void Collection::setUnsorted()
{
	this->sort = -1;
}
void Collection::clear()
{
	vector <Media*>::iterator i;
	
	for (i = vMedia.begin(); i != vMedia.end(); i++)
		delete *i;
	
	vMedia.clear();
	
	this->sort = -1;
}
//Ajout d'un album dans la collection
Media* Collection::add_Zik()
{
	this->sort = -1;
	vMedia.push_back(new Zik());
	return vMedia.back();
}
//Ajout d'un film dans la collection
Media* Collection::add_Film()
{
	this->sort = -1;
	vMedia.push_back(new Film());
	return vMedia.back();
}
//Ajout d'un livre dans la collection
Media* Collection::add_Book()
{
	this->sort = -1;
	vMedia.push_back(new Book());
	return vMedia.back();
}
//Suppresision d'unmedia de la collection
int Collection::del_Media(int id)
{
	if ((id < 0) or (id > (int)vMedia.size()))
		return 0;
	
	//suppression de l'objet
	delete vMedia[id];
	
	//tassement du vecteur
	for (int i = id; i < ((int)vMedia.size() - 1); i++)
		vMedia[i] = vMedia[i + 1];
	
	//suppression du dernier élément
	vMedia.pop_back();
	
	return 1;
}
//Recupère un media dans la collection
Media* Collection::get_Media(int id)
{
	if ((id < 0) or (id > (int)vMedia.size()))
		return NULL;
	
	return vMedia[id];
}
//Recherche l'id d'un media par sa référence
const int Collection::find_Media(string num)
{
	for (int i = 0; i < (int)vMedia.size(); i++)
		if (vMedia[i]->get_num() == num) return i;
	
	return -1;
}
//Renvoie le nombre de media dans la collection
const int Collection::nb_Media()
{
	return vMedia.size();
}
//Renvoie le nombre de media d'un type donné dans la collection
const int Collection::nb_Media(int type)
{
	int cp = 0; // compteur
	
	for (unsigned int i = 0; i < vMedia.size(); i++)
		if (get_Media(i)->get_type() == type)
			cp++;
	
	return cp;
}
//Renvoie le prochain nombre attribuable à un media de type donné
const int Collection::nextref_Media(int type)
{
	if (type < 1) return -1;
	
	//génération 1ère partie
	string num_1 = Media::make_num_1(type);
	
	//nombre maximal
	int max_nbr = (int)pow(10. ,(double)(NUM_SIZE - NUM_SEP_POS));
	
	int nbr = 0;
	
	string tmp_num;	//référence temporaire
	
	while (nbr < max_nbr)
	{
		//génération de la seconde partie
		string num_2 = Media::make_num_2(nbr);
		//concaténation des 2 parties
		tmp_num = num_1 + NUM_SEP_CAR + num_2;
		//recherche de l'existance de la référence
		if (find_Media(tmp_num) >= 0) nbr++;
		else return nbr;
	}
	
	return -1;
}
//Trie la collection (par fusion)
//SORT_ALPHA  -> trie alphabétique
//SORT_DATE -> trie par date (news)
void Collection::sort_Media(int type)
{
	//déja trié?
	if (this->sort == type)
		return;
	
	//type de trie inconnu?
	if (type != SORT_ALPHA && type != SORT_DATE)
		return;
	
	unsigned int size = vMedia.size();
	
	Media* vTmp[size];
	
	unsigned int sortLength = 1, de1, de2, de3;
	
	while (sortLength < size)
	{
		de1 = 0;
		while(de1 < size)
		{
			de2 = de1 + sortLength;
			de3 = de2 + sortLength;
			if (de2 > size) de2 = size;
			if (de3 > size) de3 = size;
			switch (type)
			{
				case SORT_ALPHA:
					fusionAlpha(vTmp, de1, de2 - 1, de2, de3 - 1, de3 - de1, de1);
					break;
				case SORT_DATE:
					fusionDate(vTmp, de1, de2 - 1, de2, de3 - 1, de3 - de1, de1);
					break;
			}
			de1 = de3;
		}
		
		for (unsigned int i = 0; i <  size; i++) vMedia[i] = vTmp[i];
		sortLength *= 2;
	}
	
	this->sort = type;
}
//Utilisée par le trie fusion alphabétique
void Collection::fusionAlpha(Media** vTmp, int de1, int vers1, int de2, int vers2, int count, int posInB)
{
	for (int i = 0; i < count; i++)
	{
		if (de2 > vers2)
			vTmp[posInB++] = vMedia[de1++];
		else if (de1 > vers1)
			vTmp[posInB++] = vMedia[de2++];
		else if (vMedia[de1]->get_type() == vMedia[de2]->get_type())
			{
				switch(vMedia[de1]->get_type())
				{
					case TYPE_ZIK:
						if (Zik::cmp_alpha(((Zik*)vMedia[de1]), ((Zik*)vMedia[de2])) < 1)
							vTmp[posInB++] = vMedia[de1++];
						else
							vTmp[posInB++] = vMedia[de2++];
						break;
					case TYPE_FILM:
						if (Film::cmp_alpha(((Film*)vMedia[de1]), ((Film*)vMedia[de2])) < 1)
							vTmp[posInB++] = vMedia[de1++];
						else
							vTmp[posInB++] = vMedia[de2++];
						break;
					case TYPE_BOOK:
						if (Book::cmp_alpha(((Book*)vMedia[de1]), ((Book*)vMedia[de2])) < 1)
							vTmp[posInB++] = vMedia[de1++];
						else
							vTmp[posInB++] = vMedia[de2++];
						break;
				}
			}
		else if (vMedia[de1]->get_type() < vMedia[de2]->get_type())
			vTmp[posInB++] = vMedia[de1++];
		else
			vTmp[posInB++] = vMedia[de2++];
	}
	return;
}
//Utilisée par le trie fusion par date
void Collection::fusionDate(Media** vTmp, int de1, int vers1, int de2, int vers2, int count, int posInB)
{
	for (int i = 0; i < count; i++)
	{
		if (de2 > vers2)
			vTmp[posInB++] = vMedia[de1++];
		else if (de1 > vers1)
			vTmp[posInB++] = vMedia[de2++];
		else if (Media::cmp_date(vMedia[de1], vMedia[de2]) < 1)
			vTmp[posInB++] = vMedia[de1++];
		else
			vTmp[posInB++] = vMedia[de2++];
	}
	return;
}
