#include "gtest/gtest.h"
<<<<<<< HEAD
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
=======
#include "Attribute.h"
#include "Component.h"
class AttributeUnitTest:public::testing::Test
{
	
protected:
	virtual void SetUp()
	{
		attribute = new Attribute();
		
	}
	virtual void TearDown()
	{
		delete attribute;
		delete component;
		
	}
	Attribute* attribute;
	Component* component;
};
TEST_F(AttributeUnitTest, testCanConnectTo)
{
	component->setType("A");
	EXPECT_FALSE(attribute->canConnectTo(component));
	component->setType("R");
	EXPECT_FALSE(attribute->canConnectTo(component));
	component->setType("C");
	EXPECT_FALSE(attribute->canConnectTo(component));
	component->setType("E");//可連Entity 且 目前一個
	EXPECT_TRUE(attribute->canConnectTo(component));
	EXPECT_FALSE(attribute->canConnectTo(component));


}
>>>>>>> 88622ec2cbf14a29da311a899ad6a9785346c9bf
