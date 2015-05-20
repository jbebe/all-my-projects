// important includes
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>

// my vars
#define WIDTH 80
#define HEIGHT 37
#define GAMEWIDTH 80
#define GAMEHEIGHT 31

// colors
	typedef enum color {
		black,darkblue,darkgreen,darkcyan,darkred,darkmagenta,darkyellow,
		grey,darkgrey,blue,green,cyan,red,magenta,yellow,white
	} color;

// terrain
	typedef enum {
		rock = '#', debris = '3', floor = ' ', killer = '*'
	} MATERIAL_TYPES;

	typedef struct {
		char texture;
		color foreground;
		color background;
		unsigned char diggable;
	} MATERIAL;

	typedef struct {
		MATERIAL rock;
		MATERIAL debris;
		MATERIAL floor;
		MATERIAL killer;
	} TERRAIN;

// character object
	typedef struct {
		unsigned char x;
		unsigned char y;
		unsigned char x_new;
		unsigned char y_new;
		char skin;
		color skincolor;
	} OBJECT;

//globals
	char player_bodies[12]			= {'V','>','>','A',' ','>',' ','<','<',' ',' ','<'};
	OBJECT player					= { 10, 10, 10, 10, '>', yellow};
	//OBJECT alien					= { 10, 10, 10, 10, '>', black};
	TERRAIN current_terrain			= {
										{ rock, black, black, 0},
										{ debris, black, darkred, 1},
										{ floor, red, darkred, 0},
										{ killer, yellow, darkred, 1}
									};
	unsigned char client_catchkeys	= 1;
	unsigned char player_moved		= 1;
	char current_map				[27][80];
	unsigned char keys				= 0;

// keys
	const unsigned char	leftarrow	= 37, 
						uparrow		= 38, 
						rightarrow	= 39, 
						downarrow	= 40,
						space		= 32;

// function declrarations
	//winapi stuffs
	void consoleWrite(char* string);
	void consolePut(char c);
	void consoleRect(unsigned char from_x, unsigned char from_y, unsigned char to_x, unsigned char to_y, color fg, color bg, char* ch);
	void consoleCrd(unsigned char x, unsigned char y);
	void consoleColor(color fg, color bg);
	void setupConsole();
	unsigned char arrowEvt();
	unsigned char controlEvt();
	// engine
	void update();
	void display();
	void drawGUI();
	void processPlayerCoord();
	unsigned char diagMove();
	unsigned char checkPlayerBoundary();
	unsigned char checkObjectBoundary(unsigned char x, unsigned char y);
	void loadMap(char* mapname);
	void showMap();
	// movement
	void dig();
	MATERIAL getObj(char c);

void main(){
    const int SKIP_TICKS = 1000 / 13;
    const unsigned char MAX_FRAMESKIP = 10;
    unsigned int loops;
    DWORD next_game_tick = GetTickCount();

	//setup game
	setupConsole();
	drawGUI();
	// first map
	loadMap("C:\\map1.map");
	showMap();

    for(;;) {
        loops = 0;
        while( GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) {
            update();
            next_game_tick += SKIP_TICKS;
            loops++;
        }
        display();
    }
}

/*
	 ______             _            
	|  ____|           (_)           
	| |__   _ __   __ _ _ _ __   ___ 
	|  __| | '_ \ / _` | | '_ \ / _ \
	| |____| | | | (_| | | | | |  __/
	|______|_| |_|\__, |_|_| |_|\___|
	               __/ |             
	              |___/              
*/
void update(){
	// key event
	keys = arrowEvt();
	if (!keys) return;
	switch (keys){
		case 12:player.x_new--;player.y_new--;break;	case 4:player.y_new--;break;	case 6:player.x_new++;player.y_new--;break;
		case 8:player.x_new--;break;													case 2:player.x_new++;break;
		case 9:player.x_new--;player.y_new++;break;		case 1:player.y_new++;break;	case 3:player.x_new++;player.y_new++;break;
		default: return;
	}
	if (controlEvt()){
		dig();	
	}
	processPlayerCoord();
	player_moved = 1;
}

void display(){
	if (player_moved){
		consoleCrd(player.x,player.y);
		consoleColor(current_terrain.floor.foreground,current_terrain.floor.background);
		consolePut(floor);
		consoleCrd(player.x_new,player.y_new);
		consoleColor(player.skincolor,current_terrain.floor.background);
		consolePut(player.skin);
		player_moved = 0;
		player.x = player.x_new;
		player.y = player.y_new;
	}
}

void drawGUI(){
	consoleRect(0, HEIGHT - 3, WIDTH, HEIGHT, yellow, darkblue, " ");
	consoleRect(0, HEIGHT - 5, WIDTH, HEIGHT - 5, yellow, darkblue, "\"");
	consoleColor(white,black);
}

void processPlayerCoord(){
	player.skin = player_bodies[keys-1];
	if (checkPlayerBoundary()){
		player_moved = 1;
	}
	else {
		if (!diagMove()){
			player.x_new = player.x;
			player.y_new = player.y;
			player_moved = 0;
		}
	}
}

unsigned char checkPlayerBoundary(){
	return checkObjectBoundary(player.x_new,player.y_new);
}

unsigned char checkObjectBoundary(unsigned char x, unsigned char y){
	return (
			x >= 0 && y >= 0 &&
			x < GAMEWIDTH && y < GAMEHEIGHT && 
			current_map[y][x] == ' '
	);
}

unsigned char diagMove(){
	/*
		12  4  6
		 8     2
		 9  1  3
	*/
	switch (keys){
	case 12:
		if (checkObjectBoundary(player.x_new,player.y_new+1)){
			player.y_new++;
			return 1;
		}
		if (checkObjectBoundary(player.x_new+1,player.y_new)){
			player.x_new++;
			return 1;
		}
		return 0;
	case 6:
		if (checkObjectBoundary(player.x_new,player.y_new+1)){
			player.y_new++;
			return 1;
		}
		if (checkObjectBoundary(player.x_new-1,player.y_new)){
			player.x_new--;
			return 1;
		}
		return 0;
	case 3:
		if (checkObjectBoundary(player.x_new,player.y_new-1)){
			player.y_new--;
			return 1;
		}
		if (checkObjectBoundary(player.x_new-1,player.y_new)){
			player.x_new--;
			return 1;
		}
		return 0;
	case 9:
		if (checkObjectBoundary(player.x_new,player.y_new-1)){
			player.y_new--;
			return 1;
		}
		if (checkObjectBoundary(player.x_new+1,player.y_new)){
			player.x_new++;
			return 1;
		}
		return 0;

	}
	return 0;
}

void loadMap(char* mapname){
	FILE *fp;
	unsigned char h,w;
	char c;
	fp = fopen(mapname, "r");
	for(h = 0; h <= GAMEHEIGHT; h++){
		for(w = 0; w < GAMEWIDTH; w++){
			c = fgetc(fp);
			if (c == '\n' && w--) continue;
			current_map[h][w] = c;
		}
	}
	fclose(fp);
}

void showMap(){
	MATERIAL mat;
	unsigned char w, h;
	char c[2] = {' ','\0'};
	consoleColor(darkgrey,black);
	for (h = 0; h <= GAMEHEIGHT; h++){
		for (w = 0; w < GAMEWIDTH; w++){
			c[0] = current_map[h][w];
			consoleCrd(w,h);
			mat = getObj(c[0]);
			consoleColor(mat.foreground,mat.background);
			consolePut(mat.texture);
		}
	}
}

/*
	          _                _____ _____ 
	         (_)         /\   |  __ \_   _|
	__      ___ _ __    /  \  | |__) || |  
	\ \ /\ / / | '_ \  / /\ \ |  ___/ | |  
	 \ V  V /| | | | |/ ____ \| |    _| |_ 
	  \_/\_/ |_|_| |_/_/    \_\_|   |_____|
*/
void consoleWrite(char* string){
	DWORD nWritten;
	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole( hOutput, string, strlen(string), &nWritten, NULL);
}

void consolePut(char c){
	char c0[2] = {c, '\0'};
	DWORD nWritten;
	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole( hOutput, c0, 1, &nWritten, NULL);
}

void consoleRect(unsigned char from_x, unsigned char from_y, unsigned char to_x, unsigned char to_y, color fg, color bg, char* ch){
	unsigned char h, w;
	consoleColor(fg,bg);
	for (h = from_y; h <= to_y; h++){
		for (w = from_x; w < to_x; w++){
			consoleCrd(w,h);
			consoleWrite(ch);
		}
	}
}

void consoleCrd(unsigned char x, unsigned char y){
	COORD coord = {x,y};
	HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleCursorPosition(hstdout, coord);
}

void consoleColor(color fg,color bg){
	HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute(hstdout, (bg<<4)|fg);
}

void setupConsole(){
	//resize window
	HWND console = GetConsoleWindow();
	RECT r;
	COORD crd = {WIDTH,HEIGHT};
	// disable cursor
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursoInfo;
	//resize window
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 720, 480, TRUE);
	SetConsoleScreenBufferSize(hConsole,crd);
	// disable cursor
	CursoInfo.dwSize = 1;
	CursoInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsole, &CursoInfo);
}

unsigned char arrowEvt(){
	return	((GetKeyState(leftarrow)==-127 || GetKeyState(leftarrow)==-128)<<3)|
			((GetKeyState(uparrow)==-127 || GetKeyState(uparrow)==-128)<<2)|
			((GetKeyState(rightarrow)==-127 || GetKeyState(rightarrow)==-128)<<1)|
			(GetKeyState(downarrow)==-127 || GetKeyState(downarrow)==-128);
}

unsigned char controlEvt(){
	return	(GetKeyState(space)==-127 || GetKeyState(space)==-128);
}

/*
	 __  __  ______      ________ __  __ ______ _   _ _______ 
	|  \/  |/ __ \ \    / /  ____|  \/  |  ____| \ | |__   __|
	| \  / | |  | \ \  / /| |__  | \  / | |__  |  \| |  | |   
	| |\/| | |  | |\ \/ / |  __| | |\/| |  __| | . ` |  | |   
	| |  | | |__| | \  /  | |____| |  | | |____| |\  |  | |   
	|_|  |_|\____/   \/   |______|_|  |_|______|_| \_|  |_|   
*/

void dig(){
	switch ( current_map[player.y_new][player.x_new] ){
	case debris:
		current_map[player.y_new][player.x_new] = ' ';
	}
}

MATERIAL getObj(char c){
	switch (c){
		case rock:		return current_terrain.rock;
		case debris:	return current_terrain.debris;
		case floor:		return current_terrain.floor;
		case killer:	return current_terrain.killer;
		default:		return current_terrain.floor;
	}
}