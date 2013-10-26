#include "gtest/gtest.h"
#include "../102598058/ERModel.h"

class ERModelUnitTest:public::testing::Test
{
public:
protected:
	virtual void SetUp()
	{
		ermodel = new ERModel();
		factory = new ComponentFactory();
	}
	virtual void TearDown()
	{
		delete ermodel;
	}
	ERModel* ermodel;
	Component* component;
	ComponentFactory* factory;
};
TEST_F(ERModelUnitTest,addNode)
{
	ermodel->addNode("A","Emp_ID");
	EXPECT_EQ("Emp_ID",ermodel->getComponentsVector().back()->getText());
	EXPECT_EQ("A",ermodel->getComponentsVector().back()->getType());
}
TEST_F(ERModelUnitTest,setComponentsVector)
{
	component = factory->createComponent("E");
	component->setText("Engineer");
	ermodel->setComponentsVector(component);
	EXPECT_EQ("Engineer",ermodel->getComponentsVector().back()->getText());
}
TEST_F(ERModelUnitTest,clone)
{
	component = factory->createComponent("A");
	component->setText("Eng_ID");
	component->setType("A");
	ermodel->setComponentsVector(component);
	EXPECT_EQ("A",ermodel->clone("A")->getType());
	EXPECT_EQ("Eng_ID",ermodel->clone("A")->getText());
}
TEST_F(ERModelUnitTest,componentsClone)
{
	component = factory->createComponent("R");
	component->setText("Has");
	component->setType("R");
	ermodel->setComponentsVector(component);
	EXPECT_EQ("Has",ermodel->componentsClone("R",0)->getText());
}
TEST_F(ERModelUnitTest,existId)
{
	component = factory->createComponent("R");
	component->setID(0);
	ermodel->setComponentsVector(component);
	component = factory->createComponent("A");
	component->setID(1);
	ermodel->setComponentsVector(component);
	EXPECT_FALSE(ermodel->existId(3));
	EXPECT_TRUE(ermodel->existId(0));
}
TEST_F(ERModelUnitTest,addComponentsFromFile)
{
	vector<string> componentLine;
	componentLine.push_back("E");
	componentLine.push_back("Engineer");
	ermodel->addComponentsFromFile(componentLine);
	EXPECT_EQ("E",ermodel->getComponentsVector().back()->getType());
	EXPECT_EQ("Engineer",ermodel->getComponentsVector().back()->getText());
}
TEST_F(ERModelUnitTest,addConnectionFromFile)
{
	component = factory->createComponent("R");
	component->setText("Has");
	component->setType("R");
	component->setID(0);
	ermodel->setComponentsVector(component);
	
	component = factory->createComponent("E");
	component->setText("PC");
	component->setType("E");
	component->setID(1);
	ermodel->setComponentsVector(component);
	component = factory->createComponent("A");
	component->setText("PC_ID");
	component->setType("A");
	component->setID(2);
	ermodel->setComponentsVector(component);

	vector<string> componentLine;
	componentLine.push_back("0");
	componentLine.push_back("1");
	componentLine.push_back("2");
	ermodel->addConnectionFromFile(componentLine);
	EXPECT_EQ("R",ermodel->getConnectionsVector()[0]->getType());
	EXPECT_EQ("E",ermodel->getConnectionsVector()[1]->getType());
	EXPECT_EQ("A",ermodel->getConnectionsVector()[2]->getType());
}
TEST_F(ERModelUnitTest,loadFile)
{
	string filePath = "file1.erd";
	ermodel->loadFile(filePath);
	ermodel->loadFile(" ");
}
TEST_F(ERModelUnitTest,saveFile)
{

	/*ermodel->loadFile("testSaveFileData.erd");
	ermodel->saveFile("outputOfTestingSaveFile.erd");
	ermodel->getComponentsVector().clear();
	ermodel->getConnectionsVector().clear();
	ermodel->getPrimaryKeysVector().clear();
	ermodel->loadFile("outputOfTestingSaveFile.erd");
	EXPECT_EQ("E", ermodel->getComponentsVector()[4]->getType());
	EXPECT_EQ(7,ermodel->getConnectionsVector()[0]->getID());
	EXPECT_EQ(1,ermodel->getPrimaryKeysVector()[1]->getID());*/
}