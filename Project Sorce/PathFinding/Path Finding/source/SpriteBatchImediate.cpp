#include "SpriteBatchImediate.h"
#include "Game.h"
#include "GLFW\glfw3.h"
#include "Texture.h"
#include "StaticSprite.h"

SpriteBatch_Imediate::SpriteBatch_Imediate( Game *pGame ) : SpriteBatch(pGame)
{

}

SpriteBatch_Imediate::~SpriteBatch_Imediate()
{

}

void SpriteBatch_Imediate::Begin()
{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glMatrixMode(GL_PROJECTION); // DEPRECIATED: shaders used instead - user to provide projection matrix to the shader
		glLoadIdentity();			 // sets the GL_PROJECTION matrix to the identity matrix

		// setup orthographic projection (for rendering 2D)
		// DEPRECIATED: the projection matrix would be sent to the active shader
		glOrtho(0.0f, m_pGame->GetWindowWidth(), m_pGame->GetWindowHeight(), 0, -1, 1);		// WINDOW ORIGIN: Top Left
		//	glOrtho(0.0f, windowWidth, 0, windowHeight, -1, 1);		// WINDOW ORIGIN: Bottom Left
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		
		
		// DEPRECIATED: pixel shaders define the final color after rasterization step in the graphics pipeline
		glEnable(GL_TEXTURE_2D); 

		// DEPRECIATED: again, Matrices do not exist on future versions of OpenGL.
		// a model view matrix would be sent to the shader... 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}
void SpriteBatch_Imediate::End()
{
	// if this was non-imidiate mode
	// we would need to finish rendering stuff here...
}

void SpriteBatch_Imediate::DrawSprite( Texture *texture, float xPos, float yPos )
{
	unsigned int width = texture->GetWidth();
	unsigned int height = texture->GetHeight();

	glBindTexture( GL_TEXTURE_2D, texture->GetTextureHandle() );
	glColor4f(m_red, m_green, m_blue, m_alpha);

	glBegin(GL_QUADS);
	
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(xPos,			yPos);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(xPos + width,	yPos);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(xPos + width,	yPos + height);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(xPos,			yPos + height);
	
	glEnd();
}

void SpriteBatch_Imediate::DrawSprite( Texture *texture, float xPos, float yPos, float width, float height )
{

	if( texture != NULL )
	{
		glBindTexture( GL_TEXTURE_2D,  texture->GetTextureHandle() );
		glColor4f(m_red, m_green, m_blue, m_alpha);

		glBegin(GL_QUADS);
	
			glTexCoord2f(0.0f, 0.0f);	glVertex2f(xPos,			yPos);
			glTexCoord2f(1.0f, 0.0f);	glVertex2f(xPos + width,	yPos);
			glTexCoord2f(1.0f, 1.0f);	glVertex2f(xPos + width,	yPos + height);
			glTexCoord2f(0.0f, 1.0f);	glVertex2f(xPos,			yPos + height);
	
		glEnd();
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glColor4f(m_red, m_green, m_blue, m_alpha);

		glBegin(GL_QUADS);
	
			glVertex2f(xPos,			yPos);
			glVertex2f(xPos + width,	yPos);
			glVertex2f(xPos + width,	yPos + height);
			glVertex2f(xPos,			yPos + height);
	
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}
}

void SpriteBatch_Imediate::DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size)
{

	Vec2 tl = (Vec2(0, 0) ) * size;
	Vec2 tr = (Vec2(1, 0) ) * size;
	Vec2 br = (Vec2(1, 1) ) * size;
	Vec2 bl = (Vec2(0, 1) ) * size;

	tl = tl * transform;
	tr = tr * transform;
	br = br * transform;
	bl = bl * transform;

	if( texture != NULL )
	{
		glBindTexture( GL_TEXTURE_2D,  texture->GetTextureHandle() );
		glColor4f(m_red, m_green, m_blue, m_alpha);

		glBegin(GL_QUADS);
	
			glTexCoord2f(0.0f, 0.0f);	glVertex2f(tl.x, tl.y);
			glTexCoord2f(1.0f, 0.0f);	glVertex2f(tr.x, tr.y);
			glTexCoord2f(1.0f, 1.0f);	glVertex2f(br.x, br.y);
			glTexCoord2f(0.0f, 1.0f);	glVertex2f(bl.x, bl.y);
	
		glEnd();
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glColor4f(m_red, m_green, m_blue, m_alpha);

		glBegin(GL_QUADS);
	
			glVertex2f(tl.x, tl.y);
			glVertex2f(tr.x, tr.y);
			glVertex2f(br.x, br.y);
			glVertex2f(bl.x, bl.y);
	
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}


}

void SpriteBatch_Imediate::DrawSprite( StaticSprite* sprite )
{
	Mat3 m = sprite->GetWorldTransform();
	Vec2 s = sprite->GetSize() / 2;
	Texture* texture = sprite->GetTexture();

	Vec2 tl = Vec2(-s.x, -s.y) * m;
	Vec2 tr = Vec2( s.x, -s.y) * m;
	Vec2 br = Vec2( s.x,  s.y) * m;
	Vec2 bl = Vec2(-s.x,  s.y) * m;

	if( texture != NULL )
	{
		glBindTexture( GL_TEXTURE_2D,  texture->GetTextureHandle() );
		glColor4f(m_red, m_green, m_blue, m_alpha);

		glBegin(GL_QUADS);
	
			glTexCoord2f(0.0f, 0.0f);	glVertex2f(tl.x, tl.y);
			glTexCoord2f(1.0f, 0.0f);	glVertex2f(tr.x, tr.y);
			glTexCoord2f(1.0f, 1.0f);	glVertex2f(br.x, br.y);
			glTexCoord2f(0.0f, 1.0f);	glVertex2f(bl.x, bl.y);
	
		glEnd();
	}
}