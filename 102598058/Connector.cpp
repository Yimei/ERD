#include <string>
#include "Connector.h"
using namespace std;
Connector::Connector():Component()
{
}
vector<Component*> Connector::getConnections()
{
	return _connectedComponent;
}
void Connector::connectTo(Component* component)
{
}
bool Connector::canConnectTo(Component* component){
	if (component->getType() == "C")
	{
		return false;
	}
	return true;
}
Connector::~Connector()
{
}