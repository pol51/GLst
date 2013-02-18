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
  public:
    typedef enum MediaType
    {
      eMTUnknown = 0,
      eMTFilm,
      eMTZik,
      eMTBook,
      eMTMax
    } EMediaType;

  protected:
    //Type du media
    EMediaType _type = eMTUnknown;
    //Numéro du contenant du media
    int _idBoite = 0;
    //Reférénce du media
    QString _num;
    //Date d'enregistrement du media
    QString _date = "20000101";

  public:
    //Constructor
    Media(const EMediaType type) : _type(type) {}

    //Destructor
    virtual ~Media() {}

    //Accesseur en lecture sur la référence
    const QString &num() const { return _num; }

    //Accesseur en lecture sur le type
    EMediaType type() const { return _type; }

    //Accesseur en lecture sur la date
    const QString &date() const { return _date; }

    //Accesseur en lecture sur le numero de la boite
    int idBoite() const { return _idBoite; }

    //Renvoie la première lettre caractéristique du média
    virtual QChar firstLetter() const = 0;

    //Accesseur en ecriture sur la référence
    void setNum(const QString &value) { _num = value; }

    //Accesseur en ecriture sur la référence par un entier
    void setNum(const int nbr);

    //Accesseur en ecriture sur la date
    void setDate(const QString &value) { _date = value.trimmed(); }

    //Accesseur en ecriture sur le numero de boite
    void setIdBoite(const int value) { _idBoite = value; }

    //Generate printable string
    virtual const QString displayable(const bool moreInfo) const = 0;

    //Test de la référence
    static bool testNum(const QString &num);
    static bool testDate(const QString &date);

    //Création de la première partie de la référence
    static const QString makeNum1(const int type);

    //Création de la seconde partie de la référence
    static const QString makeNum2(const int nbr);

    //Compare alpha
    virtual int cmpAlpha(const Media &other) const
    {
      return _type > other._type?1:(_type < other._type?-1:0);
    }

    //Compare dates
    int cmpDate(const Media &other) const
    {
      const int Date(-_date.compare(other._date));
      return Date?Date:-_num.compare(other._num);
    }
};
#endif
