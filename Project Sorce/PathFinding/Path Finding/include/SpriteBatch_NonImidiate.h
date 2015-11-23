// Author: Jarrod Dowsey
// Description: Non Imediate mode SpriteBatch Class

#ifndef SPRITEBATCH_NONIMIDIATE_H
#define SPRITEBATCH_NONIMIDIATE_H

#include "SpriteBatch.h"
#include "Game.h"
#include "MathLib.h"
#include "GLEW\GL\glew.h"
#include "GLFW\glfw3.h"

class SpriteBatch_NonImidiate : public SpriteBatch
{
public:
	/// Defualt constructor
	SpriteBatch_NonImidiate(Game *pGame);

	/// Destructor
	virtual ~SpriteBatch_NonImidiate();

	virtual void Begin();
	virtual void End();
	
	/// DrawSprite Function
	virtual void DrawSprite( StaticSprite* sprite );
	virtual void DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size);
	virtual void DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size, float red, float green, float blue, float alpha);
	virtual void DrawLine(Vec2 _point1, Vec2 _point2, float _r, float _g, float _b);


private:

	void BuildOrthoProjectionMatrix( float *pMat4x4, float left, float right, float bottom, float top, float near, float far) const;

	GLuint CreateProgram(const char *a_vertex, const char *a_frag) const;
	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile) const;


	GLuint m_texture;

	GLuint m_shader;
	GLuint m_flatShader;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;

	GLuint m_lineVao;
	GLuint m_lineVbo;

	GLFWwindow *m_pWindow;


	GLuint m_projection_flatShader_loc;

	GLuint m_projection_texturedShader_loc;
	GLuint m_diffuse_textureShader_loc;

};

struct TexturedColorVertex
{
	TexturedColorVertex(float x, float y, float r, float g, float b, float a, float u, float v)
	{
		vPosition[0] = x;
		vPosition[1] = y;
		vPosition[2] = 0;
		vPosition[3] = 1;

		vColour[0] = r;
		vColour[1] = g;
		vColour[2] = b;
		vColour[3] = a;

		vUV[0] = u;
		vUV[1] = v;
	}

	float vPosition[4];		// this could be a vec4. or, a vec3 + float... represents x y z w.
	float vColour[4];		// represents red, green, blue, alpha.
	float vUV[2];			// represents the texture coords for the vert.

};

#endif