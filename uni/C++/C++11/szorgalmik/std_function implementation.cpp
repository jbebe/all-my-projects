#include <functional>
#include <iostream>
#include <cmath>

template <typename Tret, typename... Targs>
struct CalleeBase {
    virtual Tret operator()(Targs...) = 0;
    virtual ~CalleeBase(){}
};

template <typename T, typename Tret, typename... Targs>
struct Callee : CalleeBase<Tret, Targs...> {
    T f;

    Callee(const T& f) : f(f) {}

    Tret operator()(Targs... args) {
        return f(args...);
    }
};

template <typename Tret, typename... Targs>
struct my_function;

template <typename Tret, typename... Targs>
struct my_function<Tret(Targs...)> {
    CalleeBase<Tret, Targs...> *fn = nullptr;

    template<typename T>
    my_function &operator=(T f) {
        delete fn;
        fn = new Callee<T, Tret, Targs...>(f);
        return *this;
    }

    my_function &operator=(std::nullptr_t) {
        delete fn;
        fn = nullptr;
        return *this;
    }

    Tret operator()(Targs... args) {
        if (fn == nullptr)
            throw std::bad_function_call();
        return (*fn)(args...);
    }

    bool operator ! () {
        return fn == nullptr;
    }
};

int main() {
    my_function<double(double) > f;

    if (!f)
        std::cout << "Egyelőre nullptr" << std::endl;

    f = sin;
    std::cout << sin(2.3) << "==" << f(2.3) << std::endl;

    f = [] (double x) {
        return x*x;
    };
    std::cout << 2.3 * 2.3 << "==" << f(2.3) << std::endl;

    f = std::bind(pow, std::placeholders::_1, 4);
    std::cout << pow(2.3, 4) << "==" << f(2.3) << std::endl;

    f = nullptr;
    try {
        f(2.3);
    } catch (std::bad_function_call &e) {
        std::cout << "Megint nullptr" << std::endl;
    }
    struct dummy {
        static double get(double a){ return a; }
    };

    f = dummy::get;

    std::cout << "Statikus tagfuggveny: " << f(5.0) << std::endl;
}