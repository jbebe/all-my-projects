/**
 * \file string2_test.cpp (latin-2 kódolású fájl)
 *
 * Tesztprogram az String osztály kipróbálásához.
 * A string2.h fájlban növelje az ELKESZULT makró értékét, ahogy halad a feladattal.
 * A program elszállhat, amikor a másoló konstruktor és/vagy az operator=
 * még nincs kész, de már használja!
 *
 * Ha az össes feladatot megoldotta, akkor a futás eredménye a következõ:
 *  String a; a: [0],
 *  String b('b'); b: [1], b
 *  String sos("SOS "); sos: [4], SOS
 *  sp = new String(...); sp->printDbg: [30], Az obj. is dinamikus teruleten
 *  *sp: [30], Az obj. is dinamikus teruleten
 *  Elkeszult a masolo
 *  String d = sos; d: [4], SOS
 *  Elkeszult az operator=
 *  eb: [22], Ez a bal oldali string
 *  ej: [25], Ez lesz/lett az uj erteke
 *  eb = ej; eb: [25], Ez lesz/lett az uj erteke
 *  Indexeles:
 *  sos[1]: O
 *  sos[1] ='A'; sos: [4], SAS
 *  String sk("Konstans String "); sk: [16], Konstans String
 *  sk[9]: S
 *  sk+sos: [20], Konstans String SAS
 *  Parameter nelkuli konstruktorral letrehozott Sring a: [0],
 *  sk+a: [16], Konstans String
 *  Megy a kiiras is
 *  Indexhatar ellenorzes:
 *  r: 0123
 *  r[2]: 2
 *  Indexelesi hiba
 *
 * Az elsõ és az "Parameter nelkuli konstruktorral..." kezdõdõ sor eltérhet,
 * ha megtartotta a pData kezdeti NULL értékét, és az ebbõl származó problémát
 * másként oldotta meg.
 *
 */

/// Melyik ellenõrzõt használjuk a dinamikus memóriakezeléshez?
/// Ne felejtse el a megfelelõ define-t beállítani a fejlesztõeszközében fordításkor.
// ha definialt, akkor az MSC vagy GLIBC belsõ ellenõrzõje
//#define MEMCHECK

// ha definiált, akkor a malloc, new felüldefiniálásával készített csomag,
// ami mûködésében hasonlit az infoc site-on levo debug_malloc csomaghoz.
//#define MEMTRACE

#ifdef _MSC_VER
// MSC ne adjon figyelmeztetõ üzenetet a stringkezelõ függvényekre.
  #define _CRT_SECURE_NO_WARNINGS
#endif

// MSC és GCC belsõ memóriaszivárgás és konzisztencia ellenõrzõje
#include "memcheck.h"           // Mindenképpen elsõ include-nak kell lennie

#include <iostream>             // Kiíratáshoz

// malloc, new felüldefiniálásával készített memóriaszivárgás és konzisztencia ellenõrzõ
#include "memtrace.h"           // a standard headerek utan kell lennie
#include "string2.h"

using namespace std;

/* Segédfüggvény a kiírások követéséhez.
 * Ha használni akarja, tegye definiálttá az ELK_DEBUG azonosítót!
 */
//#DEFINE ELK_DEBUG
void elk_debug(int feltetele) {
#ifdef ELK_DEBUG
    cout << " *** ELKESZULT FELTETEL=" << feltetele;
    if (ELKESZULT == feltetele)
        cout << " EZT TESZTELI";
    cout << " ***" << endl;
#endif
}

int main() {
    _StartMemoryCheck(); /// bekapcsolja a din. memória konzisztencia ellenõrzését
    try {
        // Nyitunk egy új blokkot, hogy minden ebben legyen.
        // Kívül csak a memóriaszivárgás ellenõrzése marad.
        // Másrészt ebben minden kivételt elkapunk.

        // Konstruktorok próbája:
        String a;
        a.printDbg("String a; a: ");

#if ELKESZULT >=1   // String(char) is kész
        elk_debug(1);
        String b('b');
        b.printDbg("String b('b'); b: ");     /// Magyarázza meg, hogy itt miért
        /// kap fordítási hibát, ha nincs kész a destruktor !
#endif

#if ELKESZULT >= 3  // String(const char*) is kész
        elk_debug(2);
        String sos("SOS ");
        sos.printDbg("String sos(\"SOS \"); sos: ");
        String *sp = new String("Az obj. is dinamikus teruleten");
        sp->printDbg("sp = new String(...); sp->printDbg: ");   // -> használata
        (*sp).printDbg("(*sp).printdbg: ");    // most pedig ponttal
        delete sp;
#endif

#if ELKESZULT >= 4  // másoló konstruktor teszt (kész, ha > 4)
        elk_debug(4);
#if ELKESZULT >=5
        elk_debug(5);
        cout << "Elkeszult a masolo" << endl;
#endif
        String d = sos;
        d.printDbg("String d = sos; d: ");
#endif

#if ELKESZULT >= 6  // operator= teszt (kész, ha > 6)
        elk_debug(6);
#if ELKESZULT >= 7
        elk_debug(7);
        cout << "Elkeszult az operator=" << endl;
#endif
        String eb("Ez a bal oldali string");
        eb.printDbg("eb: ");
        String ej("Ez lesz/lett az uj erteke");
        ej.printDbg("ej: ");
        eb = ej;
        eb.printDbg("eb = ej; eb: ");
#endif

#if ELKESZULT >= 8 // már tudunk indexelni is
        elk_debug(8);
        cout << "Indexeles:" << endl;
        cout << "sos[1]: " << sos[1] << endl;
        sos[1] = 'A';
        sos.printDbg("sos[1] ='A'; sos: ");
        const String sk("Konstans String ");
        sk.printDbg("String sk(\"Konstans String \"); sk: ");
        cout << "sk[9]: " << sk[9] << endl;;
#endif

#if ELKESZULT >= 9      // operator+ próba
        elk_debug(9);
        (sk+sos).printDbg("sk+sos: ");  // Itt (sk+sos) itt egy ideiglenes objektum, aminek meghívjuk egy tagfügvényét.
                        // Mi lett az ideiglenes objektummal?
#endif

#if ELKESZULT >= 10
        // Paraméter nélküli konstruktorral létrehozott obj. használata.
        // Ebben NULL pointer van, ami galibát okozhat pl. az strcpy-nál.
        elk_debug(10);
        a.printDbg("Parameter nelkuli konstruktorral letrehozott Sring a:");
        (sk+a).printDbg("sk+a: ");
#endif

#if ELKESZULT >= 11     // már megy a kíírás is
        elk_debug(11);
        cout << String("Megy a kiiras is") << endl;
#endif

#if ELKESZULT >= 12     // kivételt is kipróbáljuk
        elk_debug(12);
        cout << "Indexhatar ellenorzes:" << endl;
        try {               // várjuk a kivételt
            String r("0123");
            cout << "r: " << r << endl;
            cout << "r[2]: " << r[2] << endl;
            cout << "r[22]: " << r[22] << endl;;
        } catch (const char *) {
            cerr << "Indexelesi hiba" << endl;
        }
#endif

#if ELKESZULT >= 13     // beolvasás is kész
        elk_debug(13);
        cout << "Beolvasas proba. Irjon be egy szot:" << endl;
        cin >> a;
        cout << "Ezt irta: " << a << endl;
#endif

#if ELKESZULT >= 14
        elk_debug(14);
        void rendez();
        rendez();
#endif
    } catch (bad_alloc) {
      cerr << "Elfogyott a memoria" << endl;
    } catch (...) {
      cerr << "Baj van! Nem vart kivetel" << endl;
    }
    _CrtDumpMemoryLeaks();  /// ellenõrzi, hogy volt-e memóriaszivárgás
    return 0;
}
