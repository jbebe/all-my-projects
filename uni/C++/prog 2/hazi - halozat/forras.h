/**
 *  \file forras.h
 *  Forras oszt�ly deklar�ci�ja
 */
#ifndef FORRAS_H
#define FORRAS_H

#include "obj.h"

/**
 * Forr�s oszt�ly.
 * Jelforr�s
 *   Konstruktor 2. param�tere a jel �rt�ke
 */
class Forras :public Obj {
    Message veg[1];                         ///< egy v�ge van
    bool J;                                 ///
public:
    /// Ez a default konstruktor is
    /// @param n - objektum neve (alap�rtelmez�se "")
    /// @param j - jel (alap�rtelmez�se true); lehetne 0 forr�s is
    Forras(const char *n = "", bool j = true) : Obj(n, 1), J(j) {} // l�trehoz egy 1 v�g� objektumot

    /// Forr�s "bekapcsol�sa"
    /// A kezdeti "r�g�st" a forr�sok adj�k
    void init() { uzen(0, Message(Message::jel, J)); }

    /// M�k�d�st megval�s�t� f�ggv�ny
    /// Ha �zenet �rkezik, akkor az �zenett�l f�ggetlen�l kiadjuk a forr�s a jel�t
    void set(Pin n, Message msg) {  uzen(0, Message(Message::jel, J)); }
};

#endif // FORRAS_H
