#include "Utils.h"

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
