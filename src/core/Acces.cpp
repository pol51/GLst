#include "Acces.h"

#include "Collection.h"
#include "Zik.h"
#include "Film.h"
#include "Book.h"

#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QStringList>

//Chargement du fichier
bool Acces::load(const QString &filename)
{
  char buffer[1025];
  QString line;
  Media* med_src;

  QFile file(filename);

  if (!file.open(QIODevice::ReadOnly)) return false;

  int readSize = 0;
  do
  {
    readSize = file.readLine(buffer, 1024);
    if (readSize < 0) break;
    if (readSize == 0) continue;
    line = buffer;

    //récupération du résultat de la ligne
    med_src = decode(line);

    //test de ligne correcte
    if (med_src == NULL)
      continue;

    //test de doublon
    if (_collection.find(med_src->num()) >= 0)
    {
      delete med_src;
      med_src = NULL;
      continue;
    }

    //ajout d'un media dans la collection
    switch (med_src->type())
    {
      case Media::eMTZik:
        *_collection.addZik()  = *((Zik*)med_src);
        break;
      case Media::eMTFilm:
        *_collection.addFilm() = *((Film*)med_src);
        break;
      case Media::eMTBook:
        *_collection.addBook() = *((Book*)med_src);
        break;
      default:
        delete med_src;
        break;
    }
  }
  while (true);

  file.close();

  return true;
}

//Sauvegarde du fichier
bool Acces::save(const QString &filename) const
{
  QFile file(filename);

  if (!file.open(QIODevice::WriteOnly)) return false;

  foreach(const Media* M, _collection)
    file.write(code(*M).toUtf8());

  file.close();

  return true;
}

//Formatage d'une ligne
const QString Acces::code(const Media &media)
{
  QString line;

  //type
  line = QString("%1 %2").
    arg(QString::number(media.type())).
    arg(media.num());

  //infos spécifiques
  switch (media.type())
  {
    case Media::eMTZik:
      line.append(QString(" %1 %2 %3").
        arg(Utils::sp2und(((Zik&)media).artist())).
        arg(Utils::sp2und(((Zik&)media).title())).
        arg(QString::number(((Zik&)media).nbCd())));
      break;
    case Media::eMTFilm:
      line.append(QString(" %1 %2 %3 %4 %5").
        arg(Utils::sp2und(((Film&)media).name())).
        arg(QString::number(((Film&)media).nbCd())).
        arg(QString::number(((Film&)media).nbDvd())).
        arg(QString::number(((Film&)media).quality())).
        arg(QString::number(((Film&)media).gender())));
      break;
    case Media::eMTBook:
      line.append(QString(" %1 %2 %3").
        arg(Utils::sp2und(((Book&)media).author())).
        arg(Utils::sp2und(((Book&)media).title())).
        arg(QString::number(((Book&)media).format())));
      break;
    default:
      break;
  }

  line.append(QString(" %1 %2\n").
    arg(QString::number(media.idBoite())).
    arg(media.date()));

  return line;
}

//Décodage d'une ligne
Media* Acces::decode(const QString &ligne)
{
  Media *TmpMed;

  //test de la longueur de la ligne
  if (ligne.length() < 1)
    return NULL;

  QStringList data = ligne.split(' ');
  bool valid = false;

  switch (ligne[0].cell() - '0')
  {
    case Media::eMTZik:
      {
        //test et récup
        if (data.count() != 7)                        return NULL;

        const QString &num = data.at(1);
        if (!Media::testNum(num))                    return NULL;
        const QString &artiste = data.at(2);
        if (artiste.isEmpty())                        return NULL;
        const QString &titre = data.at(3);
        if (titre.isEmpty())                          return NULL;
        const int nbCd = data.at(4).toInt(&valid);
        if (!valid)                                   return NULL;
        const int idBoite = data.at(5).toInt(&valid);
        if (!valid)                                   return NULL;
        const QString &date = data.at(6);
        if (!Media::testDate(date.trimmed()))	    	return NULL;

        //création du media
        Zik *TmpZik = new Zik();

        //affectation des valeurs au media
        TmpZik->setArtist(Utils::und2sp(artiste));
        TmpZik->setTitle(Utils::und2sp(titre));
        TmpZik->setNbCd(nbCd);
        TmpZik->setNum(num);
        TmpZik->setIdBoite(idBoite);
        TmpZik->setDate(date);
        TmpMed = TmpZik;
      }
      break;
    case Media::eMTFilm:
      {
        //test et récup
        if (data.count() != 9)                        return NULL;

        const QString &num = data.at(1);
        if (!Media::testNum(num))                    return NULL;
        const QString &nom = data.at(2);
        if (nom.isEmpty())                            return NULL;
        const int nbCd = data.at(3).toInt(&valid);
        if (!valid)                                   return NULL;
        const int nbDvd = data.at(4).toInt(&valid);
        if (!valid)                                   return NULL;
        const int qualite = data.at(5).toInt(&valid);
        if (!valid)                                   return NULL;
        const int genre = data.at(6).toInt(&valid);
        if (!valid)                                   return NULL;
        const int idBoite = data.at(7).toInt(&valid);
        if (!valid)                                   return NULL;
        const QString &date = data.at(8);
        if (!Media::testDate(date.trimmed()))	    	return NULL;

        //création du media
        Film *TmpFilm = new Film();

        //affectation des valeurs au media
        TmpFilm->setName(Utils::und2sp(nom));
        TmpFilm->setNbCd(nbCd);
        TmpFilm->setNbDvd(nbDvd);
        TmpFilm->setQuality((Film::EQualite)qualite);
        TmpFilm->setGender((Film::EGenre)genre);
        TmpFilm->setNum(num);
        TmpFilm->setIdBoite(idBoite);
        TmpFilm->setDate(date);
        TmpMed = TmpFilm;
      }
      break;
    case Media::eMTBook:
      {
        //test et récup
        if (data.count() != 7)                        return NULL;

        const QString &num = data.at(1);
        if (!Media::testNum(num))                    return NULL;
        const QString &auteur = data.at(2);
        if (auteur.isEmpty())                         return NULL;
        const QString &titre = data.at(3);
        if (titre.isEmpty())                          return NULL;
        const int format = data.at(4).toInt(&valid);
        if (!valid)                                   return NULL;
        const int idBoite = data.at(5).toInt(&valid);
        if (!valid)                                   return NULL;
        const QString &date = data.at(6);
        if (!Media::testDate(date.trimmed()))		    return NULL;

        //création du media
        Book *TmpBook = new Book();

        //affectation des valeurs au media
        TmpBook->setAuthor(Utils::und2sp(auteur));
        TmpBook->setTitle(Utils::und2sp(titre));
        TmpBook->setFormat((Book::EBookFormat)format);
        TmpBook->setNum(num);
        TmpBook->setIdBoite(idBoite);
        TmpBook->setDate(date);
        TmpMed = TmpBook;
      }
      break;
    default:
      return NULL;
  }

  return TmpMed;
}
