#ifndef _ACCES_H
#define _ACCES_H

class QString;

class Collection;
class Media;

//Acces aux données externes
class Acces
{
  protected:
    //Collection
    Collection *_collection;

  public:
    //Constructeur
    Acces(Collection *collection) : _collection(collection) {}

    //Destructeur
    virtual ~Acces() {}

    //Chargement du fichier
    virtual int load(const QString &filename);

    //Sauvegarde du fichier
    virtual int save(const QString &filename) const;

  protected:
    //Formatage d'une ligne
    static const QString code(const Media* media);

    //Décodage d'une ligne
    static Media* decode(const QString &ligne);
};
#endif
