#include "resistor.h"

double Resistor::defR = 18600;

Resistor::Resistor() : R(defR) {}

Resistor::Resistor(const Resistor& rhs) : R(rhs.R) {}

Resistor::Resistor(const double r) {
	R = r;
}

void Resistor::setDef(const double r) {
	defR = r;
}

void Resistor::setR(const double r)
{
	R = r;
}

Resistor Resistor::operator+(const Resistor& r) const {
	return Resistor(R + r.R);
}

Resistor Resistor::operator%(const Resistor& r) const {
	return Resistor(1 / (1 / R + 1 / r.R));
}

Resistor& Resistor::operator=(const Resistor& rhs)
{
	R = rhs.R;
	return *this;
}

bool Resistor::operator==(const Resistor& rhs)
{
	return R == rhs.R;
}

Resistor operator*(const int n, const Resistor& r){
	if (n < 1)
		throw "CGQ956";
	return Resistor(r.getR() * n);
}

std::ostream& operator<<(std::ostream& o, const Resistor& rhs)
{
	return o << rhs.getR();
}