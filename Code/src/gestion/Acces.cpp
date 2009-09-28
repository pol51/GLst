#include "Acces.h"

#include <gestion/Collection.h>
#include <gestion/Zik.h>
#include <gestion/Film.h>
#include <gestion/Book.h>

#include <QFile>
#include <QString>
#include <QStringList>

//Constructeur
Acces::Acces(Collection *collection) :
  _collection(collection)
{
}

//Chargement du fichier
int Acces::load(const QString &filename)
{
  char buffer[1025];
  QString line;
  Media* med_src;

  QFile file(filename);

  if (!file.open(QIODevice::ReadOnly)) return 0;

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
    if (_collection->find_Media(med_src->get_num()) >= 0)
    {
      delete med_src;
      med_src = NULL;
      continue;
    }

    //ajout d'un media dans la collection
    switch (med_src->get_type())
    {
      case TYPE_ZIK:
        *(_collection->add_Zik())  = *((Zik*)med_src);
        break;
      case TYPE_FILM:
        *(_collection->add_Film()) = *((Film*)med_src);
        break;
      case TYPE_BOOK:
        *(_collection->add_Book()) = *((Book*)med_src);
        break;
      default:
        delete med_src;
        break;
    }
  }
  while (true);

  file.close();

  return 1;
}

//Sauvegarde du fichier
int Acces::save(const QString &filename) const
{
  QString line;

  QFile file(filename);

  if (!file.open(QIODevice::WriteOnly)) return 0;

  const int nb_Media = _collection->nb_Media();
  for (int i = 0; i < nb_Media; i++)
    file.write(code(_collection->get_Media(i)).toAscii());

  file.close();

  return 1;
}

//Formatage d'une ligne
QString Acces::code(const Media* media)
{
  QString line;

  //type
  line = QString("%1 %2").
    arg(QString::number(media->get_type())).
    arg(media->get_num());

  //infos spécifiques
  switch (media->get_type())
  {
    case TYPE_ZIK:
      line.append(QString(" %1 %2 %3").
        arg(Utils::sp2und(((Zik*)media)->get_artiste())).
        arg(Utils::sp2und(((Zik*)media)->get_titre())).
        arg(QString::number(((Zik*)media)->get_nbCd())));
      break;
    case TYPE_FILM:
      line.append(QString(" %1 %2 %3 %4 %5").
        arg(Utils::sp2und(((Film*)media)->get_nom())).
        arg(QString::number(((Film*)media)->get_nbCd())).
        arg(QString::number(((Film*)media)->get_nbDvd())).
        arg(QString::number(((Film*)media)->get_qualite())).
        arg(QString::number(((Film*)media)->get_genre())));
      break;
    case TYPE_BOOK:
      line.append(QString(" %1 %2 %3").
        arg(Utils::sp2und(((Book*)media)->get_auteur())).
        arg(Utils::sp2und(((Book*)media)->get_titre())).
        arg(QString::number(((Book*)media)->get_format())));
      break;
  }

  line.append(QString(" %1 %2\n").
    arg(QString::number(media->get_idBoite())).
    arg(media->get_date()));

  return line;
}

//Décodage d'une ligne
Media* Acces::decode(const QString &ligne)
{
  //media temporaire
  Media* tmpMed = NULL;

  //test de la longueur de la ligne
  if (ligne.length() < 1)
    return NULL;

  QStringList data = ligne.split(' ');
  bool valid = false;

  switch (ligne[0].cell() - '0')
  {
    case TYPE_ZIK:
      {
        //test et récup
        if (data.count() != 7)                        return NULL;

        const QString &num = data.at(1);
        if (Media::test_num(num) != 1)                return NULL;
        const QString &artiste = data.at(2);
        if (Zik::test_artiste(artiste) != 1)          return NULL;
        const QString &titre = data.at(3);
        if (Zik::test_titre(titre) != 1)              return NULL;
        const int nbCd = data.at(4).toInt(&valid);
        if (!valid)                                   return NULL;
        const int idBoite = data.at(5).toInt(&valid);
        if (!valid)                                   return NULL;
        const QString &date = data.at(6);
        if (Media::test_date(date.trimmed()) != 1)		return NULL;

        //création du media
        tmpMed = new Zik();

        //affectation des valeurs au media
        ((Zik*)tmpMed)->set_artiste(Utils::und2sp(artiste));
        ((Zik*)tmpMed)->set_titre(Utils::und2sp(titre));
        ((Zik*)tmpMed)->set_nbCd(nbCd);
        ((Zik*)tmpMed)->set_num(num);
        ((Zik*)tmpMed)->set_idBoite(idBoite);
        ((Zik*)tmpMed)->set_date(date);
      }
      break;
    case TYPE_FILM:
      {
        //test et récup
        if (data.count() != 9)                        return NULL;

        const QString &num = data.at(1);
        if (Media::test_num(num) != 1)                return NULL;
        const QString &nom = data.at(2);
        if (Film::test_nom(nom) != 1)                 return NULL;
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
        if (Media::test_date(date.trimmed()) != 1)		return NULL;

        //création du media
        tmpMed = new Film();

        //affectation des valeurs au media
        ((Film*)tmpMed)->set_nom(Utils::und2sp(nom));
        ((Film*)tmpMed)->set_nbCd(nbCd);
        ((Film*)tmpMed)->set_nbDvd(nbDvd);
        ((Film*)tmpMed)->set_qualite(qualite);
        ((Film*)tmpMed)->set_genre(genre);
        ((Film*)tmpMed)->set_num(num);
        ((Film*)tmpMed)->set_idBoite(idBoite);
        ((Film*)tmpMed)->set_date(date);
      }
      break;
    case TYPE_BOOK:
      {
        //test et récup
        if (data.count() != 7)                        return NULL;

        const QString &num = data.at(1);
        if (Media::test_num(num) != 1)                return NULL;
        const QString &auteur = data.at(2);
        if (Book::test_auteur(auteur) != 1)           return NULL;
        const QString &titre = data.at(3);
        if (Book::test_titre(titre) != 1)             return NULL;
        const int format = data.at(4).toInt(&valid);
        if (!valid)                                   return NULL;
        const int idBoite = data.at(5).toInt(&valid);
        if (!valid)                                   return NULL;
        const QString &date = data.at(6);
        if (Media::test_date(date.trimmed()) != 1)		return NULL;

        //création du media
        tmpMed = new Book();

        //affectation des valeurs au media
        ((Book*)tmpMed)->set_auteur(Utils::und2sp(auteur));
        ((Book*)tmpMed)->set_titre(Utils::und2sp(titre));
        ((Book*)tmpMed)->set_format(format);
        ((Book*)tmpMed)->set_num(num);
        ((Book*)tmpMed)->set_idBoite(idBoite);
        ((Book*)tmpMed)->set_date(date);
      }
      break;
    default:
      return NULL;
  }

  return tmpMed;
}
