#ifndef F14_H
#define F14_H

#include <vector>
#include <stdexcept>

template<class T>
class F14 : public std::vector<T>
{
public:
	F14();
};

template<>
class F14<char> : public std::vector<char>
{
public:
	F14(int size = 0, char def = 0){
		for (int i = 0; i < size; ++i){
			this->push_back(def);
		}
	}
	F14(iterator begin, iterator end) : std::vector<char>(begin, end) {}
};

template<>
class F14<int> : public std::vector<int>
{
public:
	F14(int size = 0, int def = 0){
		for (int i = 0; i < size; ++i){
			this->push_back(def);
		}
	}
	int get_back(){
		if (this->empty()){
			throw std::out_of_range("out_of_range");
		}
		int tmp = this->back() - 63;
		this->pop_back();
		return tmp;
	}
};

template<>
class F14<double> : public std::vector<double> {
public:
	F14(int size = 0, double def = 0){
		for (int i = 0; i < size; ++i){
			this->push_back(def);
		}
	}
	double get_back(){
		if (this->empty()){
			throw std::out_of_range("out_of_range");
		}
		double tmp = this->back();
		this->pop_back();
		return tmp;
	}
};

template<>
class F14<std::string> : public std::vector<std::string>
{
public:
	F14(int size, std::string def = ""){
		for (int i = 0; i < size; ++i){
			this->push_back(def);
		}
	}
	const char *get_back(){
		if (this->empty()){
			throw std::out_of_range("out_of_range");
		}
		this->pop_back();
		return "Juhasz Balint <j.balint@t-online.hu> CGQ956";
	}
};

#include <cstring>
#define _CRT_SECURE_NO_WARNINGS

template <class T>
class osFunctor {
private:
	std::ostream& osRef;
	char delim[3];
public:
};

template <> 
class osFunctor<char> {
private:
	std::ostream& osRef;
	char delim[3];
public:
	osFunctor(std::ostream& o, const char *d = "") : osRef(o){
		memcpy(delim, d, strlen(d)+1);
	}
	void operator()(char iter){
		osRef << iter << delim;
	}
};

template <>
class osFunctor<int> {
private:
	std::ostream& osRef;
	char delim[1000];
public:
	osFunctor(std::ostream& o, const char *d = "") : osRef(o){
		memcpy(delim, d, strlen(d) + 1);
	}
	void operator()(int iter){
		osRef << iter << delim;
	}
};

#endif