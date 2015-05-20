/**
 *  \file csp.h
 *  Csp osztály deklarációja
 */
#ifndef CSP_H
#define CSP_H

#include "obj.h"
/**
 * Csomopont osztály.
 * 3 kpacsolódási pontja van
 * Az egyik ponton bejövõ jelet változtatás nélkül kiküldi a másik kettõre.
 */
class Csp :public Obj {
protected:
    Message veg[3];                         ///< három vége van
public:
    /// Ez a default konstruktor is
    /// @param n - objektum neve (alapértelmezése "")
    Csp(const char *n = "") : Obj(n, 3) {}        // létrehoz egy 3 végû objektumot

    /// Mûködést megvalósító virtuális függvény.
    /// A beérkezõ üzenet és a saját állapota alapján ki kell számítania a választ.
    /// @param k   - kapcsolódási pontra üzenet érkezett
    /// @param msg - beérkezõ üzenet
    void set(Pin n, Message msg);           ///< mûködést megvalósító függvény
};

#endif // CSP_H
