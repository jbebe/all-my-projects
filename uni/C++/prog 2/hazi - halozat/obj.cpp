/**
 *  \file obj.cpp
 *  Obj oszt�ly tagf�ggv�nyinek megval�s�t�sa
 */

#ifdef _MSC_VER
// MSC ne adjon figyelmeztet� �zenetet a stringkezel� f�ggv�nyekre.
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "obj.h"

void Obj::setConn(Pin k, Obj &o, Pin ok) {
    if (k >= nk || ok >= o.nk)
        throw "Conn hiba!";                 // hiba, nincs ilyen v�gpont

    konn[k].setConn(ok, o);                 // kapcsolat be�l�t�sa
    o.konn[ok].setConn(k, *this);           // a kapcsolat reflekt�v a dr�t tulajdons�gai miatt
}

void Obj::uzen(Pin k, Message msg) {
    Pin n;                                  // ide ker�l a kapcsol�d� obj kapcsolatsorsz�ma
    if (k >= nk)
        throw "Uzenet hiba";                // hiba, nincs ilyen v�gpont
    if (Obj *o = konn[k].getConn(n)) {
#ifdef  DEBUG
        std::cout << "Uzenet:" << o->nev << ":" << n << ":" << msg.J << '\n';
#endif
        o->set(n, --msg);                   // szomsz�d m�k�dtet� f�ggv�nye
    }
}

