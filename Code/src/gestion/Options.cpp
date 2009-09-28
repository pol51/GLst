
#include "Options.h"

#include <QFile>
#include <QStringList>

//Constructeur
Options::Options(const QString &filename)
{
  this->filename = filename;
  style = "Plastique";
  #ifdef Q_OS_SYMBIAN
  liste = "E:/GLst/listes.txt";
  #else
  liste = "listes.txt";
  #endif
  sortType = 2; //SORT_ALPHA
}
//Ecrit le fichier d'options
int Options::save()
{
  QString data(QString("<style> %1\n<liste> %2\n<sort_type> %3\n").
    arg(style).arg(liste).arg(QString::number(sortType)));

  QFile file(filename);
  if (file.open(QIODevice::WriteOnly))
  {
    file.write(data.toUtf8());
    file.close();
    return 1;
  }
  return 0;
}
//Lit le fichier d'options
int Options::load()
{
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly))
    return 0;

  char buffer[1025];
  int found = 0;

  QString line;
  QStringList data;

  int readSize = 0;
  do
  {
    readSize = file.readLine(buffer, 1024);
    if (readSize < 0) break;
    if (readSize == 0)	continue;

    line = buffer;
    data = line.split(' ');

    if (data.count() < 2)
      continue;

    if (data.at(0) == "<style>")
    {
      style = data.at(1).trimmed();
      found++;
      continue;
    }
    if (data.at(0) == "<liste>")
    {
      liste = data.at(1).trimmed();
      found++;
      continue;
    }
    if (data.at(0) == "<sort_type>")
    {
      sortType = data.at(1).trimmed().toInt();
      found++;
      continue;
    }
  }
  while (true);

  return found;
}
