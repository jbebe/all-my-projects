/**
 *  \file nand.h
 *  NAND osztály deklarációja
 */
#ifndef NAND_H
#define NAND_H
 
#include "obj.h"
/**
 * NAND Kapu.
 * NAND kapu mûködését megvalósító osztály
 * Három lába van:
 *    0,1 - bemenetek
 *      2 - kimenet
 */
class NAND :public Obj {
protected:
    Message veg[3];                         ///< három vége van
public:
    /// Ez a default konstruktor is
    /// @param n - objektum neve (alapértelmezése "")
    NAND(const char *n = "") : Obj(n, 3) {}       // létrehoz egy 3 végû objektumot

    /// Adott láb állapotának lekérdezése
    const Message& get(Pin n) {
                        return(veg[n%3]);}  ///< be/kimenet lekérdezése (bemenet is lekérdezhetõ,
                                            ///< debug célokra)

    /// Mûködést megvalósító virtuális függvény.
    /// A beérkezõ üzenet és a saját állapota alapján ki kell számítania a választ.
    /// @param k   - kapcsolódási pontra üzenet érkezett
    /// @param msg - beérkezõ üzenet
    void set(Pin n, Message msg);           ///< mûködést megvalósító függvény
};

#endif // NAND_H
