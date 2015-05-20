#include <iostream>

#ifndef RESISTOR_H
#define RESISTOR_H

/**
* Ohmikus ellenállás
*/
class Resistor {
	double R;              	// az ellenállás értéke ohmban
	static double defR;  	// ellenállás alapértelmezett értéke ohmban
public:

	/// Konstruktor.
	/// Alapértelmezett értéket (defR) kap
	Resistor();

	/// Konstruktor
	/// @param rhs - másik Resistor objektum
	Resistor(const Resistor& rhs);

	/// Konstruktor.
	/// @param r - ellenállás értéke [ohm]
	Resistor(const double r);

	/// Default ellenállásérték beállítása
	/// @param r - ellenállás értéke [ohm]
	static void setDef(const double r);

	/// Ellenállás értékének lekérdezése.
	/// @return - ellenállás értéke [ohm]
	double getR() const {
		return R;
	}

	/// Két ellenállás soros kapcsolása.
	/// @param r - ellenállás
	/// @return  - eredő ellenállás 
	Resistor operator+(const Resistor& r) const;

	/// Két ellenállás párhuzamos kapcsolása.
	/// @param r - ellenállás
	/// @return  - eredő ellenállás
	Resistor operator%(const Resistor& r) const;

	void Resistor::setR(const double r);
	Resistor& operator=(const Resistor& rhs);
	bool operator==(const Resistor& rhs);
	friend std::ostream& operator<<(std::ostream&, const Resistor&);
};

/// Többszörös: n darab egyforma r ellenállás összege (soros kapcsolása).
/// @param n - darabszám
/// @param r - ellenállás
/// @return  - eredő ellenállás
Resistor operator*(const int n, const Resistor& r);

#endif
