/*
* vektorMain.cpp
*
* Tesztprogram a Vektor osztály kipróbálásához
*/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <iostream>
#include <iomanip>
#include "vektor.h"

using namespace std;

int main() {
	try {
		// Konstruktorok és az indexelés tesztje
		Vektor v0;
		cout << "v0 merete: " << v0.size() << " v0[0]: " << v0[0] << endl;

		Vektor v1(5, -1), v2(6, 0);
		cout << "v1 merete: " << v1.size() << " v1[4]: " << v1[4] << endl;

		Vektor v3 = v2;
		cout << "v3 merete: " << v3.size() << " v3[5]: " << v3[5] << endl;

		// értekadás és konstans indexelés teszt
		v1 = v0 = v0;
		const Vektor v4 = v0;
		cout << "v4[1]: " << v4[1] << endl;

		// indexelési hiba 1. teszt
		try {
			v3[6];
			cout << "Hoppa" << endl;
		}
		catch (const char *) {
			cout << "Jol van" << endl;
		}

		// indexelesi hiba 2. teszt
		try {
			v3[-1];
			cout << "Hoppa2" << endl;
		}
		catch (const char *) {
			cout << "Jol van2" << endl;
		}

		// Beolvasa n-et (egész)
		unsigned int n; cin >> n;
		Vektor::setDefSize(n);   // ez lesz a default méret

		// Beolvassa a default kezdőértéket és baállítja
		double val; cin >> val;
		Vektor::setDefValue(val);

		// Beolvas még egy egész értéket (ezzel kicst módosít majd)
		int k = 0; cin >> k;

		// Létrehozunk egy 4xn-es mátrixot default értékekkel;
		const int m = 4;
		Vektor vt[m];

		cout << fixed;
		for (int i = 0; i < m; i++) {
			// Értékadás próbája
			v0 = vt[i];
			for (unsigned int j = 0; j < n; j++)
				v0[j] = v0[j] * k++;

			cout << "vt[" << i << "](" << v0.size() << "): ";

			// Szorzás próbája
			vt[i] = 10 * v0;
			for (unsigned int j = 0; j < n; j++)
				cout << setw(8) << setprecision(0) << vt[i][j];
			cout << endl;
		}
	}
	catch (const std::exception &e) {   // mindent elkapunk
		cout << "Nagy baj van" << endl;
	}
#ifdef _CRTDBG_MAP_ALLOC
	_CrtDumpMemoryLeaks();  // ellenőrzi, hogy volt-e memóriaszivárgás
#endif

	fflush(stdin);
	getchar();
	return 0;
}