#include <string>
#include <iostream>
#include "Relationship.h"
#define E "E"
#define TWO 2
using namespace std;
Relationship::Relationship():Node(){
	
}
void Relationship::connectTo(Component* component)
{
}
bool Relationship::canConnectTo(Component* component){
	
	if (component->getType()!= E)
	{
		return false;
	}
	else if(_connectedEntity.size() == TWO)
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
	_connectedEntity.push_back(component);
}
vector<Component*> Relationship::getConnections()
{
	return _connectedEntity;
}
Relationship::~Relationship(){

}