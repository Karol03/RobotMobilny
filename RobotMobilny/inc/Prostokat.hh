#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include <iostream>
#include "Wektor2D.hh"
#include "Macierz2x2.hh"
#include "ObiektGraficzny.hh"

/*!
 * \file Prostokat.hh
 * Przedstawienie klasy prostokat ktory jest przeszkoda na scenie.
 */


class Prostokat 
  : public ObiektGraficzny
{
 
  public:
  /*!
   * \brief Konstruktor parametryczny prostokata
   */
  Prostokat(const Wektor2D &Przesuniecie, float x = 10, float y = 10);
  
  const Wektor2D centrum() const { return _WspGlob; }
  void WyswietlWsp() const { std::cout << "Wspolrzedne: " << _WspGlob << "\n"; }

  float Wsp_Xmin() const { return (_GrafWsp[2])[0]; }
  float Wsp_Ymin() const { return (_GrafWsp[2])[1]; }
  float Wsp_Xmax() const { return (_GrafWsp[0])[0]; }
  float Wsp_Ymax() const { return (_GrafWsp[0])[1]; }
};


#endif
