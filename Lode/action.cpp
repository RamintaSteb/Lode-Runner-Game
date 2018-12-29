#include "stdafx.h"
#include "action.h"
#include <vector>
#include <time.h>

char A[34][141];
char B[34][141];
struct Hole {
	int time;
	int x, y;
} n;
bool kill;
bool winner;

std::vector<Hole>a;

void GameField::Game() {

		readingFile();
		Enemy one(25, 12), two(115, 12), three(70, 18);
		Player player;
		kill = false;
		winner = false;
		lives = 3;
		player.score = 0;

		Coordinates(0, 33);
		std::cout << "Score: 0";
		Coordinates(0, 34);
		std::cout << "Lives: " << lives;
		while (lives>=0)
		{
			//zaidejas
			player.Fall();
			player.KeyPress();
			player.Move();
			player.EatBox();
			CheckEmptyPlace();
			player.CheckScores();
			player.Won();

			one.FindDirection(player);
			one.Fall();
			one.Move();
			one.Renew(erx, ery);
			one.KillsPlayer(player);

			two.FindDirection(player);
			two.Fall();
			two.Move();
			two.Renew(erx, ery);
			two.KillsPlayer(player);

			three.FindDirection(player);
			three.Fall();
			three.Move();
			three.Renew(erx, ery);
			three.KillsPlayer(player);

			//skaiciuoja kiek dar turi gyvybiu ir leidzia zaist is naujo
			if (kill) {
				Coordinates(0, 34);
				lives--;
				std::cout << "Lives: " << lives;
				if (lives >= 0) {
					player.OneMoreChance(70, 28);
					one.OneMoreChance(25, 12);
					two.OneMoreChance(115, 12);
					three.OneMoreChance(70, 18);
					kill = false;
				}
			}
			Coordinates(0, 34);
			if (lives >= 0) std::cout << "Lives: " << lives;
			else if (lives < 0) {

				Coordinates(0, 0);
				std::ifstream w("Loser.txt");
				system("CLS");
				Color(4);
				for (int i = 0; i < 36; i++)
				{
					for (int j = 0; j < 140; j++)
					{
						Color(2);
						w >> k;
						if (k == 'X') {
							Color(68);
							std::cout << k;
						}
						else {
							std::cout << " ";
						}
					}
					std::cout << std::endl;
				}
				w.close();
				break;
			}
			//jei laimi
			if (winner==true) {
				Coordinates(0, 0);
				std::ifstream w("winner.txt");
				system("CLS");
				Color(2);
				for (int i = 0; i < 36; i++)
				{
					for (int j = 0; j < 140; j++)
					{
						Color(2);
						w >> k;
						if (k == 'X') {
							Color(34);
							std::cout << k;
						}
						else {
							std::cout << " ";
						}
					}
					std::cout << std::endl;
				}
				w.close();
				break;
			}
		}
		Color(7);
		system("PAUSE");
		player.~Player();
		one.~Enemy();
		two.~Enemy();
		three.~Enemy();
}

void GameField::CheckEmptyPlace() {
	
	SYSTEMTIME st;
	GetSystemTime(&st);
	int time = st.wSecond;
	for (int i = 0; i < a.size(); i++)
	{
		int timedif = abs(a.at(i).time - time);
		if (timedif > 7) {
			//nebegales ikristi
			B[a.at(i).y][a.at(i).x] = '0';
			//uzpila duobe
			erx = a.at(i).x;
			ery = a.at(i).y;
			Coordinates(erx, ery);
			Color(9);
			std::cout << A[ery][erx] << A[ery][erx + 1] << A[ery][erx + 2];
			Coordinates(erx, ery+1);
			Color(9);
			std::cout << A[ery+1][erx] << A[ery+1][erx + 1] << A[ery+1][erx + 2];
			//istrina prisiminimus
			a.erase(a.begin() + i);

		}
	}
}

void GameField::readingFile()
{
	Coordinates(0, 0);
	scaleConsole();
	std::ifstream F("langas.txt");
	for (int i = 0; i < 33; i++)
	{
		for (int j = 0; j < 140; j++)
		{
			F >> A[i][j];
			if (A[i][j] == '_') A[i][j] = ' ';
			else if (A[i][j] == (char)-23) A[i][j] = (char)176;
			if (A[i][j] == (char)254 || A[i][j] == (char)219) Color(9);
			else if (A[i][j] == (char)176) Color(12);
			else Color(7);
			std::cout << A[i][j];
		}
		std::cout << std::endl;
	}
	Color(7);
	F.close();
}

void GameField::scaleConsole()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	RECT r;
	GetWindowRect(console, &r);
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
}

void GameField::Color(int x) //x- teksto spalva
{
	SetConsoleTextAttribute(hConsole, 0 * 16 + x);
}

void GameField::Coordinates(int x, int y)
{
	COORD pos = { (short)x, (short)y };
	SetConsoleCursorPosition(hConsole, pos);
}

//---------------------------------------------------------------------------------------------

void Player::KeyPress() {
	while (1) {
		c = 0;
		c = _getch();
		//duobe kairej
		if (122 == c && (A[y + 2][x - 3] == (char)254 || A[y + 2][x - 2] == (char)254))
		{
			B[y + 2][x - 3] = ' ';
			SYSTEMTIME st;
			GetSystemTime(&st);
			n.time = st.wSecond;
			n.x = x - 3;
			n.y = y + 2;
			a.push_back(n);

			Coordinates(x - 3, y + 2);
			std::cout << "   ";
			Coordinates(x - 3, y + 3);
			std::cout << "   ";
			break;
		}
		//duobe desinej
		else if (120 == c && (A[y + 2][x + 4] == (char)254 || A[y + 2][x + 5] == (char)254))
		{
			B[y + 2][x + 3] = ' ';
			SYSTEMTIME st;
			GetSystemTime(&st);
			n.time = st.wSecond;
			n.x = x + 3;
			n.y = y + 2;
			a.push_back(n);

			Coordinates(x + 3, y + 2);
			std::cout << "   ";
			Coordinates(x + 3, y + 3);
			std::cout << "   ";
			break;
		}
		else if (c == 27)
		{
			Coordinates(0, 33);
			system("PAUSE");
			break;
		}
		//juda
		else if (c == 72 || c == 80 || c == 75 || 77 == c) {
			break;
		}
		/*
		//224 ir 0 - atspaustas mygtukas
		else if (c != 224 && c != 0) {
		std::cout << c << " wrong :)" << std::endl;
		}*/
	}
}

void Player::DrawPlayer(int x, int y, int color) { //paduoda virsutinio kairio kampo koordinates
	Color(color);
	Coordinates(x, y);
	//ikrenta
	if (B[y][x] == ' ')
	{
		Coordinates(x, y-2);
		std::cout << A[y-2][x] << A[y-2][x+1] << A[y-2][x+2];
		Coordinates(x, y - 1);
		std::cout << A[y - 1][x] << A[y - 1][x + 1] << A[y - 1][x + 2];
		Coordinates(x, y);
		std::cout << ' ' << (char)162 << ' ' << std::endl;
		Coordinates(x, y + 1);
		std::cout << '/' << (char)177 << '\\' << std::endl;
	}
	//paprastai vaiksto
	else if (A[y][x] != (char)196 && A[y][x + 1] != (char)196 && A[y][x + 2] != (char)196) {
		std::cout << A[y][x] << (char)162 << A[y][x + 2] << std::endl;
		Coordinates(x, y + 1);
		std::cout << '/' << (char)177 << '\\' << std::endl;
	}
	//lipa virve
	else {
		std::cout << '\\' << (char)162 << '/' << std::endl;
		Coordinates(x, y + 1);
		std::cout << A[y+1][x] << (char)177 << A[y+1][x+2] << std::endl;
	}
	Color(7);
}

void Player::Fall() {
	//krenta zemyn
	if (B[y + 2][x] == ' ') {
		if (color != 7) {
			B[y + 2][x] = '0';
			Coordinates(x, y);
			std::cout << "   ";
			Coordinates(x, y + 1);
			std::cout << "   ";
		}
		//tuscia vieta
		if (box==true) {
			A[y + 1][x] = (char)176;
			A[y + 1][x + 1] = (char)176;
		}
		y = y + 2;
		DrawPlayer(x, y, color);
		if (box==true) {
			Coordinates(x, y - 1);
			Color(12);
			std::cout << A[y - 1][x] << A[y - 1][x + 1];
			Color(7);
			box = false;
			color = 11;
		}
	}
	while ((B[y][x]!='0') && ((A[y + 2][x] == ' ' && A[y + 2][x + 1] == ' ' && A[y + 2][x + 2] == ' ') && (A[y][x] != (char)196 || A[y][x + 1] != (char)196 || A[y][x + 2] != (char)196)) || (A[y + 2][x] == (char)196 && A[y + 2][x + 1] == (char)196 && A[y + 2][x + 2] == (char)196)) {
			
			RememberBackground();
			y++;
			DrawPlayer(x, y, color);
			if (B[y - 2][x] == ' ')
			{
				Coordinates(x, y - 2);
				std::cout << "   ";
				Coordinates(x, y - 1);
				std::cout << "   ";
			}
	}


}

void Player::Move()
{
		//------------------------------------------------
		//up
		if (72 == c && (A[y + 1][x] == (char)205 || A[y][x] == (char)205) && (A[y + 1][x + 2] == (char)205 || A[y][x + 2] == (char)205) && y - 1 >= 0) {
			Go(0);
		}
		//down
		else if (80 == c && (((A[y + 2][x] == (char)205) && (A[y + 2][x + 2] == (char)205) && y + 1 < 31) || (A[y + 2][x] == ' ' && A[y + 2][x + 1] == ' ' && A[y + 2][x + 2] == ' '))) {
			Go(1);
		}
		//left
		else if (75 == c && A[y][x - 1] != (char)254 && A[y+1][x - 1] != (char)254 && A[y][x - 1] != (char)219 && x - 1 >= 0) {
			Go(2);
		}
		//right
		else if (77 == c && A[y][x + 3] != (char)254 && A[y+1][x + 3] != (char)254 && A[y][x+3]!=(char)219 && x + 1 < 138) {
			Go(3);
		}		
}

void Player::Go(int side) //0 - up; 1-down; 2-left; 3-right;

{
	RememberBackground();
	if (side == 0) y--;
	else if (side == 1) y++;
	else if (side == 2) x--;
	else if (side == 3) x++;
	DrawPlayer(x, y, color);
	//Sleep(25);
}

Player::Player() {
	x = 70;
	y = 28;
	score = 0;
	DrawPlayer(x, y, color);
}

void Player::RememberBackground() {
	
	int x1 = x;
	int y1 = y;
	Coordinates(x, y);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{	
			if (A[y1][x1] == (char)254 || A[y1][x1] == (char)219) Color(9);
			if (A[y1][x1] == (char)176) Color(12);
			std::cout << A[y1][x1];
			x1++;
		}
		x1 = x1 - 3;
		Coordinates(x1, y1 + 1);
		y1++;
	}
	
	Color(7);

}

void Player::EatBox() {
	if ((A[y + 1][x] == (char)176 && A[y + 1][x + 1] == (char)176) || (A[y + 1][x + 2] == (char)176 && A[y + 1][x + 1] == (char)176)) {
		A[y + 1][x] = ' ';
		A[y + 1][x+1] = ' ';
		A[y + 1][x+2] = ' ';
		score = score + 100;
			Coordinates(0, 33);
			std::cout << "Taskai: " << score;
	}
}

void Player::getCoordinates(int &px, int &py) {
	px = x;
	py = y;
}

void Player::OneMoreChance(int newx, int newy) {
	RememberBackground();
	x = newx;
	y = newy;
	DrawPlayer(x, y, color);
}

void Player::CheckScores() {
	if (score == 900)
	{
		for (int i = 0; i < 8; i++) {
			A[i][90] = (char)204;
			A[i][91] = (char)205;
			A[i][92] = (char)205;
			A[i][93] = (char)205;
			A[i][94] = (char)185;
			Coordinates(90, i);
			std::cout << A[i][90] << A[i][91] << A[i][92] << A[i][93] << A[i][94];
		}
		score = 1000;
	}
}

void Player::Won() {
	if (y == 0) winner = true;
}

Player::~Player()
{
	x = 70;
	y = 28;
}

//-------------------------------------------------------------------------------

Enemy::Enemy(int xe, int ye) {
	x = xe;
	y = ye;
	box = 1;
	color = 10;
	DrawPlayer(x, y, color);
}

void Enemy::FindDirection(Player &player) {
	int right = 140;
	int left = 140;
	int px, py;
	player.getCoordinates(px, py);
	//right
	if (py == y) {
		if (px > x) {
			c = 77;
		}
		//left
		else if (px < x) {
			c = 75;
		}
	}

	//reikia zemyn
	else if (py > y && B[y][x]!=' ') {
		
		if (((A[y + 2][x] == (char)205) && (A[y + 2][x + 2] == (char)205) && y + 1 < 31) || (A[y + 2][x] == ' ' && A[y + 2][x + 1] == ' ' && A[y + 2][x + 2] == ' ')) c = 80;
		else if (A[y][x] == (char)196 || A[y][x + 2] == (char)196) {}
		else {
			right = 140;
			left = 140;
			for (int i = x; i < 140; i++)
			{
				if ((((A[y + 2][i] == (char)205)) || ((A[y][i] == (char)196))) && right == 140) {
					right = i-x;
				}
			}
			for (int j = x; j > 0; j--)
			{
				if (((A[y + 2][j] == (char)205) || A[y][j] == (char)196) && left == 140) {
					left = x - j;
				}
			}
			if (left == 140) c = 77;
			else if (right == 140) c = 75;
			else if (right > left) c = 75; //kaire arciau
			else if (left > right) c = 77; //desine arciau
		}
	}
	//reikia aukstyn
	else if (py < y) {
		right = 140;
		left = 140;
		if ((A[y + 1][x] == (char)205 || A[y][x] == (char)205) && (A[y + 1][x + 2] == (char)205 || A[y][x + 2] == (char)205) && y - 1 >= 0) c = 72;
		else {
			for (int i = x; i < 141; i++)
			{
				if ((A[y + 1][i] == (char)205) && right == 140)
					right = i-x;
			}
			for (int j = x; j > 0; j--)
			{
				if ((A[y + 1][j] == (char)205) && left == 140)
					left = x - j;
			}
			if (left == 140) c = 77;
			else if (right == 140) c = 75;
			else if (right >= left) c = 75; //kaire arciau
			else if (left > right) c = 77; //desine arciau
		}
	}
}

void Enemy::Renew(int erx, int ery) {
	if (erx == x && ery == y) {
		x = 100;
		y = 0;
	}
	
}

void Enemy::KillsPlayer(Player &player) {
	int px, py;
	player.getCoordinates(px, py);
	if (py == y && (px==x || px==x+2 || px+2==x)) {
		kill = true;
	}

}

Enemy::~Enemy()
{
}