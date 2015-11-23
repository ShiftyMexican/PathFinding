// Author: Jarrod Dowsey
// Description: Game State manager,
//				handles a stack of game states.


#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <map>
#include <vector>

class GameStateManager;
class Game;

class IGameState
{
public:
	/// Defualt Constructor
	IGameState( GameStateManager *pGameStateManger );
	virtual ~IGameState();

	/// Update
	virtual void Update( float dt );

	/// Draw
	virtual void Draw();
	bool UpdateBlocking();

protected:
	
	GameStateManager *m_gameStateManager;

private:


};


class GameStateManager
{
public:

	// Constructor
	GameStateManager(Game *pGame);

	// Destructor
	virtual ~GameStateManager();

	// Should be called each frame by the "Game" class
	void UpdateGameStates( float dt );
	void DrawGameStates();

	// Used to manipulate the game state stack
	void SetState ( const char *name, IGameState *pState);
	void PushState( const char *name );
	void PopState();

	Game *GetGame() { return m_pGame; }


protected:

	void ProcessCommands();

	// contains all the available game states that have been
	// registered with the game state manager.
	std::map< const char *, IGameState * > m_availableStates;

	// lists of game states that are being updated and drwan
	std::vector< IGameState * > m_gameStateStack;

	enum ECommands
	{
		E_PUSH,
		E_POP,
	};


	struct SCommand
	{
		const char *name;
		ECommands cmd;
	};

	std::vector< SCommand > m_commands;
	Game *m_pGame;

private:


};

#endif