#include <iostream>
#include <utility>
#include <sstream>

#include "mystring.h"

using std::cout;
using std::endl;

#define assist(testCase) cout << endl << "- - - line " << __LINE__ << ": " << testCase << " - - -" << endl;

int main() {
	{
		assist("empty ctor");
		MyString empty{};
		cout << empty << endl;
	}
	{
		assist("char* ctor");
		MyString str{"Hello!"};
		cout << str << endl;
	}
	{
		assist("operator<< &&");
		cout << MyString{"Hello!"} << endl;
	}
	{
		assist("copy ctor");
		MyString str1{"Hello!"}, str2{str1};
		cout << str2 << endl;
	}
	{
		assist("move ctor");
		MyString str{MyString{"Hello!"}};
		cout << str << endl;
	}
	{
		assist("operator=MyString&");
		MyString str1{"Hello!"}, str2{"World!"};
		str1 = str2;
		cout << str1 << endl;
	}
	{
		assist("operator=MyString&&");
		MyString str1{"Hello!"}, str2{"World!"};
		str1 = std::move(str2);
		cout << str1 << endl;
	}
	{
		assist("operator+MyString");
		cout << (MyString("Hello ") + MyString("World!")) << endl;
	}
	{
		assist("operator+=MyString");
		MyString str{"Hello "};
		str += MyString{"World!"};
		cout << str << endl;
	}
	{
		assist("operator+char");
		MyString str{"Hello"};
		cout << (str + '!') << endl;
	}
	{
		assist("operator+=char");
		MyString str{"Hello"};
		str += '!';
		cout << str << endl;
	}
	{
		assist("operator[]");
		MyString str{"Hello!"};
		cout << str[0] << str[1] << str[2] << str[3] << str[4] << str[5] << endl;
	}
	{
		assist("MyString.size()");
		MyString str{"Hello!"};
		cout << "Length of \"" << str << "\": " << str.length() << endl;
	}
	{
		assist("cin>>MyString");
		MyString str{};
		std::stringstream ss{"Hello!"};
		ss >> str;
		cout << str << endl;
	}
	return 0;
}
