/* Miert van az az erzesem, hogy ennel lehetne rovidebben is :D */
/* Amugy azert igy irtam, mert nem akartam tobb tarolot hasznalni. */

#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    using myPair = std::pair<int, std::string>;
    using vecMap = std::vector<myPair>;
    using vecMapIt = vecMap::iterator;
    vecMap l;
    std::string s;

    while (std::cin >> s){
        vecMapIt found = std::find_if(l.begin(), l.end(), [&](myPair const &a){ return a.second == s; });
        if (found != l.end())
            (*found).first++;
        else
            l.push_back(std::make_pair(1, s));
    }
    std::sort(l.begin(), l.end(), [](myPair const &a, myPair const &b){ return a.first < b.first; });
    for (auto p : l)
        std::cout << p.first << " " << p.second << std::endl;
}
