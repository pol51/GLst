#ifndef _FILM_H
#define _FILM_H

#include <gestion/Media.h>

//Item de film
class Film : public Media
{
  public:
    typedef enum Genre
    {
      eFilm,
      eLive,
      eSpectacle,
      eManga,
      eAnime,
      eSerie,
      eDocumentaire
    } EGenre;

    typedef enum Qualite
    {
      eDVDRip,
      eScreener,
      eDVD,
      eTVRip,
      ePub,
      eDVDScreener,
      eVCD
    } EQualite;

  protected:
    //Nom du film
    QString _name;
    //Nombre de cd
    int _nbCd = 0;
    //Nombre de dvd
    int _nbDvd = 0;
    //Qualité du film
    EQualite _quality = eDVDRip;
    //Genre du film
    EGenre _gender = eFilm;

  public:
    //Constructor
    Film() : Media(eMTFilm) {}

    //Accesseur en lecture sur le nom
    const QString name() const { return _name; }

    //Accesseur en lecture sur le nombre de cd
    int nbCd() const { return _nbCd; }

    //Accesseur en lecture sur le nombre de dvd
    int nbDvd() const { return _nbDvd; }

    //Accesseur en lecture sur la qualité
    EQualite quality() const { return _quality; }

    //Accesseur en lecture sur le genre
    EGenre gender() const { return _gender; }

    //Renvoie la première lettre caractéristique du média
    QChar firstLetter() const { return _name[0]; }

    //Accesseur en ecriture sur le nom
    void setName(const QString &value) { _name = value; }

    //Accesseur en ecriture sur le nombre de cd
    void setNbCd(const int value) { _nbCd = value; }

    //Accesseur en ecriture sur le nombre de dvd
    void setNbDvd(const int value) { _nbDvd = value; }

    //Accesseur en ecriture sur la qualité
    void setQuality(const EQualite value) { _quality = value; }

    //Accesseur en ecriture sur le genre
    void setGender(const EGenre value) { _gender = value; }

    //Generate printable string
    const QString displayable(const bool moreInfo) const;

    //Comparaison de 2 films par leur nom
    int cmpAlpha(const Media &other) const
    {
      const int Res(Media::cmpAlpha(other));
      return Res?Res:_name.compare(((Film&)other)._name);
    }
};
#endif
