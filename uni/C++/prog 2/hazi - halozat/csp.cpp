/**
 *  \file csp.cpp
 *  Csp oszt�ly tagf�ggv�nyinek megval�s�t�sa
 */
#include "csp.h"

void Csp::set(Pin n, Message msg) {
    if (veg[n] != msg) {                    // ha van v�ltoz�s,
        veg[n] = msg;                       // akkor megjegyzi �s
        uzen((n+1)%3, msg);                 // tov�bbk�ldi,
        uzen((n+2)%3, msg);                 // tov�bbk�ldi
    }
}
