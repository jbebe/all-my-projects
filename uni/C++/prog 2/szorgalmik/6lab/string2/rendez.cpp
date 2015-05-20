/**
 * \file rendez.cpp (latin-2 k�dol�s� f�jl)
 *
 * Egyszer� teszt modul az �kezetes karaktereket tartalmaz�
 * String kipr�b�l�s�ra.
 * Az �sszehasonl�t�s figyelembe veszi az LC_COLLATE be�ll�t�st
 */

#ifdef _MSC_VER
// MSC ne adjon figyelmeztet� �zenetet a stringkezel� f�ggv�nyekre.
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
/// �sszehasonl�t� a qsorthoz
int cmp(const void* s1, const void* s2) {
    return strcoll((*(const String**)s1)->c_str(), (*(const String**)s2)->c_str());
}

void rendez() {
#if ELKESZULT >= 15
    setlocale(LC_ALL, "");       // be�ll�tja az op.rendszer �ltal haszn�lt
                                 // nyelvi k�rnyezetet, amit felt�telez�nk, hogy magyar
#endif
    #if defined(WIN32) || defined(_WIN32)
        // Windows alatt egy�b var�zslatra is sz�ks�g van ...
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif

    cout << String("�kezetes bet�k pr�b�ja:") << endl;

    const int N = 15;
    String szavak[N];   /// Itt lesznek a szavak
    String *poik[N];    /// Itt pedig a pointerek a rendez�shez
    int db;
    cout << String("�rjon legfeljebb ") << N << 
	    String(" sz�b�l �ll� sz�veget!") << endl <<
            String("Az utols� sor ut�n EOF (ctrl-Z/ctrl-D) legyen!") << endl;
    cout << String(" Pl: �d�m B�la Ern� Ott� k�gy�t b�v�l") << endl;

    for (db = 0; db < N && cin >> szavak[db]; ++db)
        poik[db] = &szavak[db];     /// c�mek t�mbj�t k�pezz�k

    /// Pointerek t�bj�t rendezz�k
    qsort(poik, db, sizeof(String*), cmp);
    cout << "----- Rendezve: ------" << endl;
    for (int i = 0; i < db; ++i) {
        poik[i]->printDbg("");	    /// �gy a hossz is l�tszik UTF-8-n�l 
    				    /// egyezik meg a bet�k sz�m�val	
//        cout << *poik[i] << endl;
    }
}
#endif
