#include "Book.h"

//Constructeur
Book::Book() :
  Media(TYPE_BOOK),
  _auteur(""), _titre(""), _format(FRT_PAPIER)
{
}

//Comparaison de 2 livres par leur auteur/titre
int Book::cmp_alpha(const Book* book1, const Book* book2)
{
  if (Utils::str_compare(book1->get_auteur(), book2->get_auteur()) == 1)
    return 1;
  if (Utils::str_compare(book1->get_auteur(), book2->get_auteur()) == 0)
    return Utils::str_compare(book1->get_titre(), book2->get_titre());
  return -1;
}
