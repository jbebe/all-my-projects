#include <iostream>
#include <stack>

class base
{
private:
	const int baseNum;
	std::ostream *osPtr;
public:
	const static char symbols[];
	base(int baseNum, std::ostream *osPtr = nullptr) : baseNum{baseNum}, osPtr{osPtr} {}
	int getBase() const { return baseNum; }
	std::ostream &getOS() { return *osPtr; }
};
const char base::symbols[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

base operator<<(std::ostream &os, base b){
    return base(b.getBase(), &os);
}

base operator<<(base b, int a){
	std::stack<char> buffer;
	while (a > 0){
		buffer.push(a%(b.getBase()));
		a = a/(b.getBase());
	}
	while (!(buffer.empty())){
		b.getOS() << base::symbols[buffer.top()%36];
		buffer.pop();
	}
	return b;
}

int main() {
	std::cout << base(2) << 240;    // 11110000
	std::cout << std::endl;
	std::cout << base(16) << 240;   // F0
	std::cout << std::endl;
	std::cout << base(34) << 1089483 << 25796;   // ROFLMAO
	return 0;
}
