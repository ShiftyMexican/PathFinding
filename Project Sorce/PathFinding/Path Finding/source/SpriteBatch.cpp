#include "SpriteBatch.h"
#include "Game.h"
#include "Texture.h"
#include "SpriteBatchImediate.h"
#include "SpriteBatch_NonImidiate.h"

SpriteBatch::SpriteBatch( Game *pGame )
{
	m_pGame = pGame;

	m_red	= 1.0f;
	m_green = 1.0f;
	m_blue	= 1.0f;
	m_alpha = 1.0f;

}

SpriteBatch::~SpriteBatch()
{
	// nothing to delete
}

SpriteBatch *SpriteBatch::Create( Game *pGame, EType type )
{
	if( type == IMIDIATE )
		return new SpriteBatch_Imediate(pGame);

	if( type == NON_IMIDIATE )
		return new SpriteBatch_NonImidiate(pGame);

	return new SpriteBatch(pGame);
}


void SpriteBatch::Destroy( SpriteBatch *pSpriteBatch )
{
	delete pSpriteBatch;
}

void SpriteBatch::SetColor(float r, float g, float b, float a)
{
	m_red		= r;
	m_green		= g;
	m_blue		= b;
	m_alpha		= a;
}

void SpriteBatch::SetColor(unsigned int color)
{
	m_red	= ((color & 0xFF000000) >> 24 ) / 255.0f;
	m_green	= ((color & 0x00FF0000) >> 16) / 255.0f;
	m_blue	= ((color & 0x0000FF00) >> 8 ) / 255.0f;
	m_alpha	= ((color & 0x000000FF) >> 0 ) / 255.0f;
}

void SpriteBatch::DrawLine(Vec2 _point1, Vec2 _point2, float _r, float _g, float _b)
{

}