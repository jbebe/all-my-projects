/**
 *  \file drot.cpp
 *  Drot osztály tagfüggvényinek megvalósítása
 */
#include "drot.h"

void Drot::set(Pin n, Message msg) {
    if (veg[n] != msg) {                    // ha változott
        veg[n] = msg;                       // megjegyezzük, és
        uzen(n^1, msg);                     // elküldjük a másik végére
    }
}

