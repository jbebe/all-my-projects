/**
 *  \file message.h
 *  Message oszt�ly deklar�ci�ja
 */
#ifndef MESSAGE_H
#define MESSAGE_H
#include <algorithm>

const int MaxIter = 20;                     ///< Maxim�lis iter�ci�sz�m
/**
 * �zenet (strukt�ra)
 *  Egy publikus oszt�ly
 */
struct Message {
    /// �zenet t�pusa
    /// undef - jelenleg nem haszn�lt
    /// jel   - J jelszintnek megfele� szint
    enum msgt { undef, jel} typ;
    bool J;                                 ///< jelszint 0 v. 1
    int  c;                                 ///< iterr�ci�s ciklussz�ml�l�
    /// Ez a default konstruktor is
    /// @param t - �zenett�pus (alap�rtelmez�se undef)
    /// @param j - jel szint(alap�rtelmez�se 0)
    /// @param n - maxim�lis iter�ci�s sz�m (alap�rtelmez�se MaxIter)
    Message(msgt t = undef, bool j = false, int n = MaxIter)
                        :typ(t), J(j), c(n) {}
    /// K�t �zenet �sszehasonl�t�sa.
    /// Akkor egyenl�, ha a t�pusa es a jelszintje is azonos
    bool operator==(const Message &m) const { return(typ == m.typ && J == m.J); }
    bool operator!=(const Message &m) const { return(!operator==(m)); }     ///< == oper�torra van visszavezetve
    Message operator+(const Message &m) const {
        return Message(std::max(typ, m.typ), (J+m.J)!=0, // ez az MSC miatt kell ! 
											std::max(c, m.c));
    }
    /// Iter�ci�s sz�ml�l� cs�kkent�se
    /// Ha az iter�ci�s sz�m kisebb lesz mint 1, akkor
    /// "Sok Iteraci�"  const char* hib�t dob
    Message &operator--() { if (--c <= 0)   // iter�ci�s sz�ml�l� cs�kkent�se
        throw "Sok Iteracio!"; return(*this); }
};
#endif // MESSAGE_H
