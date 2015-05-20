#include <iostream>
#include <string>
#include <map>
#include <array>
#include <list>
#include <Windows.h>

class Morse {
private:
	std::map<char,std::string> abc_c;
	std::map<std::string,char> abc_s;
public:
	Morse(){
		std::array<std::string,26> temp = {	
			".-","-...","-.-.","-..",".","..-.","--.","....",
			"..",".---","-.-",".-..","--","-.","---",".--.",
			"--.-",".-.","...","-","..-","...-",".--","-..-",
			"-.--","--.."
		};
		for (int i = 0; i < 26; i++){
			abc_c.insert(std::pair<char, std::string>( 
				'a' + i,
				temp.at(i)
			));
			abc_s.insert(std::pair<std::string, char>(
				temp.at(i),
				'a' + i
			));
		}
	}
	std::string decode(std::string input){
		std::list<std::string> codes;
		std::list<std::string>::iterator it;
		unsigned char space_at = 0;
		std::string temp;
		while (1){
			space_at = input.find_first_of(' ');
			if (space_at == 255){
				codes.push_front(input);
				break;
			}
			temp = input.substr(0,space_at);
			input = input.substr(space_at + 1,input.length());
			codes.push_front(temp);
		}
		input = "";
		for (it = codes.begin(); it != codes.end(); ++it){
			if (abc_s.find(*it) != abc_s.end())
				input = abc_s.at(*it) + input;
			else 
				input = " " + input;
		}
		return input;
	}
	std::string encode(std::string input){
		std::list<char> codes;
		std::list<char>::iterator it;
		int length = input.length();
		while (length--)
			codes.push_front(input.at(length));
		input = "";
		for (it = codes.begin(); it != codes.end(); ++it){
			if (abc_c.find(*it) != abc_c.end())
				input = input + abc_c.at(*it) + " ";
			else
				input = input + "/ ";
		}
		return input;
	}
	void beep(std::string input){
		for (unsigned short i = 0; i < input.length(); i++)
			switch (input.at(i)){
			case '.':
				Sleep(50);
				Beep(500,100);
				break;
			case '-':
				Sleep(50);
				Beep(500,300);
				break;
			case ' ':
				Sleep(200);
				break;
			default:
				if (input.at(i+1) == ' ') i++;
				break;
			}
	}
};
int main(){
	Morse mrs;
	std::string input = ".... . .-.. .-.. --- / -.. .- .. .-.. -.-- / .--. .-. --- --. .-. .- -- -- . .-. / --. --- --- -.. / .-.. ..- -.-. -.- / --- -. / - .... . / -.-. .... .- .-.. .-.. . -. --. . ... / - --- -.. .- -.--";
	std::cout << input << std::endl;
	std::cout << mrs.decode(input) << std::endl;
	std::cout << mrs.encode("hello daily programmer good luck on the challenges today");
	mrs.beep(input);
	getchar();
	return 0;
}