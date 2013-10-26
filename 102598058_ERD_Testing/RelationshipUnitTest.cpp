#include "gtest/gtest.h"
#include "../102598058/Relationship.h"
#include "../102598058/ComponentFactory.h"

class RelationshipUnitTest:public::testing::Test
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
	Relationship relationship;
	Component* component;
	ComponentFactory* factory;
};
TEST_F(RelationshipUnitTest, canConnectTo)
{

	EXPECT_FALSE(relationship.canConnectTo(component));
	component->setType("R");
	EXPECT_FALSE(relationship.canConnectTo(component));
	component->setType("E");
	EXPECT_TRUE(relationship.canConnectTo(component));
	EXPECT_TRUE(relationship.canConnectTo(component));
	EXPECT_FALSE(relationship.canConnectTo(component));
}