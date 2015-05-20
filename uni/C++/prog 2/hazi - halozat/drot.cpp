/**
 *  \file drot.cpp
 *  Drot oszt�ly tagf�ggv�nyinek megval�s�t�sa
 */
#include "drot.h"

void Drot::set(Pin n, Message msg) {
    if (veg[n] != msg) {                    // ha v�ltozott
        veg[n] = msg;                       // megjegyezz�k, �s
        uzen(n^1, msg);                     // elk�ldj�k a m�sik v�g�re
    }
}

