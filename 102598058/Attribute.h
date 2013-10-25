#ifndef _Attribute_H_ 
#define _Attribute_H_
<<<<<<< HEAD
#include "gtest/gtest_prod.h"
=======
#include <gtest/gtest_prod.h>
>>>>>>> 88622ec2cbf14a29da311a899ad6a9785346c9bf
#include <string>
#include "Node.h"
#include "Connector.h"
using namespace std;
class Attribute:public Node{
<<<<<<< HEAD
	FRIEND_TEST(AttributeUnitTest,canConnectTo);
=======
	friend class AttributeUnitTest;
	
	FRIEND_TEST(AttributeUnitTest, testCanConnectTo);
>>>>>>> 88622ec2cbf14a29da311a899ad6a9785346c9bf
public:
	Attribute();
	virtual ~Attribute();
	vector<Component*> getConnections();
	void connectTo(Component* component);
	bool canConnectTo(Component* component);
	/*void pushConnectedEntity(Component* component);*/
private:
<<<<<<< HEAD
	Connector* _connector;
	vector<Component*> _connectedEntity;
=======
	Connector* connector;
	vector<Component*> connectedEntity;
	
>>>>>>> 88622ec2cbf14a29da311a899ad6a9785346c9bf
};
#endif