#include "Collection.h"

#include <gestion/Media.h>
#include <gestion/Book.h>
#include <gestion/Film.h>
#include <gestion/Zik.h>

#include <QtCore/QtCore>

//Constructeur
Collection::Collection() :
  _sort(-1)
{
}

//Vide la collection
void Collection::clear()
{
  for (int i = _vMedia.count(); --i >= 0; )
    delete _vMedia.at(i);

  _vMedia.clear();

  _sort = -1;
}

//Ajout d'un album dans la collection
Zik* Collection::add_Zik()
{
  _sort = -1;
  _vMedia.append(new Zik());
  return (Zik*)_vMedia.last();
}

//Ajout d'un film dans la collection
Film* Collection::add_Film()
{
  _sort = -1;
  _vMedia.append(new Film());
  return (Film*)_vMedia.last();
}

//Ajout d'un livre dans la collection
Book* Collection::add_Book()
{
  _sort = -1;
  _vMedia.append(new Book());
  return (Book*)_vMedia.last();
}

//Suppresision d'unmedia de la collection
int Collection::del_Media(const unsigned int id)
{
  const unsigned int newCount =  _vMedia.count() - 1;

  if (id > newCount)
    return 0;

  //suppression de l'objet
  delete _vMedia[id];

  //tassement du vecteur
  for (unsigned int i = id; i < newCount; i++)
    _vMedia[i] = _vMedia[i + 1];

  //suppression du dernier élément
  _vMedia.pop_back();

  return 1;
}

//Recupère un media dans la collection
Media* Collection::get_Media(const unsigned int id)
{
  if (id < (unsigned int)_vMedia.size())
    return _vMedia[id];

  return NULL;
}

//Recupère un media dans la collection (const)
const Media* Collection::get_Media(const unsigned int id) const
{
  if (id < (unsigned int)_vMedia.size())
    return _vMedia[id];

  return NULL;
}

//Recherche l'id d'un media par sa référence
int Collection::find_Media(const QString &num) const
{
  for (int i = _vMedia.size(); --i >= 0; )
    if (_vMedia[i]->get_num() == num) return i;

  return -1;
}

//Renvoie le nombre de media dans la collection
int Collection::nb_Media() const
{
  return _vMedia.count();
}

//Renvoie le nombre de media d'un type donné dans la collection
int Collection::nb_Media(const int type) const
{
  int cp = 0; // compteur

  for (int i = _vMedia.size(); --i >= 0; )
    if (_vMedia[i]->get_type() == type)
      cp++;

  return cp;
}

//Renvoie le prochain nombre attribuable à un media de type donné
int Collection::nextref_Media(const int type) const
{
  if (type < 1) return -1;

  //génération 1ère partie
  QString num_1 = Media::make_num_1(type);

  //nombre maximal
  const int max_nbr = (int)pow(10. ,(double)(NUM_SIZE - NUM_SEP_POS));

  int nbr = 0;

  QString tmp_num;	//référence temporaire

  while (nbr < max_nbr)
  {
    //génération de la seconde partie
    QString num_2 = Media::make_num_2(nbr);
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
void Collection::sort_Media(const int type)
{
  //déja trié?
  if (_sort == type)
    return;

  //type de tri inconnu?
  if (type != SORT_ALPHA && type != SORT_DATE)
    return;

  const unsigned int size = _vMedia.size();

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

    for (unsigned int i = 0; i <  size; i++) _vMedia[i] = vTmp[i];
    sortLength <<= 1;
  }

  _sort = type;
}

//Utilisée par le trie fusion alphabétique
void Collection::fusionAlpha(Media** vTmp, int de1, int vers1, int de2, int vers2, int count, int posInB)
{
  for (int i = 0; i < count; i++)
  {
    if (de2 > vers2)
      vTmp[posInB++] = _vMedia[de1++];
    else if (de1 > vers1)
      vTmp[posInB++] = _vMedia[de2++];
    else if (_vMedia[de1]->get_type() == _vMedia[de2]->get_type())
      {
        switch(_vMedia[de1]->get_type())
        {
          case TYPE_ZIK:
            if (Zik::cmp_alpha(((Zik*)_vMedia[de1]), ((Zik*)_vMedia[de2])) < 1)
              vTmp[posInB++] = _vMedia[de1++];
            else
              vTmp[posInB++] = _vMedia[de2++];
            break;
          case TYPE_FILM:
            if (Film::cmp_alpha(((Film*)_vMedia[de1]), ((Film*)_vMedia[de2])) < 1)
              vTmp[posInB++] = _vMedia[de1++];
            else
              vTmp[posInB++] = _vMedia[de2++];
            break;
          case TYPE_BOOK:
            if (Book::cmp_alpha(((Book*)_vMedia[de1]), ((Book*)_vMedia[de2])) < 1)
              vTmp[posInB++] = _vMedia[de1++];
            else
              vTmp[posInB++] = _vMedia[de2++];
            break;
        }
      }
    else if (_vMedia[de1]->get_type() < _vMedia[de2]->get_type())
      vTmp[posInB++] = _vMedia[de1++];
    else
      vTmp[posInB++] = _vMedia[de2++];
  }
}

//Utilisée par le trie fusion par date
void Collection::fusionDate(Media** vTmp, int de1, int vers1, int de2, int vers2, int count, int posInB)
{
  for (int i = 0; i < count; i++)
  {
    if (de2 > vers2)
      vTmp[posInB++] = _vMedia[de1++];
    else if (de1 > vers1)
      vTmp[posInB++] = _vMedia[de2++];
    else if (Media::cmp_date(_vMedia[de1], _vMedia[de2]) < 1)
      vTmp[posInB++] = _vMedia[de1++];
    else
      vTmp[posInB++] = _vMedia[de2++];
  }
  return;
}
