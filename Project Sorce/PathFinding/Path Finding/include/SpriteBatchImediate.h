#ifndef SPRITEBATCH_IMEDIATE_H
#define SPRITEBATCH_IMEDIATE_H

#include "SpriteBatch.h"
#include "MathLib.h"

class SpriteBatch_Imediate : public SpriteBatch
{
public:

	SpriteBatch_Imediate( Game *pGame );
	virtual ~SpriteBatch_Imediate();

	virtual void Begin();
	virtual void End();

	virtual void DrawSprite( Texture *texture, float xPos, float yPos );
	virtual void DrawSprite( Texture *texture, float xPos, float yPos, float width, float height );
	virtual void DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size  );

	virtual void DrawSprite( StaticSprite* sprite );

protected:
private:
};

#endif