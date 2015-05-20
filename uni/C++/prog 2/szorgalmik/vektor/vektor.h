#ifndef VEKTOR_H
#define VEKTOR_H

/**
* Dinamikus valós vektor.
* A konstruktor a statikus tagokból inicializál
*/


class Vektor {
	double *pVec;               // vektor elemeit tartalmazó din. memóriaterület cime
	unsigned int nElements;     // vektor elmeinek száma
	static unsigned int defSize;// vektor alapértelmezett mérete
	static double defValue;     // vektor elemeinek alepértelmezett kezdőértéke
public:

	/// Kontsruktor.
	/// Statikus adattagokból inicializál
	/// @param size  - vektor mérete
	/// @param value - kezdőérték, amivel feltölti a vektort
	Vektor(unsigned int size = defSize, double value = defValue) :nElements(size) {
		pVec = new double[nElements];
		for (unsigned int i = 0; i < nElements; i++)
			pVec[i] = value;
	}

	/// Másoló konstruktor.
	Vektor(const Vektor&);

	/// Destruktor.
	~Vektor();

	/// Méret lekérdezése.
	unsigned int size() const { return nElements; }

	/// Alepértelmezet méret beállítása
	/// @param size  - vektor def. mérete
	static void setDefSize(unsigned int size) { defSize = size; }

	/// Alepértelmezet érték beállítása
	/// @param value - def. kezdőérték, amivel feltölti a vektort
	static void setDefValue(double value) { defValue = value; }

	/// Értékadó operátor
	Vektor& operator=(const Vektor&);

	/// Indexoperátorok.
	/// Túlcímzés esetén Ön nagybetűs Neptun-kódját tartalmazó const char* típusú kivételt dob!
	/// @param idx - index értéke
	/// @return    - referencia az adott elemre
	double& operator[](unsigned int idx);
	const double& operator[](unsigned int idx) const;

	/// Szorzás: Valós * Vektor
	/// @param val - valós érték (bal oldali operandus)
	/// @param vec - vektor, aminek minden elemét megszorosszuk (jobb oldali operandus)
	friend Vektor operator*(double val, const Vektor& vec);
};

#endif