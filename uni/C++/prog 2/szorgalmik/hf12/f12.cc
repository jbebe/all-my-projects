#include "f12.h"
#include <iostream>

/**
* Queue osztaly
*/

Queue::Queue(const char *p)
{
	if (p != NULL)
	{
		for (int i = 0; p[i] != 0; ++i)
		{
			q.push_back(p[i]);
		}
	}
}

char Queue::pop_back()
{
	if (q.empty())
	{
		throw std::underflow_error("underflow_error");
	}
	char tmp = q.back();
	q.pop_back();
	return tmp;
}

void Queue::push_front(const char c)
{
	q.push_front(c);
}

char Queue::pop_front()
{
	if (q.empty())
	{
		throw std::underflow_error("underflow_error");
	}
	char tmp = q.front();
	q.pop_front();
	return tmp;
}

bool Queue::empty()
{
	return q.empty();
}

Queue::myIterator Queue::begin()
{
	return q.begin();
}

Queue::myIterator Queue::end()
{
	return q.end();
}

/**
* F2 osztaly
*/
const char *F2::myId = "Juhasz Balint,1MI,5,L4-R4D <j.balint@t-online.hu> CGQ956";

double F2::f(double x) const
{
	return 
		x > 63 ?
			x / 95.90 
			:
			0.374*x*x*x*x - 0.748*x*x*x + 47.88*x*x + 15*x - 63.0;
}