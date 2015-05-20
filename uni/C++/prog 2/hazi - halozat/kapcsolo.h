/**
 *  \file kapcsolo.h
 *  Kapcsoló osztály deklarációja
 */
#ifndef KAPCSOLO_H
#define KAPCSOLO_H

#include "obj.h"
#include "callback.h"
#include "drot.h"

/**
 * Kapcsoló osztály.
 * Drot-ból és Callback-ból származtatott osztály
 * Bekapcsolt állapotban Drot-ként viselkedik
 * Kikapcsoláskor mindkét végére 0 jelszintet üzen
 * Precizebb lenne nem definiált állapotot üzenni, de ezt az állapotot
 * nem kezeli a többi elem.
 */
class Kapcsolo : public Drot, public Callback { // Drótból
    bool on;                                ///< állapot
public:
    /// Ez a default konstruktor is
    /// @param n - objektum neve (alapértelmezése "")
    Kapcsolo(const char *n = "") : Drot(n), on(false) {}  // létrehozza a Drótot, és kikapcsol

    void set(Pin n, Message msg);           ///< mûködést megvalósító függvény

    /// Kikapcsolás
    /// 0 jelet üzen mindkét végére
    void ki();

    /// Bekapcsolás
    /// Drótként viselkedik
    void be();

    /// Callback függvény
    /// Ki állapotból bekapcsol, Be állapotból kikapcsol
    void callback() { if (on) ki(); else be(); } // callback
};

#endif // KAPCSOLO_H
