/**
 * (iso-8859-2 k�dol�s� fajl)
 *
 * \file string2.cpp
 *
 * Itt kell megval�s�tania a hi�nyz� tagf�ggv�nyeket.
 * Seg�ts�g�l megadtuk a C-ben meg�rt v�ltozatban haszn�lt f�ggv�nyneveket.
 *
 * Ha valamit INLINE-k�nt val�s�t meg, akkor annak a .h-ba kell ker�lnie,
 * ak�r k�v�l ak�r oszt�lyon bel�l defini�lja. (Az inline f�ggv�nyeknek minden
 * ford�t�si egys�gben el�rhet�knek kell lenni�k)
 *
 * A tesztel�skor ne felejtse el be�ll�tani a header �llom�nyban az ELKESZULT makr�t.
 * A VC saj�t mem�riafogy�s ellen�rz�je csak debug m�dban (Debug->Start) m�k�dik!
 *
 */

/// Melyik ellen�rz�t haszn�ljuk a dinamikus mem�riakezel�shez?
/// Ne felejtse el a megfelel� define-t be�ll�tani a fejleszt�eszk�z�ben ford�t�skor.
// ha definialt, akkor az MSC vagy GLIBC bels� ellen�rz�je
//#define MEMCHECK

// ha definialt, akkor a malloc, new fel�ldefini�l�s�val k�sz�tett csomag,
// ami m�k�d�s�ben hasonlit az infoc site-on levo debug_malloc csomaghoz.
//#define MEMTRACE

#ifdef _MSC_VER
// MSC ne adjon figyelmeztet� �zenetet a stringkezel� f�ggv�nyekre.
  #define _CRT_SECURE_NO_WARNINGS
#endif

// MSC �s GCC bels� mem�riasziv�rg�s �s konzisztencia ellen�rz�je
#include "memcheck.h"           // Mindenk�ppen els� include-nak kell lennie

#include <iostream>             // Ki�rat�shoz
#include <cstring>              // Stringm�veletekhez

// malloc, new fel�ldefini�l�s�val k�sz�tett mem�riasziv�rg�s �s konzisztencia ellen�rz�
#include "memtrace.h"           // a standard headerek ut�n kell lennie
#include "string2.h"

using namespace std;

#if ELKESZULT >= 1
/// Konstruktor: egy char karakterb�l (createStrFromChar)
String::String(char ch) :
	len(1)
{
	this->pData = new char[1];
	pData[0] = ch;
}
#endif

#if ELKESZULT >= 2
String::~String()
{
	delete[] pData;
}
// Destruktor (disposeString)
#endif

#if ELKESZULT >= 3
String::String(const char* p) :
	len(strlen(p))
{
	pData = new char[len];
	memcpy(pData, p, len);
}
// Konstruktor: egy null�val lez�rt char sorozatb�l (createStringFromCharStr)
#endif

#if ELKESZULT >= 5
// M�sol� konstruktor
String::String(const String& rhs):
	len(rhs.len)
{
	pData = new char[len];
	memcpy(pData, rhs.pData, len);
}
#endif

#if ELKESZULT >=7
// operator=
String& String::operator =(const String& rhs)
{
	delete[] pData;
	len = rhs.len;
	pData = new char[len];
	memcpy(pData, rhs.pData, len);
	return *this;
}
#endif

#if ELKESZULT >= 8
// [] oper�torok: egy megadott index� elem REFERENCI�J�VAL t�rnek vissza.
// indexhiba eset�n dobjon egy const char * t�pus� hib�t!
char& String::operator [](unsigned int index)
{
	if (index >= len)
	{
		throw "indexhiba";
	}
	return pData[index];
}
const char& String::operator [](unsigned int index) const
{
	if (index >= len)
	{
		throw "indexhiba";
	}
	return pData[index];
}
#endif

#if ELKESZULT >= 9
// + oper�tor, ami k�t stringet ad �ssze (concatString)
String String::operator +(const String& rhs) const
{
	char *tmp = new char[len + rhs.len + 1];
	memcpy(tmp, pData, len);
	memcpy(tmp + len, rhs.pData, rhs.len);
	tmp[len + rhs.len] = '\0';
	String sTmp(tmp);
	return sTmp;
}
#endif

#if ELKESZULT >= 11
// << operator, ami ki�r az ostream-re
std::ostream& operator<<(std::ostream& o, const String& rhs)
{
	for (unsigned int i = 0; i < rhs.len; ++i)
	{
		o << rhs.pData[i];
	}
	return o;
}
#endif

#if ELKESZULT >= 13
// << oper�tor, ami beolvas az istreamr�l egy sz�t
std::istream& operator>>(std::istream& i, String& rhs)
{
	i.skipws()
	return i;
}
#endif
