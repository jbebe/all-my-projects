/**
 * (iso-8859-2 kódolású fajl)
 *
 * \file string2.cpp
 *
 * Itt kell megvalósítania a hiányzó tagfüggvényeket.
 * Segítségül megadtuk a C-ben megírt változatban használt függvényneveket.
 *
 * Ha valamit INLINE-ként valósít meg, akkor annak a .h-ba kell kerülnie,
 * akár kívül akár osztályon belül definiálja. (Az inline függvényeknek minden
 * fordítási egységben elérhetõknek kell lenniük)
 *
 * A teszteléskor ne felejtse el beállítani a header állományban az ELKESZULT makrót.
 * A VC saját memóriafogyás ellenõrzõje csak debug módban (Debug->Start) mûködik!
 *
 */

/// Melyik ellenõrzõt használjuk a dinamikus memóriakezeléshez?
/// Ne felejtse el a megfelelõ define-t beállítani a fejlesztõeszközében fordításkor.
// ha definialt, akkor az MSC vagy GLIBC belsõ ellenõrzõje
//#define MEMCHECK

// ha definialt, akkor a malloc, new felüldefiniálásával készített csomag,
// ami mûködésében hasonlit az infoc site-on levo debug_malloc csomaghoz.
//#define MEMTRACE

#ifdef _MSC_VER
// MSC ne adjon figyelmeztetõ üzenetet a stringkezelõ függvényekre.
  #define _CRT_SECURE_NO_WARNINGS
#endif

// MSC és GCC belsõ memóriaszivárgás és konzisztencia ellenõrzõje
#include "memcheck.h"           // Mindenképpen elsõ include-nak kell lennie

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Stringmûveletekhez

// malloc, new felüldefiniálásával készített memóriaszivárgás és konzisztencia ellenõrzõ
#include "memtrace.h"           // a standard headerek után kell lennie
#include "string2.h"

using namespace std;

#if ELKESZULT >= 1
/// Konstruktor: egy char karakterbõl (createStrFromChar)
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
// Konstruktor: egy nullával lezárt char sorozatból (createStringFromCharStr)
#endif

#if ELKESZULT >= 5
// Másoló konstruktor
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
// [] operátorok: egy megadott indexû elem REFERENCIÁJÁVAL térnek vissza.
// indexhiba esetén dobjon egy const char * típusú hibát!
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
// + operátor, ami két stringet ad össze (concatString)
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
// << operator, ami kiír az ostream-re
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
// << operátor, ami beolvas az istreamrõl egy szót
std::istream& operator>>(std::istream& i, String& rhs)
{
	i.skipws()
	return i;
}
#endif
