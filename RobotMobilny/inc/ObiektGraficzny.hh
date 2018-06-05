#ifndef OBIEKTGRAFICZNY_HH
#define OBIEKTGRAFICZNY_HH

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "Wektor2D.hh"
#include "Macierz2x2.hh"

using namespace std;

/*!
 * \file ObiektGraficzny
 */

/*!
 * \brief RodzajObiektu
 * Mozliwe typy jakie rezprezentuje dany obiekt.
 */
enum RodzajObiektu{ SCIEZKA, ROBOT, PRZESZKODA };

/*!
 * \brief 
 * Klasa przedstawia podstawowe wartosci jakie musi posiadac obiekt rysowany
 * w GNU plocie.
 */
class ObiektGraficzny{

protected:
  vector<Wektor2D> _WspLok; //!< Kontener na wspolrzedne w ukladzie lokalnym
  vector<Wektor2D> _GrafWsp; //!< Kontener na wspolrzedne w ukladzie globalnym
  Wektor2D _WspGlob; //!< Wektor przesuniecia wzgledem punktu (0,0) ukladu globalnego

  float _Skala; //!< Skala podanego obiektu
  int _KatLok; //!< Kat wzgledem ukladu lokalnego
  int _KatGlob; //!< Kat wzgledem ukladu globalnego
  RodzajObiektu Rodzaj; //!< Rodzaj obiektu
  float _Promien; //!< Promien zderzenia obiektu
  
  
  static Wektor2D _WekTrans; //!< Wektor translacji wszystkich obiektow
  static int _IlObStworz;
  static int _IlObUsun;
public:
  /*! \brief
   *  Wypisz rodzaj obiektu.
   */
  RodzajObiektu JakiTyp() const { return Rodzaj; }

  /*! \brief
   *  Konstruktor ustala katy obiektu na zerowe.
   */
  ObiektGraficzny(): _Skala(0), _KatLok(0), _KatGlob(0){ ++_IlObStworz; }
  ObiektGraficzny(const ObiektGraficzny& ob){ (*this) = ob; ++_IlObStworz;}
  virtual ~ObiektGraficzny(){ ++_IlObUsun; }
  /*! \brief
   * Przeciazenie umozliwia odczyt wspolrzednych obiektu.
   */
  const Wektor2D operator[](int IND) const { return _GrafWsp[IND]; }

  /*!
   *  \brief 
   * Funkcja obrotu obiektu (w ukladzie lokalnym)
   */
  ObiektGraficzny Obrot(int);

  /*!
   * \brief 
   *  Zwraca ilosc wierzcholkow obiektu.
   */
  int Size() const { return _GrafWsp.size(); }

  /*!
   * \brief
   * Zapisuje informacje o wierzcholkach obiektu graficznego do strumienia
   * wyjsciowego.
   */
  void ZapisDoStrumienia( ostream& StrmWy ) const;

  /*!
   * \brief
   * Metoda zmienia polozenie wszystkich obiektow na scenie o wektor translacji
   * \param wektor translacji obiektow
   */
  static const Wektor2D ZmienTranslacje(Wektor2D _wek)
  {  return (_WekTrans += _wek);  }

  
  float ZmienSkale(float );
  float Wsp_X() const {  return _WspGlob[0];  }
  float Wsp_Y() const {  return _WspGlob[1];  }

  virtual float Wsp_Xmin() const {  return 0;  }
  virtual float Wsp_Ymin() const {  return 0;  }

  virtual float Wsp_Xmax() const {  return 0;  }
  virtual float Wsp_Ymax() const {  return 0;  }

  
  
  RodzajObiektu PodajTyp() const { return Rodzaj; } 
  
  /*!
   * \brief
   * Metoda odczytuje aktualna translacje obiektow na scenie.  
   */
  static const Wektor2D PodajTranslacje() 
                  {  return _WekTrans;  }

  /*  static void IloscObiektow(){
  std::cout << "Ilosc stworzonych obiektow klasy ObiektGraficzny: "
	    << _IlObStworz << "\n";
  std::cout << "Ilosc nieusunietych obiektow: "
	    << _IlObStworz-_IlObUsun << "\n";
	    }*/

  
  virtual void WyswietlWsp() const {}  
  virtual void Idz( int zwolnij = 0 ) {}
  virtual const Wektor2D ZmienKierunek(int kat) {return Wektor2D(0,0); }
  virtual const int Szybkosc() const {return 0;}
  virtual int UstawSzybkosc(int n_sz) { return 0; } 
  virtual void NastepnyKrok(const Wektor2D &wek) {} 
  virtual void Dodaj(const Wektor2D &wek){}
  virtual const Wektor2D centrum() const { return Wektor2D(0,0); }
  virtual void LiczPromien(){}
  virtual float Promien() const { return 0;}
};



#endif
