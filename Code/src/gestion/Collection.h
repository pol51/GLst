#ifndef _COLLECTION_H
#define _COLLECTION_H

#include <QString>
#include <QVector>

class Media;

#include <gestion/Media.h>
#include <gestion/Zik.h>
#include <gestion/Book.h>
#include <gestion/Film.h>

#define SORT_ALPHA	1
#define SORT_DATE	  2

//Gestionnaire de la collection de medias
class Collection
{
  protected:
    //Etat du trie de la collection
    int _sort;
    //Conteneu des medias
    QVector<Media*> _vMedia;

  public:
    //Constructeur
    Collection();

    //Destructeur
    virtual ~Collection() { clear(); }

    //Permet de savoir si la collection est actuellement tri�e de cette mani�re.
    bool isSorted(int type) { return (type == _sort); }

    //D�finie la collection comme "non-tri�e"
    void setUnsorted() { _sort = -1; }

    //Vide la collection
    void clear();

    //Ajout d'un album dans la collection
    Zik* add_Zik();

    //Ajout d'un film dans la collection
    Film* add_Film();

    //Ajout d'un livre dans la collection
    Book* add_Book();

    //Suppresision d'un media de la collection
    int del_Media(const unsigned int id);

    //Recup�re un media dans la collection
    Media* get_Media(const unsigned int id);

    //Recup�re un media dans la collection (const)
    const Media* get_Media(const unsigned int id) const;

    //Recherche l'id d'un media par sa r�f�rence
    int find_Media(const QString &num) const;

    //Renvoie le nombre de media dans la collection
    int nb_Media() const;

    //Renvoie le nombre de media d'un type donn� dans la collection
    int nb_Media(const int type) const;

    //Renvoie le prochain nombre attribuable � un media de type donn�
    int nextref_Media(const int type) const;

    //Trie la collection (par fusion)
    //SORT_ALPHA  -> trie alphab�tique
    //SORT_DATE -> trie par date (news)
    void sort_Media(const int type);

  protected:
    //Utilis�e par le trie fusion alphab�tique
    void fusionAlpha(Media** vTmp, int de1, int vers1, int de2, int vers2, int count, int posInB);

    //Utilis�e par le trie fusion par date
    void fusionDate(Media** vTmp, int de1, int vers1, int de2, int vers2, int count, int posInB);
};
#endif
