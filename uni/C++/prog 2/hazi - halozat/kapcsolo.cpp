/**
 *  \file kapcsolo.cpp
 *  Kapcsolo oszt�ly tagf�ggv�nyinek megval�s�t�sa
 */
 #include "kapcsolo.h"

void Kapcsolo::set(Pin n, Message msg) {
    if (on)                                 // ha be van kapcsolva, akkor dr�tk�nt viselkedik
        Drot::set(n, msg);                  // hivja a Drot m�k�dtet� f�ggv�ny�t
    else
        veg[n] = msg;                       // egyebk�nt csak megjegyzi a bej�v� jelet
}

/// Kikapcsol�s
/// 0 jelet �zen mindk�t v�g�re
void Kapcsolo::ki() {
        on = false ;
        uzen(0, Message(Message::jel)); // 0-t �zen midk�t v�g�re
        uzen(1, Message(Message::jel));
}

/// Bekapcsol�s
/// Dr�tk�nt viselkedik
void Kapcsolo::be() {
        on = true;
        uzen(0, veg[1]);
        uzen(1, veg[0]);
}
