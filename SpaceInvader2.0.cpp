#include "pch.h"
#include <iostream>
#include "mygraphics.h"
#include <conio.h>
#include <windows.h>
#include <time.h>
#define ROWS 25
#define COL 80
using namespace std;

HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);        // Part of the Font Size Adjustement Function.

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);     // Part of the Font Color Function.

// Global Variable.
bool GameContinue = true;

// Font Size Adjustment.
void fontsize(int a, int b) 
{
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = a;     // Width(Pixel) of Font.
	lpConsoleCurrentFontEx->dwFontSize.Y = b;     // Height(Pixel) of Font.
	SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
}

//2-D Array used to Initialize World that works at back end.
char World[ROWS][COL] = {
  "                                                                               ",
  "|                                                                             |",
  "|    aaa           sss              ccc               ooo               eee   |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|    zzz           mmm              nnn               uuu               rrr   |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                    ===                                      |",
};

// Shapes Initializer.
void ShapeInitialize(int i, int Lives)
{
	HWND console = GetConsoleWindow();                          // Fixing console windwow dimension to avoid shapes being dispersed on different computers.
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 666, 380, TRUE);            // Width=666 , Height=380

	// Player.
	if (Lives != 0)
	{
		drawRectangle(290 + i, 280, 327 + i, 288, 0, 0, 0, 0, 255, 0);     // Player Shape (Green Rectangle)
	}

	// Borders.
	drawLine(4, 1, 4, 300, 255);      //Left Border.

	drawLine(628, 1, 628, 300, 255);   // Right Border.

	// Lives.
	if (Lives == 3)
	{
		drawRectangle(525, 289, 545, 299, 0, 0, 0, 0, 255, 0);   // Green Rectangles To Represent Lives.

		drawRectangle(550, 289, 570, 299, 0, 0, 0, 0, 255, 0);

		drawRectangle(575, 289, 595, 299, 0, 0, 0, 0, 255, 0);
	}
	else if (Lives == 2)
	{
		drawRectangle(525, 289, 545, 299, 0, 0, 0, 0, 255, 0);

		drawRectangle(550, 289, 570, 299, 0, 0, 0, 0, 255, 0);

		drawRectangle(575, 289, 595, 299, 0, 0, 0, 0, 0, 0);        // Cleaning First Life.

	}
	else if (Lives == 1)
	{
		drawRectangle(525, 289, 545, 299, 0, 0, 0, 0, 255, 0);

		drawRectangle(550, 289, 570, 299, 0, 0, 0, 0, 0, 0);    // Cleaning Second Life.

	}
	else if (Lives == 0)
	{
		drawRectangle(525, 289, 545, 299, 0, 0, 0, 0, 0, 0);   // Cleaning Last life.
		GameContinue = 0;
	}
}

// Enemy Structure.
struct Enemy
{
	char Enemy1 = 'a';
	char Enemy2 = 's';
	char Enemy3 = 'c';
	char Enemy4 = 'o';
	char Enemy5 = 'e';
	char Enemy6 = 'z';
	char Enemy7 = 'm';
	char Enemy8 = 'n';
	char Enemy9 = 'u';
	char Enemy10 = 'r';
	char EnemyLaser = '.';
	int EnemyCount = 10;
	int EnemyReady = 0;
	int EnemyDrop = 0;
};

// Enemy Movements.
void EnemyMovement(Enemy& E, char& direction)
{
	for (int y = 0; y < ROWS - 1; y++)      // For loop through height of World Array.
	{
		// Check if Enemy is present at left most corner.
		if ((World[y][2] == E.Enemy1 && World[y][3] == E.Enemy1 && World[y][4] == E.Enemy1) || (World[y][2] == E.Enemy2 && World[y][3] == E.Enemy2 && World[y][4] == E.Enemy2) ||
			(World[y][2] == E.Enemy3 && World[y][3] == E.Enemy3 && World[y][4] == E.Enemy3) || (World[y][2] == E.Enemy4 && World[y][3] == E.Enemy4 && World[y][4] == E.Enemy4) ||
			(World[y][2] == E.Enemy5 && World[y][3] == E.Enemy5 && World[y][4] == E.Enemy5) || (World[y][2] == E.Enemy6 && World[y][3] == E.Enemy6 && World[y][4] == E.Enemy6) ||
			(World[y][2] == E.Enemy7 && World[y][3] == E.Enemy7 && World[y][4] == E.Enemy7) || (World[y][2] == E.Enemy8 && World[y][3] == E.Enemy8 && World[y][4] == E.Enemy8) ||
			(World[y][2] == E.Enemy9 && World[y][3] == E.Enemy9 && World[y][4] == E.Enemy9) || (World[y][2] == E.Enemy10 && World[y][3] == E.Enemy10 && World[y][4] == E.Enemy10)) 
		{
			direction = 'r';     // Set Direction to Right

			E.EnemyDrop = 1;         // Drop is true

			break;
		}

		// Check if Enemy is present at right most corner.
		if ((World[y][COL - 3] == E.Enemy1 && World[y][COL - 4] == E.Enemy1 && World[y][COL - 5] == E.Enemy1) ||
			(World[y][COL - 3] == E.Enemy2 && World[y][COL - 4] == E.Enemy2 && World[y][COL - 5] == E.Enemy2) ||
			(World[y][COL - 3] == E.Enemy3 && World[y][COL - 4] == E.Enemy3 && World[y][COL - 5] == E.Enemy3) ||
			(World[y][COL - 3] == E.Enemy4 && World[y][COL - 4] == E.Enemy4 && World[y][COL - 5] == E.Enemy4) ||
			(World[y][COL - 3] == E.Enemy5 && World[y][COL - 4] == E.Enemy5 && World[y][COL - 5] == E.Enemy5) ||
			(World[y][COL - 3] == E.Enemy6 && World[y][COL - 4] == E.Enemy6 && World[y][COL - 5] == E.Enemy6) ||
			(World[y][COL - 3] == E.Enemy7 && World[y][COL - 4] == E.Enemy7 && World[y][COL - 5] == E.Enemy7) ||
			(World[y][COL - 3] == E.Enemy8 && World[y][COL - 4] == E.Enemy8 && World[y][COL - 5] == E.Enemy8) ||
			(World[y][COL - 3] == E.Enemy9 && World[y][COL - 4] == E.Enemy9 && World[y][COL - 5] == E.Enemy9) ||
			(World[y][COL - 3] == E.Enemy10 && World[y][COL - 4] == E.Enemy10 && World[y][COL - 5] == E.Enemy10))          
		{
			direction = 'l';             // Set Direction to Left.

			E.EnemyDrop = 1;             // Drop is true.

			break;
		}
	}

	if (rand() % 13 == 3)            // Random Moving Time for Enemy.
	{
		if (direction == 'l')                 // if direction to move is set to left.
		{
			for (int x = 2; x <= COL - 3; x++)         // Nested loop through all possible postion of enemy array.
			{
				for (int y = 0; y < ROWS; y++)
				{
					// if drop is true and Enemy present at postion.
					if (E.EnemyDrop && ((World[y - 1][x + 1] == E.Enemy1 && World[y - 1][x + 2] == E.Enemy1 && World[y - 1][x + 3] == E.Enemy1) ||
						(World[y - 1][x + 1] == E.Enemy2 && World[y - 1][x + 2] == E.Enemy2 && World[y - 1][x + 3] == E.Enemy2) ||
						(World[y - 1][x + 1] == E.Enemy3 && World[y - 1][x + 2] == E.Enemy3 && World[y - 1][x + 3] == E.Enemy3) ||
						(World[y - 1][x + 1] == E.Enemy4 && World[y - 1][x + 2] == E.Enemy4 && World[y - 1][x + 3] == E.Enemy4) ||
						(World[y - 1][x + 1] == E.Enemy5 && World[y - 1][x + 2] == E.Enemy5 && World[y - 1][x + 3] == E.Enemy5) ||
						(World[y - 1][x + 1] == E.Enemy6 && World[y - 1][x + 2] == E.Enemy6 && World[y - 1][x + 3] == E.Enemy6) ||
						(World[y - 1][x + 1] == E.Enemy7 && World[y - 1][x + 2] == E.Enemy7 && World[y - 1][x + 3] == E.Enemy7) ||
						(World[y - 1][x + 1] == E.Enemy8 && World[y - 1][x + 2] == E.Enemy8 && World[y - 1][x + 3] == E.Enemy8) ||
						(World[y - 1][x + 1] == E.Enemy9 && World[y - 1][x + 2] == E.Enemy9 && World[y - 1][x + 3] == E.Enemy9) ||
						(World[y - 1][x + 1] == E.Enemy10 && World[y - 1][x + 2] == E.Enemy10 && World[y - 1][x + 3] == E.Enemy10)))       
					{
						World[y][x] = World[y - 1][x + 1];       // Store Enemy One Block downwards diagonally Leftwards (/).

						World[y][x + 1] = World[y - 1][x + 2];

						World[y][x + 2] = World[y - 1][x + 3];

						World[y - 1][x + 1] = ' ';            // Previous Positions of Enemy Erased.

						World[y - 1][x + 2] = ' ';

						World[y - 1][x + 3] = ' ';

					}

					// if drop not true and Enemy present at position
					else if (!E.EnemyDrop && ((World[y][x + 1] == E.Enemy1 && World[y][x + 2] == E.Enemy1 && World[y][x + 3] == E.Enemy1) ||
						(World[y][x + 1] == E.Enemy2 && World[y][x + 2] == E.Enemy2 && World[y][x + 3] == E.Enemy2) ||
						(World[y][x + 1] == E.Enemy3 && World[y][x + 2] == E.Enemy3 && World[y][x + 3] == E.Enemy3) ||
						(World[y][x + 1] == E.Enemy4 && World[y][x + 2] == E.Enemy4 && World[y][x + 3] == E.Enemy4) ||
						(World[y][x + 1] == E.Enemy5 && World[y][x + 2] == E.Enemy5 && World[y][x + 3] == E.Enemy5) ||
						(World[y][x + 1] == E.Enemy6 && World[y][x + 2] == E.Enemy6 && World[y][x + 3] == E.Enemy6) ||
						(World[y][x + 1] == E.Enemy7 && World[y][x + 2] == E.Enemy7 && World[y][x + 3] == E.Enemy7) ||
						(World[y][x + 1] == E.Enemy8 && World[y][x + 2] == E.Enemy8 && World[y][x + 3] == E.Enemy8) ||
						(World[y][x + 1] == E.Enemy9 && World[y][x + 2] == E.Enemy9 && World[y][x + 3] == E.Enemy9) ||
						(World[y][x + 1] == E.Enemy10 && World[y][x + 2] == E.Enemy10 && World[y][x + 3] == E.Enemy10)))          
					{
						World[y][x + 2] = World[y][x + 3];            // Store Enemy One Block Leftwards.

						World[y][x + 1] = World[y][x + 2];

						World[y][x] = World[y][x + 1];

						World[y][x + 3] = ' ';                // Previous Position of Enemy Erased.

					}
				}
			}
		}

		else if (direction == 'r')         // if direction to move is set to Right.
		{
			for (int x = COL - 3; x >= 2; x--)        // Nested loop through all possible postions of enemy in array.
			{
				for (int y = 0; y < ROWS; y++)
				{
					// if drop is true and Enemy present at postion.
					if (E.EnemyDrop && ((World[y - 1][x - 1] == E.Enemy1 && World[y - 1][x - 2] == E.Enemy1 && World[y - 1][x - 3] == E.Enemy1) ||
						(World[y - 1][x - 1] == E.Enemy2 && World[y - 1][x - 2] == E.Enemy2 && World[y - 1][x - 3] == E.Enemy2) ||
						(World[y - 1][x - 1] == E.Enemy3 && World[y - 1][x - 2] == E.Enemy3 && World[y - 1][x - 3] == E.Enemy3) ||
						(World[y - 1][x - 1] == E.Enemy4 && World[y - 1][x - 2] == E.Enemy4 && World[y - 1][x - 3] == E.Enemy4) ||
						(World[y - 1][x - 1] == E.Enemy5 && World[y - 1][x - 2] == E.Enemy5 && World[y - 1][x - 3] == E.Enemy5) ||
						(World[y - 1][x - 1] == E.Enemy6 && World[y - 1][x - 2] == E.Enemy6 && World[y - 1][x - 3] == E.Enemy6) ||
						(World[y - 1][x - 1] == E.Enemy7 && World[y - 1][x - 2] == E.Enemy7 && World[y - 1][x - 3] == E.Enemy7) ||
						(World[y - 1][x - 1] == E.Enemy8 && World[y - 1][x - 2] == E.Enemy8 && World[y - 1][x - 3] == E.Enemy8) ||
						(World[y - 1][x - 1] == E.Enemy9 && World[y - 1][x - 2] == E.Enemy9 && World[y - 1][x - 3] == E.Enemy9) ||
						(World[y - 1][x - 1] == E.Enemy10 && World[y - 1][x - 2] == E.Enemy10 && World[y - 1][x - 3] == E.Enemy10)))               
					{
						World[y][x - 2] = World[y - 1][x - 3];          // Store Enemy One Block downwards diagonally Rightwards (\).

						World[y][x - 1] = World[y - 1][x - 2];

						World[y][x] = World[y - 1][x - 1];

						World[y - 1][x - 1] = ' ';                 // Previous Positions of Enemy Erased.

						World[y - 1][x - 2] = ' ';

						World[y - 1][x - 3] = ' ';

					}

					// if drop not true and Enemy present at position
					else if (!E.EnemyDrop && ((World[y][x - 1] == E.Enemy1 && World[y][x - 2] == E.Enemy1 && World[y][x - 3] == E.Enemy1) ||
						(World[y][x - 1] == E.Enemy2 && World[y][x - 2] == E.Enemy2 && World[y][x - 3] == E.Enemy2) ||
						(World[y][x - 1] == E.Enemy3 && World[y][x - 2] == E.Enemy3 && World[y][x - 3] == E.Enemy3) ||
						(World[y][x - 1] == E.Enemy4 && World[y][x - 2] == E.Enemy4 && World[y][x - 3] == E.Enemy4) ||
						(World[y][x - 1] == E.Enemy5 && World[y][x - 2] == E.Enemy5 && World[y][x - 3] == E.Enemy5) ||
						(World[y][x - 1] == E.Enemy6 && World[y][x - 2] == E.Enemy6 && World[y][x - 3] == E.Enemy6) ||
						(World[y][x - 1] == E.Enemy7 && World[y][x - 2] == E.Enemy7 && World[y][x - 3] == E.Enemy7) ||
						(World[y][x - 1] == E.Enemy8 && World[y][x - 2] == E.Enemy8 && World[y][x - 3] == E.Enemy8) ||
						(World[y][x - 1] == E.Enemy9 && World[y][x - 2] == E.Enemy9 && World[y][x - 3] == E.Enemy9) ||
						(World[y][x - 1] == E.Enemy10 && World[y][x - 2] == E.Enemy10 && World[y][x - 3] == E.Enemy10)))                          
					{
						World[y][x] = World[y][x - 1];                // Store Enemy One Block Rightwards.

						World[y][x - 2] = World[y][x - 3];

						World[y][x - 1] = World[y][x - 2];

						World[y][x - 3] = ' ';                        // Previous Position of Enemy Erased.

					}
				}
			}
		}
	}

	for (int x = 2; x < COL - 2; x++)       // For loop to check if Enemy is at last stage to Player.
	{
		// if Enemy parallel to player is true. 
		if (World[ROWS - 1][x] == E.Enemy1 || World[ROWS - 1][x] == E.Enemy2 || World[ROWS - 1][x] == E.Enemy3 || World[ROWS - 1][x] == E.Enemy4 ||
			World[ROWS - 1][x] == E.Enemy5 || World[ROWS - 1][x] == E.Enemy6 || World[ROWS - 1][x] == E.Enemy7 || World[ROWS - 1][x] == E.Enemy8 ||
			World[ROWS - 1][x] == E.Enemy9 || World[ROWS - 1][x] == E.Enemy10)                  
		{
			GameContinue = 0;             // Game Ends.
		}
	}
}

//Output Message At the End of Game.
void OutputMessage(int Score, int Lives, int EnemyCount)
{
	if (Lives > 0 && EnemyCount == 0)      // If Player Wins
	{
		cout << endl << endl << endl << "                            Well Played!        " << endl << endl;                 // Message to Player At End.

		cout << endl << endl << endl << endl << "                                       Your Score is : " << Score << endl << endl << endl << endl;                    // Display Score At End.

	}
	else           // If Player Loses or Quits.
	{
		cout << endl << endl << endl << endl << "                Better Luck Next Time!        " << endl << endl;                 // Message to Player At End.

		cout << endl << endl << endl << endl << "                                       Your Score is : " << Score << endl << endl << endl;                    // Display Score At End.

	}
}

//Welcome Message Before Starting Game.
void Welcome(int& Difficulty)
{
	//Welcome Screen.
	fontsize(10, 18);   // Adjusting Font Size For Message Display.

	showConsoleCursor(false);

	cout << "                            WELCOME TO SPACE INVADERS! " << endl;    // Welcome To the Game.

	delay(2000);    // Delay for 2000 milliseconds.

	cls();    // Clear Screen

	cout << "                              Choose Difficulty Level : " << endl << endl;

	cout << "                        Press 1: Easy -----> For Beginners! " << endl << endl;     // Press 1 for Easy Difficulty.

	cout << "                        Press 2: Medium -----> For Regular Players! " << endl << endl;       // Press 2 for Medium Difficulty.

	cout << "                        Press 3: Hard -----> You Will Not Survive! ";    // Press 3 for Hard Difficulty.

	do     // Loop for Validation.
	{
		Difficulty = _getch();      // Gets key from User.

	} while (Difficulty != '1' && Difficulty != '2' && Difficulty != '3');      // Repeat until Valid Difficulty Selected.

	delay(400);   // Delay for 400 milliseconds.
}

//Displaying World After Every Change.
void DisplayWorld(int Score, int Lives)
{
	for (int y = 1; y < ROWS; y++)          // Loop to Display World|Array.
	{
		cout << World[y] << endl;
	}
	cout << "    SCORE : " << Score << "                                        LIVES: " << Lives;  // Score & Lives Display.
}

//Laser System For Enemies & Player.
void LaserControl(char Player, char PlayerLaser, Enemy& E , int& Score, int& Lives, int& LaserReady, int Difficulty)
{
	for (int x = 0; x < COL; x++)                                   // Nested Loops to Display Enemy Laser.
	{
		for (int y = ROWS - 1; y > 0; y--)
		{
			if (World[y][x] == E.EnemyLaser && (World[y + 1][x] == PlayerLaser))     // Checks if Enemy Laser is Above Player Laser, if True then Both Laser Disappear.
			{
				World[y][x] = ' ';                // Enemy Laser Disappear.

				World[y + 1][x] = ' ';    // Player Laser Disappear.

				Beep(200, 3);     // Kill Sound.
			}

			// Checks if Enemy is Below Enemy Laser. If Enemy is Below, Enemy Laser Disappers, Else it Continues.
			else if (World[y][x] == E.EnemyLaser && (World[y + 1][x] != E.Enemy1 || World[y + 1][x] != E.Enemy2 || World[y + 1][x] != E.Enemy3 || 
				     World[y + 1][x] != E.Enemy4 || World[y + 1][x] != E.Enemy5 || World[y + 1][x] != E.Enemy6 || World[y + 1][x] != E.Enemy7 || 
				     World[y + 1][x] != E.Enemy8 || World[y + 1][x] != E.Enemy9 || World[y + 1][x] != E.Enemy10))     
			{
				World[y + 1][x] = E.EnemyLaser;     // Enemy Laser Continues.

				World[y][x] = ' ';    // Previous Position of Enemy Laser Disappers.

			}

			// If Enemy Below Enemy Laser.
			else if (World[y][x] == E.EnemyLaser && (World[y + 1][x] == E.Enemy1 || World[y + 1][x] == E.Enemy2 || World[y + 1][x] == E.Enemy3 ||
				     World[y + 1][x] == E.Enemy4 || World[y + 1][x] == E.Enemy5 || World[y + 1][x] == E.Enemy6 || World[y + 1][x] == E.Enemy7 ||
				     World[y + 1][x] == E.Enemy8 || World[y + 1][x] == E.Enemy9 || World[y + 1][x] == E.Enemy10))       
			{
				World[y][x] = ' ';  // Enemy Laser Disappears.

			}

			else if (World[y][x] == Player && World[y - 1][x] == E.EnemyLaser)   // Checks if Player is Below Enemy Laser, if True then Enemy Laser Disappear & Player Lives Decrease. 
			{
				World[y - 1][x] = ' ';   // Enemy Laser Disappear.

				Lives--;                 // Lives Count Decrease.

				Beep(800, 10);     // Kill Sound.

				if (Lives == 0)          // Checks if No lives Left, if True then Game Finished.
				{
					GameContinue = 0;        // Game Finished.

					break;               // Break Loop.
				}
			}
		}
	}

	for (int x = 0; x < COL; x++)                            // Nested Loops to Control Player Laser & Enemy Laser.
	{
		for (int y = 0; y < ROWS; y++)
		{
			if (World[y][x] == PlayerLaser && World[y - 1][x] == E.EnemyLaser)  // Checks if Enemy Laser is Above Player Laser, if True then Both Laser Disappear.
			{
				World[y][x] = ' ';            // Player Laser Disappear.

				World[y - 1][x] = ' ';        // Enemy Laser Disappear.

				Beep(200, 3);     // Kill Sound.

			}

			else if (World[y][x] == E.EnemyLaser && World[y + 1][x] == Player)  // Checks if Player is Below Enemy Laser, if True then Enemy Laser Disappear & Player Lives Decrease. 
			{
				World[y][x] = ' ';         // Enemy Laser Disappears.

				Lives--;                 // Lives Count Decrease.

				Beep(800, 10);     // Kill Sound.

				if (Lives == 0)          // Checks if No lives Left, if True then Game Finished.
				{
					GameContinue = 0;        // Game Finished.

					break;               // Break Loop.
				}
			}

			// Checks if Enemy is Above Player Laser, if Enemy Present Above then Enemy is Killed and Player Laser Disappears.
			else if (World[y][x] == PlayerLaser && (World[y - 1][x] == E.Enemy1 || World[y - 1][x] == E.Enemy2 || World[y - 1][x] == E.Enemy3 ||
					 World[y - 1][x] == E.Enemy4 || World[y - 1][x] == E.Enemy5 || World[y - 1][x] == E.Enemy6 || World[y - 1][x] == E.Enemy7 ||
					 World[y - 1][x] == E.Enemy8 || World[y - 1][x] == E.Enemy9 || World[y - 1][x] == E.Enemy10))    
			{

				World[y][x] = ' ';          // Player Laser Disappers.

				World[y - 1][x] = ' ';         // Enemy is Killed.

				World[y - 1][x + 1] = ' ';

				World[y - 1][x + 2] = ' ';

				World[y - 1][x - 1] = ' ';

				World[y - 1][x - 2] = ' ';

				E.EnemyCount--;                      // Enemy Count Decreased.

				Score = Score + 20;               // Player Score Increased.

				Beep(800, 10);     // Kill Sound.

			}

			else if (Difficulty == '1')     // Easy Difficulty.
			{
				if (((World[y][x] == E.Enemy1 && World[y][x + 1] == E.Enemy1 && World[y][x + 2] == E.Enemy1) || 
					(World[y][x] == E.Enemy2 && World[y][x + 1] == E.Enemy2 && World[y][x + 2] == E.Enemy2) ||
					(World[y][x] == E.Enemy3 && World[y][x + 1] == E.Enemy3 && World[y][x + 2] == E.Enemy3) ||
					(World[y][x] == E.Enemy4 && World[y][x + 1] == E.Enemy4 && World[y][x + 2] == E.Enemy4) ||
					(World[y][x] == E.Enemy5 && World[y][x + 1] == E.Enemy5 && World[y][x + 2] == E.Enemy5) ||
					(World[y][x] == E.Enemy6 && World[y][x + 1] == E.Enemy6 && World[y][x + 2] == E.Enemy6) ||
					(World[y][x] == E.Enemy7 && World[y][x + 1] == E.Enemy7 && World[y][x + 2] == E.Enemy7) ||
					(World[y][x] == E.Enemy8 && World[y][x + 1] == E.Enemy8 && World[y][x + 2] == E.Enemy8) ||
					(World[y][x] == E.Enemy9 && World[y][x + 1] == E.Enemy9 && World[y][x + 2] == E.Enemy9) ||
					(World[y][x] == E.Enemy10 && World[y][x + 1] == E.Enemy10 && World[y][x + 2] == E.Enemy10)) && 
					(rand() % 9) == 2 && (rand() % 9) == 3 && (rand() % 2) == 0 && World[y + 1][x] != PlayerLaser)           // Random Shooting Time for Enemy.
				{
					for (int NewH = y + 1; NewH < ROWS; NewH++)        // Loop to Control Enemy Laser if Another Enemy is Below.
					{
						if (World[NewH][x] == E.Enemy1 || World[NewH][x] == E.Enemy2 || World[NewH][x] == E.Enemy3 || World[NewH][x] == E.Enemy4 || 
							World[NewH][x] == E.Enemy5 || World[NewH][x] == E.Enemy6 || World[NewH][x] == E.Enemy7 || World[NewH][x] == E.Enemy8 || 
							World[NewH][x] == E.Enemy9 || World[NewH][x] == E.Enemy10)           // Checks if Another Enemy is Below, if True Then Enemy Above Does Not Shoot Laser.
						{
							E.EnemyReady = 0;     // Enemy Above Ready is False.

							break;    // Loop Break.
						}

						E.EnemyReady = 1;      //For Enemy not Below, Enemy Above is Ready To Shoot.
					}

					if (E.EnemyReady)    // Enemy Above Ready is True.
					{
						World[y + 1][x + 1] = E.EnemyLaser;       // Enemy Shoots Downwards.

					}
				}
			}

			else if (Difficulty == '2')     // Medium Difficulty.
			{
				if (((World[y][x] == E.Enemy1 && World[y][x + 1] == E.Enemy1 && World[y][x + 2] == E.Enemy1) ||
					(World[y][x] == E.Enemy2 && World[y][x + 1] == E.Enemy2 && World[y][x + 2] == E.Enemy2) ||
					(World[y][x] == E.Enemy3 && World[y][x + 1] == E.Enemy3 && World[y][x + 2] == E.Enemy3) ||
					(World[y][x] == E.Enemy4 && World[y][x + 1] == E.Enemy4 && World[y][x + 2] == E.Enemy4) ||
					(World[y][x] == E.Enemy5 && World[y][x + 1] == E.Enemy5 && World[y][x + 2] == E.Enemy5) ||
					(World[y][x] == E.Enemy6 && World[y][x + 1] == E.Enemy6 && World[y][x + 2] == E.Enemy6) ||
					(World[y][x] == E.Enemy7 && World[y][x + 1] == E.Enemy7 && World[y][x + 2] == E.Enemy7) ||
					(World[y][x] == E.Enemy8 && World[y][x + 1] == E.Enemy8 && World[y][x + 2] == E.Enemy8) ||
					(World[y][x] == E.Enemy9 && World[y][x + 1] == E.Enemy9 && World[y][x + 2] == E.Enemy9) ||
					(World[y][x] == E.Enemy10 && World[y][x + 1] == E.Enemy10 && World[y][x + 2] == E.Enemy10)) &&
					(rand() % 9) == 2 && (rand() % 9) == 5 && World[y + 1][x] != PlayerLaser)           // Random Shooting Time for Enemy.
				{
					for (int NewH = y + 1; NewH < ROWS; NewH++)        // Loop to Control Enemy Laser if Another Enemy is Below.
					{
						if (World[NewH][x] == E.Enemy1 || World[NewH][x] == E.Enemy2 || World[NewH][x] == E.Enemy3 || World[NewH][x] == E.Enemy4 ||
							World[NewH][x] == E.Enemy5 || World[NewH][x] == E.Enemy6 || World[NewH][x] == E.Enemy7 || World[NewH][x] == E.Enemy8 ||
							World[NewH][x] == E.Enemy9 || World[NewH][x] == E.Enemy10)           // Checks if Another Enemy is Below, if True Then Enemy Above Does Not Shoot Laser.
						{
							E.EnemyReady = 0;     // Enemy Above Ready is False.

							break;    // Loop Break.
						}

						E.EnemyReady = 1;      //For Enemy not Below, Enemy Above is Ready To Shoot.
					}

					if (E.EnemyReady)    // Enemy Above Ready is True.
					{
						World[y + 1][x + 1] = E.EnemyLaser;       // Enemy Shoots Downwards.
					}
				}
			}

			else if (Difficulty == '3')     // Hard Difficulty.
			{
				if (((World[y][x] == E.Enemy1 && World[y][x + 1] == E.Enemy1 && World[y][x + 2] == E.Enemy1) ||
					(World[y][x] == E.Enemy2 && World[y][x + 1] == E.Enemy2 && World[y][x + 2] == E.Enemy2) ||
					(World[y][x] == E.Enemy3 && World[y][x + 1] == E.Enemy3 && World[y][x + 2] == E.Enemy3) ||
					(World[y][x] == E.Enemy4 && World[y][x + 1] == E.Enemy4 && World[y][x + 2] == E.Enemy4) ||
					(World[y][x] == E.Enemy5 && World[y][x + 1] == E.Enemy5 && World[y][x + 2] == E.Enemy5) ||
					(World[y][x] == E.Enemy6 && World[y][x + 1] == E.Enemy6 && World[y][x + 2] == E.Enemy6) ||
					(World[y][x] == E.Enemy7 && World[y][x + 1] == E.Enemy7 && World[y][x + 2] == E.Enemy7) ||
					(World[y][x] == E.Enemy8 && World[y][x + 1] == E.Enemy8 && World[y][x + 2] == E.Enemy8) ||
					(World[y][x] == E.Enemy9 && World[y][x + 1] == E.Enemy9 && World[y][x + 2] == E.Enemy9) ||
					(World[y][x] == E.Enemy10 && World[y][x + 1] == E.Enemy10 && World[y][x + 2] == E.Enemy10)) &&
					(rand() % 13) == 11 && World[y + 1][x] != PlayerLaser)           // Random Shooting Time for Enemy.
				{
					for (int NewH = y + 1; NewH < ROWS; NewH++)        // Loop to Control Enemy Laser if Another Enemy is Below.
					{
						if (World[NewH][x] == E.Enemy1 || World[NewH][x] == E.Enemy2 || World[NewH][x] == E.Enemy3 || World[NewH][x] == E.Enemy4 || 
							World[NewH][x] == E.Enemy5 || World[NewH][x] == E.Enemy6 || World[NewH][x] == E.Enemy7 || World[NewH][x] == E.Enemy8 ||
							World[NewH][x] == E.Enemy9 || World[NewH][x] == E.Enemy10)           // Checks if Another Enemy is Below, if True Then Enemy Above Does Not Shoot Laser.
						{
							E.EnemyReady = 0;     // Enemy Above Ready is False.

							break;    // Loop Break.
						}

						E.EnemyReady = 1;      //For Enemy not Below, Enemy Above is Ready To Shoot.
					}

					if (E.EnemyReady)    // Enemy Above Ready is True.
					{
						World[y + 1][x + 1] = E.EnemyLaser;       // Enemy Shoots Downwards.
					}
				}
			}

			if (World[y][x] == PlayerLaser && World[y - 1][x] != E.EnemyLaser && y > 0)   // if Enemy is Not Above Player Laser, Player Laser Continues.
			{
				World[y][x] = ' ';    // Previous Position of Player Laser Disappers.

				World[y - 1][x] = PlayerLaser;   // Player Laser Continues Upwards.

			}
		}
	}
}

// Player Movement Depending on Key Pressed. 
void PlayerMovement(char Player, char PlayerLaser, char& Key, int& LaserReady, int& i, int Lives)
{
	Key = getKey();        // Get Key from User.

	if (Key == 'a' || Key == 'A')        // In Case of Player Moving Leftwards. 
	{
		for (int x = 2; x < COL - 2; x++)         // Loop through Positive X-Axis.
		{
			if (World[ROWS - 1][x] == Player && World[ROWS - 1][x + 1] == Player && World[ROWS - 1][x + 2] == Player)        // Checks Current Position of Player.
			{
				World[ROWS - 1][x - 1] = Player;               // Store Player in Previous Positions.

				World[ROWS - 1][x] = Player;

				World[ROWS - 1][x + 1] = Player;

				World[ROWS - 1][x + 2] = ' ';        // Makes Current Position Blank.

				i = i - 8;        // Variable i controls Player Shape Movement.

				break;
			}
		}
	}

	if (Key == 'd' || Key == 'D')           //In Case of Player Moving Rightwards.
	{
		for (int x = COL - 4; x > 0; x--)       // Loop through Negative X-Axis.
		{
			if (World[ROWS - 1][x] == Player && World[ROWS - 1][x - 1] == Player && World[ROWS - 1][x - 2] == Player)    // Checks Current Position of Player.
			{
				World[ROWS - 1][x - 1] = Player;      // Store Player in Forward Positions.

				World[ROWS - 1][x] = Player;

				World[ROWS - 1][x + 1] = Player;

				World[ROWS - 1][x - 2] = ' ';                // Makes Current Position Blank.

				i = i + 8;        // Variable i controls Player Shape Movement.

				break;
			}
		}
	}

	if (Key == ' ' && LaserReady > 3)        // In Case of Player Shooting Laser.
	{
		for (int x = 0; x < COL; x++)  // Loop for X Postion of Player As Y Postion is Fixed.
		{
			if (World[ROWS - 1][x] == Player && World[ROWS - 1][x + 1] == Player)     // Check Current Positon of Player.
			{
				World[ROWS - 2][x + 1] = PlayerLaser;     // Place Player Laser One Postion Above Current Position of Player.

				LaserReady = 0;              // Laser Ready set to 0 to Avoid Multiple Shooting by Player.

				Beep(500, 2);   // Shoot Sound. Part of the Time.h Library.

				break;
			}
		}
	}

	if (Key == 'q' || Key == 'Q')    // Manual Exit.
	{
		system("cls");   // Clear Screen.

		cout << endl << endl << "                           Manual Exit   ";       // Exit Message.

		delay(1000);

		GameContinue = 0;      // Game Ends.

	}
}

// Function to Clean Shapes.
void CleaningShapes()
{
	// Cleaning Borders.
	drawLine(4, 1, 4, 300, 0);      //Left Border.

	drawLine(628, 1, 628, 300, 0);   // Right Border.

	// Green Rectangles To Represent Lives.
	drawRectangle(525, 289, 545, 299, 0, 0, 0, 0, 0, 0);   // Cleaning Lives.

	drawRectangle(550, 289, 570, 299, 0, 0, 0, 0, 0, 0);

	drawRectangle(575, 289, 595, 299, 0, 0, 0, 0, 0, 0);
}

// Main Function.
int main()
{
	char Player = '=', PlayerLaser = '^', Key = NULL, direction = 'l';        // Local Variables Initialized.

	int Score = 0, LReady = 1, Lives = 3, PlayerShapeControl = 0, Difficulty = 0;

	Enemy E;   // User-defined Enemy Structure.

	SetConsoleTextAttribute(hConsole, 11);   // Sets Text Color to Light Blue (11).

	Welcome(Difficulty);                      // Welcome Message.

	showConsoleCursor(false);          // Remove Cursor.

	delay(1000);    // Wait 1000 milliseconds.

	cls();   // Clear Screen.

	fontsize(8, 12);  // Adjusting Font Size For Game.

	SetConsoleTextAttribute(hConsole, 55);  // Set Console Background to Blue & Text Color to White.

	while (E.EnemyCount > 0 && GameContinue)        // Major Loop To Control Game, Terminates When Either All Enemies are Killed OR Player Lives are 0 OR Enemies Reach Player.
	{
		E.EnemyDrop = 0;    // Enemy Drop Control Variable.

		system("cls");  // Clear Screen.

		LReady = LReady + 1;        // Player Laser Shooting  Control Variable.

		DisplayWorld(Score, Lives);      // Display 2D World|Array.

		ShapeInitialize(PlayerShapeControl, Lives);  // Shapes Display.

		LaserControl(Player, PlayerLaser, E , Score, Lives, LReady, Difficulty);    // Laser Mechanics.

		EnemyMovement(E, direction); // Enemy Movement Mechanics.

		PlayerMovement(Player, PlayerLaser, Key, LReady, PlayerShapeControl, Lives);     // Player Movement Mechanics.

		delay(50);    // Wait 50 milliseconds.

	}

	delay(500);    // Wait 500 milliseconds.

	CleaningShapes();   // Clean Shapes.

	system("cls");   // Clear Screen.

	fontsize(10, 18);   // Adjusting Font Size For Output Message Display.

	OutputMessage(Score, Lives, E.EnemyCount);   // Display Output Message.

	system("pause");   // Program Terminate.
}


