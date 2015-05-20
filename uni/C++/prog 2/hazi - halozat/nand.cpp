/**
 *  \file nand.cpp
 *  NAND oszt�ly tagf�ggv�nyinek megval�s�t�sa
 */
#include "nand.h"

void NAND::set(Pin n, Message msg) {
    if (n != 2 && veg[n] != msg) {          // ha az input �s v�ltozott,
        veg[n] = msg;                       // akkor eltessz�k
        uzen(2, veg[2] = Message(Message::jel, // el��ll�tjuk a kimenetet, �s
           !(veg[0].J * veg[1].J), msg.c)); // elk�ldj�k a kimenetre azonos iter�ci�s sz�mmal
    }
}

