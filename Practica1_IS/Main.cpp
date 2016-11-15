#include <windows.h>
#include <conio.h>
#include <iostream>

// Constants
static const unsigned int WORLD_WIDTH  = 80;
static const unsigned int WORLD_HEIGHT = 10;
static const unsigned int FPS          = 20;
static const unsigned int GROUND_COLOR = 0x02;
static const unsigned int PLAYER_COLOR = 0x0E;
static const unsigned int BULLET_COLOR = 0x0C;

 
// Game state
int pcPosition      = WORLD_WIDTH / 2;
int bulletPosition  = -1;
int bulletDirection = 0;


void handleKey();
void paintEntities();
void paintBackground();
void gotoXY(int x, int y);
void clear();


void main()
{
	const DWORD FRAME_TIME = 1000 / FPS;
	while (1)
	{
		clear();
		paintBackground();
		handleKey();
		paintEntities();
		Sleep(FRAME_TIME);
	}
	return;
}

// Handles the key pressed
void handleKey()
{
	int c = 0;
	if (_kbhit())
		c = _getch();

	switch (c)
	{
		case 'a': if (pcPosition > 0)               pcPosition--;                                               break; // Moves player's character left
		case 'd': if (pcPosition < WORLD_WIDTH - 1) pcPosition++;                                               break; // Moves player's character right
		case 'q': if (bulletPosition < 0) { Beep(400, 50); bulletPosition = pcPosition; bulletDirection = -1; } break; // Shoots a new bullet to the left
		case 'e': if (bulletPosition < 0) { Beep(400, 50); bulletPosition = pcPosition; bulletDirection =  1; } break; // Shoots a new bullet to the right
	}
}

// Paints the player's character and the bullet
void paintEntities()
{
	// Paint player's character
	gotoXY(pcPosition, WORLD_HEIGHT);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYER_COLOR);
	printf("%c", '&');

	// Paint bullet
	if ((bulletPosition > 0) && (bulletPosition < WORLD_WIDTH - 1))
	{
		bulletPosition += bulletDirection;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BULLET_COLOR);
		gotoXY(bulletPosition, WORLD_HEIGHT);
		printf("%c", '-');
	}
	else
		bulletPosition = -1;
}

// Paints the world's background
void paintBackground()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GROUND_COLOR);
	for (int i = 0; i < WORLD_HEIGHT; i++)
		printf("%c", '\n');
	for (int i = 0; i < WORLD_WIDTH; i++)
		printf("%c", '_');
}

// Sets the console cursor in the given position
void gotoXY(int x, int y)
{
	COORD  pos    = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

// Clears console
void clear()
{
	system("cls");
}