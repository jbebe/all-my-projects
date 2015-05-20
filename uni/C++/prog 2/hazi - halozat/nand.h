/**
 *  \file nand.h
 *  NAND oszt�ly deklar�ci�ja
 */
#ifndef NAND_H
#define NAND_H
 
#include "obj.h"
/**
 * NAND Kapu.
 * NAND kapu m�k�d�s�t megval�s�t� oszt�ly
 * H�rom l�ba van:
 *    0,1 - bemenetek
 *      2 - kimenet
 */
class NAND :public Obj {
protected:
    Message veg[3];                         ///< h�rom v�ge van
public:
    /// Ez a default konstruktor is
    /// @param n - objektum neve (alap�rtelmez�se "")
    NAND(const char *n = "") : Obj(n, 3) {}       // l�trehoz egy 3 v�g� objektumot

    /// Adott l�b �llapot�nak lek�rdez�se
    const Message& get(Pin n) {
                        return(veg[n%3]);}  ///< be/kimenet lek�rdez�se (bemenet is lek�rdezhet�,
                                            ///< debug c�lokra)

    /// M�k�d�st megval�s�t� virtu�lis f�ggv�ny.
    /// A be�rkez� �zenet �s a saj�t �llapota alapj�n ki kell sz�m�tania a v�laszt.
    /// @param k   - kapcsol�d�si pontra �zenet �rkezett
    /// @param msg - be�rkez� �zenet
    void set(Pin n, Message msg);           ///< m�k�d�st megval�s�t� f�ggv�ny
};

#endif // NAND_H
