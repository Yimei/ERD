#ifndef _ComponentFactory_H_ 
#define _ComponentFactory_H_
#include "gtest/gtest_prod.h"
#include <string>
#include "Component.h"
using namespace std;
class ComponentFactory{
	FRIEND_TEST(ComponentFactoryUnitTest,createComponent);
public: 
	ComponentFactory();
	virtual ~ComponentFactory();
	Component* createComponent(string type);
};
#endif