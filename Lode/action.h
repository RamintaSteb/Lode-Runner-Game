#pragma once
#ifndef CTION_H_
#define ACTION_H_
#include <iostream>
#include <windows.h>
#include <fstream>
#include <Windows.h>
#include <conio.h>
extern char A[34][141]; //zemelapis
extern char B[34][141]; //saugo kur iskasta duobe
//hyio
class GameField
{
private:
	HWND console = GetConsoleWindow();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	
	int erx, ery;
	int lives;
	char k;
public:	
	void readingFile();
	void scaleConsole();
	void Color(int x);
	void Coordinates(int x, int y);
	void Game();
	void CheckEmptyPlace();
};

class Player : public GameField
{
private:
	int lastMove;
	char Back[2][4];

protected:
	int color=7;
	int x, y;
	int c;
	void DrawPlayer(int x, int y, int color);
	void RememberBackground(); 
	void Go(int side);

public:
	int score;
	bool box;
	void getCoordinates(int &px, int &py);
	Player();
	~Player();
	void KeyPress();
	void Fall();
	void Move();
	void EatBox();
	void OneMoreChance(int newx, int newy);
	void CheckScores();
	void Won();
	
};

class Enemy : public Player {

public:
	~Enemy();
	Enemy(int xe, int ye);
	void FindDirection(Player &player);
	void Renew(int erx, int ery);
	void KillsPlayer(Player &player);
};
#endif