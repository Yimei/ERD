#ifndef _Connector_H_ 
#define _Connector_H_
#include <string>
#include "Component.h"
using namespace std;
class Connector:public Component{
public:
	Connector();
	virtual ~Connector();
	void connectTo(Component* component);
	bool canConnectTo(Component* component);
	vector<Component*> getConnections();
private:
	string _type;
	vector<Component*> _connectedComponent;
};
#endif