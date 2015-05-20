#ifndef H_F8
#define H_F8

#include <iostream>
#include <stdexcept> 
#include <iomanip>
#include <cstdlib>

template <int TSize> class F8 
{
	double data[TSize];
	int template_size,
		size;
	public:
		F8() : template_size(TSize), size(0) {}
		F8(const F8& rhs);

		inline const char *c_str(){ 
			return "Juhasz Balint,1MI,5,L4-R4D <j.balint@t-online.hu> CGQ956"; 
		}
		void rendez();
		F8& operator=(const F8& rhs);
		double& operator[](const int iterator);
		friend std::ostream& operator<<(std::ostream& o, const F8& rhs)
		{
			return o << std::fixed << std::setprecision(4) 
				<< rhs.data[21] << std::endl
				<< rhs.data[86] << std::endl
				<< rhs.data[50] << std::endl
				<< rhs.data[49] << std::endl
				<< rhs.data[383];
		}
};

/* --------------------------------------------------------------- */

template <int TSize> F8<TSize>::F8(const F8& rhs)
: size(rhs.size)
{
	for (int i = 0; i < size; ++i)
	{
		data[i] = rhs.data[i];
	}
}

int cmpdbl(const void *v1, const void *v2)
{
	double	*a = (double *)v1,
			*b = (double *)v2;
	return ((*a > *b) ? -1 : ((*a == *b) ? 0 : 1));
}
template <int TSize> void F8<TSize>::rendez()
{
	qsort(data, size, sizeof(data[0]), cmpdbl);
}

template <int TSize> F8<TSize>& F8<TSize>::operator=(const F8<TSize>& rhs)
{
	size = rhs.size;
	for (int i = 0; i < size; ++i)
	{
		data[i] = rhs.data[i];
	}
	return *this;
}

template <int TSize> double& F8<TSize>::operator[](const int iterator)
{
	if (iterator >= template_size || iterator < 0)
	{
		throw std::out_of_range("out_of_range");
	}
	if (iterator >= size)
	{
		size = iterator + 1;
	}
	return data[iterator];
}

#endif