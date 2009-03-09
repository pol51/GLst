
#include "Acces_HTML.h"
#include "Collection.h"
#include "Media.h"

//Constructeur
Acces_HTML::Acces_HTML(Collection * collection):Acces::Acces(collection)
{
}
//Destructeur
Acces_HTML::~Acces_HTML()
{
	return;
}
//Chargement du fichier
const int Acces_HTML::load(string /*filename*/)
{
	return 0;
}
//Sauvegarde du fichier
const int Acces_HTML::save(string filename)
{
	ostringstream lettres;	//utilise pour les index
	int type = 0;			//type actuel du media
	Media* tmpM;			//media temporaire
	char firstcar = 0;		//premier caractère du media précédent
	char newcar = 0;		//premier caractère du media courant
	
	//vérification de listes non-vides
	if (collection->nb_Media() == 0)
		return 0;
		
	fstream f(filename.c_str(), fstream::out);
	
	if (f == NULL) return 0;
	
	//tri par ordre alphabétique
	collection->sort_Media(SORT_ALPHA);
	
	//recup du nombre de media
	int nb_media[3];
	nb_media[0] = 4;	//nombre de type de media + 1
	nb_media[TYPE_FILM] = collection->nb_Media(TYPE_FILM);
	nb_media[TYPE_ZIK] = collection->nb_Media(TYPE_ZIK);
	nb_media[TYPE_BOOK] = collection->nb_Media(TYPE_BOOK);
	
	//tableau du nom des medias
	char *nom_media[4]; //taille = nombre de type de media + 1
	char nom_film[] = "Films";		nom_media[1] = nom_film;
	char nom_zik[] = "Musique";		nom_media[2] = nom_zik;
	char nom_book[] = "Livres";		nom_media[3] = nom_book;
	
	//en-tête de document
	f << "<html>\n\t<head>\n\t\t<title>Listes (Export GLst)</title>";
	f << "\n\t\t<style>";
	f << "\n\t\t\tbody {";
	f << "\n\t\t\t\tfont: 1em verdana, tahoma, ms sans serif, arial;";
	f << "\n\t\t\t\tcolor: #000000;";
	f << "\n\t\t\t\tbackground-color: #EEEEEE;";
	f << "\n\t\t\t}\n";
	f << "\n\t\t\ta, a:link, a:visited, a:active {";
	f << "\n\t\t\t\tcolor: #2244BB;";
	f << "\n\t\t\t\ttext-decoration: none;";
	f << "\n\t\t\t}\n";
	f << "\n\t\t\tul {";
	f << "\n\t\t\t\tpadding: 0.25em 0em;";
	f << "\n\t\t\t\tmargin: 0em;";
	f << "\n\t\t\t\tlist-style-type:none;";
	f << "\n\t\t\t}\n";
	f << "\n\t\t\ta:hover {";
	f << "\n\t\t\t\tfont: normal;";
	f << "\n\t\t\t\tcolor: #BB4422;";
	f << "\n\t\t\t\ttext-decoration: underline overline;";
	f << "\n\t\t\t}\n";
	f << "\n\t\t\tdiv {";
	f << "\n\t\t\t\tposition: absolute;";
	f << "\n\t\t\t\tcolor: #000000;";
	f << "\n\t\t\t\tborder-style: groove;";
	f << "\n\t\t\t\tborder-width: 1px;";
	f << "\n\t\t\t\tborder-color: #000000;";
	f << "\n\t\t\t\tbackground-color: #F5F5F5;";
	f << "\n\t\t\t\tpadding: 0.25em 0.5em;";
	f << "\n\t\t\t\tmargin-top: 1em;";
	f << "\n\t\t\t\ttext-align: left;";
	f << "\n\t\t\t\tleft: 1em;";
	f << "\n\t\t\t\tright: 1em;";
	f << "\n\t\t\t}\n";
	f << "\n\t\t\t.nombres {";
	f << "\n\t\t\t\ttext-align: right;";
	f << "\n\t\t\t\tposition: absolute;";
	f << "\n\t\t\t\tvisibility: hidden;";
	f << "\n\t\t\t\tright: 0.25em;";
	f << "\n\t\t\t}\n";
	f << "\n\t\t\t.categorie {";
	f << "\n\t\t\t\theight: 1em;";
	f << "\n\t\t\t\ttop: 0em;";
	f << "\n\t\t\t}\n";
	f << "\n\t\t\t.lettres {";
	f << "\n\t\t\t\theight: 1em;";
	f << "\n\t\t\t\ttop: 2.5em;";
	f << "\n\t\t\t}\n";
	f << "\n\t\t\t.liste {";
	f << "\n\t\t\t\ttop: 5em;";
	f << "\n\t\t\t\tbottom: 1em;";
	f << "\n\t\t\t\toverflow: auto;";
	f << "\n\t\t\t}\n";
	f << "\n\t\t\t.nom {";
	f << "\n\t\t\t\tcolor: #BB8800;";
	f << "\n\t\t\t}\n";
	f << "\n\t\t\t.titre {";
	f << "\n\t\t\t\tcolor: #2244BB;";
	f << "\n\t\t\t}\n";
	f << "\n\t\t</style>";
	f << "\n\t\t<script>";
	f << "\n\t\t\tfunction ShowDiv(obj)";
	f << "\n\t\t\t{";
	f << "\n\t\t\t\t";
	for (int i = 0; i < 4; i++) //adaptation du script en fonction des types presents
		if (nb_media[i] > 0)
		{
			f << "\n\t\t\t\tHideDiv('l" << i << "');";
			f << "\n\t\t\t\tHideDiv('c" << i << "');";
			f << "\n\t\t\t\tHideDiv('m" << i << "');";
		}
	f << "\n\t\t\t\tdocument.getElementById('l' + obj).style.visibility = 'visible';";
	f << "\n\t\t\t\tdocument.getElementById('c' + obj).style.visibility = 'visible';";
	f << "\n\t\t\t\tdocument.getElementById('m' + obj).style.visibility = 'visible';";
	f << "\n\t\t\t}\n";
	f << "\n\t\t\tfunction HideDiv(obj)";
	f << "\n\t\t\t{";
	f << "\n\t\t\t\tdocument.getElementById(obj).style.visibility = 'hidden';";
	f << "\n\t\t\t}";
	f << "\n\t\t</script>";
	f << "\n\t</head>";
	f << "\n\t<body onload=\"javascript::ShowDiv('0')\">";
	f << "\n\t\t<div class=\"categorie\">";
	bool addSep = false; //flag d'ajout de séparateur des catégories
	for (int i = 1; i < 4; i++) //adaptation des liens en fonction des types presents
		if (nb_media[i] > 0)
		{
			if (addSep)
				f << " -";
			f << "\n\t\t\t<a href=\"javascript:ShowDiv('" << i
			  << "')\">" << nom_media[i] << "</a>";
			addSep = true;
		}
	f << "\n\t\t\t<span id=\"c0\"></span>";
	for (int i = 1; i < 4; i++) //affichage des comptes de media
		if (nb_media[i] > 0)
			f << "\n\t\t\t<span id=\"c" << i << "\" class=\"nombres\">"
			  << nom_media[i] << ": " << nb_media[i] << "</span>";
	f << "\n\t\t</div>";
	
	for (int i = 0; i < collection->nb_Media(); i++)
	{
		//récupération du media
		tmpM = collection->get_Media(i);
		if (tmpM == NULL) continue;
		
		//détection du changement de type
		if (type != tmpM->get_type())
		{
			//si pas premier enregistrement
			if (type != 0)
			{
				f << "\n\t\t\t</ul>";
				f << "\n\t\t</div>";
				f << "\n\t\t<div class=\"lettres\" id=\"m" << type << "\" >";
				f << lettres.str();
				f << "\n\t\t</div>";
			}
				
			//nouveau type
			type = tmpM->get_type();
			
			//raz première lettre
			firstcar = 0;
			
			//raz liste des premières lettres (index)
			lettres.str("");
			
			//nouveau div portant l'id correspondent au type
			f << "\n\t\t<div class=\"liste\" id=\"l" << type << "\" >";
			f << "\n\t\t\t<ul>";
		}
		
		//récup du premier caractère
		newcar = Utils::upchar(tmpM->get_firstLetter());
		
		//regroupement des premières caractères non-lettres
		if (newcar < 'A') newcar = '0';
		else if (newcar > 'Z') newcar = '1';
		
		//test du premier caractère
		if (firstcar != newcar)
		{
			if (firstcar != 0)	//saut de ligne si pas tête de liste
				f << "\n\t\t\t\t<br />";
			firstcar = newcar;	//attribution du nouveau caractère
			
			//index (type/lettre)
			lettres << "\n\t\t\t<a href=\"#" << type << firstcar << "\">";
			lettres << firstcar << "</a>";
			
			//ancre des index (type/lettre)
			f << "\n\t\t\t\t<a id=\"" << type;
			f << firstcar << "\"></a>";
		}
		
		//écriture d'une ligne
		f << "\n\t\t\t\t<li>" << code(tmpM) << "</li>";
	}
	
	//clotûre de la dernière liste
	f << "\n\t\t\t</ul>\n\t\t</div>";
	
	//dernier index des lettres
	f << "\n\t\t<div class=\"lettres\" id=\"m" << type << "\" >";
	f << lettres.str();
	f << "\n\t\t</div>";
	
	//pied de document
	f << "\n\t\t<div class=\"lettres\" id=\"m0\" >Choisissez une liste.</div>";
	f << "\n\t\t<div class=\"liste\" id=\"l0\" >Choisissez une liste.</div>";
	f << "\n\t</body>\n</html>";
	
	//fermeture du fichier
	f.close();
	
	return 1;
}
//Formatage d'une ligne
string Acces_HTML::code(const Media* media)
{
	ostringstream line;
	
	//infos spécifiques
	switch (media->get_type())
	{
		case TYPE_ZIK:
			line << "<span class=\"nom\">";
			line << ((Zik*)media)->get_artiste() << "</span>";
			line << ": <span class=\"titre\">";
			line << ((Zik*)media)->get_titre() << "</span>";
			if (((Zik*)media)->get_nbCd())
				line << " (" << ((Zik*)media)->get_nbCd() << "cd)";
			break;
		case TYPE_FILM:
			line << "<span class=\"nom\">";
			line << ((Film*)media)->get_nom() << "</span>";
			if (((Film*)media)->get_nbCd() > 0)
				line << " (" << ((Film*)media)->get_nbCd() << "cd)";
			if (((Film*)media)->get_nbDvd() > 0)
				line << " (" << ((Film*)media)->get_nbDvd() << "dvd)";
			//line << " " << ((Film*)media)->get_qualite();
			//line << " " << ((Film*)media)->get_genre();
			break;
		case TYPE_BOOK:
			line << "<span class=\"nom\">";
			line << ((Book*)media)->get_auteur() << "</span>";
			line << ": <span class=\"titre\">";
			line << ((Book*)media)->get_titre() << "</span>";
			//line << " " << ((Book*)media)->get_format();
			break;
		
	}
	
	//id boite
	if (media->get_idBoite() > 0)
		line << " [n°" << media->get_idBoite() << "]";
	
	//date
	//line << " " << media->get_date();
	
	return line.str();
}
//Décodage d'une ligne
Media* Acces_HTML::decode(string /*ligne*/)
{
	return NULL;
}
