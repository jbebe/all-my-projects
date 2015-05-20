/**
 *  \file csp.cpp
 *  Csp osztály tagfüggvényinek megvalósítása
 */
#include "csp.h"

void Csp::set(Pin n, Message msg) {
    if (veg[n] != msg) {                    // ha van változás,
        veg[n] = msg;                       // akkor megjegyzi és
        uzen((n+1)%3, msg);                 // továbbküldi,
        uzen((n+2)%3, msg);                 // továbbküldi
    }
}
