#include "Zik.h"

//Constructeur
Zik::Zik() :
  Media(TYPE_ZIK), _artiste(""), _titre(""), _nbCd(0)
{
}

//Comparaison de 2 album par leur artiste/titre
int Zik::cmp_alpha(const Zik* zik1, const Zik* zik2)
{
  if (Utils::str_compare(zik1->get_artiste(), zik2->get_artiste()) == 1)
    return 1;
  if (Utils::str_compare(zik1->get_artiste(), zik2->get_artiste()) == 0)
    return Utils::str_compare(zik1->get_titre(), zik2->get_titre());
  return -1;
}
