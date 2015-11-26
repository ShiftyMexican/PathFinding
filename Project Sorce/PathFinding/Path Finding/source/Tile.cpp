#include "Tile.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include <iostream>

Tile::Tile(Texture *pTileTexture, int _id, float _width, float _height) : Node()
{
	m_tileTexture = pTileTexture;
	m_id = _id;
	Transform()->SetScale(_width / pTileTexture->GetWidth(), _height / pTileTexture->GetHeight());
	m_red = 1.0f;
	m_green = 1.0f;
	m_blue = 1.0f;
	m_alpha = 1.0f;
	m_pressed = false;
	m_active = false;
	m_pathTile = false;
	m_parent = NULL;
}

/// Destructor
Tile::~Tile()
{
	delete m_tileTexture;
}

/// Update
void Tile::Update( float dt )
{

}

/// Draw
void Tile::Draw( SpriteBatch * sb)
{
	sb->DrawSprite( m_tileTexture, m_localTransform, Vec2(25, 25), m_red, m_green, m_blue, m_alpha);
}

void Tile::BFS()
{
	if(m_active == true )
		return;

	m_active = true;

	std::cout << m_id << std::endl;

	for(auto itr = m_neighbours.begin(); itr != m_neighbours.end(); itr++)
	{
		(*itr)->BFS();
	}
}

void Tile::DFS()
{
	if(m_active == true )
		return;	

	m_active = true;

	for(auto itr = m_neighbours.begin(); itr != m_neighbours.end(); itr++)
	{
		(*itr)->DFS();
	}

	std::cout << m_id << std::endl;
}

void Tile::ChangeColour(float _green, float _blue, float _alpha)
{
	m_green = _green;
	m_blue	= _blue;
	m_alpha = _alpha;
}