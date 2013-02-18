#include "Media.h"

#include <QtCore/QDate>

//Accesseur en ecriture sur la référence par un entier
void Media::setNum(int nbr)
{
  if (nbr < 0) return;

  _num = makeNum1(_type) + NUM_SEP_CAR + makeNum2(nbr);
}

//Test de la référence
bool Media::testNum(const QString &num)
{
  int size = num.size();

  if (size != NUM_SIZE) return false;

  if (num[NUM_SEP_POS] != NUM_SEP_CAR) return false;

  bool valid = false;
  num.left(NUM_SEP_POS).toInt(&valid);
  if (!valid) return false;

  num.right(NUM_SIZE - NUM_SEP_POS - 1).toInt(&valid);
  if (!valid) return false;

  return true;
}

bool Media::testDate(const QString &date)
{
  return QDate::fromString(date.trimmed(), "yyyyMMdd").isValid();
}

//Création de la première partie de la référence
const QString Media::makeNum1(const int type)
{
  //création de la chaine
  QString num_1(QString::number(type));

  //complément à la taile désirée
  while ((num_1.length()) < NUM_SEP_POS)
    num_1.insert(0, '0');

  return num_1;
}

//Création de la seconde partie de la référence
const QString Media::makeNum2(const int nbr)
{
  //calcul de la taille de la seconde partie
  int num_2_size = NUM_SIZE - (NUM_SEP_POS + 1);

  //création de la chaine
  QString num_2(QString::number(nbr));

  //complément à la taile désirée
  while ((num_2.length()) < num_2_size)
    num_2.insert(0, '0');

  return num_2;
}
