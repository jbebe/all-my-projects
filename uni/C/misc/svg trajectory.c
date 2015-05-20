#include <stdio.h>
#include <math.h>

#define WIDTH 640.0
#define HEIGHT 480.0

const double 
	PI = 3.14159265359,
	MAX_VEL = 120.0,
	MIN_VEL = 30.0;

const struct { double x, y, r; } 
	b1 = {50.0, HEIGHT-50.0, 24.0},
	b2 = {WIDTH-50.0, HEIGHT-50.0, 24.0};

void circle(double x, double y, double r){
	printf("\t<circle cx=\"%.0lf\" "
		"cy=\"%.0lf\" r=\"%.0lf\"/>\n", 
		x, y, r);
}

double x(double v0, double t, double alpha){
	return v0*t*cos(alpha)+b1.x;
}

double y(double v0, double t, double alpha){
	return-((v0*t*sin(alpha))-(4.905*t*t))+b1.y;
}

void replay(double v0, double t_max, double alpha){
	static int text_iter = 1;
	double t;
	for (t = 0.0; t <= t_max; t += 0.2)
		circle(x(v0, t, alpha), y(v0, t, alpha), 1.0);
	printf("<text x=\"10\" y=\"%d\">#%d "
		"angle: %.0lf&deg;, vel: %.1lf m/s</text>",
		text_iter*18, text_iter, alpha*180.0/PI, v0/20.0);
	++text_iter;
}

int main(void){
	double t, v0, alpha, temp_x, temp_y;
	printf("<svg width=\"%.0lf\" height=\"%.0lf\" version=\"1.1\" "
		"xmlns=\"http://www.w3.org/2000/svg\">\n", 
		WIDTH, HEIGHT, WIDTH, HEIGHT);
	circle(b1.x, b1.y, b1.r);
	circle(b2.x, b2.y, b2.r);
	for (alpha = 0.0; alpha < PI/2.0; alpha += 5.0*PI/180.0){
		for (v0 = MIN_VEL; v0 <= MAX_VEL; v0 += 10.0){
			for (t = 0.0; ;t += 0.05){
				temp_x = x(v0, t, alpha);
				temp_y = y(v0, t, alpha);
				if ((temp_x > b2.x + (b2.r*cos(alpha)))
					|| (temp_y > b2.y + (b2.r*sin(alpha))))
					break;
				if (temp_x >= b2.x-b2.r && temp_x <= b2.x+b2.r 
					&& temp_y >= b2.y-b2.r && temp_y <= b2.y+b2.r){
					replay(v0, t, alpha);
					break;
				}
			}
		}
	}
	printf("</svg>");
	return 0;
}
