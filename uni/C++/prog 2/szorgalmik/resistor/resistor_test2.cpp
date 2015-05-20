/**
* \file resistor_test2.cpp (latin2 kodolasu fajl)
*
* Ohmikus ellen�ll�st megval�sit� oszt�ly tesztel�se
* Laborfeladat
*/
#include <iostream>
#include "resistor.h"

using namespace std;

int main()
{
	Resistor r;
	Resistor r1(1000), r2(3000);

	cout << r.getR() << endl;      	        // h�zi feladatban megadott �rtek

	Resistor r11 = r1;
	Resistor r22 = r2;

	cout << (r11 + r22).getR() << endl;         // 4000

	cout << (2 * r11).getR() << endl;           // 2000

	Resistor::setDef(20);
	Resistor rt[5];

	cout << rt[3].getR() << endl;               // 20

	cout << r1.getR() << endl;			// 1000

	r1 = r2;

	cout << r1.getR() << endl;			// 3000

	return 0;
}
