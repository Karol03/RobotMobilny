#ifndef WEKTOR2D_HH
#define WEKTOR2D_HH

#include <iostream>


/*!
 * \file Wektor2D.hh
 * Plik zawiera definicje klasy do realizacji wektora.
 */



/*!
 * \brief
 *
 * Klasa pokazuje rozwiazanie wektora o dwoch wymiarach
 * oraz pozwala na podstawowe operacje dla niego.
 */
class Wektor2D {
  float _Wsp[2];  //!< Obie wspolrzedne wektora. 
  static int _StworzWek;
  static int _IstnWek;
public:
  
  Wektor2D(float x = 0, float y = 0)
  { ++_StworzWek; ++_IstnWek; _Wsp[0] = x; _Wsp[1] = y; }

  Wektor2D(const Wektor2D& wek)
  { (*this) = wek; ++_IstnWek; ++_StworzWek; }
  
  ~Wektor2D(){--_IstnWek; }
  
  /*!
   *\brief Pozwala na dodawanie wektorow.
   *\param Wektor2D wektor ktory chcemy dodac
   */
  Wektor2D operator+(Wektor2D) const; 
  /*!
   *\brief Pozwala na dodawanie wektorow.
   */
  Wektor2D operator+=(Wektor2D wek)
  {    _Wsp[0] += wek[0];  _Wsp[1] += wek[1]; return (*this);   } 
  /*!
   *\brief
   * Pozwala na odejmowanie wektorow.
   *\param Wektor2D wektor ktory chcemy odjac
   */
  Wektor2D operator-(Wektor2D) const;
  /*!
   *\brief
   * Zwraca wektor przeciwny do podanego.
   */
  Wektor2D operator-() const;
  /*!
   *\brief
   * Wylicza i zwraca modul z wektora.
   */
  float operator&() const; 
  /*!
   *\brief
   * Metoda skaluje wektor przez pewien czynnik.
   */
  const Wektor2D operator*(float czynnik) const
  {
    Wektor2D _wektor( _Wsp[0]*czynnik, _Wsp[1]*czynnik );
    return _wektor;
  }
  /*!
   *\brief
   * Wyswietla liczbe stworzonych wektorow oraz obecnie uzywanych.
   */  
  static void Statystyka(){
    std::cout << "Stworzono: " << _StworzWek << " wektorow.\n";
    std::cout << "Aktualnie istnieje: " << _IstnWek << " wektorow.\n";}
  
  /*!
   *\brief
   * Pozwala na latwe poruszanie sie po wspolrzednych Wektora2D
   * w celu odczytania.
   */
  const float& operator[](int IND) const { return _Wsp[IND]; }

  /*!
   *\brief
   * Pozwala na latwe odwolanie sie do wspolrzednych Wektora2D
   * w celu wpisania wspolrzednej.
   */
  float& operator[](int IND) { return _Wsp[IND]; }
};

/*!
 *\brief
 * Wyswietlenie wspolrzednych wektora na standardowe wys¶cie.
 */
std::ostream& operator << (std::ostream &Strm, const Wektor2D &Wek);


#endif
