/**
 *  \file obj.h
 *  Obj oszt�ly deklar�ci�ja
 */
#ifndef OBJ_H
#define OBJ_H

#ifdef _MSC_VER
// MSC ne adjon figyelmeztet� �zenetet a stringkezel� f�ggv�nyekre.
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstring>
#include "message.h"
#include "conn.h"

/**
 * Alapobjektum.
 * Absztrakt objektum a tov�bbi oszt�lyok sz�rmaztat�s�hoz.
 * Konstruktor param�tere, hogy h�ny kapcsol�d�si pontja van.
 * �rt�kad�s �s a m�sol� konstruktor lev�dve, mert nincs �rtelme.
 */
class Obj {
    char nev[10];                           ///< objektum neve
    Pin  nk;                                ///< kapcsol�d�si pontok sz�ma
    Conn *konn;                             ///< kapcsolatok le�r�sa
    Obj(const Obj&);                        ///< hogy ne lehessen haszn�lni
    Obj& operator=(const Obj&);             ///< hogy ne lehessen haszn�lni
public:
    /// Nincs default konstruktor
    /// @param n - objektum neve
    /// @param k - kapcsolod�si pontok (l�bak) sz�ma
    Obj(const char *n, Pin k) {
        setNev(n);
        konn = new Conn[nk = k];
    }
    /// Destruktor
    virtual ~Obj() { delete[] konn; }       ///< felszbaditj a konn t�mb�t

    /// N�v be�ll�t�sa
    /// @param n - objektum neve
    void setNev(const char *n) { strcpy(nev, n); }

    /// Kapcsolatok fel�p�t�se (minden kapcsolat reflekt�v)
    /// @param k  - kapcsolat saj�t oldali pontja
    /// @param o  - o objektumgoz kapcsol�dunk
    /// @param ok - o objektum ezen pontj�hoz
    /// Hiba eset�n "Conn hiba" kiv�telt dob
    void setConn(Pin k, Obj &o, Pin ok);    // kapcsolatok fel�p�t�se

    /// Uzenet k�ld�se egy kapcsolatra
    /// @param k   - kapcsolat saj�t oldali pontja
    /// @param msg - �zenet
    void uzen(Pin k, Message msg);          // �zen a szomsz�dnak

    /// M�k�d�st megval�s�t� virtu�lis f�ggv�ny.
    /// A be�rkez� �zenet �s a saj�t �llapota alapj�n ki kell sz�m�tania a v�laszt.
    /// @param k   - kapcsol�d�si pontra �zenet �rkezett
    /// @param msg - be�rkez� �zenet
    virtual void set(Pin k, Message msg) = 0;
};

#endif // OBJ_H
