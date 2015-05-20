/**
 * \file rendez.cpp (latin-2 kódolású fájl)
 *
 * Egyszerû teszt modul az ékezetes karaktereket tartalmazó
 * String kipróbálására.
 * Az összehasonlítás figyelembe veszi az LC_COLLATE beállítást
 */

#ifdef _MSC_VER
// MSC ne adjon figyelmeztetõ üzenetet a stringkezelõ függvényekre.
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <clocale>
#if defined(WIN32) || defined(_WIN32)
# include <windows.h>
#endif

#include "string2.h"

using namespace std;

#if ELKESZULT >= 14
/// Összehasonlító a qsorthoz
int cmp(const void* s1, const void* s2) {
    return strcoll((*(const String**)s1)->c_str(), (*(const String**)s2)->c_str());
}

void rendez() {
#if ELKESZULT >= 15
    setlocale(LC_ALL, "");       // beállítja az op.rendszer által használt
                                 // nyelvi környezetet, amit feltételezünk, hogy magyar
#endif
    #if defined(WIN32) || defined(_WIN32)
        // Windows alatt egyéb varázslatra is szükség van ...
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif

    cout << String("Ékezetes betûk próbája:") << endl;

    const int N = 15;
    String szavak[N];   /// Itt lesznek a szavak
    String *poik[N];    /// Itt pedig a pointerek a rendezéshez
    int db;
    cout << String("Írjon legfeljebb ") << N << 
	    String(" szóból álló szöveget!") << endl <<
            String("Az utolsó sor után EOF (ctrl-Z/ctrl-D) legyen!") << endl;
    cout << String(" Pl: Ádám Béla Ernõ Ottó kígyót bûvöl") << endl;

    for (db = 0; db < N && cin >> szavak[db]; ++db)
        poik[db] = &szavak[db];     /// címek tömbjét képezzük

    /// Pointerek töbjét rendezzük
    qsort(poik, db, sizeof(String*), cmp);
    cout << "----- Rendezve: ------" << endl;
    for (int i = 0; i < db; ++i) {
        poik[i]->printDbg("");	    /// így a hossz is látszik UTF-8-nál 
    				    /// egyezik meg a betûk számával	
//        cout << *poik[i] << endl;
    }
}
#endif
