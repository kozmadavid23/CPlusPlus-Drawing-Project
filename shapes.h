#ifndef SHAPES_H
#define SHAPES_H

#include "drawable.h"
#include "smartcanvas.h"

class point : public drawable {
public:
    // A draw metódus felülírása, amely egyetlen pontot rajzol a vászonra a kurzor pozícióján.
  virtual smartcanvas & draw(smartcanvas & c) const {
    c(c.cursor().position.x, c.cursor().position.y) = c.cursor().color; // A kurzor pozíciójában lévõ pixelt a kurzor színére állítja.
    return c;
  }
};


class rectangle : public drawable {
private:
  smartcanvas::size_type w;
  smartcanvas::size_type h;
public:
// A konstruktor alapértelmezett módon nem elérhetõ, hogy a szélességet és magasságot explicit módon kelljen megadni.
  rectangle() = delete;
// Konstruktor, amely beállítja a téglalap szélességét és magasságát.
  rectangle(smartcanvas::size_type width, smartcanvas::size_type height) : w(width), h(height) {
  }
// A draw metódus felülírása, amely egy téglalapot rajzol a vászonra a kurzor pozíciójától kezdve.
  virtual smartcanvas & draw(smartcanvas & c) const {
    auto ox    = c.cursor().position.x; // A kezdõ x koordináta (a kurzor pozíciója).
    auto oy    = c.cursor().position.y; // A kezdõ y koordináta (a kurzor pozíciója)
    auto color = c.cursor().color;      // A kurzor színe, amit a téglalap vonalainak rajzolására használunk.

// A téglalap felsõ és alsó sorának rajzolása.
    for (smartcanvas::size_type x = 0; x < w; ++x) {
      c(ox+x, oy    ) = color; // A téglalap felsõ vonalát rajzolja.
      c(ox+x, oy+h-1) = color; // A téglalap alsó vonalát rajzolja.
    }
// A téglalap bal és jobb oldali vonalának rajzolása.
    for (smartcanvas::size_type y = 0; y < h; ++y) {
      c(ox,     oy+y) = color; // A téglalap bal oldali vonalát rajzolja.
      c(ox+w-1, oy+y) = color; // A téglalap jobb oldali vonalát rajzolja.
    }
    return c;
  }
};

#endif
