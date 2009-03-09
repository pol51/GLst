#include <QApplication>

#include "winListe.h"
//#include "./gestion/Collection.h"

int main(int argc, char * argv[])
{	
	QApplication myApp(argc,argv);
	
	winListe *myListe = new winListe();
	
	myListe->show();
        myListe->refreshStyle();
	myListe->load();
	myListe->sortList();
	
	return myApp.exec();
}
