#ifndef _ERModel_H_ 
#define _ERModel_H_
#include <gtest/gtest_prod.h> 

#include "string"
#include <vector>
#include "CommandManager.h"
#include "Component.h"
#include "ComponentFactory.h"
#include <iostream>
using namespace std;
class ERModel{
	//friend class ERModelTest;
	FRIEND_TEST(ERModelUnitTest, addNode);
	FRIEND_TEST(ERModelUnitTest,setComponentsVector);
	FRIEND_TEST(ERModelUnitTest,getConnectionsVector);
	FRIEND_TEST(ERModelTest, clone);
	
	FRIEND_TEST(ERModelTest, componentsClone);
	FRIEND_TEST(ERModelTest, checkDeleteComponentIDLoop);
	FRIEND_TEST(ERModelTest, existId);
	FRIEND_TEST(ERModelTest, addComponentsFromFile);
	FRIEND_TEST(ERModelTest, updateID);
	FRIEND_TEST(ERModelTest, convertIdtoComponent);
	FRIEND_TEST(ERModelTest, loadFile);
	FRIEND_TEST(ERModelTest, saveFile);
	FRIEND_TEST(ERModelTest, addPrimaryKeyFromFile);
	FRIEND_TEST(ERModelTest, checkAddConnectionNodeTwo);
	FRIEND_TEST(ERModelTest, connectTwoNode);
	FRIEND_TEST(ERModelTest, createConnector);
	FRIEND_TEST(ERModelTest, checkExistConnection);
	
public:
	ERModel();
	virtual ~ERModel();
	void addNode(string,string);
	string getWholeName(string);
	void setPrimaryKey();
	void checkPrimaryKey();
	vector<string> splitString(string,string);
	void showPrimary();
	void displayTable();
	void loadFile(string);
	void saveFile(string);

	void addComponentsFromFile(vector<string>);
	void addConnectionFromFile(vector<string>);
	void addPrimaryKeyFromFile(vector<string>);
	/*void displayComponentTable();*/
	string displayConnectionTable();
	void displayEntityTable();
	void displayAttributeOfEntity();
	void updateID();
	Component* convertIdtoComponent(int);
	bool existId(int);
	int checkDeleteComponentIDLoop();
	void examineTwoNodes();
	int checkAddConnectionNodeOneLoop();
	void checkEntityLoop();
	bool checkAddConnectionNodeTwo(string);
	void setConnectionNodes(int);
	bool checkExistConnection(vector<int>);//連過的兩個相同node不可再連
	Component* createConnector();
	void checkPrimaryKeyLoop();
	void setPKEntity(int);
	int getPKEntity();
	void deleteComponent(int);
	void undo();
	void redo();
	void addNodePresentation(string,string);
	void deleteComponentPresentation(int);
	void connectComponentPresentation();
	vector<Component*> getComponentsVector();
	void setComponentsVector(Component*);
	vector<Component*> getConnectionsVector();
	void setConnectionsVector(Component*);
	Component* clone(string);
	Component* componentsClone(string, int);
	void setDeleteID(int);
	int getDelelteID();
	int getIndexOfComponentID(int);
	int getIndexOfConnectionsID(int);
	string getCheckDeleteComponentHint(int);
	string printLoadFileHint();
	string displayComponentTable();
	string printSaveFileHint();
	void setPrimaryKeysVector(Component*);
	vector<Component*> getPrimaryKeysVector();
	string checkTypeChar(string type);
	string whetherToInputTypeAgain();
	int checkAddConnectionNode(string);
	bool getHint();
	void clearConnectionNodesVector();
	string printConnectNodesHint();
	void clearCheckConnectHint();
	void printDisconnectItselfHint(int);
	void printDisconnectSameTypeHint(int,int);
	void printDisconnectExistHint(int,int);
	void printDisconnectConditionHint(int, int);
	void printConnectedSuccessedHint(int, int);
	//void setConnectorText(string);
	void setConnectionsVector();
	bool getCanConnectBool();
private:
	void analyzeComponentFromFile( ifstream& myfile );
	void analyzeConnectionFromFile( ifstream& myfile );
	void analyzePrimaryKeyFromFile( ifstream& myfile );
	void inputComponentToFile( ofstream& myfile );
	void inputConnectionToFile( ofstream& myfile );
	void inputPrimaryKeyFromFile( ofstream& myfile );
	string intToString(int i);
	CommandManager _commandManager;
	ERModel* _eRModel;
	vector<Component*> _components;
	vector<Component*> _connections;//[0]connection [1]node1 [2]node2 [3]connection...
	vector<Component*> _primaryKeys;//[0]entity [1]attribute1 [2]attribute2 [3]entity... ps.有PK的Entity
	ComponentFactory* _componentFactory;
	Component* _entityTemp;
	string _primaryKey;
	vector<int> _attributesId;
	vector<string> _primaryKeyVector;
	int _thisKey;
	vector<Component*> _entityHasPrimaryKey;
	vector<vector<string>> _pkOfEntities;
	vector<Component*> _attributeWithOutPK;
	vector<string> splitStringItem;
	int _id;
	int _deleteId;
	
	
	vector<int> _connectionNodesVector;//[0]node1 [1]node2
	int _entityID;
	string _checkDeletIdTemp;
	string _checkDeleteComponentHint;
	string _line;
	bool _hint;
	bool _canConnect;
	string checkConnectHint;
	
};
#endif