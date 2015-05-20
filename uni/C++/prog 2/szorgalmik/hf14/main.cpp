#include <iostream>
#include <vector>
#include <time.h>

template<class T>
class greedyVector : public std::vector<T>
{
private: int counter;
public:
	T pop()
	{
		srand(time(0));
		if (rand() % 4 == 0)
		{
			if (this->empty())
			{
				throw std::out_of_range("out of range");
			}
			T tmp = this->back();
			this->pop_back();
			return tmp;
		}
		else
		{
			return 0;
		}
	}
};

int main()
{
	greedyVector<int> foo = { 1, 2, 3, 4, 5 };
	std::cout << "penis";

	fflush(stdin);
	getchar();
	return 0;
}