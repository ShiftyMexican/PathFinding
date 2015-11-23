// Author: Jarrod Dowsey
// Description: Basic Texture Class.

#ifndef TEXTURE_H
#define TEXTURE_H



class Texture
{
public:
	// Overloaded Constructor
	Texture(const char *filename);

	// Destructor
	~Texture();

	unsigned int GetWidth()				{ return m_width; }
	unsigned int GetHeight()			{ return m_height; }
	unsigned int GetTextureHandle()		{ return m_glTextureHandle;	}
	unsigned int GetLoadTexture()		{ return m_loadTexture; }

protected:

private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_glTextureHandle;
	unsigned int m_loadTexture;

	// Returns the width and height values if values arent NULL.
	unsigned int LoadTexture(const char *filename, unsigned int *out_width = nullptr, unsigned int *out_height = nullptr);

	void DeleteTexture(unsigned int textureID);
};

#endif