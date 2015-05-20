#define _CRT_SECURE_NO_WARNINGS


#include "f10.h"
#include <cstring>

F10::F10() : 
	line(new char[1]), len(0) 
{
	strcpy(line, "");
}

F10::F10(const F10& that) : 
	line(new char[that.len + 1]),
	len(that.len)
{
	strcpy(line, that.line);
}

F10::~F10()
{
	delete[] line;
}

const char *F10::ident() const {
	return "Juhasz Balint,1MI,5,L4-R4D <j.balint@t-online.hu> CGQ956";
}

bool F10::match(const char *line)
{
	len = strlen(line) + 1;
	this->line = new char[len];
	strcpy(this->line, line);
	return strstr(line, "alak") != NULL 
			|| strstr(line, "csucsbol") != NULL 
			|| strstr(line, "osztalyatol") != NULL;
}

const char *F10::getLine() const
{
	return line;
}

F10& F10::operator=(const F10& that)
{
	if (this != &that)
	{
		delete[] line;
		len = that.len;
		line = new char[len + 1];
		strcpy(line, that.line);
	}
	return *this;
}