#ifndef _COLLECTION_H
#define _COLLECTION_H

#include <QtCore/QVector>

#include <gestion/Media.h>

class QString;

class Zik;
class Film;
class Book;

//Gestionnaire de la collection de medias
class Collection : public QVector<Media*>
{
  public:
    typedef enum SortType {
      eSTUnsorted,
      eSTAlpha,
      eSTDate
    } ESortType;

  protected:
    //Etat du trie de la collection
    ESortType _sort = eSTUnsorted;

  public:
    //Constructor
    Collection() : QVector<Media*>() {}

    //Destructor
    ~Collection() {}

    //Permet de savoir si la collection est actuellement triée de cette manière.
    bool isSorted(const ESortType type) { return type == _sort; }

    //Définie la collection comme "non-triée"
    void setUnsorted() { _sort = eSTUnsorted; }

    //Vide la collection
    void clear();

    //Ajout d'un album dans la collection
    Zik *addZik();

    //Ajout d'un film dans la collection
    Film *addFilm();

    //Ajout d'un livre dans la collection
    Book *addBook();

    //Recherche l'id d'un media par sa référence
    int find(const QString &num) const;

    //Renvoie le nombre de media dans la collection
    virtual int size() const { return QVector<Media*>::size(); }

    //Renvoie le nombre de media d'un type donné dans la collection
    virtual int size(const int type) const;

    //Renvoie le prochain nombre attribuable à un media de type donné
    int nextref(const int type) const;

    //Trie la collection (par fusion)
    void sort(const ESortType type);
};
#endif
