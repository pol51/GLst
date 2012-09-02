#ifndef _FILM_H
#define _FILM_H

#include <gestion/Media.h>

#define TYPE_FILM 1

//Item de film
class Film : public Media
{
  public:
    typedef enum
    {
      eFilm,
      eLive,
      eSpectacle,
      eManga,
      eAnime,
      eSerie,
      eDocumentaire
    } EGenre;

    typedef enum
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
    QString _nom;
    //Nombre de cd
    int _nbCd;
    //Nombre de dvd
    int _nbDvd;
    //Qualité du film
    EQualite _qualite;
    //Genre du film
    EGenre _genre;

  public:
    //Constructeur
    Film() : Media(TYPE_FILM),
      _nbCd(0), _nbDvd(0), _qualite(eDVDRip), _genre(eFilm) {}

    //Destructeur
    virtual ~Film() {}

    //Accesseur en lecture sur le nom
    const QString get_nom() const { return _nom; }

    //Accesseur en lecture sur le nombre de cd
    int get_nbCd() const { return _nbCd; }

    //Accesseur en lecture sur le nombre de dvd
    int get_nbDvd() const { return _nbDvd; }

    //Accesseur en lecture sur la qualité
    EQualite get_qualite() const { return _qualite; }

    //Accesseur en lecture sur le genre
    EGenre get_genre() const { return _genre; }

    //Renvoie la première lettre caractéristique du média
    virtual QChar get_firstLetter() const { return _nom[0]; }

    //Accesseur en ecriture sur le nom
    void set_nom(const QString &value) { _nom = value; }

    //Accesseur en ecriture sur le nombre de cd
    void set_nbCd(const int value) { _nbCd = value; }

    //Accesseur en ecriture sur le nombre de dvd
    void set_nbDvd(const int value) { _nbDvd = value; }

    //Accesseur en ecriture sur la qualité
    void set_qualite(const EQualite value) { _qualite = value; }

    //Accesseur en ecriture sur le genre
    void set_genre(const EGenre value) { _genre = value; }

    //Comparaison de 2 films par leur nom
    static int cmp_alpha(const Film* film1, const Film* film2);
};
#endif
