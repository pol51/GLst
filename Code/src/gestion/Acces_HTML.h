#ifndef _ACCES_HTML_H
#define _ACCES_HTML_H

#include <QString>

#include <gestion/Acces.h>

class Collection;
class Media;

//Export au format HTML
class Acces_HTML : public Acces
{
  public:
    //Constructeur
    Acces_HTML(Collection *collection) : Acces::Acces(collection) {}

    //Destructeur
    virtual ~Acces_HTML() {}

    //Chargement du fichier
    virtual int load(const QString &/*filename*/) { return 0; }

    //Sauvegarde du fichier
    virtual int save(const QString &filename) const;

  protected:
    //Formatage d'une ligne
    static const QString code(const Media* media);
};
#endif
