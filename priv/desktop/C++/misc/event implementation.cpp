#include <iostream>
#include <forward_list>
#include <string>
#include <algorithm>
#include <exception>

template <typename T>
class event {
private:
	using delegate_t = T;
	std::forward_list<delegate_t> functions;
public:
	event(): functions{std::forward_list<delegate_t>{}} {}
	void operator += (T func){
		functions.push_front(func);
	}
	void operator -= (T func){
		functions.remove_if([func](delegate_t f) -> bool { return f == func; });
	}
	void operator () (std::string s){
		for (auto &fn : functions) fn(s);
	}
};

class LogMonitor {
	using monitorFn_t = void (*)(std::string);
public:
	event<monitorFn_t> onChange;
	void run(){
		onChange("information");
	}
};

void removeThis(std::string){ printf("i should not be here"); }

int main(){
	LogMonitor m;
	m.onChange += removeThis;
	m.onChange += [](std::string s) -> void { printf("fancy function ~~%s~~\n", s.c_str()); };
	m.onChange += [](std::string s) -> void { printf("simple function %s\n", s.c_str()); };
	m.onChange -= removeThis;
	m.run();
}
