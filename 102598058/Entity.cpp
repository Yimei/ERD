#include <string>
#include <iostream>
#include "Entity.h"
using namespace std;
Entity::Entity():Node()
{
}
void Entity::connectTo(Component* component)
{
}
bool Entity::canConnectTo(Component* component)
{
	setConnections(component);
	return true;
}
void Entity::setConnections(Component* component)
{
	this->_connectedNodesVector.push_back(component);
}
vector<Component*> Entity::getConnections()
{
	return _connectedNodesVector;
}
Entity::~Entity()
{
}