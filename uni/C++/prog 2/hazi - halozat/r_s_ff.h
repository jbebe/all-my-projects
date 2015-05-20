/**
 *  \file r_s_ff.h
 *  R_S_FF osztály deklarációja
 */
#ifndef R_S_FF_H
#define R_S_FF_H

#include "nand.h"

/**
 * Inverz bemenetû S-R tároló.
 * Négy kapcsolódási pontja van:
 *   0 - S negált
 *   1 - R negált
 *   2 - Q
 *   3 - Q negált
 */
class R_S_FF :public Obj {
protected:
    Message veg[4];                         ///< négy vége van
    NAND N[2];                              ///< két kapu a megvalósításhoz
public:
    /// Ez a default konstruktor is
    /// @param n - objektum neve (alapértelmezése "")
    R_S_FF(const char *n = "") : Obj(n, 4) {      // létrehoz egy 4 végû objektumot
        N[0].setConn(2, N[1], 0);           // összekötések megvalósítása
        N[1].setConn(2, N[0], 0); }

    /// Adott láb állapotának lekérdezése
    void set(Pin n, Message msg);          ///< mûködést megvalósító függvény

    /// Mûködést megvalósító virtuális függvény.
    /// A beérkezõ üzenet és a saját állapota alapján ki kell számítania a választ.
    /// @param k   - kapcsolódási pontra üzenet érkezett
    /// @param msg - beérkezõ üzenet
    const Message& get(Pin n) {
                        return(veg[n%4]);}  ///< be/kimenet lekérdezése (bemenet is lekérdezhetõ,
                                            ///< debug célokra)
};

#endif // R_S_FF_H
