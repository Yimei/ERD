#ifndef _Attribute_H_ 
#define _Attribute_H_

#include "gtest/gtest_prod.h"

#include <gtest/gtest_prod.h>

#include <string>
#include "Node.h"
#include "Connector.h"
using namespace std;
class Attribute:public Node{
	friend class AttributeUnitTest;
	FRIEND_TEST(AttributeUnitTest,canConnectTo);


public:
	Attribute();
	virtual ~Attribute();
	vector<Component*> getConnections();
	void connectTo(Component* component);
	bool canConnectTo(Component* component);
	/*void pushConnectedEntity(Component* component);*/
private:

	Connector* _connector;
	vector<Component*> _connectedEntity;

	Connector* connector;
	vector<Component*> connectedEntity;
	

};
#endif