/// Author: Jarrod Dowsey
/// Description: Basic Physics class for AI

#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "Tile.h"

class Node;
class SpriteBatch;
class StaticSprite;
class Game;
class Texture;
struct Tile;

class PhysicsObject
{
public:

	PhysicsObject();

	virtual ~PhysicsObject();

	virtual void Simulate( float dt );

	void SetPosition( Vec2 pos )		{ m_position = pos;			}
	void SetMass( float mass )			{ m_mass = mass;			}
	void SetFriction( float friction )	{ m_friction = friction;	}
	void AddForce( Vec2 force )			{ m_force = force;			}

	Vec2 GetForce()			{ return m_force;			}
	Vec2 GetPosition()		{ return m_position;		}
	Vec2 GetAcceleration()	{ return m_acceleration;	}
	Vec2 GetVelocity()		{ return m_velocity;		}
	float GetMass()			{ return m_mass;			}
	float GetFriction()		{ return m_friction;		}

protected:
private:

	float m_mass;
	float m_friction;
	Vec2 m_force;
	Vec2 m_position;
	Vec2 m_acceleration;
	Vec2 m_velocity;

};

class PhysicsObject;
class RandomGenState;

class AI : public Node
{
public:
	/// Default Constructor
	AI(Texture * pAiTexture);

	/// Destructor
	virtual ~AI();

	/// Update
	virtual void Update( float dt );

	// Draw
	virtual void Draw( SpriteBatch *sb);

	void AddForce(const Vec2& _force);

	Texture *GetTexture() {return m_aiTexture;}

	PhysicsObject *GetPhysics() { return m_physics; }

protected:
private:

	Texture			*m_aiTexture;
	StaticSprite	*m_ai;
	PhysicsObject	*m_physics;
	RandomGenState	*m_randGen;

	float m_xPos;
	float m_yPos;

};

#endif