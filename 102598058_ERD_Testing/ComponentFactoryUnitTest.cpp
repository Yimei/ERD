#include "gtest/gtest.h"
#include "../102598058/ComponentFactory.h"

class ComponentFactoryUnitTest:public::testing::Test
{
public:
protected:
	virtual void SetUp()
	{
		factory = new ComponentFactory();
		
	}
	virtual void TearDown()
	{
		delete componentConnected;
		delete component;
		delete factory;
	}
	ComponentFactory* factory;
	Component* component;
	Component* componentConnected;
};
TEST_F(ComponentFactoryUnitTest,createComponent)
{
	component = factory->createComponent("A");
	componentConnected = factory->createComponent("A");
	componentConnected->setType("A");
	EXPECT_FALSE(component->canConnectTo(componentConnected));

	component = factory->createComponent("E");
	componentConnected = factory->createComponent("E");
	componentConnected->setType("E");
	EXPECT_FALSE(component->canConnectTo(componentConnected));

	component = factory->createComponent("R");
	componentConnected = factory->createComponent("R");
	componentConnected->setType("R");
	EXPECT_FALSE(component->canConnectTo(componentConnected));

	component = factory->createComponent("C");
	componentConnected = factory->createComponent("C");
	componentConnected->setType("C");
	EXPECT_FALSE(component->canConnectTo(componentConnected));

}