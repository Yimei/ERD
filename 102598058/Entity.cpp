#include <string>
#include <iostream>
#include "Entity.h"
#define E "E"
using namespace std;
Entity::Entity():Node(){
}
void Entity::connectTo(Component* component){
}
bool Entity::canConnectTo(Component* component){
	if (component->getType() == E)//�Orelationship �� attribute
	{
		return false;
	}
	else 
	{
		setConnections(component);
		return true;
	}
}
void Entity::setConnections(Component* component)
{
	this->_connectedNodesVector.push_back(component);
}
vector<Component*> Entity::getConnections()
{
	return _connectedNodesVector;
}
Entity::~Entity(){
}