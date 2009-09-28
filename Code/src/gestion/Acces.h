#ifndef _ACCES_H
#define _ACCES_H

#include <QString>

class Collection;
class Media;

//Acces aux donn�es externes
class Acces
{
  protected:
    //Collection
    Collection *_collection;

  public:
    //Constructeur
    Acces(Collection *collection);

    //Destructeur
    virtual ~Acces() {}

    //Chargement du fichier
    virtual int load(const QString &filename);

    //Sauvegarde du fichier
    virtual int save(const QString &filename) const;

  protected:
    //Formatage d'une ligne
    static QString code(const Media* media);

    //D�codage d'une ligne
    static Media* decode(const QString &ligne);
};
#endif
