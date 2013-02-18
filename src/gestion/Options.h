#ifndef _OPTIONS_H
#define _OPTIONS_H

#include <QString>

#include <gestion/Collection.h>

#define NB_OPTIONS 3

//Gestion des options
class Options
{
  protected:
    //Nom du fichier des options
    QString _filename;
    //Style (thème)
    QString _style = "Fusion";
    //Nom du fichier contenant les listes
    QString _liste = "listes.txt";
    //Type de trie utilisé
    Collection::ESortType _sortType = Collection::eSTUnsorted;

  public:
    //Constructeur
    Options(const QString &filename) : _filename(filename) {}

    //Accesseur en lecture sur le nom du fichier
    const QString &filename() const { return _filename; }

    //Accesseur en lecture sur le style
    const QString &style() const { return _style; }

    //Accesseur en lecture sur le nom du fichier des listes
    const QString &liste() const { return _liste; }

    //Accesseur en lecture sur le type de trie utilisé
    Collection::ESortType sortType() const { return _sortType; }

    //Accesseur en ecriture sur le nom du fichier
    void setFilename(const QString &value) { _filename = value; }

    //Accesseur en ecriture sur le style
    void setStyle(const QString &value) { _style = value; }

    //Accesseur en ecriture sur le nom du fichier des listes
    void setListe(const QString &value) { _liste = value; }

    //Accesseur en écriture sur le type de trie utilisé
    void setSortType(const Collection::ESortType value) { _sortType = value; }

    //Ecrit le fichier d'options
    int save() const;

    //Lit le fichier d'options
    int load();
};
#endif
