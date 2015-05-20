/**
 * foprogram az F14 osztaly kiprobalasahoz.
 * Juhasz Balint, CGQ956 reszere
 * Datum: 2014-03-15 23:47:26
 * Ez az allomany tetszes szerint modosithato
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "f14.hpp"

// tobbszoros include ellenorzese
#include "f14.hpp"

// Csak akkor fordithato, ha nincs a header fajlokban 
// 'using namespace std;'
// Ha megis van, valami ilyesmi hibauzenetet kapunk:
// 'reference to .endl. is ambiguous'
namespace nsteszt { int endl; }
void nstesztf() {
	using namespace nsteszt;
	std::cout << endl;
}

using namespace std;

int _main() {
  F14<char> cv0;
  F14<char> cv1(10);
  F14<char> cv2(10, 'a');
  F14<char> cv4(cv2.begin(), cv2.end());
  
  F14<int> iv(5, 6);
  F14<double> dv;

  F14<string> sv(11);

  F14<string> sn(1);
  
  try {
    // a hftest elso azonosito sorat adja
    cout << sn.get_back() << endl;
    cout << "Feladat = 14" << endl; 
    // Kiirtuk hftest azonosító sorokat
    cout << endl;

    sv.back() = string("C++");
    cout << sv.back() << endl;
    cv2.push_back('?');
    cv2.push_back('n');
    cv2.push_back('\n');
    iv.front() = 12;
    iv.push_back(64);

    // itt kevesebb kellene
    cout << iv.get_back();

    // osFunctor tesztje 
    for_each(cv2.begin(), cv2.end(), osFunctor<char>(cout));

    // osFunctor tesztje 
    for_each(iv.begin(), iv.end(), osFunctor<int>(cout, ", "));

  } catch (exception& e) {
    cerr << "baj van:"  << e.what() << endl;
  }
  fflush(stdin);
  getchar();
  return 0;
}
