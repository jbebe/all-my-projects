/**
 *  \file forras.h
 *  Forras osztály deklarációja
 */
#ifndef FORRAS_H
#define FORRAS_H

#include "obj.h"

/**
 * Forrás osztály.
 * Jelforrás
 *   Konstruktor 2. paramétere a jel értéke
 */
class Forras :public Obj {
    Message veg[1];                         ///< egy vége van
    bool J;                                 ///
public:
    /// Ez a default konstruktor is
    /// @param n - objektum neve (alapértelmezése "")
    /// @param j - jel (alapértelmezése true); lehetne 0 forrás is
    Forras(const char *n = "", bool j = true) : Obj(n, 1), J(j) {} // létrehoz egy 1 végû objektumot

    /// Forrás "bekapcsolása"
    /// A kezdeti "rúgást" a források adják
    void init() { uzen(0, Message(Message::jel, J)); }

    /// Mûködést megvalósító függvény
    /// Ha üzenet érkezik, akkor az üzenettõl függetlenül kiadjuk a forrás a jelét
    void set(Pin n, Message msg) {  uzen(0, Message(Message::jel, J)); }
};

#endif // FORRAS_H
