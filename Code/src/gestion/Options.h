#ifndef _OPTIONS_H
#define _OPTIONS_H


#include <QString>

#define NB_OPTIONS 3

//Gestion des options
class Options
{
  protected:
  //Nom du fichier des options
  QString filename;
  //Style (thème)
  QString style;
  //Nom du fichier contenant les listes
  QString liste;
  //Type de trie utilisé
  int sortType;

  public:
  //Constructeur
  Options(const QString &filename);
  //Destructeur
  virtual ~Options() {}
  //Accesseur en lecture sur le nom du fichier
  const QString &get_filename() const { return filename; }
  //Accesseur en lecture sur le style
  const QString &get_style() const { return style; }
  //Accesseur en lecture sur le nom du fichier des listes
  const QString &get_liste() const { return liste; }
  //Accesseur en lecture sur le type de trie utilisé
  int get_sortType() const { return sortType; }
  //Accesseur en ecriture sur le nom du fichier
  void set_filename(const QString &value) { filename = value; }
  //Accesseur en ecriture sur le style
  void set_style(const QString &value) { style = value; }
  //Accesseur en ecriture sur le nom du fichier des listes
  void set_liste(const QString &value) { liste = value; }
  //Accesseur en écriture sur le type de trie utilisé
  void set_sortType(int value) { sortType = value; }
  //Ecrit le fichier d'options
  int save();
  //Lit le fichier d'options
  int load();
};
#endif
