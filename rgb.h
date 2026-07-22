#ifndef RGB_H
#define RGB_H

#include <iostream>

class rgb {

public:

  typedef int value_type;

private:

  value_type r;
  value_type g;
  value_type b;

public:

// Alapértelmezett konstruktor: a színek alapértelmezetten fekete (0, 0, 0).
  rgb() : r(0), g(0), b(0) {
  }

// Konstruktor, amely három paramétert vár: piros, zöld és kék színértékek.
  rgb(value_type red, value_type green, value_type blue) : r(red), g(green), b(blue) {
  }

// Másoló konstruktor: egy meglévõ rgb objektum másolata.
  rgb(const rgb & orig) : r(orig.r), g(orig.g), b(orig.b) {
  }

  ~rgb() {
  }

  // Másoló operátor: az aktuális objektumot egy másik rgb objektummal helyettesíti.
  rgb & operator = (const rgb & other) {
    r = other.r;
    g = other.g;
    b = other.b;
    return *this;
  }


   //A piroshoz:
  // getter
  value_type red() const {
    return r;
  }

  // setter
  void red(value_type value) {
    r = value;
  }

  //A zoldhoz
  // getter
  value_type green() const {
    return g;
  }

  // setter
  void green(value_type value) {
    g = value;
  }

   //A kekhez
  // getter
  value_type blue() const {
    return b;
  }

  // setter
  void blue(value_type value) {
    b = value;
  }

  // Statikus metódus, amely egy szürke árnyalatú színt állít elõ
  // Minden színkomponens ugyanaz, így szürke árnyalatot kapunk.
  static rgb gray(int shade) {
    return rgb(shade, shade, shade);
  }
};

// Az rgb osztály bemeneti operátora: színadatok beolvasása stream-bõl
inline std::ostream & operator << (std::ostream & s, const rgb & color) {
  return s << color.red() << ' ' << color.green() << ' ' << color.blue();
}

inline std::istream & operator >> (std::istream & s, rgb & color) {
  rgb::value_type r, g, b;
  s >> r >> g >> b; // A három színkomponenst beolvassuk
  if (s) {
    color = rgb(r,g,b); // Létrehozzuk az rgb objektumot a beolvasott értékekkel
  }
  return s;
}

#endif
