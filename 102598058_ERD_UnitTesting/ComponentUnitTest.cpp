#include "gtest/gtest.h"
#include "../102598058/Component.h"


class ComponentUnitTest:public::testing::Test
{
	Component* component;
protected:
	virtual void SetUp()
	{
		component->_id = 0;
		component->_text = "";
		component->_type = "";
	}
	virtual void TearDown()
	{
		delete component;
	}
};
