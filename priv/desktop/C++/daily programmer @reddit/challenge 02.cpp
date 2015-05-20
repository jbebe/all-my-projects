#include <iostream>
#include <fstream>
#include <string>

class User {
protected:
	std::string name;
	std::string username;
	unsigned short age;
public:
	void setName(std::istream &stringline){std::getline(stringline,name);}
	void setName(std::string stringline){name = stringline;}
	void setUser(std::istream &stringline){std::getline(stringline,username);}
	void setUser(std::string stringline){username = stringline;}
	void setAge(std::istream &stringline){
		std::string temp;
		std::getline(stringline,temp);
		age = std::stoi(temp);
	}
	void setAge(int age){ this->age = age; }
	std::string getName(){ return name; }
	std::string getUser(){ return username; }
	unsigned short getAge(){ return age; }
};

class Challenge : public User {
public:
	std::string report(){ 
		return "Your name is  " + name + "\nyour reddit username is " + username + "\nand you are " + std::to_string(age) + " years old"; 
	}
	void save(std::string filedir){
		std::ofstream output_file(filedir);
		output_file.clear();
		output_file << report();
		output_file.close();
	}
};

int main(){
	Challenge u1;
	std::cout << "What is your name? ";
	u1.setName(std::cin);
	std::cout << "What is your reddit username? ";
	u1.setUser(std::cin);
	std::cout << "How old are you? ";
	u1.setAge(std::cin);
	
	std::cout << u1.report();

	std::string yesno;
	std::cout << "\nWould you like to save it? (yes/no)";
	std::cin >> yesno;
	if (yesno == "yes"){
		u1.save("kaki.log");
	}
	return 0;
}