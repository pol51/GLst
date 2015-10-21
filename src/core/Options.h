#ifndef _OPTIONS_H
#define _OPTIONS_H

#include <QtCore/QString>

#include "Collection.h"

//Gestion des options
class Options
{
  protected:
    //Style (thème)
    QString _style = "Fusion";
    //Nom du fichier contenant les listes
    QString _filename = "listes.txt";
    //Type de trie utilisé
    Collection::ESortType _sortType = Collection::eSTUnsorted;
    //Type de media affiché
    Media::EMediaType _mediaType = Media::eMTFilm;

  public:
    Options() { load(); }
    ~Options() { save(); }

    const QString &style() const { return _style; }
    const QString &filename() const { return _filename; }
    Collection::ESortType sortType() const { return _sortType; }
    Media::EMediaType mediaType() const { return _mediaType; }

    void setStyle(const QString &value) { _style = value; }
    void setFilename(const QString &value) { _filename = value; }
    void setSortType(const Collection::ESortType value) { _sortType = value; }
    void setMediaType(const Media::EMediaType value) { _mediaType = value; }

    void save() const;
    void load();
};
#endif
