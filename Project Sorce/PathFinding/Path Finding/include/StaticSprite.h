// Author: jarrod dowsey
// Description: basic static sprite class - inherits from node

#ifndef STATIC_SPRITE_H
#define STATIC_SPRITE_H

#include "Node.h"

class Texture;
class SpriteBatch;

class StaticSprite : public Node
{
public:

	/// Defualt Constructor
	StaticSprite(Texture *pTexture);

	/// Destructor
	virtual ~StaticSprite();

	/// Draw Function
	virtual void Draw(SpriteBatch *sb);
	
	/// Function to set Textures
	void SetTexture(Texture *pTexture);
	Texture *GetTexture();

	Vec2 GetSize();

	void SetColour( unsigned char r, unsigned char g, unsigned char b, unsigned char a);

protected:

	Texture *m_texture;

	unsigned char m_r, m_g, m_b, m_a;

private:

};

#endif