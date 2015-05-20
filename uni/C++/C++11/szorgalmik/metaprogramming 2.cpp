// érzem hogy ez nem az a bizonyos elegáns megoldás. 
// std::pair-re nem tudtam operator overload-ot mert már foglalt volt 

#include <iostream>
#include <tuple>

template <typename T>
struct PairWrapper {
    std::pair<T, T> value;
    PairWrapper<T> operator = (PairWrapper<T> rhs){
        auto temp = *(value.first);
        *(value.first) = *(value.second);
        *(value.second) = temp;
        return *this;
    }
};

template<typename T>
PairWrapper<T *> $(T &x, T &y){
    PairWrapper<T *> p;
    p.value = std::make_pair(&x, &y);
    return p;
}

int main() {
    int x = 5, y = 7;
    std::cout << "x: " << x << " y: " << y << std::endl;
    $(x, y) = $(y, x);
    std::cout << "x: " << x << " y: " << y << std::endl;
    return 0;
}