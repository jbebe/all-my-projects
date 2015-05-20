/**
 *  \file r_s_ff.h
 *  R_S_FF oszt�ly deklar�ci�ja
 */
#ifndef R_S_FF_H
#define R_S_FF_H

#include "nand.h"

/**
 * Inverz bemenet� S-R t�rol�.
 * N�gy kapcsol�d�si pontja van:
 *   0 - S neg�lt
 *   1 - R neg�lt
 *   2 - Q
 *   3 - Q neg�lt
 */
class R_S_FF :public Obj {
protected:
    Message veg[4];                         ///< n�gy v�ge van
    NAND N[2];                              ///< k�t kapu a megval�s�t�shoz
public:
    /// Ez a default konstruktor is
    /// @param n - objektum neve (alap�rtelmez�se "")
    R_S_FF(const char *n = "") : Obj(n, 4) {      // l�trehoz egy 4 v�g� objektumot
        N[0].setConn(2, N[1], 0);           // �sszek�t�sek megval�s�t�sa
        N[1].setConn(2, N[0], 0); }

    /// Adott l�b �llapot�nak lek�rdez�se
    void set(Pin n, Message msg);          ///< m�k�d�st megval�s�t� f�ggv�ny

    /// M�k�d�st megval�s�t� virtu�lis f�ggv�ny.
    /// A be�rkez� �zenet �s a saj�t �llapota alapj�n ki kell sz�m�tania a v�laszt.
    /// @param k   - kapcsol�d�si pontra �zenet �rkezett
    /// @param msg - be�rkez� �zenet
    const Message& get(Pin n) {
                        return(veg[n%4]);}  ///< be/kimenet lek�rdez�se (bemenet is lek�rdezhet�,
                                            ///< debug c�lokra)
};

#endif // R_S_FF_H
