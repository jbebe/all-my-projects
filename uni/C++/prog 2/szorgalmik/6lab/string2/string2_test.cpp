/**
 * \file string2_test.cpp (latin-2 k�dol�s� f�jl)
 *
 * Tesztprogram az String oszt�ly kipr�b�l�s�hoz.
 * A string2.h f�jlban n�velje az ELKESZULT makr� �rt�k�t, ahogy halad a feladattal.
 * A program elsz�llhat, amikor a m�sol� konstruktor �s/vagy az operator=
 * m�g nincs k�sz, de m�r haszn�lja!
 *
 * Ha az �sses feladatot megoldotta, akkor a fut�s eredm�nye a k�vetkez�:
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
 * Az els� �s az "Parameter nelkuli konstruktorral..." kezd�d� sor elt�rhet,
 * ha megtartotta a pData kezdeti NULL �rt�k�t, �s az ebb�l sz�rmaz� probl�m�t
 * m�sk�nt oldotta meg.
 *
 */

/// Melyik ellen�rz�t haszn�ljuk a dinamikus mem�riakezel�shez?
/// Ne felejtse el a megfelel� define-t be�ll�tani a fejleszt�eszk�z�ben ford�t�skor.
// ha definialt, akkor az MSC vagy GLIBC bels� ellen�rz�je
//#define MEMCHECK

// ha defini�lt, akkor a malloc, new fel�ldefini�l�s�val k�sz�tett csomag,
// ami m�k�d�s�ben hasonlit az infoc site-on levo debug_malloc csomaghoz.
//#define MEMTRACE

#ifdef _MSC_VER
// MSC ne adjon figyelmeztet� �zenetet a stringkezel� f�ggv�nyekre.
  #define _CRT_SECURE_NO_WARNINGS
#endif

// MSC �s GCC bels� mem�riasziv�rg�s �s konzisztencia ellen�rz�je
#include "memcheck.h"           // Mindenk�ppen els� include-nak kell lennie

#include <iostream>             // Ki�rat�shoz

// malloc, new fel�ldefini�l�s�val k�sz�tett mem�riasziv�rg�s �s konzisztencia ellen�rz�
#include "memtrace.h"           // a standard headerek utan kell lennie
#include "string2.h"

using namespace std;

/* Seg�df�ggv�ny a ki�r�sok k�vet�s�hez.
 * Ha haszn�lni akarja, tegye defini�ltt� az ELK_DEBUG azonos�t�t!
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
    _StartMemoryCheck(); /// bekapcsolja a din. mem�ria konzisztencia ellen�rz�s�t
    try {
        // Nyitunk egy �j blokkot, hogy minden ebben legyen.
        // K�v�l csak a mem�riasziv�rg�s ellen�rz�se marad.
        // M�sr�szt ebben minden kiv�telt elkapunk.

        // Konstruktorok pr�b�ja:
        String a;
        a.printDbg("String a; a: ");

#if ELKESZULT >=1   // String(char) is k�sz
        elk_debug(1);
        String b('b');
        b.printDbg("String b('b'); b: ");     /// Magyar�zza meg, hogy itt mi�rt
        /// kap ford�t�si hib�t, ha nincs k�sz a destruktor !
#endif

#if ELKESZULT >= 3  // String(const char*) is k�sz
        elk_debug(2);
        String sos("SOS ");
        sos.printDbg("String sos(\"SOS \"); sos: ");
        String *sp = new String("Az obj. is dinamikus teruleten");
        sp->printDbg("sp = new String(...); sp->printDbg: ");   // -> haszn�lata
        (*sp).printDbg("(*sp).printdbg: ");    // most pedig ponttal
        delete sp;
#endif

#if ELKESZULT >= 4  // m�sol� konstruktor teszt (k�sz, ha > 4)
        elk_debug(4);
#if ELKESZULT >=5
        elk_debug(5);
        cout << "Elkeszult a masolo" << endl;
#endif
        String d = sos;
        d.printDbg("String d = sos; d: ");
#endif

#if ELKESZULT >= 6  // operator= teszt (k�sz, ha > 6)
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

#if ELKESZULT >= 8 // m�r tudunk indexelni is
        elk_debug(8);
        cout << "Indexeles:" << endl;
        cout << "sos[1]: " << sos[1] << endl;
        sos[1] = 'A';
        sos.printDbg("sos[1] ='A'; sos: ");
        const String sk("Konstans String ");
        sk.printDbg("String sk(\"Konstans String \"); sk: ");
        cout << "sk[9]: " << sk[9] << endl;;
#endif

#if ELKESZULT >= 9      // operator+ pr�ba
        elk_debug(9);
        (sk+sos).printDbg("sk+sos: ");  // Itt (sk+sos) itt egy ideiglenes objektum, aminek megh�vjuk egy tagf�gv�ny�t.
                        // Mi lett az ideiglenes objektummal?
#endif

#if ELKESZULT >= 10
        // Param�ter n�lk�li konstruktorral l�trehozott obj. haszn�lata.
        // Ebben NULL pointer van, ami galib�t okozhat pl. az strcpy-n�l.
        elk_debug(10);
        a.printDbg("Parameter nelkuli konstruktorral letrehozott Sring a:");
        (sk+a).printDbg("sk+a: ");
#endif

#if ELKESZULT >= 11     // m�r megy a k��r�s is
        elk_debug(11);
        cout << String("Megy a kiiras is") << endl;
#endif

#if ELKESZULT >= 12     // kiv�telt is kipr�b�ljuk
        elk_debug(12);
        cout << "Indexhatar ellenorzes:" << endl;
        try {               // v�rjuk a kiv�telt
            String r("0123");
            cout << "r: " << r << endl;
            cout << "r[2]: " << r[2] << endl;
            cout << "r[22]: " << r[22] << endl;;
        } catch (const char *) {
            cerr << "Indexelesi hiba" << endl;
        }
#endif

#if ELKESZULT >= 13     // beolvas�s is k�sz
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
    _CrtDumpMemoryLeaks();  /// ellen�rzi, hogy volt-e mem�riasziv�rg�s
    return 0;
}
