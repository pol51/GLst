#include "Film.h"

//Constructeur
Film::Film() :
  Media(TYPE_FILM),
  _nom(""), _nbCd(0), _nbDvd(0), _qualite(QLT_DVDRIP), _genre(GNR_FILM)
{
}

//Comparaison de 2 films par leur nom
int Film::cmp_alpha(const Film* film1, const Film* film2)
{
  return Utils::str_compare(film1->get_nom(), film2->get_nom());
}
