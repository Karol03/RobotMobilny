#include "Prostokat.hh"
#include <cmath>

Prostokat::Prostokat(const Wektor2D &Przesuniecie, float x, float y)
{
  x = abs(x);
  y = abs(y);
  _WspLok.reserve(4);
  _GrafWsp.reserve(4);
  _WspLok.push_back( Wektor2D(x, y) );
  _WspLok.push_back( Wektor2D(x, -y) );
  _WspLok.push_back( Wektor2D(-x, -y) );
  _WspLok.push_back( Wektor2D(-x, y) );

  for(const Wektor2D &Elem : _WspLok)
    _GrafWsp.push_back( Elem+Przesuniecie );
  _WspGlob = Przesuniecie;
  _Promien = sqrt(pow(x,2)+pow(y,2));
  Rodzaj = PRZESZKODA;
}
