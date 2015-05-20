/**
 *  \file obj.cpp
 *  Obj osztály tagfüggvényinek megvalósítása
 */

#ifdef _MSC_VER
// MSC ne adjon figyelmeztetõ üzenetet a stringkezelõ függvényekre.
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "obj.h"

void Obj::setConn(Pin k, Obj &o, Pin ok) {
    if (k >= nk || ok >= o.nk)
        throw "Conn hiba!";                 // hiba, nincs ilyen végpont

    konn[k].setConn(ok, o);                 // kapcsolat beálítása
    o.konn[ok].setConn(k, *this);           // a kapcsolat reflektív a drót tulajdonságai miatt
}

void Obj::uzen(Pin k, Message msg) {
    Pin n;                                  // ide kerül a kapcsolódó obj kapcsolatsorszáma
    if (k >= nk)
        throw "Uzenet hiba";                // hiba, nincs ilyen végpont
    if (Obj *o = konn[k].getConn(n)) {
#ifdef  DEBUG
        std::cout << "Uzenet:" << o->nev << ":" << n << ":" << msg.J << '\n';
#endif
        o->set(n, --msg);                   // szomszéd mûködtetõ függvénye
    }
}

