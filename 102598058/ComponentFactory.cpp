#include <string>
#include "ComponentFactory.h"
#include "Connector.h"
#include "Attribute.h"
#include "Entity.h"
#include "Relationship.h"
#define ATTRIBUTE "A"
#define ENTITY "E"
#define RELATIONSHIP "R"
#define CONNECTOR "C"
using namespace std;
ComponentFactory::ComponentFactory()
{
}
Component* ComponentFactory::createComponent(string type){
	if(type  == ATTRIBUTE)
	{
		return new Attribute();
	}
	else if(type == ENTITY)
	{
		return new Entity();
	}
	else if(type == RELATIONSHIP)
	{
		return new Relationship();
	}
	else if(type == CONNECTOR)
	{
		return new Connector();
	}
	else
	{
		return NULL;
	}
}
ComponentFactory::~ComponentFactory(){
}