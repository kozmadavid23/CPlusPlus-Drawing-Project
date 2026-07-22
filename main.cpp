#include <iostream>
#include <fstream>
#include "smartcanvas.h"
#include "canvasmanip.h"
#include "shapes.h"
#include "complexmatrix.h"
#include <cmath>


typedef complexmatrix::value_type complex;

int iter(complex c, int maxiter) {
  complex z = 0; // Kezdeti komplex szám (0 + 0i).
  for (int i = 0; i < maxiter; ++i) {
    z = z*z + c; // Mandelbrot iteráció (z = z*z + c).
    if (abs(z) > 2) {
      return i; // A szín intenzitása a kilépésnél szereplõ iteráció számával arányos.
    }
  }
  return maxiter; // Ha a max iterációkig nem történt kilépés, akkor visszaadjuk a maximális értéket.
}

int main() {
//complex bottomleft(-1.5, -0.5);
//complex topright(-1.0, 0.0);
  complex bottomleft(-2,-2); // Mandelbrot halmaz bal alsó sarkának komplex koordinátája.
  complex topright(2,2);     // Mandelbrot halmaz jobb felsõ sarkának komplex koordinátája.
  int resolution = 1000000;  // A felbontás, ami a képpontok számát jelenti.

// A kép szélességének és magasságának meghatározása a komplex sík dimenziói alapján.
  auto dr = topright.real()-bottomleft.real(); // A kép szélessége.
  auto di = topright.imag()-bottomleft.imag(); // A kép magassága.
  int W = sqrt(dr/di*resolution); // A szélesség pixelben
  int H = sqrt(di/dr*resolution); // A magasság pixelben.

  smartcanvas screen(W,H,255); // A képernyõ vászon létrehozása (W x H méret, 255 a maximális színérték).
  complexmatrix grid(W,H); // A komplex számok mátrixa (grid), amely a Mandelbrot halmaz pontjait tárolja.

  auto step_x = dr/W; // A komplex síkban az egyes képpontok közötti lépés a x irányban.
  auto step_y = di/W; // A komplex síkban az egyes képpontok közötti lépés az y irányban.

// A komplex számok kiszámítása a megfelelõ pozíciókhoz.
  for (int y = 0; y < H; ++y) {
    for (int x = 0; x < W; ++x) {
      grid(x,y) = complex(bottomleft.real() + x*step_x, bottomleft.imag() + (H-y-1)*step_y);
    }
  }


// A Mandelbrot halmaz képpontjainak színezése a számított iterációk alapján.

/*for (int y = 0; y < H; ++y) {
    for (int x = 0; x < W; ++x) {
        int iter_count = iter(grid(x, y), 255);
        screen(x, y) = rgb(iter_count % 256, (iter_count * 5) % 256, (iter_count * 10) % 256);
    }
}*/
  for (int y = 0; y < H; ++y) {
    for (int x = 0; x < W; ++x) {
      screen(x,y) = rgb::gray(iter(grid(x,y), 255));
    }
  }


  // A fájl megnyitása írásra
  std::ofstream file("mandelbrot.ppm");

  // Ellenorzes, hogy sikerült-e a fájl megnyitása
  if (!file) {
    std::cerr << "Hiba a fájl megnyitasakor!" << std::endl;
    return 1;
  }

  // Az operátor túlterhelés használata a kimenet fájlba írásához
  file << screen;  // A 'screen' változó itt a PPM formátumban kerül a fájlba.

  std::cout << "A kepet sikeresen elmentettuk mandelbrot.ppm neven." << std::endl;
  //std::cout << screen;
  return 0;
}
