/**
 *  \file r_s_ff.cpp
 *  R_S_FF oszt�ly tagf�ggv�nyinek megval�s�t�sa
 */
#include "r_s_ff.h"

void R_S_FF::set(Pin n, Message msg) {
    if (n < 2 && veg[n] != msg) {           // ha input �s v�ltozott
        veg[n] = msg;                       // megjegyezi �s a
        N[n].set(1, msg);                   // megfelel� bemenetre k�ldi
        uzen(2, veg[2] = N[0].get(2));      // kimenetek sz�tk�ld�se
        uzen(3, veg[3] = N[1].get(2));      // kimenetek sz�tk�ld�se
    }
}

