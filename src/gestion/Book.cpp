#include "Book.h"

const QString Book::displayable(const bool moreInfo) const
{
  QString Line(_author);
  Line.append(" - ");
  Line.append(_title);
  if (moreInfo)
    switch (_format)
    {
      case Book::ePaper:    Line.append(" [papier]"); break;
      case Book::eNumeric:  Line.append(" [e-book]"); break;
    }
  return Line;
}
