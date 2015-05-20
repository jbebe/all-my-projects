#include <iostream>
#include <string>

class Physics {
private:
	double	F,
			m,
			a;
public:
	Physics(){
			F = 0;
			m = 0;
			a = 0;
	}
	void	set_F(double F)	{ this->F = F; }
	void	set_m(double m)	{ this->m = m; }
	void	set_a(double a)	{ this->a = a; }
	double	get_F()			{ return m*a; }
	double	get_m()			{ return F/a; }
	double	get_a()			{ return F/m; }
};

int main(){
	char unknown;
	double F,m,a;
	Physics *Fmt = new Physics();
	std::cout	<< "What do you want to calculate?\n"
				<< "[F]orce\n"
				<< "[m]mass\n"
				<< "[a]cceleration ";
	std::cin >> unknown;
	if (unknown != 'F'){
		std::cout << "Force: ";
		std::cin >> F;
		Fmt->set_F(F);
	}
	if (unknown != 'm'){
		std::cout << "mass: ";
		std::cin >> m;
		Fmt->set_m(m);
	}
	if (unknown != 'a'){
		std::cout << "acceleration: ";
		std::cin >> a;
		Fmt->set_a(a);
	}
	std::cout << ((unknown == 'F') ?
			Fmt->get_F()
		:
			(
				(unknown == 'm') ?
					Fmt->get_m()
				:
					Fmt->get_a()
			)
	);
	std::cin >> F;
	return 0;
}