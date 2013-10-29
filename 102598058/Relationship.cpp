#include <string>
#include <iostream>
#include "Relationship.h"
#define E "E"
#define TWO 2
using namespace std;
Relationship::Relationship():Node()
{
	
}
void Relationship::connectTo(Component* component)
{
}
bool Relationship::canConnectTo(Component* component)
{
	if (component->getType()!= E)
	{
		return false;
	}
	else if(_connectedEntityVector.size() == TWO)
	{
		return false;
	}
	else  
	{
		setConnections(component);
		return true;
	}
}
void Relationship::setConnections(Component* component)
{
	_connectedEntityVector.push_back(component);
}
vector<Component*> Relationship::getConnections()
{
	return _connectedEntityVector;
}
Relationship::~Relationship(){

}