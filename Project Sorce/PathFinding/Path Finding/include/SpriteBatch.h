// Author: Jarrod Dowsey
// Descrition: SprtieBatch class


#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <assert.h>

#include "Vec2.h"

class Game;
class Texture;
class Mat3;
class SpriteBatch_Imidiate;
class Vec2;
class Player;
class StaticSprite;

class SpriteBatch
{
public:

	enum EType
	{
		IMIDIATE,
		NON_IMIDIATE,
	};

public:


	// very simplistic Factory Create function
	static SpriteBatch *Create(  Game *pGame, EType type );
	
	// destroy function created to keep with rule of thumb
	// whatever creates it destroys it.
	static void Destroy( SpriteBatch *pSpriteBatch );

	virtual void Begin() {};
	virtual void End()   {};

	virtual void DrawSprite( Texture *texture, float xPos, float yPos ){ assert(false && "your sprite batch has not overloaded \"DrawSprite( Texture *texture, float xPos, float yPos )\""); }
	virtual void DrawSprite( Texture *texture, float xPos, float yPos, float width, float height ) {assert(false && "your sprite batch has not overloaded \"DrawSprite( Texture *texture, float xPos, float yPos, float width, float height )\"");}
	virtual void DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size){assert(false && "your sprite batch has not overloaded \"DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size)\"");}
	virtual void DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size, float red, float green, float blue, float alpha);
	virtual void DrawSprite( StaticSprite* sprite ){assert(false && "your sprite batch has not overloaded \"DrawSprite( StaticSprite* sprite )\"");}

	virtual void DrawLine(Vec2 _point1, Vec2 _point2, float _r, float _g, float _b);

	void SetColor(float r, float g, float b, float a);
	void SetColor(unsigned int color);

protected:

	// constructor protected: 
	// its expected that the SpriteBatch is created from the static Create Method
	SpriteBatch( Game *pGame );

	// destructor
	virtual ~SpriteBatch();

	// store the color value that sprites should be drawn with
	float m_red, m_green, m_blue, m_alpha;

	Game *m_pGame;
};


#endif
