#include <iostream>
#include <tuple>
#include <sstream>

// könnyebbik fele
template <typename ARG>
void unpack(std::string fmt, ARG &arg){
    std::stringstream{fmt} >> arg;
}

template <typename ARG1, typename... ARGS>
void unpack(std::string fmt, ARG1 &arg1, ARGS&... args){
    std::stringstream fmtBuff{fmt};
    fmtBuff >> arg1 >> fmt;
    unpack(fmt, args...);
}

// 4. laborfeladat
template<int ...> struct seq {};
template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};
template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };

// nehezebbik fele
template <typename ...ARGS>
struct listData {
    std::tuple<ARGS&...> t;
    
    listData(ARGS&... args): t{std::tie(args...)} {}

    // utolsó laborfeladat
    void operator = (std::string values){
        callFunc(values, typename gens<sizeof...(ARGS)>::type());
    }
    template<int ...S>
    void callFunc(std::string values, seq<S...>) const {
        unpack(values, std::get<S>(t)...);
    }
};

template <typename ...ARGS>
inline listData<ARGS&...> list(ARGS&... args){
    return listData<ARGS&...>{args...};
}

// nehezbbik felének könnyebbik fele
inline const std::string explode(const std::string values){
    return values;
}

int main(int argc, char** argv) {
    int a;
    double b;
    list(a, b) = explode("3 4.5");

    std::cout << "a: " << a << std::endl << "b: " << b << std::endl;
    return 0;
}
