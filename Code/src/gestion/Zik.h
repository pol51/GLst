#ifndef _ZIK_H
#define _ZIK_H

#include <gestion/Media.h>

#define TYPE_ZIK 2

//Item de musique
class Zik : public Media
{
  protected:
    //Nom de l'artiste
    QString _artiste;
    //Titre de l'album
    QString _titre;
    //Nombre de cd
    int _nbCd;

  public:
    //Constructeur
    Zik();

    //Destructeur
    virtual ~Zik() {}

    //Accesseur en lecture sur l'artiste
    const QString &get_artiste() const { return _artiste; }

    //Accesseur en lecture sur le titre
    const QString &get_titre() const { return _titre; }

    //Accesseur en lecture sur le nombre de cd
    int get_nbCd() const { return _nbCd; }

    //Renvoie la première lettre caractéristique du média
    virtual char get_firstLetter() const { return _artiste[0].cell(); }

    //Accesseur en ecriture sur l'artiste
    void set_artiste(const QString &value) { _artiste = value; }

    //Accesseur en ecriture sur le titre
    void set_titre(const QString &value) { _titre = value; }

    //Accesseur en ecriture sur le nombre de cd
    void set_nbCd(int value) { _nbCd = value; }

    //Test de l'artiste
    static int test_artiste(const QString &artiste);

    //Test du titre
    static int test_titre(const QString &titre);

    //Test du nombre de cd
    static int test_nbCd(const int /*nbCd*/);

    //Comparaison de 2 album par leur artiste/titre
    static int cmp_alpha(const Zik* zik1, const Zik* zik2);
};
#endif
