#include "Zik.h"

const QString Zik::displayable(const bool moreInfo) const
{
  QString Line(_artist);
  Line.append(" - ");
  Line.append(_title);
  if (_nbCd)
    Line.append(QString(" (%1CD)").arg(_nbCd));
  if (moreInfo && _idBoite)
    Line.append(QString(" [#%1]").arg(_idBoite));
  return Line;
}
