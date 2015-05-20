/**
 *  \file drot.h
 *  Drot osztály deklarációja
 */
#ifndef DROT_H
#define DROT_H

#include "obj.h"
/**
 * Drót osztály.
 *   A két végpontja között vezet
 *   A végpontok protected védelemmel vannak, hogy használható legyen
 *   egy esetleges származtatásnál (kapcsoló)
 */
class Drot :public Obj {
protected:                                  // védelel enyhítése
    Message veg[2];                         ///< két vége van
public:
    /// Ez a default konstruktor is
    /// @param n - objektum neve (alapértelmezése "")
    Drot(const char *n = "") : Obj(n, 2) {}       // létrehoz egy 2 végû objektumot

    /// Allapot lekérdezése
    /// két végen levõ jel összegét adja
    const Message get() { return(veg[0]+veg[1]);}

    /// Mûködést megvalósító virtuális függvény.
    /// A beérkezõ üzenet és a saját állapota alapján ki kell számítania a választ.
    /// @param k   - kapcsolódási pontra üzenet érkezett
    /// @param msg - beérkezõ üzenet
    void set(Pin n, Message msg);           ///< mûködést megvalósító függvény
};

#endif // DROT_H
