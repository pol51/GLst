#ifndef _BOOK_H
#define _BOOK_H

#include <gestion/Media.h>

#define TYPE_BOOK 3

typedef enum
{
  FRT_PAPIER,
  FRT_NUMERIC
} FRT;

//Item de livre
class Book : public Media
{
  protected:
    //Nom de l'auteur
    QString _auteur;
    //Titre du livre
    QString _titre;
    //Format du livre
    int _format;

  public:
    //Constructeur
    Book();

    //Destructeur
    virtual ~Book() {}

    //Accesseur en lecture sur l'auteur
    const QString &get_auteur() const { return _auteur; }

    //Accesseur en lecture sur le titre
    const QString &get_titre() const { return _titre; }

    //Accesseur en lecture sur le format
    int get_format() const { return _format; }

    //Renvoie la première lettre caractéristique du média
    virtual char get_firstLetter() const { return _auteur[0].cell(); }

    //Accesseur en ecriture sur l'auteur
    void set_auteur(const QString &value) { _auteur = value; }

    //Accesseur en ecriture sur le titre
    void set_titre(const QString &value) { _titre = value; }

    //Accesseur en ecriture sur le format
    void set_format(int value) { _format = value; }

    //Comparaison de 2 livres par leur auteur/titre
    static int cmp_alpha(const Book* book1, const Book* book2);
};
#endif
