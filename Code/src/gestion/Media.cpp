
#include "Media.h"

//Constructeur
Media::Media()
{
	this->type = 0;
	this->num = "";
	this->date = "20000101";
	this->idBoite = 0;
}
//Destructeur
Media::~Media()
{
	return;
}
//Accesseur en lecture sur la référence
const string Media::get_num() const
{
	  return num;
}
//Accesseur en lecture sur le type
const int Media::get_type() const
{
	  return type;
}
//Accesseur en lecture sur la date
const string Media::get_date() const
{
	  return date;
}
//Accesseur en lecture sur le numero de la boite
const int Media::get_idBoite() const
{
	  return idBoite;
}
//Accesseur en ecriture sur la référence
void Media::set_num(string value)
{
	  num = value;
}
//Accesseur en ecriture sur la référence par un entier
void Media::set_num(int nbr)
{
	if (nbr < 0) return;
	
	this->num = make_num_1(this->type) + NUM_SEP_CAR + make_num_2(nbr);
}
//Accesseur en ecriture sur le type
void Media::set_type(int value)
{
	  type = value;
}
//Accesseur en ecriture sur la date
void Media::set_date(string value)
{
	  date = value;
}
//Accesseur en ecriture sur le numero de boite
void Media::set_idBoite(int value)
{
	  idBoite = value;
}
//Test de la référence
const int Media::test_num(string num)
{
	int size = num.size();
	
	if (size != NUM_SIZE) return 0;
	
	if (num[NUM_SEP_POS] != NUM_SEP_CAR) return 0;
	
	for (int i = 0; i < NUM_SEP_POS; i++)
	{
		int pos = _num_valid_cars1.find(num[i]);
		if ((pos < 0) or (pos >= (int)_num_valid_cars1.size())) return 0;
	}
	
	for (int i = (NUM_SEP_POS + 1); i < NUM_SIZE; i++)
	{
		int pos = _num_valid_cars2.find(num[i]);
		if ((pos < 0) or (pos >= (int)_num_valid_cars2.size())) return 0;
	}
	
	return 1;
}
const int Media::test_date(string date)
{
	if (date.size() != 8) return 0;
	
	return Utils::test_numeric(date);
}
//Création de la première partie de la référence
string Media::make_num_1(int type)
{
	//création de la chaine
	ostringstream tmp;
	tmp << type;
	string num_1 = tmp.str();
	
	//complément à la taile désirée
	while ((num_1.size()) < NUM_SEP_POS)
		num_1.insert(num_1.begin(), '0');
	
	return num_1;
}
//Création de la seconde partie de la référence
string Media::make_num_2(int nbr)
{
	//calcul de la taille de la seconde partie
	int num_2_size = NUM_SIZE - (NUM_SEP_POS + 1);
	
	//création de la chaine
	ostringstream tmp;
	tmp << nbr;
	string num_2 = tmp.str();
	
	//complément à la taile désirée
	while ((int)(num_2.size()) < num_2_size)
		num_2.insert(num_2.begin(), '0');
	
	return num_2;
}
const int Media::cmp_date(const Media* med1, const Media* med2)
{
	if (med1->get_date() > med2->get_date())
		return -1;
	if (med1->get_date() == med2->get_date())
		if (med1->get_num() > med2->get_num())
			return -1;
	return 1;
}
