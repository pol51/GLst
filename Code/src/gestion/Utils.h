#ifndef _UTILS_H
#define _UTILS_H

#include <QString>

//Classe d'utilitaires divers
class Utils
{
  public:
    //Transforme les espaces en underscores
    static const QString sp2und(const QString &ligne);

    //Transforme les underscores en espaces
    static const QString und2sp(const QString &ligne);
};
#endif
