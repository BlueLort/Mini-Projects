#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <random>
#include <chrono>
#include <ctime>
#include <fstream>
#define TAIL_X_SIZE 100
#define TAIL_Y_SIZE 100
#define GET_TIME_CHRONO_MS (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()))
enum direction{STOP=0,UP,DOWN,LEFT,RIGHT};
enum gameState{MENU,OPTIONS,EXIT,GAME};
gameState SYSTEM = MENU;
direction dir = STOP;
direction lastDir = STOP;//for pausing purposes
void ShowConsoleCursor(bool showFlag);
void printFile(std::string fileName);
void setColor(int i);
void drawSYSTEM();
void draw();
void clearDraw();
char getCursorChar();
void logic();
void menuLogic();
void optionsLogic();
void setup();
void input();
void gotoxy(int x, int y);
const int WIDTH = 55;
const int HEIGHT = 25;
struct body {
	int x;
	int y;
	int length;
};
int CHOOSEN=0;
int CHOOSE;
char buffer;
int speed=1;
int highScore = 0;
int snakeColor=153, wallColor=136, fruitColor=170;
std::vector<std::string> screen;
// RANDOM // snake body // fruit ** INFORMATION**
std::mt19937 Engine(time(0));

std::uniform_int_distribution<int> FruitX(1, WIDTH - 2);
std::uniform_int_distribution<int> FruitY(1, HEIGHT - 2);
body snake;
int tailX[TAIL_X_SIZE] = { 0 }, tailY[TAIL_Y_SIZE] = { 0 };

int prevX, prevY, prev2X, prev2Y;
int fruitX, fruitY;
bool eaten;
int sleepTime;
float gameTime = 0;
bool INGAME = true;
bool RUNNING = true;
bool esc = false;
int main() {
	
	ShowConsoleCursor(false);
	printFile("intro.txt");

	system("CLS");
	while (RUNNING) {
		switch (SYSTEM) {
		case MENU:
			esc = false; CHOOSEN = 0;
			system("cls"); gotoxy(0, 0);
			while (!esc) {
				//Sleep(10);
				setColor(12);
				gotoxy(1, 0); std::cout << "**w/s -Enter To choose**";
				for (int i = 0; i < 3; i++) {
					if (i == CHOOSEN) setColor(15);
					else setColor(8);
					switch (i) {
					case 0:
						gotoxy(1, i+1); std::cout << "Start";
						break;
					case 1:
						gotoxy(1, i+1); std::cout << "Options";
						break;
					case 2:
						gotoxy(1, i+1); std::cout << "Exit";
						break;
					}
				}
				
				buffer = _getch();
						if (buffer == (char)13) {
							switch (CHOOSEN) {
							case 0:
								SYSTEM = GAME;
								esc =true;
								break;
							case 1:
								SYSTEM = OPTIONS;
								esc = true;
								break;
							case 2:
								SYSTEM = EXIT;
								esc = true;
								break;
							
					}
					}
					menuLogic();
				
			}
			break;
		case OPTIONS:
			CHOOSEN = 0;
			system("CLS"); gotoxy(0, 0); setColor(7); esc = false;
			while (!esc) {
				setColor(12);
				gotoxy(1, 0); std::cout << "**w/s &a/d to change setting(ESC to back)**";
				for (int i = 0; i < 5; i++) {
					if (i == CHOOSEN) setColor(15);
					else setColor(8);
					switch (i) {
					case 0:
						gotoxy(1, i + 1); std::cout << "Speed:" << speed;
						break;
					case 1:
						gotoxy(1, i + 1); std::cout << "Snake Color->";
						setColor(snakeColor); gotoxy(14, i + 1); std::cout << ' ';
						break;
					case 2:
						gotoxy(1, i + 1); std::cout << "Wall Color->";
						setColor(wallColor); gotoxy(13, i + 1); std::cout << ' ';
						break;
					case 3:
						gotoxy(1, i + 1); std::cout << "Fruit Color->";
						setColor(fruitColor); gotoxy(14, i + 1); std::cout << ' ';
						break;
					case 4:
						gotoxy(1, i + 1); std::cout << "Key Bindings(Coming Soon)";
						break;
					}
				}
					
						switch(buffer=_getch()) {
						case 'a':
							switch (CHOOSEN) {
							case 0:
								if (speed > 1)speed--;
								break;
							case 1:
								if (snakeColor > 17)snakeColor -= 17;
								break;
							case 2:
								if (wallColor > 17)wallColor -= 17;
								break;
							case 3:
								if (fruitColor > 17)fruitColor -= 17;
								break;
							}
							break;
						case 'd':
							switch (CHOOSEN) {
							case 0:
								if (speed < 9)speed++;
								break;
							case 1:
								if (snakeColor < 255)snakeColor += 17;
								break;
							case 2:
								if (wallColor  <255)wallColor += 17;
								break;
							case 3:
								if (fruitColor <255)fruitColor += 17;
								break;
							}
							break;
							
						
					}
					optionsLogic();
				
			}
			break;
		case GAME:
			system("CLS"); gotoxy(0, 0); setColor(7);
			setup();
			drawSYSTEM();
			std::chrono::milliseconds currentTime = GET_TIME_CHRONO_MS;
			std::chrono::milliseconds deltaTime=GET_TIME_CHRONO_MS;
			for (int i = 0; i < TAIL_X_SIZE; i++)tailX[i] = 0;
			for (int i = 0; i < TAIL_Y_SIZE; i++)tailY[i] = 0;
			gameTime = 0;
			while (INGAME) {
				deltaTime = GET_TIME_CHRONO_MS-currentTime;
				currentTime = GET_TIME_CHRONO_MS;
				if(dir!=STOP)gameTime += (deltaTime.count()) / 1000.0f;
				Sleep(sleepTime);
				draw();
				input();
				logic();
				setColor(12);
				gotoxy(0, HEIGHT); std::cout << "Score:" << snake.length * 4*speed;
				gotoxy(WIDTH / 4, HEIGHT); std::cout << "Time:" <<gameTime;
				if (highScore < snake.length * 4 * speed)highScore = snake.length * 4 * speed;
				gotoxy(WIDTH / 4+18, HEIGHT); std::cout << "Highest Score:" << highScore;
				
			}
			break;
		case EXIT:
			setColor(12);
			std::cout << "\nThanks For Playing Our Snake Game\nImplemented by:Lort->Omar\n";
			setColor(11);
			std::cout <<(char)169<<"LORTIANS GAMING\n"; 
			setColor(14);
			system("pause");
			system("CLS"); gotoxy(0, 0); setColor(7);
			RUNNING = false;
			
			printFile("Lortians Logo.txt");
			break;
		}

		
	}
	
	return 0;
}
void drawSYSTEM() {
	setColor(wallColor);
	for (int i = 0; i < WIDTH; i++) {
		gotoxy(i, 0);
		std::cout << '#';
		
	}
	for (int i = 0; i < HEIGHT-1; i++) {
		
		gotoxy(0, i); std::cout << '#';
		gotoxy(WIDTH-1, i); std::cout << '#';
			
	}
	for (int i = 0; i < WIDTH; i++) {
		gotoxy(i, HEIGHT-1);
		std::cout << '#';

	}
}
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void setColor(int i) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
void logic() {
	clearDraw();
	if (dir != STOP) {
		prevX = tailX[0]; prevY = tailY[0];
		tailX[0] = snake.x; tailY[0] = snake.y;
		for (int i = 1; i < snake.length; i++) {
			prev2X = tailX[i]; prev2Y = tailY[i];
			tailX[i] = prevX; tailY[i] = prevY;
			prevX = prev2X; prevY = prev2Y;

		}

		switch (dir) {
		case UP:
			if (snake.y > 1)
				snake.y--;
			else
				snake.y = HEIGHT - 2;

			break;

		case DOWN:
			if (snake.y < HEIGHT - 2)
				snake.y++;
			else
				snake.y = 1;

			break;
		case LEFT:
			if (snake.x > 1)
				snake.x--;
			else
				snake.x = WIDTH - 2;
			break;
		case RIGHT:
			if (snake.x < WIDTH - 2)
				snake.x++;
			else
				snake.x = 1;

			break;
		default:
			break;
		}
		if (snake.x == fruitX && snake.y == fruitY) {
			eaten = true;
			snake.length++;
		LOOP1:
			fruitX = FruitX(Engine); fruitY = FruitY(Engine);
			for (int i = 0; i < snake.length; i++) {
				if (fruitX == tailX[i] && fruitY == tailY[i]) goto LOOP1;
			}
		}
		for (int i = 0; i < snake.length; i++) {
			if (snake.x == tailX[i] && snake.y == tailY[i]) {
				INGAME = false;
				setColor(14);
				gotoxy(0, HEIGHT + 3); std::cout << "****GAME OVER****\nyou have bitten your Self\n";
				SYSTEM = MENU;
				system("pause");

			}
		}
	}
	draw();
}
void setup() {
	eaten = true;
	INGAME = true;
	sleepTime = 120 - speed * 9;
	dir = STOP;
	snake.length = 0;
	snake.x = WIDTH / 2; snake.y = HEIGHT / 2;
	fruitX = FruitX(Engine); fruitY = FruitY(Engine);
}
void draw() {
	if (eaten) {
		setColor(fruitColor);
		gotoxy(fruitX, fruitY); std::cout << 'F';
		eaten = false;
	}
	setColor(snakeColor);
	gotoxy(snake.x, snake.y); std::cout << 'O';
	for (int i = 0; i < snake.length; i++) {
		if (tailX[i] != 0 && tailY[i] != 0) {
			gotoxy(tailX[i], tailY[i]); std::cout << 'o';
		}
	}
	
}
void clearDraw() {
	setColor(0);
	gotoxy(snake.x, snake.y); std::cout << ' ';
	for (int i = 0; i < snake.length; i++) {
		if (tailX[i] != 0 && tailY[i] != 0) {
			gotoxy(tailX[i], tailY[i]); std::cout << ' ';
		}
	}
}
char getCursorChar()    /// Function which returns character on console's cursor position || Totally not copied from the Internet
{
	char c = '\0';
	CONSOLE_SCREEN_BUFFER_INFO con;
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hcon != INVALID_HANDLE_VALUE &&
		GetConsoleScreenBufferInfo(hcon, &con))
	{
		DWORD read = 0;
		if (!ReadConsoleOutputCharacterA(hcon, &c, 1,
			con.dwCursorPosition, &read) || read != 1
			)
			c = '\0';
	}
	return c;
}
void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case'w':
			if (dir != DOWN && lastDir != DOWN) {
				if (dir == STOP)lastDir = STOP;
				dir = UP;

			}
			else if (snake.length == 0)
				dir = UP;
			break;
		case's':
			if (dir != UP && lastDir != UP) {
				if (dir == STOP)lastDir = STOP;
				dir = DOWN;
			}
			else if (snake.length == 0)
				dir = DOWN;
			break;
		case'a':
			if (dir != RIGHT && lastDir != RIGHT) {
				if (dir == STOP)lastDir = STOP;
				dir = LEFT;
			}
			else if (snake.length == 0)
				dir = LEFT;
			break;
		case'd':
			if (dir != LEFT && lastDir != LEFT) {
				if (dir == STOP)lastDir = STOP;
				dir = RIGHT;
			}
			else if (snake.length == 0)
				dir = RIGHT;

			break;
		case'p':
			lastDir = dir;
			dir = STOP;
			break;
		case (char)27:
			INGAME = false;
			SYSTEM = MENU;
			break;
		}
	}
}
void printFile(std::string fileName) {
	system("cls");
	gotoxy(0, 0);
	 std::ifstream file;
	 std::string Line;
	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("pause");
		exit(1);
	}
	while (getline(file, Line)) {
		screen.push_back(Line);
	}
	file.close();
	for (int i = 0; i<screen.size(); i++) {
		std::cout << screen[i] << std::endl;
	}

	system("pause");
}
void menuLogic() {

		switch (buffer) {
		case 'w':
			if (CHOOSEN > 0)CHOOSEN--;
			break;
		case 's':
			if (CHOOSEN < 2)CHOOSEN++;
			break;
		case (char)27:
			SYSTEM = EXIT;
			esc = true;
			break;
		}
}
void optionsLogic() {
	switch (buffer) {
	case 'w':
		if (CHOOSEN > 0)CHOOSEN--;
		break;
	case 's':
		if (CHOOSEN < 3)CHOOSEN++;
		break;
	case (char)27:
		SYSTEM = MENU;
		esc = true;
		break;
	}
}