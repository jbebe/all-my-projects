/**
 *  \file r_s_ff.cpp
 *  R_S_FF osztály tagfüggvényinek megvalósítása
 */
#include "r_s_ff.h"

void R_S_FF::set(Pin n, Message msg) {
    if (n < 2 && veg[n] != msg) {           // ha input és változott
        veg[n] = msg;                       // megjegyezi és a
        N[n].set(1, msg);                   // megfelelõ bemenetre küldi
        uzen(2, veg[2] = N[0].get(2));      // kimenetek szétküldése
        uzen(3, veg[3] = N[1].get(2));      // kimenetek szétküldése
    }
}

