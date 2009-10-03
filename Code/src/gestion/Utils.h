#ifndef _UTILS_H
#define _UTILS_H

#include <QString>

//Classe d'utilitaires divers
class Utils
{
  public:
    //Test sur une chaine numérique
    static int test_numeric(const QString &alpha);

    //Mise en majuscule
    static const QString upcase(const QString &str);

    //Renvoie le caractère en majuscule
    static char upchar(const char car);

    //Transforme les espaces en underscores
    static const QString sp2und(const QString &ligne);

    //Transforme les underscores en espaces
    static const QString und2sp(const QString &ligne);

    //Comparaison lexicographique de deux chaines
    static int str_compare(const QString &str1, const QString &str2);
};
#endif
