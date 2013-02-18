#ifndef _BOOK_H
#define _BOOK_H

#include <gestion/Media.h>

//Item de livre
class Book : public Media
{
  public:
    typedef enum BookFormat
    {
      ePaper,
      eNumeric
    } EBookFormat;

  protected:
    //Nom de l'auteur
    QString _author;
    //Titre du livre
    QString _title;
    //Format du livre
    EBookFormat _format = ePaper;

  public:
    //Constructeur
    Book() : Media(eMTBook) {}

    //Accesseur en lecture sur l'auteur
    const QString &author() const { return _author; }

    //Accesseur en lecture sur le titre
    const QString &title() const { return _title; }

    //Accesseur en lecture sur le format
    EBookFormat format() const { return _format; }

    //Renvoie la première lettre caractéristique du média
    QChar firstLetter() const { return _author[0]; }

    //Accesseur en ecriture sur l'auteur
    void setAuthor(const QString &value) { _author = value; }

    //Accesseur en ecriture sur le titre
    void setTitle(const QString &value) { _title = value; }

    //Accesseur en ecriture sur le format
    void setFormat(EBookFormat value) { _format = value; }

    //Generate printable string
    const QString displayable(const bool moreInfo) const;

    //Comparaison de 2 livres par leur auteur/titre
    int cmpAlpha(const Media &other) const
    {
      const int Res(Media::cmpAlpha(other));
      if (Res) return Res;
      const int Author(_author.compare(((Book&)other)._author));
      return Author?Author:_title.compare(((Book&)other)._title);
    }
};
#endif
