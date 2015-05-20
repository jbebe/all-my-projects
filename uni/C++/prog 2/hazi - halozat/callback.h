/**
 *  \file callback.h
 *  Callback oszt�ly deklar�ci�ja
 */
#ifndef CALLBACK_H
#define CALLBACK_H

/**
 * Callback seg�doszt�ly
 */
struct Callback {
    virtual void callback() = 0;            ///< virtu�lis callback f�ggv�ny
};

#endif // CALLBACK_H
