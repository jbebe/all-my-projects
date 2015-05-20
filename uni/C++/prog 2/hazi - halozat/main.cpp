/**
 * \mainpage Digit�lis �ramk�r�k modellez�se
 *
 * \par Feladat:
 * Digit�lis �ramk�r modellez�se, szimul�l�sa. Megval�s�tott objektumok:
 *  - Dr�t (Drot)
 *  - Csom�pont (Csp)
 *  - Kapcsol� (Kapcsolo)
 *  - Forr�s (Forras)
 *  - Nyom�gomb (Gomb)
 *  - NAND kapu
 *  - Inverz bemenet� RS flip-flop (R_S_FF)
 *
 * \par Demostr�ci�s c�l:
 *  - �r�kl�s �s t�bbsz�r�s �r�kl�s megval�s�t�s�nak bemutat�sa
 *  - virtu�lis tagf�ggv�ny bemutat�sa
 * \par Hivatkoz�sok
 *  - A program forr�sa let�lthet� <A href="svn.iit.bme.hu=eloadas_peldak/ea_06/digit">innen.</a>
 *  - A meg�rt�st seg�ti a 6. el�ad�s anyaga.
 *
 * \par Hi�nyoss�gok:
 *  - A jelkezel�s nem haszn�lja a nem defini�lt �llapotot
 *  - A kapcsol�d�si pontoknak (l�bsz�moknak) semmi k�ze a t�nyleges �ramk�ri elem l�bsorsz�m�hoz
 *  - A l�bakon megjelen� t�rol� lehetne a Conn objektumban is.
 *
 */
#ifdef _MSC_VER
// MSC ne adjon figyelmeztet� �zenetet a stringkezel� f�ggv�nyekre.
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "forras.h"
#include "kapcsolo.h"
#include "r_s_ff.h"
#include "nand.h"

using namespace std;
/**
 * Egyszer� tesztkapcsol�s
 * 2 forr�s, 2 kapcsol�, RS flop-flop.
 *
 */
int main()
{
	Kapcsolo K1("K1"), K2("K2");    // kapcsol�k
	Forras F1("F1"), F2("F2");      // forr�sok
	R_S_FF FF("FF");                // RS FF

	try {
		
		F1.setConn(0, K1, 0);  // F1 l�b 0 -> K1 l�b 0
		FF.setConn(0, K1, 1);  // FF l�b 0 -> K1 l�b 1
		F2.setConn(0, K2, 0);  // F2 l�b 0 -> K2 l�b 0
		FF.setConn(1, K2, 1);  // FF l�b 1 -> K1 l�b 1

		cerr << "\nInit:"; F1.init(); F2.init(); // Forr�sokat "bekapcsoljuk"
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
		N1.setConn(2, N1, 1);   // saj�t mag�hoz k�t�tt�k
		F1.init();              // �s beler�gunk
	}
	catch (const char *s) {
		cerr << "Elkaptuk: " << s << '\n';
	}

	getchar();
	return(0);
}
