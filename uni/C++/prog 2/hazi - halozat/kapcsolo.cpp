/**
 *  \file kapcsolo.cpp
 *  Kapcsolo osztály tagfüggvényinek megvalósítása
 */
 #include "kapcsolo.h"

void Kapcsolo::set(Pin n, Message msg) {
    if (on)                                 // ha be van kapcsolva, akkor drótként viselkedik
        Drot::set(n, msg);                  // hivja a Drot mûködtetõ függvényét
    else
        veg[n] = msg;                       // egyebként csak megjegyzi a bejövõ jelet
}

/// Kikapcsolás
/// 0 jelet üzen mindkét végére
void Kapcsolo::ki() {
        on = false ;
        uzen(0, Message(Message::jel)); // 0-t üzen midkét végére
        uzen(1, Message(Message::jel));
}

/// Bekapcsolás
/// Drótként viselkedik
void Kapcsolo::be() {
        on = true;
        uzen(0, veg[1]);
        uzen(1, veg[0]);
}
