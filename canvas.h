#ifndef CANVAS_H
#define CANVAS_H

#include "rgbmatrix.h"


// A canvas osztály örökli az rgbmatrix osztályt, így egy színes kétdimenziós mátrixot reprezentál.
class canvas : public rgbmatrix {

public:

// A színkomponens típusa (pl. int vagy más típus, ami a színértékeket tárolja).
  typedef value_type::value_type color_component_type;

private:

  color_component_type maxcv; // A színértékek maximális komponens értéke (pl. 255, ha RGB színrendszerrõl van szó).
  mutable value_type   dummy; // Dummy változó, amelyet akkor használunk, ha az adott koordinátán kívül esõ pixelhez próbálunk hozzáférni.

// A 'visible' függvény ellenõrzi, hogy egy adott (x, y) koordináta a mátrixban van-e, azaz látható-e.
  bool visible(size_type x, size_type y) const {
    return x >= 0 and x < width() and y >= 0 and y < height();
  }

public:

// Alapértelmezett konstruktor törölve, nem használható.
  canvas() = delete;

// Paraméterezett konstruktor: a szélesség, magasság és a maximális színérték alapján hoz létre egy canvas objektumot.
  canvas(size_type width, size_type height, color_component_type maxColorComponentValue) :
  rgbmatrix(width, height), maxcv(maxColorComponentValue) {
  }

// (x, y) koordinátájú elem elérése (nem konstans változat).
// Ha a koordináta kívül esik a mátrixon, akkor a dummy értéket adja vissza.
  value_type & operator () (size_type x, size_type y) {
    return visible(x,y) ? rgbmatrix::operator()(x,y) : dummy; // Ha látható, akkor a megfelelõ színt adja vissza, különben a dummy-t.
  }

// (x, y) koordinátájú elem elérése (konstans változat).
  const value_type & operator () (size_type x, size_type y) const {
    return visible(x,y) ? rgbmatrix::operator()(x,y) : dummy;
  }

// A maximális színkomponens érték lekérdezése.
  color_component_type maxColorComponentValue() const {
    return maxcv;
  }
};

// A canvas osztály kiírása PPM formátumban. A P3 formátumot használja a képek tárolásához.
inline std::ostream & operator << (std::ostream & s, const canvas c) {
// P3 formátumban kiírjuk a mátrixot, ami tartalmazza a szélességet, magasságot, a maximális színértéket és a színeket.
  return s
  << "P3\n"
  << c.width() << ' ' << c.height() << '\n'
  << c.maxColorComponentValue() << '\n'
  << dynamic_cast<const rgbmatrix &>(c); // Az rgbmatrix osztálytól örökölt színek kiírása.
}


// A canvas osztály beolvasása PPM formátumban.
inline std::istream & operator >> (std::istream & s, canvas & c) {
// Beolvasás P3 formátumban.

  char magicP, magic3; // Az elsõ két karakter (P3) ellenõrzésére.

  s.get(magicP);
  s.get(magic3);

// Ha nem P3 formátum, akkor hiba állapotot állítunk be és visszatérünk.
  if (magicP != 'P' or magic3 != '3') {
    s.setstate(std::ios::failbit);
    return s;
  }

  canvas::size_type            w, h;
  canvas::color_component_type maxcv;

  s >> w >> h >> maxcv;

  if (!s) { return s; } // Ha hiba történt, térjünk vissza.

// Létrehozzuk a canvas objektumot a beolvasott adatok alapján.
  c = canvas(w, h, maxcv);

// A szinek beolvasása. Az rgbmatrix osztály beolvasása.
  return s >> dynamic_cast<rgbmatrix &>(c);
}

#endif
