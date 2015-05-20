/**
 *  \file csp.h
 *  Csp oszt�ly deklar�ci�ja
 */
#ifndef CSP_H
#define CSP_H

#include "obj.h"
/**
 * Csomopont oszt�ly.
 * 3 kpacsol�d�si pontja van
 * Az egyik ponton bej�v� jelet v�ltoztat�s n�lk�l kik�ldi a m�sik kett�re.
 */
class Csp :public Obj {
protected:
    Message veg[3];                         ///< h�rom v�ge van
public:
    /// Ez a default konstruktor is
    /// @param n - objektum neve (alap�rtelmez�se "")
    Csp(const char *n = "") : Obj(n, 3) {}        // l�trehoz egy 3 v�g� objektumot

    /// M�k�d�st megval�s�t� virtu�lis f�ggv�ny.
    /// A be�rkez� �zenet �s a saj�t �llapota alapj�n ki kell sz�m�tania a v�laszt.
    /// @param k   - kapcsol�d�si pontra �zenet �rkezett
    /// @param msg - be�rkez� �zenet
    void set(Pin n, Message msg);           ///< m�k�d�st megval�s�t� f�ggv�ny
};

#endif // CSP_H
