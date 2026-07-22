#ifndef CANVASMANIP_H
#define CANVASMANIP_H

#include "drawable.h"
#include "smartcanvas.h"

class clear : public drawable {
private:
// A háttér színe, amire a vásznat töröljük.
  smartcanvas::value_type color;
public:
// Törölt alapértelmezett konstruktor, a színt explicit módon kell megadni.
  clear() = delete;
// Konstruktor, amely beállítja a törléshez használt színt.
  explicit clear(const smartcanvas::value_type & clearColor) : color(clearColor) {
  }

// A draw metódus felülírása. A vászon összes pixelét a törléshez használt színnel tölti ki.
  virtual smartcanvas & draw(smartcanvas & c) const {
    for (auto & pixel : c) {
      pixel = color; // A vászon minden pixelét a megadott színnel állítja be.
    }
    return c; // A módosított vászont visszaadja.
  }
};

class setpos : public drawable {
private:
  smartcanvas::position_type pos; // A kurzor pozíciója (x, y).
public:
  setpos() = delete;

// Konstruktor, amely beállítja a kurzor pozícióját.
  explicit setpos(const smartcanvas::position_type & position) : pos(position) {
  }

// Konstruktor, amely közvetlenül a koordinátákat (x, y) adja meg.
  setpos(smartcanvas::size_type x, smartcanvas::size_type y) : pos{x,y} {
  }

// A draw metódus felülírása. A kurzor pozícióját a megadott értékre állítja be.
  virtual smartcanvas & draw(smartcanvas & c) const {
    c.cursor().position = pos; // A vászon kurzorának pozícióját a beállított pozícióra módosítja.
    return c; // A módosított vászont visszaadja.
  }
};

class setcolor : public drawable {
private:
  smartcanvas::value_type col; // A kurzor színe.
public:
  setcolor() = delete;
// Konstruktor, amely beállítja a kurzor színét.
  explicit setcolor(const smartcanvas::value_type & color) : col(color) {
  }
// A draw metódus felülírása. A kurzor színét a megadott színre állítja be.
  virtual smartcanvas & draw(smartcanvas & c) const {
    c.cursor().color = col;
    return c;
  }
};

#endif
