// Author: Jarrod Dowsey
// Description: Basic Node class. Allows for parenting of objects.
// Classes that inherit from Node will be "parentable".

#ifndef NODE_H
#define NODE_H

#include "Mat3.h"

/// Predeclare Classes.
class SpriteBatch;

class Node
{
public:

	/// Constructors
	Node();
	Node( Node *parent );

	/// Destructor
	virtual ~Node();

	/// Update
	virtual void Update	( float dt );

	// Returns reference to the local transform matrix
	Mat3 *Transform();

	// Calculates the global and local transform matrix for this node.
	Mat3 GetWorldTransform();
	Mat3 GetLocalTransform();


	/// Add Child Function
	void AddChild	(Node *child);

	/// Remove Child Function
	void RemoveChild(Node *child);

	Vec2 m_position;
	float m_rotation;
	Vec2 m_scale;

protected:

	Mat3 m_localTransform;
	Mat3 m_worldTransform;
	Node *m_parent;

private:
};

#endif