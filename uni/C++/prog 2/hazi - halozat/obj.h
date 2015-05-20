/**
 *  \file obj.h
 *  Obj osztály deklarációja
 */
#ifndef OBJ_H
#define OBJ_H

#ifdef _MSC_VER
// MSC ne adjon figyelmeztetõ üzenetet a stringkezelõ függvényekre.
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstring>
#include "message.h"
#include "conn.h"

/**
 * Alapobjektum.
 * Absztrakt objektum a további osztályok származtatásához.
 * Konstruktor paramétere, hogy hány kapcsolódási pontja van.
 * Értékadás és a másoló konstruktor levédve, mert nincs értelme.
 */
class Obj {
    char nev[10];                           ///< objektum neve
    Pin  nk;                                ///< kapcsolódási pontok száma
    Conn *konn;                             ///< kapcsolatok leírása
    Obj(const Obj&);                        ///< hogy ne lehessen használni
    Obj& operator=(const Obj&);             ///< hogy ne lehessen használni
public:
    /// Nincs default konstruktor
    /// @param n - objektum neve
    /// @param k - kapcsolodási pontok (lábak) száma
    Obj(const char *n, Pin k) {
        setNev(n);
        konn = new Conn[nk = k];
    }
    /// Destruktor
    virtual ~Obj() { delete[] konn; }       ///< felszbaditj a konn tömböt

    /// Név beállítása
    /// @param n - objektum neve
    void setNev(const char *n) { strcpy(nev, n); }

    /// Kapcsolatok felépítése (minden kapcsolat reflektív)
    /// @param k  - kapcsolat saját oldali pontja
    /// @param o  - o objektumgoz kapcsolódunk
    /// @param ok - o objektum ezen pontjához
    /// Hiba esetén "Conn hiba" kivételt dob
    void setConn(Pin k, Obj &o, Pin ok);    // kapcsolatok felépításe

    /// Uzenet küldése egy kapcsolatra
    /// @param k   - kapcsolat saját oldali pontja
    /// @param msg - üzenet
    void uzen(Pin k, Message msg);          // üzen a szomszédnak

    /// Mûködést megvalósító virtuális függvény.
    /// A beérkezõ üzenet és a saját állapota alapján ki kell számítania a választ.
    /// @param k   - kapcsolódási pontra üzenet érkezett
    /// @param msg - beérkezõ üzenet
    virtual void set(Pin k, Message msg) = 0;
};

#endif // OBJ_H
