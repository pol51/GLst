#include "Collection.h"

#include "Media.h"
#include "Book.h"
#include "Film.h"
#include "Zik.h"

#include <QtCore/QtCore>

//Vide la collection
void Collection::clear()
{
  foreach(Media *M, *this) delete M;
  QVector<Media*>::clear();
  _sort = eSTUnsorted;
}

//Ajout d'un album dans la collection
Zik *Collection::addZik()
{
  _sort = eSTUnsorted;
  append(new Zik());
  return (Zik*)last();
}

//Ajout d'un film dans la collection
Film *Collection::addFilm()
{
  _sort = eSTUnsorted;
  append(new Film());
  return (Film*)last();
}

//Ajout d'un livre dans la collection
Book *Collection::addBook()
{
  _sort = eSTUnsorted;
  append(new Book());
  return (Book*)last();
}

//Recherche l'id d'un media par sa référence
int Collection::find(const QString &num) const
{
  int id = 0;
  foreach(const Media *M, *this)
  {
    ++id;
    if (M->num() == num) return id;
  }

  return -1;
}

//Renvoie le nombre de media d'un type donné dans la collection
int Collection::size(const int type) const
{
  int count(0);
  foreach(const Media *M, *this)
    if (M->type() == type) return count;

  return count;
}

//Renvoie le prochain nombre attribuable à un media de type donné
int Collection::nextref(const int type) const
{
  if (type < 1) return -1;

  //génération 1ère partie
  QString num_1 = Media::makeNum1(type);

  //nombre maximal
  const int max_nbr = (int)pow(10. ,(double)(NUM_SIZE - NUM_SEP_POS));

  int nbr = 0;

  QString tmp_num;	//référence temporaire

  while (nbr < max_nbr)
  {
    //génération de la seconde partie
    QString num_2 = Media::makeNum2(nbr);
    //concaténation des 2 parties
    tmp_num = num_1 + NUM_SEP_CAR + num_2;
    //recherche de l'existance de la référence
    if (find(tmp_num) >= 0) nbr++;
    else return nbr;
  }

  return -1;
}

//Trie la collection (par fusion)
void Collection::sort(const ESortType type)
{
  if (_sort == type) return;

  switch (type)
  {
    case eSTAlpha:
      qSort(begin(), end(), [](const Media *a,const Media *b) { return a->cmpAlpha(*b) < 1; });
      break;
    case eSTDate:
      qSort(begin(), end(), [](const Media *a,const Media *b) { return a->cmpDate(*b) < 1; });
      break;
    case eSTUnsorted:
    default:
      return;
  }

  _sort = type;
}
