#include <iostream>
#include <sstream>

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

int main(int argc, char** argv) {
    int a = 0;
    double b = 0;
    unpack("3 4.5", a, b); // a = 3; b = 4.5;
    std::cout << "a: " << a << ", b: " << b << std::endl;
    
    return 0;
}

