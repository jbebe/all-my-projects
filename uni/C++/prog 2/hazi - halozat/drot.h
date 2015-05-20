/**
 *  \file drot.h
 *  Drot oszt�ly deklar�ci�ja
 */
#ifndef DROT_H
#define DROT_H

#include "obj.h"
/**
 * Dr�t oszt�ly.
 *   A k�t v�gpontja k�z�tt vezet
 *   A v�gpontok protected v�delemmel vannak, hogy haszn�lhat� legyen
 *   egy esetleges sz�rmaztat�sn�l (kapcsol�)
 */
class Drot :public Obj {
protected:                                  // v�delel enyh�t�se
    Message veg[2];                         ///< k�t v�ge van
public:
    /// Ez a default konstruktor is
    /// @param n - objektum neve (alap�rtelmez�se "")
    Drot(const char *n = "") : Obj(n, 2) {}       // l�trehoz egy 2 v�g� objektumot

    /// Allapot lek�rdez�se
    /// k�t v�gen lev� jel �sszeg�t adja
    const Message get() { return(veg[0]+veg[1]);}

    /// M�k�d�st megval�s�t� virtu�lis f�ggv�ny.
    /// A be�rkez� �zenet �s a saj�t �llapota alapj�n ki kell sz�m�tania a v�laszt.
    /// @param k   - kapcsol�d�si pontra �zenet �rkezett
    /// @param msg - be�rkez� �zenet
    void set(Pin n, Message msg);           ///< m�k�d�st megval�s�t� f�ggv�ny
};

#endif // DROT_H
