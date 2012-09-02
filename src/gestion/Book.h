#ifndef _BOOK_H
#define _BOOK_H

#include <gestion/Media.h>

#define TYPE_BOOK 3

//Item de livre
class Book : public Media
{
  public:
    typedef enum
    {
      ePapier,
      eNumeric
    } EFormat;

  protected:
    //Nom de l'auteur
    QString _auteur;
    //Titre du livre
    QString _titre;
    //Format du livre
    EFormat _format;

  public:
    //Constructeur
    Book() : Media(TYPE_BOOK), _format(ePapier) {}

    //Destructeur
    virtual ~Book() {}

    //Accesseur en lecture sur l'auteur
    const QString &get_auteur() const { return _auteur; }

    //Accesseur en lecture sur le titre
    const QString &get_titre() const { return _titre; }

    //Accesseur en lecture sur le format
    EFormat get_format() const { return _format; }

    //Renvoie la première lettre caractéristique du média
    virtual QChar get_firstLetter() const { return _auteur[0]; }

    //Accesseur en ecriture sur l'auteur
    void set_auteur(const QString &value) { _auteur = value; }

    //Accesseur en ecriture sur le titre
    void set_titre(const QString &value) { _titre = value; }

    //Accesseur en ecriture sur le format
    void set_format(EFormat value) { _format = value; }

    //Comparaison de 2 livres par leur auteur/titre
    static int cmp_alpha(const Book* book1, const Book* book2);
};
#endif
