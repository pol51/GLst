#ifndef _MEDIA_H
#define _MEDIA_H

#include <gestion/Utils.h>

#define NUM_SIZE	9
#define NUM_SEP_POS	2
#define NUM_SEP_CAR	'-'

class QString;

//Item de base
class Media
{
  protected:
    int _type;
    //Date d'enregistrement du media
    //Numéro du contenant du media
    int _idBoite;
    //Reférénce du media
    QString _num;
    //Type du media
    QString _date;

  public:
    //Constructeur
    Media(const int type);

    //Destructeur
    virtual ~Media() {}

    //Accesseur en lecture sur la référence
    const QString &get_num() const { return _num; }

    //Accesseur en lecture sur le type
    int get_type() const { return _type; }

    //Accesseur en lecture sur la date
    const QString &get_date() const { return _date; }

    //Accesseur en lecture sur le numero de la boite
    int get_idBoite() const { return _idBoite; }

    //Renvoie la première lettre caractéristique du média
    virtual char get_firstLetter() const = 0;

    //Accesseur en ecriture sur la référence
    void set_num(const QString &value) { _num = value; }

    //Accesseur en ecriture sur la référence par un entier
    void set_num(const int nbr);

  public:
    //Accesseur en ecriture sur la date
    void set_date(const QString &value) { _date = value; }

    //Accesseur en ecriture sur le numero de boite
    void set_idBoite(const int value) { _idBoite = value; }

    //Test de la référence
    static int test_num(const QString &num);
    static int test_date(const QString &date);

    //Création de la première partie de la référence
    static const QString make_num_1(const int type);

    //Création de la seconde partie de la référence
    static const QString make_num_2(const int nbr);
    static int cmp_date(const Media* med1, const Media* med2);
};
#endif
