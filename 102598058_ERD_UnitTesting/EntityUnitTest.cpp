#include "gtest/gtest.h"
#include "../102598058/Entity.h"
#include "../102598058/ComponentFactory.h"

class EntityUnitTest:public::testing::Test
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
	Entity entity;
	Component* component;
	ComponentFactory* factory;
};
TEST_F(EntityUnitTest, canConnectTo)
{
	component->setType("E");
	EXPECT_FALSE(entity.canConnectTo(component));
	component->setType("A");
	EXPECT_TRUE(entity.canConnectTo(component));
	component->setType("R");
	EXPECT_TRUE(entity.canConnectTo(component));

}

