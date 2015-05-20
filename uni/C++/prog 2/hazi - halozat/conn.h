/**
 *  \file conn.h
 *  Conn oszt�ly deklar�ci�ja
 */
#ifndef CONN_H
#define CONN_H

typedef unsigned int Pin;
class Obj;

/**
 * �sszek�t�s�rt felel�s objektum
 */
class Conn {
    Obj    *obj;                            ///< ezen objektumhoz kapcsol�dik
    Pin n;                                  ///< erre a pontj�ra
public:
    Conn() :obj(NULL) {}                    ///< Kell a default konstruktor. Nem kapcsol�dik sehova
    /// Kapcsolat l�trehoz�sa
    /// @param k - o (idegen) objektumnak ehhez a ponth�hoz kapcsol�dunk
    /// @param o - objektum amihez kapcsol�dunk
    void setConn(Pin k, Obj &o) { n = k; obj = &o; }

    /// Kapcsolat lek�rdz�se
    /// @param k - o (idegen) objektumnak ehhez a ponth�hoz kapcsol�dunk
    /// @return objektum amihez kapcsol�dik
    Obj *getConn(Pin &k) const { k = n; return(obj); }
};

#endif // CONN_H
