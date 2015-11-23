/** \Author Jarrod Dowsey */
/** \Description Basic Tile class */

#ifndef	TILE_H
#define TILE_H

#include "Node.h"
#include <list>

class Node;
class Game;
class Texture;
class SpriteBatch;
class StaticSprite;
class PlayState;


struct Tile : public Node
{
public:
	/// Defualt Constructor
	Tile(Texture * pTileTexture, int _id, float _width, float _height);

	/// Destructor
	virtual ~Tile();

	/// Update
	virtual void Update( float dt );
	
	/// Draw
	virtual void Draw( SpriteBatch * sb);

	std::list< Tile* > m_neighbours;

	Texture *GetTexture() { return m_tileTexture; }

	void BFS();
	void DFS();

	/// Getter Functions
	int GetId()			{ return m_id;		}
	float GetGScore()	{ return m_gScore;	}
	float GetHScore()	{ return m_hScore;	}
	float GetFScore()	{ return m_fScore;	}
	bool GetOpen()		{ return m_open;	}
	Tile* GetParent()	{ return m_parent;	}

	/// Setter Functions
	void SetGScore(float _gScore)	{ m_gScore = _gScore;	}
	void SetHScore(float _hScore)	{ m_hScore = _hScore;	}
	void SetFScore(float _fScore)	{ m_fScore = _fScore;	}
	void SetOpen(bool _open)		{ m_open = _open;		}
	void SetParent(Tile* _parent)	{ m_parent = _parent;	}

	void ChangeColour(float _green, float _blue, float _alpha);

	bool m_active;
	bool m_pressed;
	bool m_pathTile;

protected:
private:

	Texture			*m_tileTexture;

	float m_red, m_green, m_blue, m_alpha;

	int m_id;
	float m_gScore;
	float m_hScore;
	float m_fScore;
	bool m_open;
	Tile* m_parent;
	
};

#endif