#include "StaticSprite.h"
#include "Mat3.h"
#include "SpriteBatch.h"
#include "Texture.h"

StaticSprite::StaticSprite(Texture *pTexture)
	: Node()
{
	m_texture = pTexture;

	m_r = 255;
	m_g = 255;
	m_b = 255;
	m_a = 255;
}
StaticSprite::~StaticSprite()
{

}

void StaticSprite::Draw(SpriteBatch *sb)
{
	Mat3 worldTransform = GetWorldTransform();
	//Vec2 pos = worldTransform.GetTranslation();
	//Vec2 scale = worldTransform.GetScale();

	//TODO: set coordinance for the sprite batch
	sb->SetColor(m_r/255.0f, m_g/255.0f, m_b/255.0f, m_a/255.0f);
	//sb->DrawSprite( m_texture, pos.x, pos.y, m_size.x * scale.x, m_size.y * scale.y);

	sb->DrawSprite( this );
}

void StaticSprite::SetTexture(Texture *pTexture)
{
	m_texture = pTexture;
}
Texture *StaticSprite::GetTexture()
{
	return m_texture;
}

Vec2 StaticSprite::GetSize()
{
	return Vec2((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
}

void StaticSprite::SetColour( unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
}
