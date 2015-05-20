#include <iostream>
#include <fstream>
#include <string>
#include <map>
int main(){
	bool access_granted = false;
	std::string user_in, 
				password_in,
				temp;
	std::map<std::string,std::string> users;
	std::map<std::string,std::string>::iterator it = users.begin();
	std::fstream log("auth.ini");
	while (log.good()){
		std::getline(log,temp);
		users.insert(it, std::pair<std::string,std::string>(
			temp.substr(0,temp.find_first_of(' ')),
			temp.substr(temp.find_first_of(' ') + 1,temp.length())
		));
    }
	do {
		std::cout	<< "Welcome to Aperture Science Labs.\n"
					<< "login: ";
		std::getline(std::cin,user_in);
		std::cout	<< "password: ";
		std::getline(std::cin,password_in);
		for (it = users.begin(); it != users.end(); ++it)
			if (it->first == user_in && it->second == password_in)
				access_granted = true;
		system("cls");
	} while (!access_granted);
	std::cout << "Welcome!";
	getchar();
	return 0;
}