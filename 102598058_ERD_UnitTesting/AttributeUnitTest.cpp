#include "gtest/gtest.h"

#include "../102598058/Attribute.h"
#include "../102598058/ComponentFactory.h"

class AttributeUnitTest:public::testing::Test
{
public:

protected:
	virtual void SetUp()
	{
		factory = new ComponentFactory();
		component = factory->createComponent("A");
	}
	virtual void TearDown()
	{
		delete factory;
		delete component;
	}
	Attribute attribute;
	Component* component;
	ComponentFactory* factory;
};
TEST_F(AttributeUnitTest, canConnectTo)
{
	component->setType("A");
	EXPECT_FALSE(attribute.canConnectTo(component));
	component->setType("R");
	EXPECT_FALSE(attribute.canConnectTo(component));
	component->setType("C");
	EXPECT_FALSE(attribute.canConnectTo(component));
	component->setType("E");
	EXPECT_TRUE(attribute.canConnectTo(component));
	component->setType("E");
	EXPECT_FALSE(attribute.canConnectTo(component));

};