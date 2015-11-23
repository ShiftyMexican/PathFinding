// Author: Jarrod Dowsey
// Description:
// This is the game calass, it will encapsulate window management and the main
// game loop.

#pragma once
#ifndef GAME_H
#define GAME_H

#include <list>

class GLFWwindow;
class GameStateManager;
class IGameState;
class MenuState;
class SpriteBatch;
class Texture;
class PlayState;
class Node;
class StaticSprite;
class P1Wins;
class P2Wins;

class Game
{
public:

	// constructor
	Game(unsigned int windowWidth, unsigned int windowHeight, const char *windowTitle, bool fullscreen);

	// destructor
	~Game();

	// returns when the main game loop has finished
	void RunGame();

	unsigned int GetWindowWidth()	{ return m_windowWidth;		}
	unsigned int GetWindowHeight()	{ return m_windowHeight;	}

	// After Quit has been called,
	// the main game loop will finish the current iteration and not continue,
	// to the next iteration
	void Quit()	{ m_gameOver  = true;	}

	GLFWwindow *GetWindow()	{ return m_pWindow;		} 
	float GetDeltaTime()	{ return m_deltaTime;	}
	SpriteBatch *GetSpriteBatch() { return m_spriteBatch; }


private:

	// called each frame from within RunGame()
	void Update(float deltaTime);

	// called each frame from within RunGame()
	void Draw();

	// called from RunGame before the main game loop
	void Load();
	
	// called from RunGame after the main game loop
	void UnLoad();


	GameStateManager *GetGameStateManager() { return m_gameStateManager; }

private:

	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	bool m_gameOver;

	double m_lastTime;
	double m_currentTime;
	float m_deltaTime;

	GLFWwindow *m_pWindow;
	GameStateManager *m_gameStateManager;
	SpriteBatch *m_spriteBatch;

	std::list<IGameState *> m_CreatedGameStates;


	//TODO: place game related variables here
	//TODO: place game related functions here

};

#endif