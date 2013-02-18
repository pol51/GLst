#include "Film.h"

const QString Film::displayable(const bool moreInfo) const
{
  QString Line(_name);
  if (_nbCd)
    Line.append(QString(" (%1CD)").arg(_nbCd));
  if (_nbDvd)
    Line.append(QString(" (%1DVD)").arg(_nbDvd));
  if (moreInfo)
  {
    if (_idBoite)
      Line.append(QString(" [#%1]").arg(_idBoite));
    switch (_quality)
    {
      case Film::eDVDRip:       Line.append(" [DvdRip]"); break;
      case Film::eScreener:     Line.append(" [Scr]");    break;
      case Film::eDVD:          Line.append(" [Dvd]");    break;
      case Film::eTVRip:        Line.append(" [TvRip]");  break;
      case Film::ePub:          Line.append(" [Pub]");    break;
      case Film::eDVDScreener:  Line.append(" [DvdScr]"); break;
      case Film::eVCD:          Line.append(" [Vcd]");    break;
    }
    switch (_gender)
    {
      case Film::eFilm:         Line.append(" <Film>");         break;
      case Film::eLive:         Line.append(" <Concert>");      break;
      case Film::eSpectacle:    Line.append(" <Spectacle>");    break;
      case Film::eManga:        Line.append(" <Manga>");        break;
      case Film::eAnime:        Line.append(" <Dessin Anime>"); break;
      case Film::eSerie:        Line.append(" <Serie>");        break;
      case Film::eDocumentaire: Line.append(" <Documentaire>"); break;
    }
  }
  return Line;
}
