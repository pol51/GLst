#include "Film.h"

//Comparaison de 2 films par leur nom
int Film::cmp_alpha(const Film* film1, const Film* film2)
{
  return film1->get_nom().compare(film2->get_nom());
}
