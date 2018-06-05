#ifndef MACIERZ2X2_HH
#define MACIERZ2X2_HH


#include <iostream>
#include "Wektor2D.hh"

/*!
 * \file Macierz2x2.hh
 * Plik przedstawia klase macierz oraz jej metody.
 */

/*!
 * \brief 
 * Klasa jest macierza 2x2 stworzona z wektorow2D. 
 */
class Macierz2x2 {
  
  Wektor2D _Kolumna[2];  //!< Wektory tworz±ce macierz 
  
public:
  Macierz2x2(){ _Kolumna[0][0] = 1; _Kolumna[1][1] = 1; }

  /*!
   * \brief Metoda wykonuje operacje mnozenia macierzy przez wektor.
   * \param const Wektor2D& 
   * \return Wektor2D
   */
  Wektor2D operator*(const Wektor2D&) const;
  /*!
   * \brief W macierz dla ktorej wywolywana jest metoda wpisywane sa 
   * wartosci dzieki ktorym mnozac przez nia wektor ze wspolrzednymi punktu
   * otrzymujemy punkt obrocony o dany kat wzgledem srodka ukladu
   * \param float wskazuje o ile stopni chcemy obracac punkt
   */
  Macierz2x2 MacierzObrotu(float); 
  /*!
   * \brief Obie metody sluza do sprawnego odwolywania sie do okreslonej 
   * kolumny i wiersza w macierzy.
   */
  const float& operator()(int x, int y)const{ return (_Kolumna[x])[y]; }
        float& operator()(int x, int y) {return (_Kolumna[x])[y]; }
  
};

/*!
 * \brief Operator dla latwiejszego wypisywania wartosci macierzy, korzystny
 * przy testach dzialania oraz moglby byc przydatny przy dalszym rozwoju
 * programu.
 * \param std::ostream& referencja na strumien wyjsciowy
 * \param const Macierz2x2& referencja na obiekt 
 * \return Zwraca referencje na strumien wyjscia
 */
std::ostream& operator << (std::ostream &Strm, const Macierz2x2 &Mac);

#endif
