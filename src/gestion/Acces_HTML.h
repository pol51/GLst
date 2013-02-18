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
    Acces_HTML(Collection &collection) : Acces::Acces(collection) {}

    //Destructeur
    virtual ~Acces_HTML() {}

    //Chargement du fichier
    virtual bool load(const QString &filename) { Q_UNUSED(filename); return false; }

    //Sauvegarde du fichier
    virtual bool save(const QString &filename) const;

  protected:
    //Formatage d'une ligne
    static const QString code(const Media &media);
};
#endif
