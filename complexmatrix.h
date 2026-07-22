#ifndef COMPLEXMATRIX_H
#define COMPLEXMATRIX_H

#include <iostream>
#include <vector>
#include <complex>

class complexmatrix {

public:

  typedef int                            size_type;
  typedef std::complex<double>          value_type;
  typedef std::vector<value_type>        container;
  typedef container::iterator             iterator;
  typedef container::const_iterator const_iterator;

private:

  size_type w;
  size_type h;
  container m;

public:

  complexmatrix() = delete;

  complexmatrix(size_type width, size_type height) : w(width), h(height), m(width*height) {
  }

// Másoló konstruktor alapértelmezett implementációval.
  complexmatrix(const complexmatrix & orig) = default;

  ~complexmatrix() = default;

  complexmatrix & operator = (const complexmatrix & other) = default;

// A (x, y) koordinátájú mátrixelem módosítása:
  value_type & operator () (size_type x, size_type y) {
    return m[y*w+x]; // A vektorban az (x,y) indexelt elem elérése.
  }

// A (x, y) koordinátájú mátrixelem konstans módosítása:
  const value_type & operator () (size_type x, size_type y) const {
    return m[y*w+x];
  }


  size_type width() const {
    return w;
  }

  size_type height() const {
    return h;
  }


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

// Az operátor túlterhelése a mátrix kimenetének kiírására.
// Az összes elem kiírása.
inline std::ostream & operator << (std::ostream & s, const complexmatrix & mat) {
  for (auto & item : mat) {
    s << ' ' << item; // Minden elem kiírása egy szóközzel elválasztva.
  }
  return s;
}

// Az operátor túlterhelése a mátrix bemeneti adatainak beolvasására.
// Minden elem beolvasása a bemeneti stream-bõl.
inline std::istream & operator >> (std::istream & s, complexmatrix & mat) {
  for (auto & item : mat) {
    s >> item; // Minden elem beolvasása.
  }
  return s;
}

#endif
