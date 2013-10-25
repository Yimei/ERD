#include <string>
#include <iostream>
#include "Attribute.h"
#define E "E"
using namespace std;
Attribute::Attribute():Node()
{	
	for (unsigned int i = 0; i < _connectedEntity.size();i++)
		_connectedEntity.push_back(NULL);
}
void Attribute::connectTo(Component* component)
{
}
bool Attribute::canConnectTo(Component* component){
	if ((component->getType() != E) )//不會有重複connector問題
	{
		return false;
	}
	else if(_connectedEntity.size() > 0)
	{
		return false;
	}
	else
	{
<<<<<<< HEAD
		_connectedEntity.push_back(component);
=======
		//return true;
		connectedEntity.push_back(component);
>>>>>>> 88622ec2cbf14a29da311a899ad6a9785346c9bf
	}
}
vector<Component*> Attribute::getConnections()
{
	return _connectedEntity;
}
//void Attribute::pushConnectedEntity()
//{
//	conn
//}
Attribute::~Attribute()
{
}