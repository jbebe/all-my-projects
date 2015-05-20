/**
 * \mainpage Digitális áramkörök modellezése
 *
 * \par Feladat:
 * Digitális áramkör modellezése, szimulálása. Megvalósított objektumok:
 *  - Drót (Drot)
 *  - Csomópont (Csp)
 *  - Kapcsoló (Kapcsolo)
 *  - Forrás (Forras)
 *  - Nyomógomb (Gomb)
 *  - NAND kapu
 *  - Inverz bemenetû RS flip-flop (R_S_FF)
 *
 * \par Demostrációs cél:
 *  - öröklés és többszörös öröklés megvalósításának bemutatása
 *  - virtuális tagfüggvény bemutatása
 * \par Hivatkozások
 *  - A program forrása letölthetõ <A href="svn.iit.bme.hu=eloadas_peldak/ea_06/digit">innen.</a>
 *  - A megértést segíti a 6. elõadás anyaga.
 *
 * \par Hiányosságok:
 *  - A jelkezelés nem használja a nem definiált állapotot
 *  - A kapcsolódási pontoknak (lábszámoknak) semmi köze a tényleges áramköri elem lábsorszámához
 *  - A lábakon megjelenõ tároló lehetne a Conn objektumban is.
 *
 */
#ifdef _MSC_VER
// MSC ne adjon figyelmeztetõ üzenetet a stringkezelõ függvényekre.
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "forras.h"
#include "kapcsolo.h"
#include "r_s_ff.h"
#include "nand.h"

using namespace std;
/**
 * Egyszerû tesztkapcsolás
 * 2 forrás, 2 kapcsoló, RS flop-flop.
 *
 */
int main()
{
	Kapcsolo K1("K1"), K2("K2");    // kapcsolók
	Forras F1("F1"), F2("F2");      // források
	R_S_FF FF("FF");                // RS FF

	try {
		
		F1.setConn(0, K1, 0);  // F1 láb 0 -> K1 láb 0
		FF.setConn(0, K1, 1);  // FF láb 0 -> K1 láb 1
		F2.setConn(0, K2, 0);  // F2 láb 0 -> K2 láb 0
		FF.setConn(1, K2, 1);  // FF láb 1 -> K1 láb 1

		cerr << "\nInit:"; F1.init(); F2.init(); // Forrásokat "bekapcsoljuk"
		cerr << "\n\nS_  R_  Q   Q_";
		K1.be(); K2.be();
		cerr << "\n" << FF.get(0).J << "   " << FF.get(1).J << "   " << FF.get(2).J << "   " << FF.get(3).J;
		cin.ignore(1);
		K1.ki(); K2.be();
		cerr << "\n" << FF.get(0).J << "   " << FF.get(1).J << "   " << FF.get(2).J << "   " << FF.get(3).J;
		cin.ignore(1);
		K1.be(); K2.be();
		cerr << "\n" << FF.get(0).J << "   " << FF.get(1).J << "   " << FF.get(2).J << "   " << FF.get(3).J;
		cin.ignore(1);
		K1.be(); K2.ki();
		cerr << "\n" << FF.get(0).J << "   " << FF.get(1).J << "   " << FF.get(2).J << "   " << FF.get(3).J;
		cin.ignore(1);
		K1.ki(); K2.ki();
		cerr << "\n" << FF.get(0).J << "   " << FF.get(1).J << "   " << FF.get(2).J << "   " << FF.get(3).J;

		cerr << "\nHurok kovetkezik:" << endl;
		cin.ignore(1);
		NAND N1;
		F1.setConn(0, N1, 0);
		N1.setConn(2, N1, 1);   // saját magához kötöttük
		F1.init();              // és belerúgunk
	}
	catch (const char *s) {
		cerr << "Elkaptuk: " << s << '\n';
	}

	getchar();
	return(0);
}
