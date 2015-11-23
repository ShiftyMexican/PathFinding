#include "SpriteBatch_NonImidiate.h"
#include "Lodepng.h"
#include <string>
#include <vector>
#include <fstream>
#include "StaticSprite.h"
#include "Texture.h"

SpriteBatch_NonImidiate::SpriteBatch_NonImidiate(Game *pGame) : SpriteBatch( pGame )
{
	glewInit();
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	// load shaders
	//----------------------------------------------------------------------------
	// sprite rendering shader
	m_shader = CreateProgram("./shaders/TexturedVertexShader.glsl", "./shaders/TexturedFragmentShader.glsl");
	
	// line rendering shader
	m_flatShader = CreateProgram("./shaders/FlatVertexShader.glsl", "./shaders/FlatFragmentShader.glsl");


	m_projection_flatShader_loc		= glGetUniformLocation(m_flatShader, "projection");
	m_projection_texturedShader_loc = glGetUniformLocation(m_shader, "projection");
	m_diffuse_textureShader_loc		= glGetUniformLocation(m_shader, "diffuse");
	//----------------------------------------------------------------------------


	// genorate vertex arrays objects for sprite rendering
	//----------------------------------------------------------------------------
	glGenVertexArrays(1,	&m_vao);
	glGenBuffers(1,			&m_vbo);
	glGenBuffers(1,			&m_ibo);

	glBindVertexArray( m_vao );
	glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ibo );

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof( TexturedColorVertex ), (void *) 0 );
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof( TexturedColorVertex ), (void *) 16);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof( TexturedColorVertex ), (void *) 32);

	glBindVertexArray(0);
	//----------------------------------------------------------------------------


	// genorate vertex arrays objects for line rendering
	//----------------------------------------------------------------------------
	glGenVertexArrays(1,	&m_lineVao);
	glGenBuffers(1,			&m_lineVbo);

	glBindVertexArray( m_lineVao);
	glBindBuffer(GL_ARRAY_BUFFER, m_lineVbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(float) * 8, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(float) * 8, (void *)16);

	glBindVertexArray(0);
	//----------------------------------------------------------------------------
}

SpriteBatch_NonImidiate::~SpriteBatch_NonImidiate()
{

}

void SpriteBatch_NonImidiate::Begin()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SpriteBatch_NonImidiate::End()
{

}

void SpriteBatch_NonImidiate::DrawSprite( StaticSprite* sprite )
{
	Mat3 m = sprite->GetWorldTransform();
	Vec2 s = sprite->GetSize() / 2;
	Texture* texture = sprite->GetTexture();
	unsigned int width = texture->GetWidth();
	unsigned int height = texture->GetHeight();

	Vec2 tl = Vec2(-s.x, -s.y) * m;
	Vec2 tr = Vec2( s.x, -s.y) * m;
	Vec2 br = Vec2( s.x,  s.y) * m;
	Vec2 bl = Vec2(-s.x,  s.y) * m;

	TexturedColorVertex verts[4] = 
	{
		//						x,				y,				r,		g,		b,		a,		u,		v
		TexturedColorVertex(	tl.x,			tl.y,			1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f), // vert 0 - top left
		TexturedColorVertex(	tr.x,			tr.y,			1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f), // vert 1 - top right
		TexturedColorVertex(	br.x,			br.y,			1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f), // vert 2 - bottom right
		TexturedColorVertex(	bl.x,			bl.y,			1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f)  // vert 3 - bottom left
	};

	GLubyte indicies[6] = 
	{
		0 , 1 , 2, // Face 1
		0 , 2 , 3  // Face 2
	};

	float ortho[16];
	BuildOrthoProjectionMatrix( ortho, 0.0f, (float)m_pGame->GetWindowWidth(), (float)m_pGame->GetWindowHeight(), 0.0f, 0.0f, 100.0f);

	glUseProgram( m_shader );

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureHandle());

	// tell our shader about the orthographic projection
	glUniform1i( m_diffuse_textureShader_loc, 0);

	
	glUniformMatrix4fv( m_projection_texturedShader_loc, 1, false, ortho );

	// bind the vertex array object
	// this contains the information describing our vertex data
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glBufferData(GL_ARRAY_BUFFER, sizeof( TexturedColorVertex ) * 4, verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( GLubyte ) * 6, indicies, GL_STATIC_DRAW);

	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL );

	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void SpriteBatch_NonImidiate::DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size)
{
	const Mat3 &m = transform;
	const Vec2 &s = size;
	
	unsigned int width = texture->GetWidth();
	unsigned int height = texture->GetHeight();

	Vec2 tl = Vec2(-s.x, -s.y) * m;
	Vec2 tr = Vec2( s.x, -s.y) * m;
	Vec2 br = Vec2( s.x,  s.y) * m;
	Vec2 bl = Vec2(-s.x,  s.y) * m;

	TexturedColorVertex verts[4] = 
	{
		//						x,				y,				r,		g,		b,		a,		u,		v
		TexturedColorVertex(	tl.x,			tl.y,			1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f), // vert 0 - top left
		TexturedColorVertex(	tr.x,			tr.y,			1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f), // vert 1 - top right
		TexturedColorVertex(	br.x,			br.y,			1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f), // vert 2 - bottom right
		TexturedColorVertex(	bl.x,			bl.y,			1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f)  // vert 3 - bottom left
	};

	GLubyte indicies[6] = 
	{
		0 , 1 , 2, // Face 1
		0 , 2 , 3  // Face 2
	};

	float ortho[16];
	BuildOrthoProjectionMatrix( ortho, 0.0f, (float)m_pGame->GetWindowWidth(), (float)m_pGame->GetWindowHeight(), 0.0f, 0.0f, 100.0f);
	
	glEnable(GL_BLEND);
	glUseProgram( m_shader );

	// tell the shader about the texture... 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureHandle());
	glUniformMatrix4fv( m_projection_texturedShader_loc, 1, false, ortho );

	// tell our shader about the orthographic projectio
	glUniform1i( m_diffuse_textureShader_loc, 0);


	// bind the vertex array object
	// this contains the information describing our vertex data
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);


	glBufferData(GL_ARRAY_BUFFER, sizeof( TexturedColorVertex ) * 4, verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( GLubyte ) * 6, indicies, GL_STATIC_DRAW);

	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL );

	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void SpriteBatch_NonImidiate::DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size, float red, float green, float blue, float alpha)
{
	const Mat3 &m = transform;
	const Vec2 &s = size;
	
	unsigned int width = texture->GetWidth();
	unsigned int height = texture->GetHeight();

	Vec2 tl = Vec2(-s.x, -s.y) * m;
	Vec2 tr = Vec2( s.x, -s.y) * m;
	Vec2 br = Vec2( s.x,  s.y) * m;
	Vec2 bl = Vec2(-s.x,  s.y) * m;

	TexturedColorVertex verts[4] = 
	{
		//						x,				y,				r,		g,		b,		a,		u,		v
		TexturedColorVertex(	tl.x,			tl.y,			red,	green,	blue,	alpha,	0.0f,	0.0f), // vert 0 - top left
		TexturedColorVertex(	tr.x,			tr.y,			red,	green,	blue,	alpha,	1.0f,	0.0f), // vert 1 - top right
		TexturedColorVertex(	br.x,			br.y,			red,	green,	blue,	alpha,	1.0f,	1.0f), // vert 2 - bottom right
		TexturedColorVertex(	bl.x,			bl.y,			red,	green,	blue,	alpha,	0.0f,	1.0f)  // vert 3 - bottom left
	};

	GLubyte indicies[6] = 
	{
		0 , 1 , 2, // Face 1
		0 , 2 , 3  // Face 2
	};

	float ortho[16];
	BuildOrthoProjectionMatrix( ortho, 0, (float)m_pGame->GetWindowWidth(), (float)m_pGame->GetWindowHeight(), 0, 0, 100);
	
	glEnable(GL_BLEND);
	glUseProgram( m_shader );

	// tell the shader about the texture... 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureHandle());
	glUniformMatrix4fv( m_projection_texturedShader_loc, 1, false, ortho );

	// tell our shader about the orthographic projectio
	glUniform1i( m_diffuse_textureShader_loc, 0);


	// bind the vertex array object
	// this contains the information describing our vertex data
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof( TexturedColorVertex ), (void *) 0 );
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof( TexturedColorVertex ), (void *) 16);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof( TexturedColorVertex ), (void *) 32);

	glBufferData(GL_ARRAY_BUFFER, sizeof( TexturedColorVertex ) * 4, verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( GLubyte ) * 6, indicies, GL_STATIC_DRAW);

	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL );

	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}
void SpriteBatch_NonImidiate::BuildOrthoProjectionMatrix( float *pMat4x4, float left, float right, float bottom, float top, float near, float far) const
{
	float w = right - left;
	float h = top - bottom;
	float d = far - near;

	pMat4x4[0]	=  2.0f / w;
	pMat4x4[1]	=  0.0f;
	pMat4x4[2]	=  0.0f;
	pMat4x4[3]	=  0.0f;
	pMat4x4[4]	=  0.0f;
	pMat4x4[5]	=  2.0f / h;
	pMat4x4[6]	=  0.0f;
	pMat4x4[7]	=  0.0f;
	pMat4x4[8]	=  0.0f;
	pMat4x4[9]	=  0.0f;
	pMat4x4[10] =  2.0f / d;
	pMat4x4[11] =  0.0f;
	pMat4x4[12] = -1.0f * ( (right + left) / w );
	pMat4x4[13] = -1.0f * ( (top + bottom) / h );
	pMat4x4[14] = -1.0f * ( (far + near)   / d );
	pMat4x4[15] =  1.0f;
}

GLuint SpriteBatch_NonImidiate::CreateProgram(const char *a_vertex, const char *a_frag) const
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for(auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv (uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	// now that the program has been built, we can get rid of the individual shaders...
	for(auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	// return our compiled shader program.
	return uiProgram;
}

GLuint SpriteBatch_NonImidiate::CreateShader(GLenum a_eShaderType, const char *a_strShaderFile) const
{
	std::string strShaderCode;

	//open shader file
	std::ifstream shaderStream(a_strShaderFile);

	//if that worked ok, load file line by line
	if(shaderStream.is_open())
	{
		std::string Line = "";
		while(std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();
	
	//create shader ID
	GLuint uiShader = glCreateShader(a_eShaderType);

	//attach the shader source to our generated shader ID
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader - GL nust compile the shader source code.
	//as each graphics card is different, instructions may differ on the hardware GPU
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);

	//if there is an error, print the error to the console window
	if (iStatus == GL_FALSE)
	{

		// how long is the of the error
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		// create memory for the error message
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch(a_eShaderType)
		{
			case GL_VERTEX_SHADER:		strShaderType = "vertex"; break;
			case GL_FRAGMENT_SHADER:	strShaderType = "fragment"; break;
		}

		// print the error to the console window.
		printf("Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		
		// remember the memory we created 13 lines above...
		delete[] strInfoLog;
	}

	// return the shader ID...
	return uiShader;
}

void SpriteBatch_NonImidiate::DrawLine(Vec2 _point1, Vec2 _point2, float _r, float _g, float _b)
{

	
	float ortho[16];
	BuildOrthoProjectionMatrix( ortho, 0, (float)m_pGame->GetWindowWidth(), (float)m_pGame->GetWindowHeight(), 0, 0, 100);
	
	// preform rendering for the line with this shader
	glUseProgram( m_flatShader );
	

	glUniformMatrix4fv( m_projection_flatShader_loc, 1, false, ortho );
	
	float data[16] =
	{
		_point1.x, _point1.y, 0.0f, 1.0f, _r, _g, _b, 1.0f,
		_point2.x, _point2.y, 0.0f, 1.0f, _r, _g, _b, 1.0f
	};

	// bind the line rendering buffers
	glBindVertexArray(m_lineVao);	
	glBindBuffer(GL_ARRAY_BUFFER, m_lineVbo);

	// send the verted data
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, data, GL_STATIC_DRAW);
	
	// render the line	
	glDrawArrays(GL_LINES, 0, 2);
	
	// turn off the shader again
	glUseProgram(0);
	glBindVertexArray(0);
	
	
}