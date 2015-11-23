#include "Node.h"
#include "SpriteBatch.h"

Node::Node()
{
	m_localTransform = Mat3::CreateIdentity();
	m_worldTransform = Mat3::CreateIdentity();
	m_position = Vec2(0,0);
	m_scale = Vec2(1,1);
	m_rotation = 0;
	m_parent = nullptr;

}
Node::Node( Node *parent )
{
	m_localTransform = Mat3::CreateIdentity();
	m_worldTransform = Mat3::CreateIdentity();
	m_position = Vec2(0,0);
	m_scale = Vec2(1,1);
	m_rotation = 0;
	m_parent = parent;
}

Node::~Node()
{

}

void Node::Update( float dt )
{
	m_localTransform = 
		Mat3::CreateScale(m_scale) *
		Mat3::CreateRotation(m_rotation) *
		Mat3::CreateTranslation(m_position);
	
	if(m_parent != nullptr)
		m_worldTransform = m_localTransform * m_parent->GetWorldTransform();
	else
		m_worldTransform = m_localTransform;
}

// Returns reference to the local transform matrix
Mat3 *Node::Transform()
{
	return &m_localTransform;
}

// Calculates the global transform matrix for this node.
Mat3 Node::GetWorldTransform()
{
	return m_worldTransform;
}

Mat3 Node::GetLocalTransform()
{
	return m_localTransform;
}

void Node::AddChild	(Node *child)
{
	child->m_parent = this;
}
void Node::RemoveChild(Node *child)
{
	if( child->m_parent == this)
		child->m_parent = nullptr;
}