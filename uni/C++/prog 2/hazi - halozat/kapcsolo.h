/**
 *  \file kapcsolo.h
 *  Kapcsol� oszt�ly deklar�ci�ja
 */
#ifndef KAPCSOLO_H
#define KAPCSOLO_H

#include "obj.h"
#include "callback.h"
#include "drot.h"

/**
 * Kapcsol� oszt�ly.
 * Drot-b�l �s Callback-b�l sz�rmaztatott oszt�ly
 * Bekapcsolt �llapotban Drot-k�nt viselkedik
 * Kikapcsol�skor mindk�t v�g�re 0 jelszintet �zen
 * Precizebb lenne nem defini�lt �llapotot �zenni, de ezt az �llapotot
 * nem kezeli a t�bbi elem.
 */
class Kapcsolo : public Drot, public Callback { // Dr�tb�l
    bool on;                                ///< �llapot
public:
    /// Ez a default konstruktor is
    /// @param n - objektum neve (alap�rtelmez�se "")
    Kapcsolo(const char *n = "") : Drot(n), on(false) {}  // l�trehozza a Dr�tot, �s kikapcsol

    void set(Pin n, Message msg);           ///< m�k�d�st megval�s�t� f�ggv�ny

    /// Kikapcsol�s
    /// 0 jelet �zen mindk�t v�g�re
    void ki();

    /// Bekapcsol�s
    /// Dr�tk�nt viselkedik
    void be();

    /// Callback f�ggv�ny
    /// Ki �llapotb�l bekapcsol, Be �llapotb�l kikapcsol
    void callback() { if (on) ki(); else be(); } // callback
};

#endif // KAPCSOLO_H
