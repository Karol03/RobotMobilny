#include "Macierz2x2.hh"
#include <cmath>

#define PI 3.14159265

/* MNOZENIE MACIERZY PRZEZ WEKTOR */
Wektor2D Macierz2x2::operator*(const Wektor2D& wektor) const
{
  Wektor2D Iloczyn;
  Iloczyn[0] = (_Kolumna[0])[0]*wektor[0]+(_Kolumna[1])[0]*wektor[1];
  Iloczyn[1] = (_Kolumna[0])[1]*wektor[0]+(_Kolumna[1])[1]*wektor[1];
  return Iloczyn;
}

/************************************************/
/*  MACIERZ ZOSTAJE WYPELNIONA WARTOSCIAMI DLA  */
/* ODPOWIEDNIEGO KATA, ABY NASTEPNIE MOGLA BYC  */
/* UZYTA DO OPERACJI OBROTU DANEGO PUNKTU O TEN */
/* KAT W UKLADZIE WSPOLRZEDNYCH KARTEZJANSKICH  */
/************************************************/
Macierz2x2 Macierz2x2::MacierzObrotu(float STOPNIE){
  float STP = STOPNIE*(PI/180);
  (_Kolumna[0])[0] = cos(STP);
  (_Kolumna[1])[0] = -(sin(STP));
  (_Kolumna[0])[1] = sin(STP);
  (_Kolumna[1])[1] = cos(STP);
  return (*this);
}

/***********************************************/
/*   OPERATOR WYSWIETLA WSZYSTKIE CZTERY POLA  */
/*                  MACIERZY                   */
/***********************************************/
std::ostream& operator<<(std::ostream &Strm, const Macierz2x2 &Mac)
{
  std::cout << Mac(0,0) << "\t" << Mac(1,0) << "\n"
	    << Mac(0,1) << "\t" << Mac(1,1) << "\n";
  return Strm;
}
