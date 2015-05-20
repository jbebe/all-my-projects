/**
 *  \file conn.h
 *  Conn osztály deklarációja
 */
#ifndef CONN_H
#define CONN_H

typedef unsigned int Pin;
class Obj;

/**
 * Összekötésért felelõs objektum
 */
class Conn {
    Obj    *obj;                            ///< ezen objektumhoz kapcsolódik
    Pin n;                                  ///< erre a pontjára
public:
    Conn() :obj(NULL) {}                    ///< Kell a default konstruktor. Nem kapcsolódik sehova
    /// Kapcsolat létrehozása
    /// @param k - o (idegen) objektumnak ehhez a ponthához kapcsolódunk
    /// @param o - objektum amihez kapcsolódunk
    void setConn(Pin k, Obj &o) { n = k; obj = &o; }

    /// Kapcsolat lekérdzése
    /// @param k - o (idegen) objektumnak ehhez a ponthához kapcsolódunk
    /// @return objektum amihez kapcsolódik
    Obj *getConn(Pin &k) const { k = n; return(obj); }
};

#endif // CONN_H
