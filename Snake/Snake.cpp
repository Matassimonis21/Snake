#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Defines.h"

using namespace std;
bool gameOver;
int uodegaX[50], uodegaY[50];
int uodegaIlgis;

int x, y, taskasX, taskasY; // Gyvates galvos ir tasko pozicija
enum judejimas {STOP = 0, KAIRE, DESINE, VIRSUS, APACIA};
judejimas jud;

void Setup()
{
	gameOver = false;
	jud = STOP; // Kol nepaspaudziam nejudam
	x = plotis / 2;
	y = aukstis / 2; //Centre pradedame zaidima
	taskasX = rand() % aukstis;
	taskasY = rand() % plotis; 
}
void Draw()
{
	system("cls"); // Issivalom konsole
	for (int i = 0; i < plotis+2; i++)
		cout << "I";
	cout << endl;

	for (int i = 0; i < aukstis; i++)
	{
		for (int j = 0; j < plotis; j++)
		{
			if (j == 0)
				cout << "I";
			if (i == y && j == x) //Tikriniam auksti ir gyv. galva
				cout << "O";
			else if (i == taskasY && j == taskasX) //auksti ir taska
				cout << "8";
			else
			{
				bool spausdinta = false;
				for (int k = 0; k < uodegaIlgis; k++)
				{
					if (uodegaX[k] == j && uodegaY[k] == i)
					{
						cout << "o";
						spausdinta = true;
					}
				}
				if (!spausdinta)
				cout << " ";
			}

			if (j == plotis - 1)
				cout << "I";
		}
		cout << endl;
	}

	for (int i = 0; i < plotis+2; i++)
		cout << "I";
	cout << endl;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			jud = KAIRE;
			break;
		case 'd':
			jud = DESINE;
			break;
		case 'w':
			jud = VIRSUS;
			break;
		case 's':
			jud = APACIA;
			break;
		}
	}
}
void Logic()
{
	int buvesX = uodegaX[0];
	int buvesY = uodegaY[0];
	int buvesX1, buvesY1;
	uodegaX[0] = x;
	uodegaY[0] = y;
	for (int i = 1; i <= uodegaIlgis; i++)
	{
		buvesX1 = uodegaX[i];
		buvesY1 = uodegaY[i];
		uodegaX[i] = buvesX;
		uodegaY[i] = buvesY;
		buvesX = buvesX1;
		buvesY = buvesY1;
	}
	switch (jud)
	{
	case KAIRE:
		x--;
		break;
	case DESINE:
		x++;
		break;
	case VIRSUS:
		y--;
		break;
	case APACIA:
		y++;
		break;
	}

	if (x > plotis || y > aukstis || x < 0 || y < 0)
		gameOver = true;
	for (int i = 0; i < uodegaIlgis; i++)
	{
		if (uodegaX[i] == x && uodegaY[i] == y)
			gameOver = true;
		else if (uodegaX[i] > plotis || uodegaY[i] > aukstis || uodegaX[i] < 0 || uodegaY[i] < 0)
			gameOver = true;
	}
	if (x == taskasX && y == taskasY)
	{
		uodegaIlgis++;
		taskasX = rand() % aukstis;
		taskasY = rand() % plotis;
	}
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(50);
	}
    return 0;
}

