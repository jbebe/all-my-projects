/**
 *  \file nand.cpp
 *  NAND osztály tagfüggvényinek megvalósítása
 */
#include "nand.h"

void NAND::set(Pin n, Message msg) {
    if (n != 2 && veg[n] != msg) {          // ha az input és változott,
        veg[n] = msg;                       // akkor eltesszük
        uzen(2, veg[2] = Message(Message::jel, // elõállítjuk a kimenetet, és
           !(veg[0].J * veg[1].J), msg.c)); // elküldjük a kimenetre azonos iterációs számmal
    }
}

