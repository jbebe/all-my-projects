#include "vektor.h"
#include <cstring>

unsigned int Vektor::defSize = 11;
double Vektor::defValue = -393;

Vektor::Vektor(const Vektor& that) : 
	pVec(new double[that.nElements]),
	nElements(that.nElements)
{
	memcpy(pVec, that.pVec, nElements * sizeof(double));
}

Vektor::~Vektor()
{
	if (nElements != 0)
	{
		delete[] pVec;
	}
}

Vektor& Vektor::operator =(const Vektor& rhs)
{
	if (this != &rhs)
	{
		delete[] pVec;
		nElements = rhs.nElements;
		pVec = new double[nElements];
		memcpy(pVec, rhs.pVec, nElements * sizeof(double));
	}
	return *this;
}

double& Vektor::operator[](unsigned int idx)
{
	if (idx >= nElements || idx < 0)
	{
		throw "CGQ956";
	}
	return pVec[idx];
}

const double& Vektor::operator[](unsigned int idx) const
{
	if (idx >= nElements || idx < 0)
	{
		throw "CGQ956";
	}
	return pVec[idx];
}

Vektor operator*(double val, const Vektor& vec)
{
	Vektor out = vec;
	for (unsigned int i = 0; i < vec.nElements; ++i)
	{
		out[i] *= val;
	}
	return out;
}