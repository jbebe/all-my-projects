#include "mystring.h"

MyString::MyString()
: strVal{nullptr}, refCnt{nullptr} {}

MyString::MyString(const char *inputStr)
: strVal{new char[strlen(inputStr) + 1]}, refCnt{new size_t{1}} {
	strcpy(strVal, inputStr);
}

MyString::MyString(const MyString &copy)
: strVal{copy.strVal}, refCnt{&(++(*copy.refCnt))} {}

MyString::MyString(MyString &&move)
: strVal{move.strVal}, refCnt{move.refCnt} {
	move.strVal = nullptr;
	move.refCnt = 0;
}

void MyString::release(){
	if (strVal != nullptr && (*refCnt)-- == 1){
		//std::cout << "[DEBUG] unused string deleted\n";
		delete refCnt;
		delete[] strVal;
	}
}

MyString::~MyString(){
	release();
}

MyString &MyString::operator = (const MyString &rhs){
	release();
	strVal = rhs.strVal;
	refCnt = &(++(*rhs.refCnt));
	return *this;
}

MyString &MyString::operator = (MyString &&move){
	release();
	strVal = move.strVal;
	refCnt = move.refCnt;
	move.strVal = nullptr;
	move.refCnt = nullptr;
	return *this;
}

MyString MyString::operator + (const MyString &rhs) const {
	size_t	thisLen = strlen(strVal);
	char *tempStr = new char[thisLen + strlen(rhs.strVal) + 1];
	strcpy(tempStr, strVal);
	strcpy(tempStr + thisLen, rhs.strVal);
	MyString tempMy{tempStr};
	delete[] tempStr;
	return tempMy;
}

MyString &MyString::operator += (const MyString &rhs){
	return operator=(operator+(rhs));
}

MyString MyString::operator + (const char rhs) const {
	char temp[] = {rhs, '\0'};
	return operator+(MyString{temp});
}

MyString &MyString::operator += (const char rhs){
	return operator=(operator+(rhs));
}

char &MyString::operator [ ] (const size_t index){
	return strVal[index];
}

size_t MyString::length() const {
	return strVal != nullptr ? strlen(strVal) : 0;
}

std::ostream &operator << (std::ostream &os, MyString &m){
	return os << (m.strVal != nullptr ? m.strVal : "\"\"");
}

std::ostream &operator << (std::ostream &os, MyString &&m){
	return os << (m.strVal != nullptr ? m.strVal : "\"\"");
}

std::istream &operator >> (std::istream &is, MyString &m){
	char buffer[256];
	is.getline(buffer, 256);
	m.operator=(MyString{buffer});
	return is;
}
