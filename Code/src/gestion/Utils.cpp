
#include "Utils.h"

//Test sur une chaine alphanumérique
const int Utils::test_alpha(string /*alpha*/)
{
	/*for (unsigned int i = 0; i < alpha.size(); i++)
	{
		int place = _valid_cars.find(alpha[i]);
			if ((place < 0) or (place > int(_valid_cars.size()))) return 0;
	}*/
	
	return 1;
}
//Test sur une chaine numérique
const int Utils::test_numeric(string alpha)
{
	for (unsigned int i = 0; i < alpha.size(); i++)
	{
		int place = _valid_numeric.find(alpha[i]);
			if ((place < 0) or (place > int(_valid_cars.size()))) return 0;
	}
	
	return 1;
}
//Mise en majuscule
string Utils::upcase(string str)
{
	string tmp = str;
	
	transform(
		tmp.begin(),
		tmp.end(),
		tmp.begin(),
		static_cast<int (*)(int)>(toupper));
	
	return tmp;
}
//Renvoie le caractère en majuscule
const char Utils::upchar(char car)
{
	if ((car >= 'a') and (car <= 'z'))
		car -= ('a' - 'A');
	
	return car;
}
//Transforme les espaces en underscores
const string Utils::sp2und(string ligne)
{
	string tmp = ligne;
	
	for (int i = 0; i < (int)tmp.size(); i++)
	{
		if (tmp[i] == ' ')
			tmp[i] = '_';
	}
	
	return tmp;
}
//Transforme les underscores en espaces
const string Utils::und2sp(string ligne)
{
	string tmp = ligne;
	
	for (int i = 0; i < (int)tmp.size(); i++)
	{
		if (tmp[i] == '_')
			tmp[i] = ' ';
	}
	
	return tmp;
}
//Comparaison lexicographique de deux chaines
const int Utils::str_compare(string str1, string str2)
{
	if (str1 == str2)
		return 0;
	
	if (lexicographical_compare(
		str1.begin(), str1.end(),
		str2.begin(), str2.end()))
		return -1;
	return 1;
}
