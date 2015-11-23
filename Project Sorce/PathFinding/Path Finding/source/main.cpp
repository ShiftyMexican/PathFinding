#include "Game.h"
#include "time.h"

int main(int argc, char **argv)
{
	srand((unsigned int)time(NULL));

	Game *pGame = new Game( 1280, 720, "Tiny Tanks", false);
	pGame->RunGame();
	delete pGame;

	return 0;
}