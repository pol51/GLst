#include "Acces_HTML.h"

#include <gestion/Collection.h>
#include <gestion/Media.h>
#include <gestion/Book.h>
#include <gestion/Film.h>
#include <gestion/Zik.h>

#include <QtCore/QFile>

//Sauvegarde du fichier
bool Acces_HTML::save(const QString &filename) const
{
  QString lettres;		//utilise pour les index
  int type = 0;       //type actuel du media
  QChar firstcar(0);	//premier caractère du media précédent
  QChar newcar(0);		//premier caractère du media courant

  //vérification de listes non-vides
  if (!_collection.size())
    return false;

  QFile file(filename);
  QString f;

  if (!file.open(QIODevice::WriteOnly)) return false;

  //tri par ordre alphabétique
  _collection.sort(Collection::eSTAlpha);

  //recup du nombre de media
  int nb_media[Media::eMTMax];
  nb_media[0] = Media::eMTMax;	//nombre de type de media + 1
  nb_media[Media::eMTFilm] = _collection.size(Media::eMTFilm);
  nb_media[Media::eMTZik]  = _collection.size(Media::eMTZik);
  nb_media[Media::eMTBook] = _collection.size(Media::eMTBook);

  //tableau du nom des medias
  char *nom_media[Media::eMTMax]; //taille = nombre de type de media + 1
  char nom_film[] = "Films";		nom_media[Media::eMTFilm] = nom_film;
  char nom_zik[]  = "Musique";	nom_media[Media::eMTZik]  = nom_zik;
  char nom_book[] = "Livres";		nom_media[Media::eMTBook] = nom_book;

  //en-tête de document
  f.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
      "\n<html>\n\t<head>\n\t\t<title>Listes (Export GLst)</title>"
      "\n\t\t<style>"
      "\n\t\t\tbody {"
      "\n\t\t\t\tfont: 1em verdana, tahoma, ms sans serif, arial;"
      "\n\t\t\t\tcolor: #000000;"
      "\n\t\t\t\tbackground-color: #EEEEEE;"
      "\n\t\t\t}\n"
      "\n\t\t\ta, a:link, a:visited, a:active {"
      "\n\t\t\t\tcolor: #2244BB;"
      "\n\t\t\t\ttext-decoration: none;"
      "\n\t\t\t}\n"
      "\n\t\t\tul {"
      "\n\t\t\t\tpadding: 0.25em 0em;"
      "\n\t\t\t\tmargin: 0em;"
      "\n\t\t\t\tlist-style-type:none;"
      "\n\t\t\t}\n"
      "\n\t\t\ta:hover {"
      "\n\t\t\t\tfont: normal;"
      "\n\t\t\t\tcolor: #BB4422;"
      "\n\t\t\t\ttext-decoration: underline overline;"
      "\n\t\t\t}\n"
      "\n\t\t\tdiv {"
      "\n\t\t\t\tposition: absolute;"
      "\n\t\t\t\tcolor: #000000;"
      "\n\t\t\t\tborder-style: groove;"
      "\n\t\t\t\tborder-width: 1px;"
      "\n\t\t\t\tborder-color: #000000;"
      "\n\t\t\t\tbackground-color: #F5F5F5;"
      "\n\t\t\t\tpadding: 0.25em 0.5em;"
      "\n\t\t\t\tmargin-top: 1em;"
      "\n\t\t\t\ttext-align: left;"
      "\n\t\t\t\tleft: 1em;"
      "\n\t\t\t\tright: 1em;"
      "\n\t\t\t}\n"
      "\n\t\t\t.nombres {"
      "\n\t\t\t\ttext-align: right;"
      "\n\t\t\t\tposition: absolute;"
      "\n\t\t\t\tvisibility: hidden;"
      "\n\t\t\t\tright: 0.25em;"
      "\n\t\t\t}\n"
      "\n\t\t\t.categorie {"
      "\n\t\t\t\theight: 1em;"
      "\n\t\t\t\ttop: 0em;"
      "\n\t\t\t}\n"
      "\n\t\t\t.lettres {"
      "\n\t\t\t\theight: 1em;"
      "\n\t\t\t\ttop: 2.5em;"
      "\n\t\t\t}\n"
      "\n\t\t\t.liste {"
      "\n\t\t\t\ttop: 5em;"
      "\n\t\t\t\tbottom: 1em;"
      "\n\t\t\t\toverflow: auto;"
      "\n\t\t\t}\n"
      "\n\t\t\t.nom {"
      "\n\t\t\t\tcolor: #BB8800;"
      "\n\t\t\t}\n"
      "\n\t\t\t.titre {"
      "\n\t\t\t\tcolor: #2244BB;"
      "\n\t\t\t}\n"
      "\n\t\t</style>"
      "\n\t\t<script>"
      "\n\t\t\tfunction ShowDiv(obj)"
      "\n\t\t\t{"
      "\n\t\t\t\t");
  for (int i = 0; i < 4; i++) //adaptation du script en fonction des types presents
    if (nb_media[i] > 0)
      f.append(QString("\n\t\t\t\tHideDiv('l%1');").arg(QString::number(i))).
        append(QString("\n\t\t\t\tHideDiv('c%1');").arg(QString::number(i))).
        append(QString("\n\t\t\t\tHideDiv('m%1');").arg(QString::number(i)));
  f.append("\n\t\t\t\tdocument.getElementById('l' + obj).style.visibility = 'visible';"
      "\n\t\t\t\tdocument.getElementById('c' + obj).style.visibility = 'visible';"
      "\n\t\t\t\tdocument.getElementById('m' + obj).style.visibility = 'visible';"
      "\n\t\t\t}\n"
      "\n\t\t\tfunction HideDiv(obj)"
      "\n\t\t\t{"
      "\n\t\t\t\tdocument.getElementById(obj).style.visibility = 'hidden';"
      "\n\t\t\t}"
      "\n\t\t</script>"
      "\n\t</head>"
      "\n\t<body onload=\"javascript::ShowDiv('0')\">"
      "\n\t\t<div class=\"categorie\">");
  bool addSep = false; //flag d'ajout de séparateur des catégories
  for (int i = 1; i < 4; i++) //adaptation des liens en fonction des types presents
    if (nb_media[i] > 0)
    {
      if (addSep)
        f.append(" -");
      f.append(QString("\n\t\t\t<a href=\"javascript:ShowDiv('%1')\">%2</a>").
          arg(QString::number(i)).arg(nom_media[i]));
      addSep = true;
    }
  f.append("\n\t\t\t<span id=\"c0\"></span>");
  for (int i = 1; i < 4; i++) //affichage des comptes de media
    if (nb_media[i] > 0)
      f.append(QString(
        "\n\t\t\t<span id=\"c%1\" class=\"nombres\">%2: %3</span>").
        arg(QString::number(i)).
        arg(nom_media[i]).
        arg(QString::number(nb_media[i])));

  f.append("\n\t\t</div>");

  foreach(const Media *M, _collection)
  {
    //détection du changement de type
    if (type != M->type())
    {
      //si pas premier enregistrement
      if (type != 0)
        f.append("\n\t\t\t</ul>\n\t\t</div>").
          append(QString("\n\t\t<div class=\"lettres\" id=\"m%1\" >").
            arg(QString::number(type))).
          append(lettres).
          append("\n\t\t</div>");

      //nouveau type
      type = M->type();

      //raz première lettre
      firstcar = 0;

      //raz liste des premières lettres (index)
      lettres.clear();

      //nouveau div portant l'id correspondent au type
      f.append(QString("\n\t\t<div class=\"liste\" id=\"l%1\" >").
        arg(QString::number(type))).append("\n\t\t\t<ul>");
    }

    //récup du premier caractère
    newcar = M->firstLetter().toUpper();

    //regroupement des premières caractères non-lettres
    if (newcar < 'A') newcar = '0';
    else if (newcar > 'Z') newcar = '1';

    //test du premier caractère
    if (firstcar != newcar)
    {
      if (firstcar != 0)	//saut de ligne si pas tête de liste
        f.append("\n\t\t\t\t<br />");
      firstcar = newcar;	//attribution du nouveau caractère

      //index (type/lettre)
      lettres.append(QString("\n\t\t\t<a href=\"#%1%2\">%2</a>").
        arg(QString::number(type)).
        arg(firstcar));

      //ancre des index (type/lettre)
      f.append(QString("\n\t\t\t<a id=\"%1%2\"></a>").
        arg(QString::number(type)).
        arg(firstcar));
    }

    //écriture d'une ligne
    f.append(QString("\n\t\t\t\t<li>%1</li>").arg(code(*M)));
  }

  //clotûre de la dernière liste
  f.append("\n\t\t\t</ul>\n\t\t</div>");

  //dernier index des lettres
  f.append(QString("\n\t\t<div class=\"lettres\" id=\"m%1\" >%2\n\t\t</div>").
    arg(QString::number(type)).
    arg(lettres));

  //pied de document
  f.append("\n\t\t<div class=\"lettres\" id=\"m0\" >Choisissez une liste.</div>"
      "\n\t\t<div class=\"liste\" id=\"l0\" >Choisissez une liste.</div>"
      "\n\t</body>\n</html>");

  //ecriture dans le fichier
  file.write(f.toUtf8());

  //fermeture du fichier
  file.close();

  return 1;
}
//Formatage d'une ligne
const QString Acces_HTML::code(const Media &media)
{
  QString line;

  //infos spécifiques
  switch (media.type())
  {
    case Media::eMTZik:
      line.append(QString("<span class=\"nom\">%1</span>"
        ": <span class=\"titre\">%2</span>").
        arg(((Zik&)media).artist()).
        arg(((Zik&)media).title()));
      if (((Zik&)media).nbCd())
        line.append(QString(" (%1cd)").
          arg(QString::number(((Zik&)media).nbCd())));
      break;
    case Media::eMTFilm:
      line.append(QString("<span class=\"nom\">%1</span>").
        arg(((Film&)media).name()));
      if (((Film&)media).nbCd() > 0)
        line.append(QString(" (%1cd)").
          arg(((Film&)media).nbCd()));
      if (((Film&)media).nbDvd() > 0)
        line.append(QString(" (%1dvd)").
          arg(((Film&)media).nbDvd()));
      break;
    case Media::eMTBook:
      line.append(QString("<span class=\"nom\">%1</span>"
        ": <span class=\"titre\">%2</span>").
        arg(((Book&)media).author()).
        arg(((Book&)media).title()));
      break;
    default:
      break;
  }

  //id boite
  if (media.idBoite())
    line.append(QString(" [n°%1]").arg(media.idBoite()));

  return line;
}
