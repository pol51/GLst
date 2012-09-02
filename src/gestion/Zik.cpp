#include "Zik.h"

//Comparaison de 2 album par leur artiste/titre
int Zik::cmp_alpha(const Zik* zik1, const Zik* zik2)
{
  int result = zik1->get_artiste().compare(zik2->get_artiste());
  if (result) return result;
  return zik1->get_titre().compare(zik2->get_titre());
}
