#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "smartcanvas.h"

// Az absztrakt osztály, amely definiálja, hogy minden rajzolható objektumnak
// rendelkeznie kell egy 'draw' metódussal, ami rajzol egy smartcanvas-ra.
class drawable {
public:

// Tiszta virtuális metódus, amelyet a származtatott osztályoknak implementálniuk kell.
// A 'draw' metódus egy smartcanvas-t módosít.
  virtual smartcanvas & draw(smartcanvas &) const = 0;
};

// Kimeneti operátor túlterhelése a smartcanvas osztály számára, hogy rajzolhasson
// egy rajzolható objektumot a smartcanvas-ra.
inline smartcanvas & operator << (smartcanvas & c, const drawable & d) {
  return d.draw(c);
}

// Egy másik operátor túlterhelés, amely lehetõvé teszi manipulátorok alkalmazását
// a smartcanvas-ra, ha a manipulátorok egy smartcanvas-t módosítanak.
inline smartcanvas & operator << (smartcanvas & c, smartcanvas & (manipulator) (smartcanvas &)) {
  return manipulator(c); // Meghívja a manipulátor függvényt, amely módosítja a smartcanvas-t.
}

#endif
