// Author: Jarrod Dowsey
// Description: Play State mode for the randomly generated graph.

#ifndef	RANDOMGENSTATE_H
#define RANDOMGENSTATE_H

#include "GameStateManager.h"
#include "Game.h"
#include "GLFW\glfw3.h"

class Game;
class Texture;
class Node;
class StaticSprite;
struct Tile;
class AI;
class PhysicsObject;

//const int X_SPACING_RAND = 100;
//const int Y_SPACING_RAND = 100;
const int TILE_X_RAND = 15;
const int TILE_Y_RAND = 15;

class RandomGenState : public IGameState
{
public:
	/// Defualt Constructor
	RandomGenState(GameStateManager *pGameStateManagaer);

	/// Destructor
	virtual ~RandomGenState();

	/// Function to reset the play State
	void ResetPlayState();

	/// Adding a Tile to the screen
	void AddTile( float xPos, float yPos ); 

	bool TileClicked(Tile* _tile, const Vec2& _pos);

	void Generate();

	void ResetState();

	void SetNewStart();

	void PopulateDijkstras();

	void Dijkstraspath( Tile* start, std::vector< Tile* > &outPath );
	void AStarPath( Tile* start, Tile* end, std::vector< Tile* > &outPath );
	std::list< Tile* > m_priorityList;
	std::list< Tile* > m_closedList;
	std::vector< Tile* > outPath;
	

protected:

private:
	/// Update
	virtual void Update( float deltaTime );

	/// Draw
	virtual void Draw();

private:

	int m_xOffset;
	int m_yOffset;
	int m_howManyTiles;

	float m_lineRed;
	float m_lineGreen;
	float m_lineBlue;
	float m_coolDown;
	float m_coolDownReset;
	float m_howManyEndTiles;

	bool m_mouseClicked;
	bool m_rightClicked;
	bool m_colourSelected;
	bool m_startSelected;
	bool m_endSelected;
	bool m_tilesOnScreen;
	bool m_pathFound;
	bool m_leftShiftPressed;
	bool m_endFound;
	bool m_started;
	bool m_rShiftPressed;
	bool m_firstStart;
	bool m_aStarSearch;
	bool m_newRightClick;
	bool m_dijkstrasDone;

	Game *m_pGame;
	SpriteBatch *m_spriteBatch;
	Texture *m_tileTexture;
	Texture *m_aiTexture;
	Tile* m_start;
	Tile* m_end;
	Tile* m_endRoam;
	Tile *m_currentTile;
	AI *m_ai;
	std::vector< Tile * > m_possibleEnds;
	std::vector< Tile* > dijksraPoints;
	std::vector< Tile* > m_tiles;

	float testFloat;
};

#endif