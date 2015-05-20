#ifndef STRING_H
#define STRING_H
/**
 * \file string2.h (latin2 kodolasu fajl)
 *
 * Ez a fájl tartalmazza a
 *   - String osztály deklarációját
 *   - az inline függvényeket. Ha valamit inline-ként akar megvalósítani,
 *     akkor azt ebbe a fájlba írja! Tipikusan a rövid kódokat szokás
 *     inline-két megvalósítani (pl: c_str).
 *
 * A C-ben megírt (string1.c) függvények most tagfüggvényekké váltak, és
 *   eltûnt az elsõ paraméterük (s0) (ebbõl lett a this).
 * A nevük is megváltozott, mert most már az összetartozást, és a
 *   paraméterek típusára való utalást már nem a név hordozza, hanem az osztály.
 * A createString... alakú függvényekbõl konstruktorok keletkeztek.
 * A disposeString destruktorrá alakült át.
 * Egyes mûveletvégzõ függvényekbõl pedig operátor függvény lett.
 */

/**
 * Az Ön feladata a string1.cpp fájlban megvalósítani (definiálni) az egyes
 * függvényeket. Ahogyan halad a megvalósítással egyre több tesztesetet kell
 * lefuttatni, ezért az ELKESZULT makro értéket folyamatosan növelje a
 * feladatsorszámoknak megfelelõen!
 * Tanulságos a megvalósítás elõtt már a megnövelt értékkel is lefordítani
 * a programot, és elemezni a kapott hibajelzést.
 *
 */
#define ELKESZULT 12

/**
 *Feladatok:
 *
 *  0. Nem készített el semmit, csak egy paraméter nélküli kontruktor van
 *     (ezt már elkészítettük)
 *  1. Készítsen konstruktort, ami karakterbõl hoz létre Stringet!
 *  2. Készítse el a destruktort!
 *  3. Készítsen olyan konstruktort, ami Stringet készít C-stringbõl (char*)
 *     Készítse el inline függvényként c_str() függvényt is!
 *  4. Ellenõrizze, hogy a default (implicit) másoló konstruktor
 *     használható-e a feladatban!
 *  5. Készitse el a másoló konstruktort!
 *  6. Ellenõrizze, hogy a default (implicit) értékadó operátor
 *     használható-e a feladatban!
 *  7. Készítse el az értékadó operátort!
 *  8. Készítsen operátorokat az indexeléshez!
 *  9. Készítsen olyan + operátort, amivel két String összefûzhetõ!
 * 10. Paraméter nélküli konstruktorral létrehozott obj. használata.
 *     Az elõre elkészített paraméter nélküli konstruktor NULL pointert
 *     tartalmaz, ami galibát okozhat a hagyományos (C) stringkezelõ
 *     függvények használatakor.
 *    *Megoldási javaslat:
 *     Módosítsa ezt a konstruktort úgy, hogy ne lehessen NULL értékû a pData.
 *     Ezt könnyen elérheti, ha törli paraméter nélküli konstruktort a string2.h
 *     fájlból, és a C stringes konstruktornak default paraméterként ad egy üres
 *     stringet.
 *    *Megj: Elképzelhetõ, hogy a fent javasolt megoldás következtében
 *     most memóriaszivárgást jelez program. Az okot operator + megvalósításban
 *     keresse! Ne lépjen tovább, amíg ezt meg nem találta!
 * 11. Készítsen olyan << operátort, amivel egy szting kiírható egy ostream típusú
 *     objektumra!
 * 12. Ellenõrizze, hogy a kivételkezelést jól oldotta-e meg a 8. feladatban!
 * Szorgalmi feladatok:
 * 13. Készítsen olyan >> operátort, amivel be tud olvasni egy szót egy String-be!
 *     A beolvasó mûködjön úgy, mint a scanf %s, azaz a szó végét white space
 *     határolja. A szó eleji white space karaktereket pedig el kell dobni.
 *    *Megj: az istream wshite space kezelése a flags() tagfüggvénnyel szabályozható
 * 14. Próbálja ki az ékezetes karakterek rendezését is! Ehhez elkészítettünk egy
 *     egyszerû kódrészletet ami qsort() függvényt használ.
 *     Értse meg a rendez.cpp fájlban levõ kód mûködését és futtassa a programot!
 * 15. A setlocale függvényhívás beállítja a karakterek és stringek összehasonlításához
 *     szükséges nyelvi környezetet (LC_COLLATE) próbálja ki! Változott a rendezési
 *     sorrend?
 *
 */

#include <iostream>       /// az ostream miatt kell
/**
 * Header fájlokból megfontoltan kell include-ot használni.
 * Névteret azonban nem célszerû kinyitni, mert annak hatása zavaró lehet
 * ott ahol ez a header include-olva lesz.
 */

/**
 * A String osztály.
 * A 'pData'-ban vannak a karakterek (a lezáró nullával együtt), 'len' a hossza.
 * A hosszba nem számít bele a lezáró nulla.
 */
class String {
    char *pData;         /// pointer az adatra
    unsigned int len;    /// hossz lezáró nulla nélkül
public:
  /// Konstruktorok és a Destruktor
    /// Default konstruktor:
    /// Ilyen nem volt a C programban, helyette a main-ben a static változók voltak
    /// Ezt a megoldást 10. feladat megoldásánál felül kell vizsgálnia!
    String() :pData(0), len(0) {}

    /// Konstruktor: egy karakterbõl (createStringFromChar-ból keletkezett)
    /// @param ch - karakter, amibõl a String-et létrehozzuk
    String(char ch);

    /// Konstruktor: egy egy nullával lezárt char sorozatból (createStringFromCharStr)
    /// @param p - pointer a C stringre
    String(const char* p);

    /// C stringet ad vissza
    /// @return nullával lezárt karaktersorozatra mutató pointer
    const char* c_str() const;

#if ELKESZULT >= 5
    /// MÁSOLÓ konstruktor, ami a createStringFromString-bõl keletkezett
    /// @param s1 - String, amibõl létrehozzuk az új String-et
    String(const String& s1);
#endif

#if ELKESZULT >= 2
    /// Destruktor (disposeString)
    ~String();
#endif

  /// Egyéb tagfüggvények:
    /// Kiírunk egy Stringet (debug célokra) (ez kész)
    /// Elötte kiírunk egy tetszõleges szöveget.
    /// @param txt - nullával lezárt szövegre mutató pointer
    void printDbg(const char *txt = "") const {
        std::cout << txt << "[" << len << "], "
                  << (pData ? pData : "(NULL)") << std::endl;
    }

  /// Operátorok:
#if ELKESZULT >= 7
    /// Értékadó operátor is kell !
    /// @param rhs_s - jobboldali String
    /// @return baoldali (módosított) string (referenciája)
    String& operator=(const String& rhs_s);
#endif

    /// Két Stringet összefûz (concatString)
    /// @param rhs_s - jobboldali String
    /// @return új String, ami tartalmazza a két stringet egmás után
    String operator+(const String& rhs_s) const ;

    /// A string egy megadott indexû elemének REFERENCIÁJÁVAL tér vissza.
    /// charAtString-bõl keletkezett, de ezt bal oldalon is lehet használni
    /// @param idx - charakter indexe
    /// @return karakter (referencia)
    ///         Indexelési hiba esetén const char* kivételt dob (assert helyett).
    char& operator[](unsigned int idx);

    /// A string egy megadott indexû elemének REFERENCIÁJÁVAL tér vissza.
    /// charAtString-bõl keletkezett. Konstans stringre alkalmazható.
    /// Indexelési hiba esetén const char* kivételt dob (assert helyett).
    /// @param idx - charakter indexe
    /// @return karakter (referencia)
    ///         Indexelési hiba esetén const char* kivételt dob (assert helyett).
    const char& operator[](unsigned int idx) const;

  /// Barát függvények:
    /// kiír az ostream-re (printString)
    /// Nem célszerû using-ot használni, mert ez egy include file. Így ki kell írni az std::-t
    /// @param os - ostream típusú objektum
    /// @param s0 - String, amit kiírunk
    /// @return os
    /// Vigyázat nem tagfüggvény! Nem is tûnik el az s0 !
    friend std::ostream& operator<<(std::ostream& os, const String& s0);

    /// Beolvas az istream-rõl egy szót egy string-be.
    /// @param is - istream típusú objektum
    /// @param s0 - String, amibe beolvas
    /// @return is
    /// Vigyázat nem tagfüggvény! Nem is tûnik el az s0 !
    friend std::istream& operator>>(std::istream& is, String& s0);
};
#endif
