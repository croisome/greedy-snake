#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>//_kbhit();_getch();
using std::cout;
using std::endl;
const int LINE = 28;
const int COLUMN = 60;//map line and map column;
char map[LINE][COLUMN];// to define a map;
unsigned long  snake[LINE][COLUMN];//snake's track,express it with numbers int decending order,every dudction is one;
int score = 0;
int head_x = 1;//head and tail's location;
int head_y = 4;
int tail_x = 1;
int tail_y = 1;
int flag = 0;//判断是否撞到自己;
int food_x;
int food_y;
void goto_xy(int x, int y) {
	HANDLE hout;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { y,x };
	SetConsoleCursorPosition(hout, pos);
}
inline void clear_xy(int x, int y) {
	goto_xy(x, y);
	cout << ' ';
}//make the character unseen;functional function;//using it for move the tail of the snake;
bool crash_wall() {
	if (head_x == 0 || head_x == LINE - 1 || head_y == 0 || head_y == COLUMN - 1) {
		return true;
	}
	return false;
}//to define if the game is over;
void map_maker() {
	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (i == 0 || i == LINE - 1) {
				map[i][j] = '&';
				cout << map[i][j];
				continue;
			}
			if (j == 0 || j == COLUMN - 1) {
				map[i][j] = '!';
				cout << map[i][j];
				continue;
			}
			map[i][j] = ' ';
			cout << map[i][j];
		}
		cout << endl;
	}
}
int  control(char t) {
	if (t == 'a' || t == 'd' || t == 'A' || t == 'D')
		return 1;
	if (t == 'w' || t == 's' || t == 'W' || t == 'S')
		return 2;
	return 0;
}
void clear_tail() {
	clear_xy(tail_x, tail_y);
	if (snake[tail_x][tail_y] - snake[tail_x + 1][tail_y] == -1) {
		snake[tail_x][tail_y] = 0;
		tail_x++; return;
	}
	if (snake[tail_x][tail_y] - snake[tail_x - 1][tail_y] == -1) {
		snake[tail_x][tail_y] = 0;
		tail_x--; return;
	}
	if (snake[tail_x][tail_y] - snake[tail_x][tail_y + 1] == -1) {
		snake[tail_x][tail_y] = 0;
		tail_y++; return;
	}
	if (snake[tail_x][tail_y] - snake[tail_x][tail_y - 1] == -1) {
		snake[tail_x][tail_y] = 0;
		tail_y--; return;
	}
}
void head_maker(char direction) {
	goto_xy(head_x, head_y);
	cout << "*";
	int d = snake[head_x][head_y];
	if (direction == 'd' || direction == 'D')
		head_y++;
	if (direction == 'a' || direction == 'A')
		head_y--;
	if (direction == 's' || direction == 'S')
		head_x++;
	if (direction == 'w' || direction == 'W')
		head_x--;
	goto_xy(head_x, head_y);
	if (snake[head_x][head_y] != 0) {
		flag = 1;
		return;
	}
	snake[head_x][head_y] = d + 1;
	cout << "0";
}
void create_food() {
	int x;
	int y;
	do {
		x = (LINE - 1) * rand() / (RAND_MAX + 1.0);
		y = (COLUMN - 1) * rand() / (RAND_MAX + 1.0);
	} while (x == 0 || y == 0 || x > LINE || y > COLUMN);
	goto_xy(x, y);
	cout << "1";
	food_x = x;
	food_y = y;
}
bool catch_food() {
	if (head_x == food_x && head_y == food_y) {
		return 1;
	}
	return 0;
}
int speed() {
	static int j = 0;
	for (j = 0; j < 1; j++) {
		srand((unsigned)GetCurrentTime());
	}
	static int i = 150 * rand() / RAND_MAX + 10;
	return i;
}
int speed(int i) {
	if (i == 0)
		return 300;
	if (i < 5) {
		return 300 - 50 * i;
	}
	return 10;
}
void move() {
	static int  i = 300;
	static char  direction = 'd';
	static  char ch = 'd';
	if (_kbhit()) {
		ch = _getch();
		if (control(ch) != 0 && control(ch) != control(direction))
			direction = ch;
	}
	if (!catch_food()) {
		clear_tail();
	}
	else {
		create_food();
		score++;
		i = speed();
	}
	head_maker(direction);
	if (crash_wall() || flag) {
		return;
	}
	Sleep(i);
	move();
}
void auto_move() {

}
void snake_maker() {
	goto_xy(head_x, head_y);
	cout << "@";
	goto_xy(1, 1);
	cout << "***";
	for (int i = 0; i < LINE - 1; i++) {
		for (int j = 0; j < COLUMN - 1; j++) {
			snake[i][j] = 0;
		}
	}
	for (int i = 1; i <= head_y; i++) {
		snake[1][i] = i;
	}
}
void result() {
	goto_xy(LINE, 0);
	cout << "your score is " << score << endl;
}
int main() {
	//map_maker();
	//snake_maker();
	//create_food();
	//move();
	//result();
	int a = -10;
	std::cout<<a%3;
}