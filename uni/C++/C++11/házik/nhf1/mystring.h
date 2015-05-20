#pragma once

#include <iostream>
#include <cstring>

/**
 * @name String with reference counting
 */
class MyString {
private:
	char *strVal;
	size_t *refCnt;
public:
	/**
	 * Paraméter nélküli konstruktor
	 */
	MyString();
	/**
	 * Karaktertömb paraméterű konstruktor
	 * @param inputStr karaktertömb
	 */
	MyString(const char *inputStr);
	/**
	 * Másoló konstruktor
	 * @param copy másolandó objektum
	 */
	MyString(const MyString &copy);
	/**
	 * Move konstruktor
	 * @param move mozgatandó(?!) objektum
	 */
	MyString(MyString &&move);
	/**
	 * Destruktor
	 * @brief Nem csak a tagváltozóit tünteti el,
	 * de meghívja a release() metódust is
	 */
	~MyString();
	/**
	 * Új értéket ad az objektumnak
	 * @param rhs másolandó objektum
	 * @return Balérték
	 */
	MyString &operator = (const MyString &rhs);
	/**
	 * Átmozgatja a jobbértéket balértékbe és kiüríti jobbértéket
	 * @param move A mozgatandó objektum
	 * @return Balérték
	 */
	MyString &operator = (MyString &&move);
	/**
	 * Konkatenál két stringet
	 * @param rhs Jobbérték
	 * @return Konkatenált sztring.
	 */
	MyString operator + (const MyString &rhs) const;
	/**
	 * Hozzáadva értékül adja jobbértéket balértékhez
	 * @param rhs Jobbérték
	 * @return Balérték összefűzve jobbértékkel
	 */
	MyString &operator += (const MyString &rhs);
	/**
	 * Konkatenálja balértéket egy karakterrel
	 * @param rhs Karakter
	 * @return Konkatenált sztring.
	 */
	MyString operator + (const char rhs) const;
	/**
	 * Hozzáadva értékül adja a karaktert a balértékhez
	 * @param rhs Karakter
	 * @return Balérték összefűzve a karakterrel
	 */
	MyString &operator += (const char rhs);
	/**
	 * Sztring indexét kiválasztja
	 * @param index index
	 * @return Karakterreferencia a sztringből
	 */
	char &operator [ ] (const size_t index);
	/**
	 * Sztring hosszát adja meg
	 * @return Sztring hossza
	 */
	size_t length() const;
	/**
	 * Hivatkozott karaktertömböt engedi el, ha ő volt az utolsó, lekapcsolja a villanyt.
	 */
	void release();
	/**
	 * Sztring kiíratásáért felelős függvény
	 * @param os ostream interfészt megvalósító osztály
	 * @param &m MyString példány referencia
	 * @return os
	 */
	friend std::ostream &operator << (std::ostream &os, MyString &m);
	/**
	 * Sztring kiíratásáért felelős függvény
	 * @param os ostream interfészt megvalósító osztály
	 * @param &&m MyString balérték
	 * @return os
	 */
	friend std::ostream &operator << (std::ostream &os, MyString &&m);
	/**
	 * Sztringbe olvasást megvalósító függvény
	 * @param is istream interfészt megvalósító osztály
	 * @param &m MyString példány referencia
	 * @return is
	 */
	friend std::istream &operator >> (std::istream &is, MyString &m);
};
