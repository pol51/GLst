
#include "Options.h"

//Constructeur
Options::Options(string filename)
{
	this->filename = filename;
	this->style = "Plastique";
	this->liste = "listes.txt";
}
//Destructeur
Options::~Options()
{
	return;
}
//Accesseur en lecture sur le nom du fichier
const string Options::get_filename() const
{
	return filename;
}
//Accesseur en lecture sur le style
const string Options::get_style() const
{
	return style;
}
//Accesseur en lecture sur le nom du fichier des listes
const string Options::get_liste() const
{
	return liste;
}
//Accesseur en lecture sur le type de trie utilisé
const int Options::get_sortType() const
{
	return sortType;
}
//Accesseur en ecriture sur le nom du fichier
void Options::set_filename(string value)
{
	filename = value;
}
//Accesseur en ecriture sur le style
void Options::set_style(string value)
{
	style = value;
}
//Accesseur en ecriture sur le nom du fichier des listes
void Options::set_liste(string value)
{
	liste = value;
}
//Accesseur en écriture sur le type de trie utilisé
void Options::set_sortType(int value)
{
	sortType = value;
}
//Ecrit le fichier d'options
int Options::save()
{
	string line;
	
	fstream f(this->filename.c_str(), fstream::out);
	
	if (f == NULL) return 0;
	
	f << "<style> " << this->style.c_str() << "\n";
	f << "<liste> " << this->liste.c_str() << "\n";
	f << "<sort_type> " << this->sortType << "\n";
	
	f.close();
	
	return 1;
}
//Lit le fichier d'options
int Options::load()
{
	char buffer[1024];
	char cat[32];
	char value[256];
	
	fstream f(this->filename.c_str(), fstream::in);
	
	if (f == 0) return 0;
	
	int i = 0;
	
	while (!f.eof())
	{
		f.get(buffer, 1024, '\n');
		f.ignore();
		
		if (sscanf(buffer, "%s %s", cat, value) != 2)
			continue;
	
		if (strcmp(cat, "<style>") == 0)
		{
			this->style = string(value);
			i++;
		}
		
		if (strcmp(cat, "<liste>") == 0)
		{
			this->liste = string(value);
			i++;
		}
		
		if (strcmp(cat, "<sort_type>") == 0)
		{
			sscanf(value, "%d", &(this->sortType));
			i++;
		}	
	}
	
	f.close();
	
	return i;
}
