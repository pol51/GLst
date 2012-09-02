#ifndef _OPTIONS_H
#define _OPTIONS_H

#include <QString>

#define NB_OPTIONS 3

//Gestion des options
class Options
{
  protected:
    //Nom du fichier des options
    QString _filename;
    //Style (thème)
    QString _style;
    //Nom du fichier contenant les listes
    QString _liste;
    //Type de trie utilisé
    int _sortType;

  public:
    //Constructeur
    Options(const QString &filename);

    //Destructeur
    ~Options() {}

    //Accesseur en lecture sur le nom du fichier
    const QString &get_filename() const { return _filename; }

    //Accesseur en lecture sur le style
    const QString &get_style() const { return _style; }

    //Accesseur en lecture sur le nom du fichier des listes
    const QString &get_liste() const { return _liste; }

    //Accesseur en lecture sur le type de trie utilisé
    int get_sortType() const { return _sortType; }

    //Accesseur en ecriture sur le nom du fichier
    void set_filename(const QString &value) { _filename = value; }

    //Accesseur en ecriture sur le style
    void set_style(const QString &value) { _style = value; }

    //Accesseur en ecriture sur le nom du fichier des listes
    void set_liste(const QString &value) { _liste = value; }

    //Accesseur en écriture sur le type de trie utilisé
    void set_sortType(const int value) { _sortType = value; }

    //Ecrit le fichier d'options
    int save() const;

    //Lit le fichier d'options
    int load();
};
#endif
