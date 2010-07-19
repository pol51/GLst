
#include "Media.h"

//Accesseur en ecriture sur la r�f�rence par un entier
void Media::set_num(int nbr)
{
  if (nbr < 0) return;

  _num = make_num_1(_type) + NUM_SEP_CAR + make_num_2(nbr);
}

//Test de la r�f�rence
bool Media::test_num(const QString &num)
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

bool Media::test_date(const QString &date)
{
  if (date.count() != 8) return 0;
  bool result;
  date.toInt(&result);
  return result;
}

//Cr�ation de la premi�re partie de la r�f�rence
const QString Media::make_num_1(const int type)
{
  //cr�ation de la chaine
  QString num_1(QString::number(type));

  //compl�ment � la taile d�sir�e
  while ((num_1.length()) < NUM_SEP_POS)
    num_1.insert(0, '0');

  return num_1;
}

//Cr�ation de la seconde partie de la r�f�rence
const QString Media::make_num_2(const int nbr)
{
  //calcul de la taille de la seconde partie
  int num_2_size = NUM_SIZE - (NUM_SEP_POS + 1);

  //cr�ation de la chaine
  QString num_2(QString::number(nbr));

  //compl�ment � la taile d�sir�e
  while ((num_2.length()) < num_2_size)
    num_2.insert(0, '0');

  return num_2;
}

int Media::cmp_date(const Media* med1, const Media* med2)
{
  const int res = QString::compare(med1->get_date(), med2->get_date());
  if (res) return -res;
  return -QString::compare(med1->get_num(), med2->get_num());
}
