#ifndef _OPTIONS_H
#define _OPTIONS_H


#include <string>
using namespace std;

#define NB_OPTIONS 3

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

//Gestion des options
class Options
{
  protected:
	//Nom du fichier des options
	string filename;
	//Style (thème)
	string style;
	//Nom du fichier contenant les listes
	string liste;
	//Type de trie utilisé
	int sortType;

  public:
	//Constructeur
	Options(string filename);
	//Destructeur
	virtual ~Options();
	//Accesseur en lecture sur le nom du fichier
	const string get_filename() const;
	//Accesseur en lecture sur le style
	const string get_style() const;
	//Accesseur en lecture sur le nom du fichier des listes
	const string get_liste() const;
	//Accesseur en lecture sur le type de trie utilisé
	const int get_sortType() const;
	//Accesseur en ecriture sur le nom du fichier
	void set_filename(string value);
	//Accesseur en ecriture sur le style
	void set_style(string value);
	//Accesseur en ecriture sur le nom du fichier des listes
	void set_liste(string value);
	//Accesseur en écriture sur le type de trie utilisé
	void set_sortType(int value);
	//Ecrit le fichier d'options
	int save();
	//Lit le fichier d'options
	int load();
};
#endif
