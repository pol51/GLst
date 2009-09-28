#include "Zik.h"

//Constructeur
Zik::Zik() :
  Media(TYPE_ZIK), _artiste(""), _titre(""), _nbCd(0)
{
}

//Test de l'artiste
int Zik::test_artiste(const QString &artiste)
{
  if (!artiste.isEmpty()) return 1;

  return 0;
}

//Test du titre
int Zik::test_titre(const QString &titre)
{
  if (!titre.isEmpty()) return 1;

  return 0;
}

//Test du nombre de cd
int Zik::test_nbCd(const int /*nbCd*/)
{
  return 1;
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
