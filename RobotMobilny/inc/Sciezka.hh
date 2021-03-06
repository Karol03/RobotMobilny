#ifndef SCIEZKA_HH
#define SCIEZKA_HH

#include "ObiektGraficzny.hh"
#include "Wektor2D.hh"


/*!
 * \file Sciezka
 * Plik przedstawia klase sciezki
 */

/*!
 * \brief Sciezka
 *  Klasa dziedziczaca po klasie ObiektGraficzny.
 *  Przedstawia droge jaka pokonuje Robot.
 */
class Sciezka
  : public ObiektGraficzny
{

  int _dlugosc;
public:
  /*!
   * \brief Konstruktor ustawia poczatek rysowania sciezki
   * na punkt startu robota, oraz rodzaj rysowanego obiektu jako sciezke.
   */
  Sciezka(Wektor2D wek): _dlugosc(0)
  {_GrafWsp.push_back(wek);
    _GrafWsp.push_back(wek);
    Rodzaj = SCIEZKA;};
  
  /*!
   * \brief operator[]
   * Przeciazenie ulatwia wpisywanie nowych punktow ktore pokonuje robot
   * \param Wektor2D wek to nowe wspolrzedne robota
   */
  void NastepnyKrok(const Wektor2D &wek)
  { _GrafWsp.pop_back();
    _GrafWsp.push_back( wek ); }

  void Dodaj(const Wektor2D &wek){ _GrafWsp.push_back( wek ); }
  
  int DlugoscSciezki() const { return _dlugosc; }
  int ZmienDlugosc(int dlg){ return (_dlugosc += dlg); }
};


#endif
