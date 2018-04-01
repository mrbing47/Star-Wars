#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
int points = 0, life = 30, ctrlife = 0, bullets = 25, ctrbullets = 0, deploy = 0, ctrclife = 0, ctrbshot = 0, ctroutb = 0;
void gotoxy(short, short);
void size(int, int);
void ini(int[26][80]);
void print(int[26][80]);
void plant(int[26][80]);
void xshoot(int[26][80]);
void ishoot(int[26][80]);
void strike(int[26][80]);
void destroyer(int[26][80], int, int);
int xmovecheck(int[26][80], int);
void xmove(int[26][80], int);
void imove(int[26][80],int);
void stats(int);
void menucall(int[26][80],unsigned int&);
void welscr();
void instructions(int);
void main()
{
	srand((unsigned)time(NULL));
	int map[26][80], input = 0, lok = 0, bok = 0;
	unsigned int ctr = 0;
	size(10, 1);
	welscr();
	instructions(1);
	ini(map);
	do {
		if (!(ctr % 16))
		{
			plant(map);
		}
		if (_kbhit())
		{
			for (int i = 0; i < 100; i++)
			{
				if (_kbhit())
				{
					input = _getch();
					if (input == 32)
					{
						if (bullets > 0)
						{
							xshoot(map);
						}
					}
					if (input == 75 || input == 77)
					{
						if (xmovecheck(map, input) == -2)
							life -= 2;
						if (xmovecheck(map, input) == -1)
							life--;
						if (xmovecheck(map, input) == 1)
							xmove(map, input);
						i = 0;
					}
					if (input == 27)
						menucall(map,ctr);
				}
			}
		}
		ishoot(map);
		print(map);
		strike(map);
		imove(map, ctr);
		Sleep(250);
		ctr++;
		if (ctrlife == 8 && life < 30)
		{
			life++;
			ctrlife = 0;
		}
		else
		{
			ctrlife++;
		}
		if (bullets == 0 && bok)
		{
			ctroutb++;
			bok = 0;
		}
		if (bullets > 0 && !bok)
			bok = 1;
		if (life <= 5 && lok)
		{
			ctrclife++;
			lok = 0;
		}
		if (life > 5 && !lok)
			lok = 1;
		if (ctrbullets == 4 && bullets < 25)
		{
			bullets++;
			ctrbullets = 0;
		}
		else
		{
			ctrbullets++;
		}
	} while (life > 0);
	print(map);
	gotoxy(0, 24);
	for (int i = 0; i < 80; i++)
		cout << " ";
	gotoxy(32, 24);
	SetConsoleTextAttribute(out, 4);
	cout << "---GAME OVER---";
	gotoxy(0, 24);
	SetConsoleTextAttribute(out, 15);
	cout << "Press ";
	SetConsoleTextAttribute(out, 2);
	cout << "ENTER";
	SetConsoleTextAttribute(out, 15);
	cout << " to view STATS";
	gotoxy(60, 24);
	SetConsoleTextAttribute(out, 15);
	cout << "Press ";
	SetConsoleTextAttribute(out, 2);
	cout << "ESC";
	SetConsoleTextAttribute(out, 15);
	cout << " to exit";
	do {
		input = _getch();
		if (input == 27)
			exit(0);
	} while (input != 13);
	stats(1);
}
void gotoxy(short x, short y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(out, c);
}
void size(int ratio, int bold)
{
	bold *= 100;
	int x = 1 * ratio, y = 2 * ratio;
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = y;
	info.dwFontSize.X = x;
	info.FontWeight = bold;
	SetCurrentConsoleFontEx(out, NULL, &info);
}
void ini(int map[26][80])
{
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			map[i][j] = 0;
		}
	}
	map[25][38] = map[25][40] = map[25][39] = map[24][39] = map[23][39] = 1;
	points = 0, life = 30, ctrlife = 0, bullets = 25, ctrbullets = 0, deploy = 0, ctrclife = 0, ctrbshot = 0, ctroutb = 0;
}
void print(int map[26][80])
{
	system("cls");
	int ctr = 0;
	for (int i = 2; i < 27; i++)
	{
		if (i == 26)
		{
			if (life > 5)
				SetConsoleTextAttribute(out, 14);
			else
				SetConsoleTextAttribute(out, 4);
			cout << "YOU:";
			SetConsoleTextAttribute(out, 128);
			for (int k = 0; k < life; k++)
			{
				cout << " ";
			}
			cout << life;
			SetConsoleTextAttribute(out, 14);
			gotoxy(45, 24);
			cout << "BULLETS: " << bullets;
			gotoxy(67, 24);
			cout << "POINTS: " << points;
		}
		else
		{
			for (int j = 0; j < 80; j++)
			{
				if (map[i][j] < 0)
				{
					if (map[i][j] == -1)
						SetConsoleTextAttribute(out, 2);
					if (map[i][j] == -2)
						SetConsoleTextAttribute(out, 4);
					cout << "|";
				}
				if (map[i][j] == 1)
				{
					ctr++;
					if (ctr == 3 || ctr == 5)
					{
						SetConsoleTextAttribute(out, 14);
						cout << "X";
					}
					else
					{
						SetConsoleTextAttribute(out, 7);
						cout << "+";
					}
				}
				if (map[i][j] > 1)
				{
					char ch = map[i][j];
					SetConsoleTextAttribute(out, 8);
					cout << ch;
				}
				if (!map[i][j])
				{
					cout << " ";
				}
			}
			cout << endl;
		}
		
	}
}
void plant(int map[26][80])
{
	for (int j = 0; j < 78; j++)
	{
		if (!((rand() % 19 + 1) % 10))
		{
			map[0][j] = map[0][j + 2] = map[1][j] = map[1][j + 2] = map[2][j] = map[2][j + 2] = 88;
			map[2][j + 1] = 34;
			map[1][j + 1] = 79;
			deploy++;
			j += 3;
		}
	}
}
void xshoot(int map[26][80])
{
	for (int j = 0; j < 80; j++)
	{
		if (map[23][j] == 1 && !map[22][j])
		{
			map[22][j] = -1;
			bullets--;
			ctrbullets = 0;
			ctrbshot++;
		}
	}
}
void ishoot(int map[26][80])
{
	int ahead=0;
	for (int i = 25; i >= 0; i--)
	{
		for (int j = 0; j < 80; j++)
		{
			if (map[i][j] == 34)
			{
				if (rand() % 2)
				{
					ahead = 0;
					for (int k = i + 1; k < 26; k++)
					{
						if (map[k][j] > 1)
							ahead = 1;
					}
					if (!ahead && (!(map[i + 1][j] == 1 || map[i + 1][j] == -1)))
						map[i + 1][j] = -2;
				}
			}
		}
	}
}
void strike(int map[26][80])
{
	for (int i = 2; i < 26; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			if (map[i][j] == -1)
			{
				if (i == 2)
				{
					map[i][j] = 0;
				}
				else
				{
					if (map[i - 1][j] == 0)
					{
						map[i - 1][j] = map[i - 1][j] + map[i][j];
						map[i][j] = map[i - 1][j] - map[i][j];
						map[i - 1][j] = map[i - 1][j] - map[i][j];
					}
					if (map[i - 1][j] == 88 && map[i - 1][j - 1] == 34)
					{
						destroyer(map, i - 3, j - 2);
						map[i][j] = 0;
						points++;
					}
					if (map[i - 1][j] == 88 && map[i - 1][j + 1] == 34)
					{
						destroyer(map, i - 3, j);
						map[i][j] = 0;
						points++;
					}
					if (map[i - 1][j] == 34)
					{
						destroyer(map, i - 3, j - 1);
						map[i][j] = 0;
						points++;
					}
					if (map[i - 1][j] == -2)
					{
						map[i - 1][j] = 0;
						map[i][j] = 0; 
					}
				}
			}
		}
	}
}
void destroyer(int map[26][80], int i, int j)
{
	map[i][j] = map[i][j + 2] = map[i + 1][j] = map[i + 1][j + 1] = map[i + 1][j + 2] = map[i + 2][j] = map[i + 2][j + 1] = map[i + 2][j + 2] = 0;
}
int xmovecheck(int map[26][80], int dir)
{
	dir = dir - 76;
	for (int i = 25; i >= 23; i--)
	{
		for (int j = 0; j < 80; j++)
		{
			if (map[i][j] == 1)
			{
				if (map[i][j + dir] > 1)
				{
					if (map[i][j + dir] == 88 && map[i][j + dir * 2] == 34)
					{
						destroyer(map, i - 2, j + dir);
					}
					if (map[i][j + dir] == 88 && map[i][j + dir * 2] == 34)
					{
						destroyer(map, i - 1, j + dir);
					}
					if (map[i][j + dir] == 88 && map[i][j + dir * 2] == 0)
					{
						map[i][j + dir] = map[i][j + dir * 3] = 0;
					}
					return -2;
				}
				if (map[i][j + dir] < -1)
				{
					map[i][j + dir] = 0;
					return -1;
				}
				if (j + dir < 0 || j + dir > 80)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}
void xmove(int map[26][80],int dir)
{
	if (dir == 75)
	{
		for (int i = 25; i >= 23; i--)
		{
			for (int j = 0; j < 80; j++)
			{
				if (map[i][j] == 1)
				{
					map[i][j - 1] = map[i][j] + map[i][j - 1];
					map[i][j] = map[i][j - 1] - map[i][j];
					map[i][j - 1] = map[i][j - 1] - map[i][j];
				}
			}
		}
	}
	else
	{
		for (int i = 25; i >= 23; i--)
		{
			for (int j = 79; j >= 0; j--)
			{
				if (map[i][j] == 1)
				{
					map[i][j + 1] = map[i][j] + map[i][j + 1];
					map[i][j] = map[i][j + 1] - map[i][j];
					map[i][j + 1] = map[i][j + 1] - map[i][j];
				}
			}
		}
	}
}
void imove(int map[26][80],int ctr)
{
	for (int i = 25; i >= 0; i--)
	{
		if (i == 25)
		{
			for (int j = 0; j < 80; j++)
			{
				if (map[i][j] < -1) 
				{
					map[i][j] = 0;
				}
				if (map[i][j] > 1 && !(ctr % 4))
				{
					map[i][j] = 0;
				}
			}
		}
		else
		{
			for (int j = 0; j < 80; j++)
			{
				if (map[i][j] < -1 ) 
				{
					if (map[i + 1][j] == 0)
					{
						map[i][j] = map[i][j] + map[i + 1][j];
						map[i + 1][j] = map[i][j] - map[i + 1][j];
						map[i][j] = map[i][j] - map[i + 1][j];
					}
					if (map[i + 1][j] == -1)
					{
						map[i + 1][j] = 0;
						map[i][j] = 0;
					}
					if (map[i + 1][j] == 1)
					{
						map[i][j] = 0;
						life--;
						ctrlife = 0;
					}
				}
				if (map[i][j] > 1 && !(ctr % 4))
				{
					if (!map[i + 1][j])
					{
						map[i][j] = map[i][j] + map[i + 1][j];
						map[i + 1][j] = map[i][j] - map[i + 1][j];
						map[i][j] = map[i][j] - map[i + 1][j];
					}
					if (map[i + 1][j] == 1)
					{
						if (map[i][j] == 88 && map[i][j - 1] == 34)
						{
							destroyer(map, i - 2, j - 2);
							map[i + 1][j - 1] = 0;
							map[i + 1][j - 2] = 0;
							life -= 2;
							ctrlife = 0;
						}
						if (map[i][j] == 88 && map[i][j + 1] == 34)
						{
							destroyer(map, i - 2, j);
							life -= 2;
							ctrlife = 0;
						}
						if (map[i][j] == 34)
						{
							destroyer(map, i - 2, j - 1);
							map[i + 1][j - 1] = 0;
							life -= 2;
							ctrlife = 0;
						}
					}
					if (map[i + 1][j] == -1)
					{
						if (map[i][j] == 88 && map[i + 1][j - 1] == 34)
						{
							destroyer(map, i - 2, j - 2);
							map[i + 1][j - 2] = 0;
							map[i + 1][j - 1] = 0;
							points++;
						}
						if (map[i][j] == 88 && map[i][j + 1] == 34)
						{
							destroyer(map, i - 2, j);
							points++;
						}
						if (map[i][j] == 34)
						{
							destroyer(map, i - 2, j - 1);
							map[i + 1][j - 1] = 0;
							points++;
						}
					}
				}
			}
		}
	}
}
void stats(int op)
{
	system("cls");
	gotoxy(38, 1);
	SetConsoleTextAttribute(out, 4);
	cout << "STATS\n";
	for (int i = 0; i < 80; i++)
		cout << "-";
	gotoxy(5, 4);
	SetConsoleTextAttribute(out, 14);
	cout << "TOTAL TROOPS DEPLOYED:\n";
	SetConsoleTextAttribute(out, 128);
	gotoxy(5, 5);
	for (int i = 0; i < deploy/10; i++)
		cout << " ";
	SetConsoleTextAttribute(out, 2);
	cout << deploy;
	gotoxy(5, 7);
	SetConsoleTextAttribute(out, 14);
	cout << "TOTAL TROOPS DESTROYED:\n";
	SetConsoleTextAttribute(out, 128);
	gotoxy(5, 8);
	for (int i = 0; i < points/10; i++)
		cout << " ";
	SetConsoleTextAttribute(out, 2);
	cout << points;
	gotoxy(5, 10);
	SetConsoleTextAttribute(out, 14);
	cout << "TOTAL BULLETS FIRED:\n";
	SetConsoleTextAttribute(out, 128);
	gotoxy(5, 11);
	for (int i = 0; i < ctrbshot/10; i++)
		cout << " ";
	SetConsoleTextAttribute(out, 2);
	cout << ctrbshot;
	gotoxy(5, 13);
	SetConsoleTextAttribute(out, 14);
	cout << "TOTAL TIMES OUT-OF-BULLETS:\n";
	SetConsoleTextAttribute(out, 128);
	gotoxy(5, 14);
	for (int i = 0; i < ctroutb/5; i++)
		cout << " ";
	SetConsoleTextAttribute(out, 2);
	cout << ctroutb;
	gotoxy(5, 16);
	SetConsoleTextAttribute(out, 14);
	cout << "TOTAL TIMES TOUCHED CRITICAL HEALTH:\n";
	SetConsoleTextAttribute(out, 128);
	gotoxy(5, 17);
	for (int i = 0; i < ctrclife/5; i++)
		cout << " ";
	SetConsoleTextAttribute(out, 2);
	cout << ctrclife;
	int input = 0;
	if (op)
	{
		gotoxy(32, 20);
		SetConsoleTextAttribute(out, 15);
		cout << "Press ";
		SetConsoleTextAttribute(out, 4);
		cout << "ESC";
		SetConsoleTextAttribute(out, 15);
		cout << " to exit";
		int input = 0;
		do {
			input = _getch();
		} while (input != 27);
	}
	else
	{
		gotoxy(35, 20);
		SetConsoleTextAttribute(out, 2);
		cout << "<-BACK";
		do {
			input = _getch();
		} while (input != 13 && input != 27);
	}
}
void welscr()
{
	system("cls");
	gotoxy(36, 1);
	SetConsoleTextAttribute(out, 15);
	cout << "WELCOME TO ";
	SetConsoleTextAttribute(out, 14);
	gotoxy(36, 2);
	cout<<" STAR WARS\n";
	SetConsoleTextAttribute(out, 15);
	for (int i = 0; i < 80; i++)
		cout << "-";
	gotoxy(10, 6);
	SetConsoleTextAttribute(out, 15);
	cout << "The Empire has been growing very fast lately. It has been reported\n that they are building an ultimate weapon, a planet killer called ";
	SetConsoleTextAttribute(out, 4);
	cout << "DEATH STAR.\n\n\t  ";
	SetConsoleTextAttribute(out, 15);
	cout << "The Empire is aware that we know their catastrophic plans. So they\n have send their troops to attack on our base. \n\n\t  ";
	cout << "You are the best pilot and the last hope of "; 
	SetConsoleTextAttribute(out, 2);
	cout << "THE RESISTANCE.";
	SetConsoleTextAttribute(out, 15);
	cout << " From the\n orders of Princess Leia, you have been sent off to fight the TWIN ION ENGINE\n on your most suitable ship X-WING STARFIGHTER.";
	gotoxy(35, 17);
	SetConsoleTextAttribute(out, 2);
	cout << "ALL THE BEST";
	SetConsoleTextAttribute(out, 15);
	gotoxy(5, 21);
	cout << "Press ";
	SetConsoleTextAttribute(out, 4);
	cout << "DOWN ARROW";
	SetConsoleTextAttribute(out, 15);
	cout << " to view instructions\n";
	int input = 0;
	do {
		input = _getch();
	} while (input != 80);
}
void instructions(int op)
{
	system("cls");
	gotoxy(35, 1);
	SetConsoleTextAttribute(out, 14);
	cout << "INSTRUCTIONS\n";
	SetConsoleTextAttribute(out, 15);
	for (int i = 0; i < 80; i++)
		cout << '-';
	gotoxy(25, 7);
	SetConsoleTextAttribute(out, 15);
	cout << "USE ";
	SetConsoleTextAttribute(out, 4);
	cout << "LEFT ARROW";
	SetConsoleTextAttribute(out, 15);
	cout << " TO MOVE SHIP LEFT";
	gotoxy(25, 9);
	cout << "USE ";
	SetConsoleTextAttribute(out, 4);
	cout << "RIGHT ARROW";
	SetConsoleTextAttribute(out, 15);
	cout << " TO MOVE SHIP RIGHT";
	gotoxy(25, 11);
	cout << "USE ";
	SetConsoleTextAttribute(out, 4);
	cout << "SPACEBAR";
	SetConsoleTextAttribute(out, 15);
	cout << " TO SHOOT";
	if (op)
	{
		gotoxy(10, 20);
		cout << "Press ";
		SetConsoleTextAttribute(out, 2);
		cout << "ENTER";
		SetConsoleTextAttribute(out, 15);
		cout << " to play";
		gotoxy(10, 21);
		cout << "Press ";
		SetConsoleTextAttribute(out, 2);
		cout << "ESC";
		SetConsoleTextAttribute(out, 15);
		cout << " to exit\n";
	}
	else
	{
		gotoxy(38, 20);
		SetConsoleTextAttribute(out, 2);
		cout << "<- BACK";
	}
	int input = 0;
	do {
		input = _getch();
		if (input == 27 && op)
			exit(0);
	} while (input != 13 && input != 27);
}
void menucall(int map[26][80], unsigned int &ctr)
{
	int input = 0;
	int menux = 1;
	int exitmenu = 1;
	static int fontsize = 10, fontwt = 1, fontcl = 15, options = 2;
	do {
		system("cls");
		gotoxy(35, 10);
		SetConsoleTextAttribute(out, fontcl);
		if (menux == 1)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "Resume";
		SetConsoleTextAttribute(out, fontcl);
		gotoxy(35, 11);
		if (menux == 2)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "Restart";
		SetConsoleTextAttribute(out, fontcl);
		gotoxy(35, 12);
		if (menux == 3)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "Stats";
		SetConsoleTextAttribute(out, fontcl);
		gotoxy(35, 13);
		if (menux == 4)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "Font";
		SetConsoleTextAttribute(out, fontcl);
		gotoxy(35, 14);
		if (menux == 5)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "Instructions";
		SetConsoleTextAttribute(out, fontcl);
		gotoxy(35, 15);
		if (menux == 6)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "About";
		SetConsoleTextAttribute(out, fontcl);
		gotoxy(35, 16);
		if (menux == 7)
		{
			SetConsoleTextAttribute(out, options);
		}
		cout << "Exit";
		SetConsoleTextAttribute(out, fontcl);
		input = _getch();
		if (input == 72)
		{
			if (menux > 1)
				menux--;
			else
				menux = 7;
		}
		if (input == 80)
		{
			if (menux < 7)
				menux++;
			else
				menux = 1;
		}
		if (input == 13)
		{
			if (menux == 1)
			{
				exitmenu = 0;
			}
			if (menux == 2)
			{
				menux = 1;
				do {
					system("cls");
					SetConsoleTextAttribute(out, fontcl);
					gotoxy(0, 8);
					for (int j = 0; j < 80; j++)
						cout << "-";
					gotoxy(35, 9);
					cout << "ARE YOU SURE?\n";
					for (int j = 0; j < 80; j++)
						cout << "-";
					if (!menux)
						SetConsoleTextAttribute(out, options);
					gotoxy(35, 12);
					cout << "YES";
					SetConsoleTextAttribute(out, fontcl);
					if (menux)
						SetConsoleTextAttribute(out, options);
					gotoxy(45, 12);
					cout << "NO";
					SetConsoleTextAttribute(out, fontcl);
					input = _getch();
					if (input == 75)
					{
						if (menux)
							menux--;
					}
					if (input == 77)
					{
						if (!menux)
							menux++;
					}
					if (input == 13)
					{
						if (!menux)
						{
							ini(map);
							ctr = -1;
						}
						menux = 6;
					}
				} while (menux != 6 && input != 27);
				menux = 2;
			}
			if (menux == 3)
			{
				stats(0);
			}
			if (menux == 4)
			{
				menux = 1;
				do {
					system("cls");
					gotoxy(35, 1);
					SetConsoleTextAttribute(out, fontcl);
					cout << "FONTS\n";
					for (int i = 0; i < 80; i++)
						cout << "-";
					gotoxy(5, 6);
					if (menux == 1)
						SetConsoleTextAttribute(out, options);
					cout << "FONT SIZE";
					gotoxy(55, 6);
					cout << "< " << fontsize << " >";
					SetConsoleTextAttribute(out, fontcl);
					gotoxy(5, 8);
					if (menux == 2)
						SetConsoleTextAttribute(out, options);
					cout << "FONT WEIGHT";
					gotoxy(55, 8);
					cout << "< " << fontwt;
					gotoxy(59, 8);
					cout << " >";
					SetConsoleTextAttribute(out, fontcl);
					gotoxy(35, 19);
					if (menux == 3)
						SetConsoleTextAttribute(out, options);
					cout << "<- BACK";
					SetConsoleTextAttribute(out, fontcl);
					input = _getch();
					if (input == 72)
					{
						if (menux > 1)
							menux--;
						else
							menux = 3;
					}
					if (input == 80)
					{
						if (menux < 3)
							menux++;
						else
							menux = 1;
					}
					if (input == 77)
					{
						if (menux == 1)
						{
							if (fontsize < 19)
								fontsize++;
						}
						if (menux == 2)
						{
							if (fontwt < 10)
								fontwt++;
						}
					}
					if (input == 75)
					{
						if (menux == 1)
						{
							if (fontsize > 9)
								fontsize--;
						}
						if (menux == 2)
						{
							if (fontwt > 1)
								fontwt--;
						}
					}
					size(fontsize, fontwt);
				} while (!((input == 13 && menux == 3) || input == 27));
				menux = 4;
			}
			if (menux == 5)
			{
				instructions(0);
				menux = 5;
			}
			if (menux == 6)
			{
				do {
					system("cls");
					gotoxy(35, 5);
					SetConsoleTextAttribute(out, 14);
					cout << "STAR WARS";
					gotoxy(27, 10);
					SetConsoleTextAttribute(out, 4);
					cout << "A Program by SARTHIK GARG";
					gotoxy(31, 12);
					cout << "950 Lines of Code";
					gotoxy(31, 13);
					cout << "Made On 21.01.2018";
					gotoxy(35, 20);
					SetConsoleTextAttribute(out, 2);
					cout << "<- BACK";
					SetConsoleTextAttribute(out, fontcl);
					input = _getch();
				} while (input != 13 && input != 27);
			}
			if (menux == 7)
			{
				menux = 1;
				do {
					system("cls");
					SetConsoleTextAttribute(out, fontcl);
					gotoxy(0, 8);
					for (int j = 0; j < 80; j++)
						cout << "-";
					gotoxy(35, 9);
					cout << "ARE YOU SURE?\n";
					for (int j = 0; j < 80; j++)
						cout << "-";
					
					if (!menux)
						SetConsoleTextAttribute(out, options);
					gotoxy(35, 12);
					cout << "YES";
					SetConsoleTextAttribute(out, fontcl);
					if (menux)
						SetConsoleTextAttribute(out, options);
					gotoxy(45, 12);
					cout << "NO";
					SetConsoleTextAttribute(out, fontcl);
					input = _getch();
					if (input == 75)
					{
						if (menux)
							menux--;
					}
					if (input == 77)
					{
						if (!menux)
							menux++;
					}
					if (input == 13)
					{
						if (!menux)
							exit(0);
						else
							menux = 6;
					}
				} while (menux != 6 && input != 27);
				menux = 7;
			}
			input = 0;
		}
		if (input == 27)
		{
			exitmenu = 0;
		}
	} while (exitmenu);
}