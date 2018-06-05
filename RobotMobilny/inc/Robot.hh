#ifndef ROBOT_HH
#define ROBOT_HH

#include "ObiektGraficzny.hh"
#include "Wektor2D.hh"
#include "Sciezka.hh"

/*!
 * \file Robot.hh
 * Klasa przedstawiajaca robota
 */


/*!
 * \brief 
 * Klasa Robot dziedziczy po klasie ObiektGraficzny
 */
class Robot
  : public ObiektGraficzny
{
  int _Szybkosc;  //!< Wartosc predkosci robota
  Wektor2D _Kierunek; //!< Jednostkowy wektor kierunkowy robota

public:
  /*!
   * \brief
   *  Konstruktor bezparametryczny, podczas tworzenia robota sa mu przypisywane
   * wartosci w ukladzie lokalnym jak i globalnym, a takze kierunek i predkosc.
   */
  Robot( Wektor2D, int );

  /*!
   * \brief 
   *  Metoda Idz() wykonuje ruch robota o zadany wektor kierunkowy  
   * \param jezeli dlugosc kroku jest wieksza od przesuniecia to przesuwa sie
   * o niepelny wektor przemieszczenia a o dlugosci podanej w parametrze
   */
  void Idz( int zwolnij = 0 );


  /*!
   * \brief 
   * Ustawia predkosc robota.
   */
  int UstawSzybkosc(int n_sz){ return (_Szybkosc = n_sz);}

  /*!
   * \brief
   * Zwraca szybkosc robota.
   */
  const int Szybkosc() const { return _Szybkosc; }

  /*!
   * \brief
   * Zmienia wektor kierunkowy robota o zadany kat.
   */
  const Wektor2D ZmienKierunek(int kat);

  /*!
   * \brief
   * Zwraca wektor na srodek robota.
   */
  const Wektor2D centrum() const{ return _WspGlob; }

  
  void WyswietlWsp() const
  { std::cout << "Wspolrzedne: " << centrum() << "\n"; }

  void LiczPromien()
  { _Promien = &(_WspLok[1]); }

  float Promien() const { return _Promien; }
  
};





#endif
