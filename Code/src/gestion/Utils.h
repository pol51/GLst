#ifndef _UTILS_H
#define _UTILS_H


#include <string>
using namespace std;

#include <cstring>
#include <sstream>
#include <algorithm>

const string _valid_cars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$%*:;.,_+-=§²|\\/'?!%èéêà@îôûâ()[]{}=#& çÄÉÀ°¤óëäöïü¡";
const string _valid_numeric = "0123456789";

//Classe d'utilitaires divers
class Utils
{
  public:
	//Test sur une chaine alphanumérique
	static const int test_alpha(string /*alpha*/);
	//Test sur une chaine numérique
	static const int test_numeric(string alpha);
	//Mise en majuscule
	static string upcase(string str);
	//Renvoie le caractère en majuscule
	static const char upchar(char car);
	//Transforme les espaces en underscores
	static const string sp2und(string ligne);
	//Transforme les underscores en espaces
	static const string und2sp(string ligne);
	//Comparaison lexicographique de deux chaines
	static const int str_compare(string str1, string str2);
};
#endif
