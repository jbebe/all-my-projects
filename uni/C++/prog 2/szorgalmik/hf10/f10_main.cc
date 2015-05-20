/**
 * foprogram az F10 osztaly kiprobalasahoz.
 * Juhasz Balint, CGQ956 reszere
 * Datum: 2014-03-15 12:01:44
 * Ez az allomany tetszes szerint modosithato
 */

#include <iostream>
#include "f10.h"

using namespace std;

int main() {
  F10 a, c;

  cout << a.ident() << endl;
  cout << a.match("xxa asalak as \n") << endl;
  for (int i = 0; i < 5; i ++) { 
    F10 b = a;
    cout << b.match(" csucsbol ") << endl;
  }
  F10 b = a;
  a = a;
  c = b;

  cout << c.getLine();

  fflush(stdin);
  getchar();
  return 0;
}
