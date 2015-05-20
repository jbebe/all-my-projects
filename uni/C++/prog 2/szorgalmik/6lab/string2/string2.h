#ifndef STRING_H
#define STRING_H
/**
 * \file string2.h (latin2 kodolasu fajl)
 *
 * Ez a f�jl tartalmazza a
 *   - String oszt�ly deklar�ci�j�t
 *   - az inline f�ggv�nyeket. Ha valamit inline-k�nt akar megval�s�tani,
 *     akkor azt ebbe a f�jlba �rja! Tipikusan a r�vid k�dokat szok�s
 *     inline-k�t megval�s�tani (pl: c_str).
 *
 * A C-ben meg�rt (string1.c) f�ggv�nyek most tagf�ggv�nyekk� v�ltak, �s
 *   elt�nt az els� param�ter�k (s0) (ebb�l lett a this).
 * A nev�k is megv�ltozott, mert most m�r az �sszetartoz�st, �s a
 *   param�terek t�pus�ra val� utal�st m�r nem a n�v hordozza, hanem az oszt�ly.
 * A createString... alak� f�ggv�nyekb�l konstruktorok keletkeztek.
 * A disposeString destruktorr� alak�lt �t.
 * Egyes m�veletv�gz� f�ggv�nyekb�l pedig oper�tor f�ggv�ny lett.
 */

/**
 * Az �n feladata a string1.cpp f�jlban megval�s�tani (defini�lni) az egyes
 * f�ggv�nyeket. Ahogyan halad a megval�s�t�ssal egyre t�bb tesztesetet kell
 * lefuttatni, ez�rt az ELKESZULT makro �rt�ket folyamatosan n�velje a
 * feladatsorsz�moknak megfelel�en!
 * Tanuls�gos a megval�s�t�s el�tt m�r a megn�velt �rt�kkel is leford�tani
 * a programot, �s elemezni a kapott hibajelz�st.
 *
 */
#define ELKESZULT 12

/**
 *Feladatok:
 *
 *  0. Nem k�sz�tett el semmit, csak egy param�ter n�lk�li kontruktor van
 *     (ezt m�r elk�sz�tett�k)
 *  1. K�sz�tsen konstruktort, ami karakterb�l hoz l�tre Stringet!
 *  2. K�sz�tse el a destruktort!
 *  3. K�sz�tsen olyan konstruktort, ami Stringet k�sz�t C-stringb�l (char*)
 *     K�sz�tse el inline f�ggv�nyk�nt c_str() f�ggv�nyt is!
 *  4. Ellen�rizze, hogy a default (implicit) m�sol� konstruktor
 *     haszn�lhat�-e a feladatban!
 *  5. K�szitse el a m�sol� konstruktort!
 *  6. Ellen�rizze, hogy a default (implicit) �rt�kad� oper�tor
 *     haszn�lhat�-e a feladatban!
 *  7. K�sz�tse el az �rt�kad� oper�tort!
 *  8. K�sz�tsen oper�torokat az indexel�shez!
 *  9. K�sz�tsen olyan + oper�tort, amivel k�t String �sszef�zhet�!
 * 10. Param�ter n�lk�li konstruktorral l�trehozott obj. haszn�lata.
 *     Az el�re elk�sz�tett param�ter n�lk�li konstruktor NULL pointert
 *     tartalmaz, ami galib�t okozhat a hagyom�nyos (C) stringkezel�
 *     f�ggv�nyek haszn�latakor.
 *    *Megold�si javaslat:
 *     M�dos�tsa ezt a konstruktort �gy, hogy ne lehessen NULL �rt�k� a pData.
 *     Ezt k�nnyen el�rheti, ha t�rli param�ter n�lk�li konstruktort a string2.h
 *     f�jlb�l, �s a C stringes konstruktornak default param�terk�nt ad egy �res
 *     stringet.
 *    *Megj: Elk�pzelhet�, hogy a fent javasolt megold�s k�vetkezt�ben
 *     most mem�riasziv�rg�st jelez program. Az okot operator + megval�s�t�sban
 *     keresse! Ne l�pjen tov�bb, am�g ezt meg nem tal�lta!
 * 11. K�sz�tsen olyan << oper�tort, amivel egy szting ki�rhat� egy ostream t�pus�
 *     objektumra!
 * 12. Ellen�rizze, hogy a kiv�telkezel�st j�l oldotta-e meg a 8. feladatban!
 * Szorgalmi feladatok:
 * 13. K�sz�tsen olyan >> oper�tort, amivel be tud olvasni egy sz�t egy String-be!
 *     A beolvas� m�k�dj�n �gy, mint a scanf %s, azaz a sz� v�g�t white space
 *     hat�rolja. A sz� eleji white space karaktereket pedig el kell dobni.
 *    *Megj: az istream wshite space kezel�se a flags() tagf�ggv�nnyel szab�lyozhat�
 * 14. Pr�b�lja ki az �kezetes karakterek rendez�s�t is! Ehhez elk�sz�tett�nk egy
 *     egyszer� k�dr�szletet ami qsort() f�ggv�nyt haszn�l.
 *     �rtse meg a rendez.cpp f�jlban lev� k�d m�k�d�s�t �s futtassa a programot!
 * 15. A setlocale f�ggv�nyh�v�s be�ll�tja a karakterek �s stringek �sszehasonl�t�s�hoz
 *     sz�ks�ges nyelvi k�rnyezetet (LC_COLLATE) pr�b�lja ki! V�ltozott a rendez�si
 *     sorrend?
 *
 */

#include <iostream>       /// az ostream miatt kell
/**
 * Header f�jlokb�l megfontoltan kell include-ot haszn�lni.
 * N�vteret azonban nem c�lszer� kinyitni, mert annak hat�sa zavar� lehet
 * ott ahol ez a header include-olva lesz.
 */

/**
 * A String oszt�ly.
 * A 'pData'-ban vannak a karakterek (a lez�r� null�val egy�tt), 'len' a hossza.
 * A hosszba nem sz�m�t bele a lez�r� nulla.
 */
class String {
    char *pData;         /// pointer az adatra
    unsigned int len;    /// hossz lez�r� nulla n�lk�l
public:
  /// Konstruktorok �s a Destruktor
    /// Default konstruktor:
    /// Ilyen nem volt a C programban, helyette a main-ben a static v�ltoz�k voltak
    /// Ezt a megold�st 10. feladat megold�s�n�l fel�l kell vizsg�lnia!
    String() :pData(0), len(0) {}

    /// Konstruktor: egy karakterb�l (createStringFromChar-b�l keletkezett)
    /// @param ch - karakter, amib�l a String-et l�trehozzuk
    String(char ch);

    /// Konstruktor: egy egy null�val lez�rt char sorozatb�l (createStringFromCharStr)
    /// @param p - pointer a C stringre
    String(const char* p);

    /// C stringet ad vissza
    /// @return null�val lez�rt karaktersorozatra mutat� pointer
    const char* c_str() const;

#if ELKESZULT >= 5
    /// M�SOL� konstruktor, ami a createStringFromString-b�l keletkezett
    /// @param s1 - String, amib�l l�trehozzuk az �j String-et
    String(const String& s1);
#endif

#if ELKESZULT >= 2
    /// Destruktor (disposeString)
    ~String();
#endif

  /// Egy�b tagf�ggv�nyek:
    /// Ki�runk egy Stringet (debug c�lokra) (ez k�sz)
    /// El�tte ki�runk egy tetsz�leges sz�veget.
    /// @param txt - null�val lez�rt sz�vegre mutat� pointer
    void printDbg(const char *txt = "") const {
        std::cout << txt << "[" << len << "], "
                  << (pData ? pData : "(NULL)") << std::endl;
    }

  /// Oper�torok:
#if ELKESZULT >= 7
    /// �rt�kad� oper�tor is kell !
    /// @param rhs_s - jobboldali String
    /// @return baoldali (m�dos�tott) string (referenci�ja)
    String& operator=(const String& rhs_s);
#endif

    /// K�t Stringet �sszef�z (concatString)
    /// @param rhs_s - jobboldali String
    /// @return �j String, ami tartalmazza a k�t stringet egm�s ut�n
    String operator+(const String& rhs_s) const ;

    /// A string egy megadott index� elem�nek REFERENCI�J�VAL t�r vissza.
    /// charAtString-b�l keletkezett, de ezt bal oldalon is lehet haszn�lni
    /// @param idx - charakter indexe
    /// @return karakter (referencia)
    ///         Indexel�si hiba eset�n const char* kiv�telt dob (assert helyett).
    char& operator[](unsigned int idx);

    /// A string egy megadott index� elem�nek REFERENCI�J�VAL t�r vissza.
    /// charAtString-b�l keletkezett. Konstans stringre alkalmazhat�.
    /// Indexel�si hiba eset�n const char* kiv�telt dob (assert helyett).
    /// @param idx - charakter indexe
    /// @return karakter (referencia)
    ///         Indexel�si hiba eset�n const char* kiv�telt dob (assert helyett).
    const char& operator[](unsigned int idx) const;

  /// Bar�t f�ggv�nyek:
    /// ki�r az ostream-re (printString)
    /// Nem c�lszer� using-ot haszn�lni, mert ez egy include file. �gy ki kell �rni az std::-t
    /// @param os - ostream t�pus� objektum
    /// @param s0 - String, amit ki�runk
    /// @return os
    /// Vigy�zat nem tagf�ggv�ny! Nem is t�nik el az s0 !
    friend std::ostream& operator<<(std::ostream& os, const String& s0);

    /// Beolvas az istream-r�l egy sz�t egy string-be.
    /// @param is - istream t�pus� objektum
    /// @param s0 - String, amibe beolvas
    /// @return is
    /// Vigy�zat nem tagf�ggv�ny! Nem is t�nik el az s0 !
    friend std::istream& operator>>(std::istream& is, String& s0);
};
#endif
