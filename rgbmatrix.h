#ifndef RGBMATRIX_H
#define RGBMATRIX_H

#include <iostream>
#include <vector>
#include "rgb.h"

class rgbmatrix {

public:

  typedef int                            size_type;
  typedef rgb                           value_type;
  typedef std::vector<value_type>        container; // A színmátrix tárolásához használt konténer (std::vector).
  typedef container::iterator             iterator; // Iterátor a mátrix elemzéséhez.
  typedef container::const_iterator const_iterator; // Konstans iterátor, ha nem szeretnénk módosítani az elemeket.

private:

  size_type w;
  size_type h;
  container m;

public:

  rgbmatrix() = delete;

  // Paraméterezett konstruktor: a kívánt méret alapján hoz létre egy üres színes mátrixot.
  rgbmatrix(size_type width, size_type height) : w(width), h(height), m(width*height) {
  }

  rgbmatrix(const rgbmatrix & orig) = default;

  ~rgbmatrix() = default;

  rgbmatrix & operator = (const rgbmatrix & other) = default;

// (x, y) koordinátájú elem módosítása: a megfelelõ elem módosítása a mátrixban.
  value_type & operator () (size_type x, size_type y) {
    return m[y*w+x];
  }

// (x, y) koordinátájú elem lekérdezése: a megfelelõ elem visszaadása, ha nem módosítható.
  const value_type & operator () (size_type x, size_type y) const {
    return m[y*w+x];
  }

// A mátrix szélességének lekérdezése.
  size_type width() const {
    return w;
  }

// A mátrix magasságának lekérdezése.
  size_type height() const {
    return h;
  }

// Iterátorok a mátrix elemeinek eléréséhez (nem konstans és konstans verziók):
  iterator begin() {
    return m.begin();
  }

  iterator end() {
    return m.end();
  }

  const_iterator begin() const {
    return m.begin();
  }

  const_iterator end() const {
    return m.end();
  }
};

// A rgbmatrix osztály kiírása: minden szín kiírása egy sorban (PPM formátumban).
inline std::ostream & operator << (std::ostream & s, const rgbmatrix & mat) {
  for (auto & color : mat) {
    s << ' ' << color;
  }
  return s;
}

// A rgbmatrix osztály beolvasása: minden szín beolvasása stream-bõl.
inline std::istream & operator >> (std::istream & s, rgbmatrix & mat) {
  for (auto & color : mat) {
    s >> color;
  }
  return s;
}

#endif
