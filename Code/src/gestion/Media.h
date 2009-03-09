#ifndef _MEDIA_H
#define _MEDIA_H


#include <string>
using namespace std;

#include "Utils.h"

#define NUM_SIZE	9
#define NUM_SEP_POS	2
#define NUM_SEP_CAR	'-'

const string _num_valid_cars1 = "0123456789";
const string _num_valid_cars2 = "0123456789";

//Item de base
class Media
{
  protected:
	//Reférénce du media
	string num;
	//Type du media
	int type;
	//Date d'enregistrement du media
	string date;
	//Numéro du contenant du media
	int idBoite;

  public:
	//Constructeur
	Media();
	//Destructeur
	virtual ~Media();
	//Accesseur en lecture sur la référence
	const string get_num() const;
	//Accesseur en lecture sur le type
	const int get_type() const;
	//Accesseur en lecture sur la date
	const string get_date() const;
	//Accesseur en lecture sur le numero de la boite
	const int get_idBoite() const;
	//Renvoie la première lettre caractéristique du média
	virtual char get_firstLetter() = 0;
	//Accesseur en ecriture sur la référence
	void set_num(string value);
	//Accesseur en ecriture sur la référence par un entier
	void set_num(int nbr);

  protected:
	//Accesseur en ecriture sur le type
	void set_type(int value);

  public:
	//Accesseur en ecriture sur la date
	void set_date(string value);
	//Accesseur en ecriture sur le numero de boite
	void set_idBoite(int value);
	//Test de la référence
	static const int test_num(string num);
	static const int test_date(string date);
	//Création de la première partie de la référence
	static string make_num_1(int type);
	//Création de la seconde partie de la référence
	static string make_num_2(int nbr);
	static const int cmp_date(const Media* med1, const Media* med2);
};
#endif
