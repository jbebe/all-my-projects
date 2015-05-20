/**
 *  \file message.h
 *  Message osztály deklarációja
 */
#ifndef MESSAGE_H
#define MESSAGE_H
#include <algorithm>

const int MaxIter = 20;                     ///< Maximális iterációszám
/**
 * Üzenet (struktúra)
 *  Egy publikus osztály
 */
struct Message {
    /// üzenet típusa
    /// undef - jelenleg nem használt
    /// jel   - J jelszintnek megfeleõ szint
    enum msgt { undef, jel} typ;
    bool J;                                 ///< jelszint 0 v. 1
    int  c;                                 ///< iterrációs ciklusszámláló
    /// Ez a default konstruktor is
    /// @param t - üzenettípus (alapértelmezése undef)
    /// @param j - jel szint(alapértelmezése 0)
    /// @param n - maximális iterációs szám (alapértelmezése MaxIter)
    Message(msgt t = undef, bool j = false, int n = MaxIter)
                        :typ(t), J(j), c(n) {}
    /// Két üzenet összehasonlítása.
    /// Akkor egyenlõ, ha a típusa es a jelszintje is azonos
    bool operator==(const Message &m) const { return(typ == m.typ && J == m.J); }
    bool operator!=(const Message &m) const { return(!operator==(m)); }     ///< == operátorra van visszavezetve
    Message operator+(const Message &m) const {
        return Message(std::max(typ, m.typ), (J+m.J)!=0, // ez az MSC miatt kell ! 
											std::max(c, m.c));
    }
    /// Iterációs számláló csökkentése
    /// Ha az iterációs szám kisebb lesz mint 1, akkor
    /// "Sok Iteració"  const char* hibát dob
    Message &operator--() { if (--c <= 0)   // iterációs számláló csökkentése
        throw "Sok Iteracio!"; return(*this); }
};
#endif // MESSAGE_H
