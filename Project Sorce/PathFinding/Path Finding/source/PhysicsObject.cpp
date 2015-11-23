#include "PhysicsObject.h"
#include "MathLib.h"
#include "SpriteBatch.h"
#include "Tile.h"
#include "RandomGenState.h"

/// Physics Object
PhysicsObject::PhysicsObject()
{
	m_mass			= 0.5f;
	m_friction		= 1.2f;
	m_force			= Vec2( 0.0f, 0.0f );
	m_position		= Vec2( 0.0f, 0.0f );
	m_acceleration	= Vec2( 0.0f, 0.0f );
	m_velocity		= Vec2( 0.0f, 0.0f );
}

PhysicsObject::~PhysicsObject()
{

}

void PhysicsObject::Simulate( float dt )
{
	
	Vec2 maxVelocity = Vec2(0.1f, 0.1f);
	Vec2 fakeFriction = m_velocity * -m_friction;
	m_acceleration = ( m_force + fakeFriction ) * ( 1.0f / m_mass);
	m_velocity += m_acceleration * dt;

	m_position += m_velocity * dt;

	/// Reset the Force
	m_force.x = 0.0f;
	m_force.y = 0.0f;
}

/// AI
AI::AI(Texture * pAiTexture)
{
	m_aiTexture = pAiTexture;
	m_physics = new PhysicsObject();
}

/// Destructor
AI::~AI()
{
	delete m_physics;
}

/// Update
void AI::Update( float dt )
{
	m_physics->Simulate(dt);
	Transform()->SetTranslation(m_physics->GetPosition());

	Vec2 velocity = m_physics->GetVelocity();
	velocity.Normalize();
	float rot = atan2(-velocity.x, -velocity.y);
	Transform()->SetRotation(rot);
}

// Draw
void AI::Draw( SpriteBatch *sb)
{
	sb->DrawSprite(m_aiTexture, m_localTransform, Vec2( 10, 10 ));
}


void AI::AddForce(const Vec2& _force)
{
	m_physics->AddForce(_force);
}
