#ifndef SMARTCANVAS_H
#define SMARTCANVAS_H

#include "canvas.h"

class smartcanvas : public canvas {

public:

// A pozíció típus, amely a vászon (x, y) koordinátáit tárolja.
  struct position_type {
    size_type x;
    size_type y;
  };

// A kurzor típus, amely a pozíciót és a színt tárolja.
  struct cursor_type {
    position_type position;
    value_type    color;
  };

private:

  cursor_type curs;

public:

// Alapértelmezett konstruktor törölve, nem használható.
  smartcanvas() = delete;


// Paraméterezett konstruktor: a vászon szélességét, magasságát és a maximális színértéket adja meg.
// A kurzor alapértelmezett pozícióját (0,0) és színét az alapértelmezett szürke színre állítja.
  smartcanvas(size_type width, size_type height, color_component_type maxColorComponentValue) :
  canvas(width, height, maxColorComponentValue),
  curs{{0,0},value_type::gray(maxColorComponentValue)} {
  }

  smartcanvas(const smartcanvas &) = default;

  ~smartcanvas() = default;

// Az assignment operátor a smartcanvas osztály másolatának hozzárendeléséhez.
  smartcanvas & operator = (const smartcanvas &) = default;

// Getter és setter

  const cursor_type & cursor() const {
    return curs;
  }

  cursor_type & cursor() {
    return curs;
  }
};

#endif
