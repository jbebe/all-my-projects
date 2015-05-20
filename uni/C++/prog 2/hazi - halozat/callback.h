/**
 *  \file callback.h
 *  Callback osztály deklarációja
 */
#ifndef CALLBACK_H
#define CALLBACK_H

/**
 * Callback segédosztály
 */
struct Callback {
    virtual void callback() = 0;            ///< virtuális callback függvény
};

#endif // CALLBACK_H
