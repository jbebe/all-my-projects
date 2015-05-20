#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define PI 3.14159265359f
#define WIDTH 280
#define HEIGHT 432
#define CENTER_X 140.0f
#define CENTER_Y 216.0f

void svg_initialize(short width, short height){
	printf("<?xml version=\"1.0\"?>\n"
		"<svg width=\"%d\" height=\"%d\" "
		"xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" "
		"xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
		"\t<filter id=\"shadow\">\n"
		"\t\t<feGaussianBlur in=\"SourceGraphic\" stdDeviation=\"7\"/>\n"
		"\t</filter>\n"
		"\t<defs>\n"
		"\t\t<linearGradient id=\"clock_outer\">\n"
		"\t\t\t<stop offset=\"0%%\" stop-color=\"#cecece\"/>\n"
		"\t\t\t<stop offset=\"50%%\" stop-color=\"#666\"/>\n"
		"\t\t\t<stop offset=\"100%%\" stop-color=\"#cecece\"/>\n"
		"\t\t</linearGradient>\n"
		"\t\t<radialGradient id=\"clock_inner\">\n"
		"\t\t\t<stop offset=\"0%%\" stop-color=\"#444444\"/>\n"
		"\t\t\t<stop offset=\"100%%\" stop-color=\"#262626\"/>\n"
		"\t\t</radialGradient>\n"
		"\t</defs>\n",
		width, height);
}
void svg_end(){ printf("</svg>"); }
void svg_circle(short x, short y, short r, char *color){
	printf("\t<circle cx=\"%d\" cy=\"%d\" r=\"%d\" "
		"style=\"fill:%s\" />\n",
		x, y, r, 
		(r == 100 ? "url(#clock_outer)" 
			: (r == 88 ? "url(#clock_inner)" : color)));
}
void svg_ellipse(short x, short y, short r1, short r2, char *color){
	printf("\t<ellipse cx=\"%d\" cy=\"%d\" "
		"rx=\"%d\" ry=\"%d\" style=\"fill:%s\"/>\n",
			x, y, r1, r2, color);
}
void svg_rect(short x, short y, short width, short height, char *color){
	printf("\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" "
		"style=\"fill:%s\"/>\n",
		x, y, width, height, color);
}
void svg_polygon(char *coords, char *color){
	printf("\t<polygon points=\"%s\" "
		"style = \"fill:%s\" />\n", 
		coords, color);
}
void svg_polygon_shadow(char *coords, char *color){
	printf("\t<polygon points=\"%s\" "
		"style=\"fill:%s;filter:url(#shadow);\" />\n",
			coords, 
			color);
}
void svg_lines(float ratio, float offset, float w, float h, char *color){
	ratio *= 2.0*PI;
	printf("\t<line "
		"x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" "
		"style=\"stroke-width:%dpx;stroke:%s;\"/>\n",
		(int) (CENTER_X + offset*sinf(ratio)),
		(int) (CENTER_Y - offset*cosf(ratio)),
		(int) (CENTER_X + (h + offset)*sinf(ratio)),
		(int) (CENTER_Y - (h + offset)*cosf(ratio)),
		(int) w, color);
}
void svg_second(float angle_ratio){ 
	svg_lines(angle_ratio, 0.0, 1.0, 75.0, "#d00"); 
}
void svg_minute(float angle_ratio){ 
	svg_lines(angle_ratio, 0.0, 3.0, 70.0, "#bbb"); 
}
void svg_hour(float angle_ratio){ 
	svg_lines(angle_ratio, 0.0, 4.0, 50.0, "#999"); 
}
void svg_guide_min(float minute){ 
	svg_lines(minute / 60.0, 80.0, 1.0, 5.0, "#000"); 
}
void svg_guide_quarter(float minute){ 
	svg_lines(minute / 60.0, 75.0, 3.0, 10.0, "#000"); 
}
void svg_text(char *text, short x, short y, char size, char *fam, char *col){
	printf("\t<text x=\"%d\" y=\"%d\" font-style=\"italic\" "
		"style=\"font:%d/%d %s;fill:%s;\">%s</text>\n", 
		x, y, size, size, fam, col, text);
}
void svg_month(){
	struct tm *tm;
	time_t t_now;
	time(&t_now);
	tm = localtime(&t_now);
	printf("\t<text x=\"178\" y=\"220\" "
		"style=\"font:11px Arial,Tahoma,Verdana;fill:#333;"
		"font-weight:900;\">%02d</text>\n",
		tm->tm_mday);
}

int main(void){
	struct {
		float hour, min, sec;
	} time;
	float i;

	scanf("%f %f %f", &time.hour, &time.min, &time.sec);
	if (time.hour > 24 || time.min > 59 || time.sec > 59){
		return EXIT_FAILURE;
	}

	svg_initialize(WIDTH, HEIGHT);
	// draw static stuff
	svg_rect(0, 0, WIDTH, HEIGHT, "#eee");
	svg_polygon_shadow("75,92 204,92 208,216 204,338 75,338 71,216", "#999");
	svg_polygon("75,92 204,92 208,216 204,338 75,338 71,216", "#999");
	svg_rect(86, 0, 108, 432, "#111");
	svg_polygon("86,116 96,112 184,112 194,116 194,316 183,320 96,320 86,316",
		"#ccc");
	// time adjuster 
	svg_rect(242, 214, 6, 10, "#999");
	svg_rect(246, 209, 7, 20, "#ccc");
	svg_ellipse(252, 219, 4, 10, "#ccc");
	for (i = 0.0; i < 10.0; i+=1.0)
		svg_rect(247, 210 + (int)(i*2.0), 5, 1, "#777");
	// shiny clock surface and stuff
	svg_circle(140, 216, 102, "#bbb");
	svg_circle(140, 216, 100, "#dcdcdc");
	svg_circle(140, 216, 90, "#bbb");
	svg_circle(140, 216, 88, "#262626");
	// guides
	for (i = 0.0; i < 60.0; i+=1.0)
		if (fmodf(i, 5.0) == 0)
			svg_guide_quarter(i); 
		else
			svg_guide_min(i);
	// brand...
	svg_text("bebe", CENTER_X-15, CENTER_Y+50, 15, "Georgia, serif", "#666");
	// waddayisit?
	svg_rect(174, 213, 196 - 174, 217 - 211, "#ddd");
	svg_rect(174 + 3, 210, 197 - 174 - 6, 223 - 211, "#ddd");
	svg_circle(177, 213, 3, "#ddd");
	svg_circle(193, 213, 3, "#ddd");
	svg_circle(177, 219, 3, "#ddd");
	svg_circle(193, 219, 3, "#ddd");
	svg_month();
	// pointers & cover
	svg_second(time.sec/60.0);
	svg_minute((time.min+time.sec/60.0)/60.0);
	svg_hour(((fmodf(time.hour,12))+time.min/60.0)/12.0);
	svg_circle((int) CENTER_X, (int) CENTER_Y, 7, "#cecece");
	svg_circle((int) CENTER_X, (int) CENTER_Y, 4, "#fff");
	svg_circle((int) CENTER_X, (int) CENTER_Y, 2, "#333");
	svg_end();
	return EXIT_SUCCESS;
}