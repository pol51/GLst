#include "Book.h"

//Comparaison de 2 livres par leur auteur/titre
int Book::cmp_alpha(const Book* book1, const Book* book2)
{
  int result = book1->get_auteur().compare(book2->get_auteur());
  if (result) return result;
  return book1->get_titre().compare(book2->get_titre());
}
