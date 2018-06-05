#include "Wektor2D.hh"
#include <cmath>
#include <iomanip>

int Wektor2D::_IstnWek;
int Wektor2D::_StworzWek;

/* ZREALIZOWANIE OPERACJI DODAWANIA WEKTOROW */
Wektor2D Wektor2D::operator+(Wektor2D wektor) const
{
  Wektor2D Suma;
  Suma[0] = _Wsp[0]+wektor[0];
  Suma[1] = _Wsp[1]+wektor[1];
  return Suma;
}

/* OPERACJA ZWRACA WEKTOR PRZECIWNY */
Wektor2D Wektor2D::operator-() const
{
  Wektor2D Przeciwny;
  Przeciwny[0] = -(_Wsp[0]);
  Przeciwny[1] = -(_Wsp[1]);
  return Przeciwny;
}

/* OPERACJA ODEJMOWANIA DWOCH WEKTOROW */
Wektor2D Wektor2D::operator-(Wektor2D wektor) const
{
  return ((*this)+(-wektor));
}

float Wektor2D::operator&() const
{
  float x,y;
  x = pow(_Wsp[0],2);
  y = pow(_Wsp[1],2);
  return ( sqrt( x+y ) );
}


std::ostream& operator<<(std::ostream &Strm, const Wektor2D &Wek)
{
  std::cout << std::setw(16) << std::fixed << std::setprecision(10) << Wek[0]
	    << std::setw(16) << std::fixed << std::setprecision(10) << Wek[1];
  return Strm;
}
