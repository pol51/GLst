#include "Options.h"

#include <QtCore/QFile>
#include <QtCore/QStringList>

//Constructeur
Options::Options(const QString &filename) :
  _filename(filename), _style("Plastique"),
  _liste("listes.txt"),
  _sortType(2) // SORT_ALPHA
{
}

//Ecrit le fichier d'options
int Options::save() const
{
  QString data(QString("<style> %1\n<liste> %2\n<sort_type> %3\n").
    arg(_style).arg(_liste).arg(QString::number(_sortType)));

  QFile file(_filename);
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
  QFile file(_filename);
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
      _style = data.at(1).trimmed();
      found++;
      continue;
    }
    if (data.at(0) == "<liste>")
    {
      _liste = data.at(1).trimmed();
      found++;
      continue;
    }
    if (data.at(0) == "<sort_type>")
    {
      _sortType = data.at(1).trimmed().toInt();
      found++;
      continue;
    }
  }
  while (true);

  return found;
}
