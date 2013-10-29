#ifndef _Relationship_H_ 
#define _Relationship_H_
#include "gtest/gtest_prod.h"
#include <string>
#include <vector>
#include "Node.h"
using namespace std;
class Relationship:public Node{
	FRIEND_TEST(RelationshipUnitTest, canConnectTo);
public:
	Relationship();
	virtual ~Relationship();
	vector<Component*> getConnections();
	void connectTo(Component* component);
	bool canConnectTo(Component* component);
	void setConnections(Component* component);
private:
	vector<Component*> _connectedEntityVector;
};
#endif