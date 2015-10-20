#ifndef _ZIK_H
#define _ZIK_H

#include "Media.h"

//Item de musique
class Zik : public Media
{
  protected:
    //Nom de l'artiste
    QString _artist;
    //Titre de l'album
    QString _title;
    //Nombre de cd
    int _nbCd = 0;

  public:
    //Constructeur
    Zik() : Media(eMTZik) {}

    //Accesseur en lecture sur l'artiste
    const QString &artist() const { return _artist; }

    //Accesseur en lecture sur le titre
    const QString &title() const { return _title; }

    //Accesseur en lecture sur le nombre de cd
    int nbCd() const { return _nbCd; }

    //Renvoie la première lettre caractéristique du média
    QChar firstLetter() const { return _artist[0]; }

    //Accesseur en ecriture sur l'artiste
    void setArtist(const QString &value) { _artist = value; }

    //Accesseur en ecriture sur le titre
    void setTitle(const QString &value) { _title = value; }

    //Accesseur en ecriture sur le nombre de cd
    void setNbCd(int value) { _nbCd = value; }

    //Generate printable string
    const QString displayable(const bool moreInfo) const;

    //Comparaison de 2 album par leur artiste/titre
    int cmpAlpha(const Media &other) const
    {
      const int Res(Media::cmpAlpha(other));
      if (Res) return Res;
      const int Artist(_artist.compare(((Zik&)other)._artist));
      return Artist?Artist:_title.compare(((Zik&)other)._title);
    }
};
#endif
