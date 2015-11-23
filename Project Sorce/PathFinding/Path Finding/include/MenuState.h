// Author: Jarrod Dowsey
// Description: basic menu state

#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameStateManager.h"
#include "GLFW\glfw3.h"
#include "Game.h"

class Game;
class Texture;
class Node;
class StaticSprite;

class MenuState : public IGameState
{
public:

	MenuState(GameStateManager *pGameStateManager);

	virtual ~MenuState();

	virtual void Update( float dt );
	virtual void Draw();

	virtual void Load();
	virtual void UnLoad();

protected:
private:

	float m_clickCoolDown;

	bool cursorOverTopButton;
	bool cursorOverBottomButton;

	SpriteBatch *m_spriteBatch;
	Game *m_pGame;

	Texture *m_titleTexture;
	Texture *m_randomGenTexture;
	Texture *m_makeYourOwnTexture;
	StaticSprite *m_title;
	StaticSprite *m_randomGen;
	StaticSprite *m_MakeYourOwn;

};

#endif