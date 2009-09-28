
#include "Utils.h"

//Test sur une chaine numérique
int Utils::test_numeric(const QString &alpha)
{
  bool valid = false;
  alpha.toInt(&valid);

  return valid?1:0;
}
//Mise en majuscule
const QString Utils::upcase(const QString &str)
{
  QString tmp(str);

  return tmp.toUpper();
}

//Renvoie le caractère en majuscule
char Utils::upchar(const char car)
{
  char tmp = car;
  if ((car >= 'a') and (car <= 'z'))
    tmp = car - ('a' - 'A');

  return tmp;
}
//Transforme les espaces en underscores
const QString Utils::sp2und(const QString &ligne)
{
  QString tmp(ligne);

  return tmp.replace(' ', '_');
}
//Transforme les underscores en espaces
const QString Utils::und2sp(const QString &ligne)
{
  QString tmp(ligne);

  return tmp.replace('_', ' ');
}
//Comparaison lexicographique de deux chaines
int Utils::str_compare(const QString &str1, const QString &str2)
{
  return QString::compare(str1, str2, Qt::CaseInsensitive);
}
