#include "ERModel.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "AddComponentCmd.h"
#include "DeleteComponentCmd.h"
#include "ConnectComponentsCmd.h"
#define ATTRIBUTE "A"
#define ENTITY "E"
#define RELATIONSHIP "R"
#define CONNECTOR "C"
#define COMMA ","
#define EMPTY_STRING ""
#define BLANK " "
#define DOUBLE_BLANK "  "
#define TWO 2
#define THREE 3
#define COMMABLANK ", "
#define ZERO_STRING "0"
#define NONAME "No name"
using namespace std;
ERModel::ERModel(){
	_entityTemp=NULL;
	_primaryKey = EMPTY_STRING;
	_thisKey=0;
	_id=0;
}
ERModel::~ERModel()
{
	/*delete _entityTemp;
	delete _componentFactory;
	while(!_attributeWithOutPK.empty())
	{
		Component* component = _attributeWithOutPK.back();
		_attributeWithOutPK.pop_back();
		delete component;
	}
	while(!_entityHasPrimaryKey.empty())
	{
		Component* component = _entityHasPrimaryKey.back();
		_entityHasPrimaryKey.pop_back();
		delete component;
	}
	while(!_primaryKeys.empty())
	{
		Component* component = _primaryKeys.back();
		_primaryKeys.pop_back();
		delete component;
	}
	while(!_connections.empty())
	{
		Component* component = _connections.back();
		_connections.pop_back();
		delete component;
	}
	while(!_components.empty())
	{
		Component* component = _components.back();
		_components.pop_back();
		delete component;
	}
	delete _eRModel;*/
}
void ERModel::undo()//復原
{
	_commandManager.undo();
	cout << _commandManager.getHint() <<endl;
}
void ERModel::redo()//重作
{
	_commandManager.redo();
	cout << _commandManager.getHint() <<endl;
}
void ERModel::addNodePresentation( string text,string type)
{
	_commandManager.execute(new AddComponentCmd(this, type,text));
}
void ERModel::deleteComponentPresentation(int deleteComponent)//delete Component command
{
	_commandManager.execute(new DeleteComponentCmd(this,deleteComponent));
}
void ERModel::connectComponentPresentation()//connect component command
{
	_commandManager.execute(new ConnectComponentsCmd(this,CONNECTOR));
}
vector<Component*> ERModel::getComponentsVector()//取全部的component vector
{
	return _components;
}
void ERModel::addNode(string type,string text)
{
	_componentFactory = new ComponentFactory();
	Component* component = _componentFactory->createComponent(type);
	component->setID(_id);
	updateID();
	component->setText(text);
	component->setType (type);
	_components.push_back(component);
}
void ERModel::setComponentsVector(Component* component)//設定 component vector
{
	_components.push_back(component);
}
vector<Component*> ERModel::getConnectionsVector()//取得全部connection vector
{
	return _connections;
}
void ERModel::setConnectionsVector(Component* component)//設定connection vector
{
	_connections.push_back(component);
}
Component* ERModel::clone(string type)//複製components vector最後一個值
{
	_componentFactory = new ComponentFactory();
	Component* component = _componentFactory->createComponent(type);
	component->setID(_components.back()->getID());
	component->setText(_components.back()->getText());
	component->setType(type);
	return component;
}
Component* ERModel::componentsClone(string type, int pos)//複製components component
{
	_componentFactory = new ComponentFactory();
	Component* component = _componentFactory->createComponent(type);
	component->setID(_components.at(pos)->getID());
	component->setText(_components.at(pos)->getText());
	component->setType(type);
	return component;
}
void ERModel::setDeleteID(int deleteId)//設定deleted component id
{
	_deleteId = deleteId;
}
int ERModel::getDelelteID()//取得deleted component id
{
	return _deleteId;
}
int ERModel::checkDeleteComponentIDLoop()
{
	cin >> _checkDeletIdTemp;
	if (_checkDeletIdTemp == ZERO_STRING)
	{
		return 0;
	}
	else if (atoi(_checkDeletIdTemp.c_str()) == 0)
	{
		cout <<"The component ID You entered does not exist. Please enter a valid one again."<<endl;

		checkDeleteComponentIDLoop();
	}
	else if (existId(atoi(_checkDeletIdTemp.c_str())))
	{
		return atoi(_checkDeletIdTemp.c_str());
	}
	else
	{
		cout <<  "The component ID You entered does not exist. Please enter a valid one again."<<endl;
		checkDeleteComponentIDLoop();
	}
}
bool ERModel::existId(int id)//是否存在此id
{
	for(unsigned int i = 0; i < _components.size();i++)
	{
		if(_components[i]->getID() == id)
		{
			return true;
		}
	}
	return false;	
}
void ERModel::addComponentsFromFile(vector<string> nodeVectorFromFile)//從file增加components
{
		_componentFactory = new ComponentFactory();
		Component* component = _componentFactory->createComponent(nodeVectorFromFile[0].substr(0,1));
		component->setID(_id);
		updateID();
		component->setType(nodeVectorFromFile[0].substr(0,1));
		if (nodeVectorFromFile.size() == TWO)
		{
			component->setText(nodeVectorFromFile[1]);
		}
		else
		{
			component->setText(BLANK);
		}
		_components.push_back(component);
} 
void ERModel::updateID()//更新id
{
	_id = _id + 1;
}
void ERModel::addConnectionFromFile(vector<string> connectionVectorFromFile)//增加connections 從file
{
	_componentFactory = new ComponentFactory();
	for (unsigned int i = 0; i < connectionVectorFromFile.size();i++)
	{
		Component* component = _componentFactory->createComponent(convertIdtoComponent(atoi(connectionVectorFromFile[i].c_str()))->getType());
		component->setID(atoi(connectionVectorFromFile[i].c_str()));
		component->setType(convertIdtoComponent(atoi(connectionVectorFromFile[i].c_str()))->getType());
		component->setText(convertIdtoComponent(atoi(connectionVectorFromFile[i].c_str()))->getText());
		_connections.push_back(component);
	}
}
Component* ERModel::convertIdtoComponent(int id)//輸入id 傳出components裡的 compontent
{
	for (unsigned int i = 0; i < _components.size();i++)
	{
		if (id == _components[i]->getID())
			return _components[i];
	}
	return NULL;
}
void ERModel::analyzeComponentFromFile( ifstream& myfile )
{
	while (getline(myfile,_line))
	{	
		if (_line == EMPTY_STRING)
		{
			break;
		}
		addComponentsFromFile(splitString(_line,BLANK));
	}	
}
void ERModel::analyzeConnectionFromFile( ifstream& myfile )
{
	while (getline(myfile,_line))
	{	
		if (_line == EMPTY_STRING)
		{
			break;
		}
		int pos = _line.find(BLANK);
		if (pos == 1)
		{
			_line.replace(_line.find(DOUBLE_BLANK), TWO,BLANK);
		}
		_line.replace(_line.find(COMMA),1,BLANK);
		addConnectionFromFile(splitString(_line,BLANK));
	}	
}
void ERModel::analyzePrimaryKeyFromFile( ifstream& myfile )
{
	while (getline(myfile,_line))
	{	
		if (_line == EMPTY_STRING)
		{
			break;
		}
		_line.replace(_line.find(BLANK),1,COMMA);
		addPrimaryKeyFromFile(splitString(_line,COMMA));
	}	
}
void ERModel::loadFile( string _filePath)
{
	ifstream myfile(_filePath);
	if (myfile.is_open())
	{
		analyzeComponentFromFile(myfile);
		analyzeConnectionFromFile(myfile);
		analyzePrimaryKeyFromFile(myfile);
		_hint = true;
		myfile.close();
	}
	else 
		_hint = false;
}

string ERModel::displayComponentTable()
{
	string totalTable = "Components:\n---------------------------------\nType |  ID  |  Name  \n------+------+-------------------\n";
		
		for (unsigned int i = 0; i < _components.size();i++)
		{
			totalTable += "   ";
			totalTable += _components[i]->getType();
			totalTable += "  |  ";
			totalTable +=  intToString(_components[i]->getID());
			totalTable += "  |  ";
			totalTable += _components[i]->getText();
			totalTable += "\n";			
		}
		
		return totalTable;
}
string ERModel::printLoadFileHint()
{
	if (_hint)
	{
		string totalHint = "The ER diagram is displayed as follows:\n";
		totalHint += displayComponentTable();
		return totalHint;
	}
	else
		return "File not found!!";
}
string ERModel::intToString(int i) {
	string stringLine;
	stringstream ss(stringLine);
	ss << i;
	return ss.str();
}
void ERModel::inputComponentToFile( ofstream& myfile )
{
	for (unsigned int i = 0; i < _components.size();i++)
	{
		myfile << _components[i]->getType() << COMMABLANK << _components[i]->getText() << endl;
	}
	myfile << endl;
}
void ERModel::inputConnectionToFile( ofstream& myfile )
{
	for (unsigned int i = 0; i < _connections.size();i = i+THREE)
	{
		myfile <<setiosflags(ios::left) <<setw(THREE)<< _connections[i]->getID() << _connections[i+1]->getID()<< COMMA << _connections[i+TWO]->getID()<<endl;
	}
}
void ERModel::inputPrimaryKeyFromFile( ofstream& myfile )
{
	int entityPresentIndex = 0;//Entity count
	for (unsigned int i = 0; i < _primaryKeys.size();i++)
	{
		if(_primaryKeys[i]->getType() == "E")
		{
			myfile << endl<<_primaryKeys[i]->getID()<<BLANK;
			entityPresentIndex = i;
		}
		else 
		{
			if (i == entityPresentIndex+1)
				myfile << _primaryKeys[i]->getID();
			else
				myfile <<COMMA << _primaryKeys[i]->getID();
		}
	}
}
string ERModel::printSaveFileHint()
{
	if (_hint)
	{
		return "Save file succeeded.";
	}
	else
	{
		return "No Components to save file!";
	}
}
void ERModel::saveFile(string _fileName)
{
	cout << _components.size();
	if (_components.size()!=0)
	{
		ofstream myfile(_fileName);
		if(myfile.is_open())
		{
			inputComponentToFile(myfile);
			inputConnectionToFile(myfile);
			inputPrimaryKeyFromFile(myfile);
			myfile.close();
		}
		_hint = true;
	}
	else 
		_hint =false;
		
}
void ERModel::setPrimaryKeysVector(Component* component)
{
	_primaryKeys.push_back(component);
}
vector<Component*> ERModel::getPrimaryKeysVector()
{
	return _primaryKeys;
}
void ERModel::addPrimaryKeyFromFile(vector<string> primaryKeyVectorFromFile)//從file增加primary key
{
	_componentFactory = new ComponentFactory();
	for (unsigned int i = 0; i< primaryKeyVectorFromFile.size();i++)
	{
		Component* component = _componentFactory->createComponent(convertIdtoComponent(atoi(primaryKeyVectorFromFile[i].c_str()))->getType());
		component->setID(atoi(primaryKeyVectorFromFile[i].c_str()));
		component->setType(convertIdtoComponent(atoi(primaryKeyVectorFromFile[i].c_str()))->getType());
		component->setText(convertIdtoComponent(atoi(primaryKeyVectorFromFile[i].c_str()))->getText());
		_primaryKeys.push_back(component);
	}
}
bool ERModel::checkAddConnectionNodeTwo(string nodeTwo)//檢查第二個connected node
{
	
	if (nodeTwo == ZERO_STRING)//string 不用轉換前就是0
	{
		return true;
	}
	else 
	{
		for (unsigned int i = 0; i < _components.size(); i++)
		{
			if ((atoi(nodeTwo.c_str()) == _components[i]->getID()) && (atoi(nodeTwo.c_str())!=0))
			{
				return true;
			}
		}
		cout << "The node ID you entered does not exist."<< endl;
		return false;
	}
}
string ERModel::printConnectNodesHint()
{
	return checkConnectHint;

}
void ERModel::clearCheckConnectHint()
{
	checkConnectHint = "";
}
void ERModel::printDisconnectItselfHint(int node)
{
	cout << "&"<<endl;
	checkConnectHint = "The Node '";
	checkConnectHint += intToString(node);
	checkConnectHint += "' cannot be connected to itself.";
	checkConnectHint += "\n";
	clearConnectionNodesVector();
}
void ERModel::printDisconnectSameTypeHint(int nodeOne, int nodeTwo)
{
	cout << "@~"<<endl;
	checkConnectHint = "The node '";
	checkConnectHint += intToString(nodeOne);
	checkConnectHint += "' cannot be connected by the node '";
	checkConnectHint += intToString(nodeTwo);
	checkConnectHint += "'.\n"; 
	clearConnectionNodesVector();
}
void ERModel::printDisconnectExistHint(int nodeOne,int nodeTwo)
{
	cout << "***"<<endl;
	checkConnectHint = "The node '";
	checkConnectHint += intToString(nodeOne);
	checkConnectHint += "' has already been connected to node '";
	checkConnectHint += intToString(nodeTwo);
	checkConnectHint += "'.\n";
	clearConnectionNodesVector();
}
void ERModel::printDisconnectConditionHint(int nodeOne, int nodeTwo)
{
	cout << "+++"<<endl;
	checkConnectHint = "The node '";
	checkConnectHint += intToString(nodeOne);
	checkConnectHint += "' cannot be connected by the node '";
	checkConnectHint += intToString(nodeTwo);
	checkConnectHint += "'.\n";
	clearConnectionNodesVector();
}
void ERModel::examineTwoNodes()//connect nodes
{
	_canConnect = false;
	if (_connectionNodesVector[1] == _connectionNodesVector[0])//itself
	{
		printDisconnectItselfHint(_connectionNodesVector[1]);
	}//same type
	else if (convertIdtoComponent(_connectionNodesVector[1])->getType() == convertIdtoComponent(_connectionNodesVector[0])->getType())//type相同
	{
		printDisconnectSameTypeHint(_connectionNodesVector[1], _connectionNodesVector[0]);
	}//已連過同一條connector
	else if (checkExistConnection(_connectionNodesVector))//true: 已存在
	{
		printDisconnectExistHint(_connectionNodesVector[1], _connectionNodesVector[0]);
	}
	else if (!(convertIdtoComponent(_connectionNodesVector[0])->canConnectTo(convertIdtoComponent(_connectionNodesVector[1]))) || !(convertIdtoComponent(_connectionNodesVector[1])->canConnectTo(convertIdtoComponent(_connectionNodesVector[0]))))//個別定義不能連
	{
		printDisconnectConditionHint(_connectionNodesVector[1], _connectionNodesVector[0]);
	}
	else
	{
		_canConnect = true;
		printConnectedSuccessedHint(_connectionNodesVector[1], _connectionNodesVector[0]);
		
		/*createConnector(_connectionNodesVector);
		
		_connections.push_back(convertIdtoComponent(_connectionNodesVector[0])]);
		_connections.push_back(convertIdtoComponent(_connectionNodesVector[1])]);
		displayConnectionTable();
		clearConnectionNodesVector();*/
	}
}
bool ERModel::getCanConnectBool()
{
	return _canConnect;
}
void ERModel::setConnectionsVector()
{
	_connections.push_back(convertIdtoComponent(_connectionNodesVector[0]));
	_connections.push_back(convertIdtoComponent(_connectionNodesVector[1]));
}
void ERModel::printConnectedSuccessedHint(int nodeOne, int nodeTwo)
{
	checkConnectHint = "The node '";
	checkConnectHint += intToString(nodeOne);
	checkConnectHint += "' has been connected to the node '";
	checkConnectHint += intToString(nodeTwo);
	checkConnectHint += "'.\n";
}
void ERModel::clearConnectionNodesVector()
{
		_connectionNodesVector.clear();
}
Component* ERModel::createConnector()//生出connector
{
	_componentFactory = new ComponentFactory();
	Component* component = _componentFactory->createComponent(CONNECTOR);
	component->setID(_id);
	updateID();
	component->setType(CONNECTOR);
	if ((convertIdtoComponent(_connectionNodesVector[0])->getType() == RELATIONSHIP) || (convertIdtoComponent(_connectionNodesVector[1])->getType() == RELATIONSHIP))
	{
		_hint = true;
	}
	else
	{
		_hint = false;
	}
	return component;
	/*setRelationConnectorText(connectionNodes, component);

	
	_components.push_back(component);
	_connections.push_back(component);*/
}
//void ERModel::setConnectorText(string cardinality)
//{
//	
//		
//	}
//	else
//	{
//		component->setText(BLANK);
//	}

	/*if ((convertIdtoComponent[connectionNodes[0]]->getType() == RELATIONSHIP) || (convertIdtoComponent[connectionNodes[1]]->getType() == RELATIONSHIP))
	{
		string cardinality;
		string cardinalityTemp;
		cout << "Enter the type of the cardinality:" <<endl<<"[0]1 [1]N"<<endl<<"> ";
		cin >> cardinality;
		if (atoi(cardinality.c_str()) == 0)
		{
			component->setText("1");
			cardinalityTemp = "1";
		}
		else if (atoi(cardinality.c_str()) == 1)
		{
			component->setText("N");
			cardinalityTemp = "N";
		}
		
		cout << "Its cardinality of the relationship is '"<< cardinalityTemp << "'."<< endl;
	}
	else
	{
		component->setText(BLANK);
	}*/
//}
bool ERModel::checkExistConnection(vector<int> connectionNodes)//檢查是否存在此connection
{
	//cout << "present connection size:"<< _connections.size() <<endl;
	for (unsigned  int i = 0; i < _connections.size(); i++)
	{
		//cout << "for= " << i << endl;
		if (i%3 != 0)
		{
			if (_connections[i]->getID() == connectionNodes[0])
			{
				if (_connections[i+1]->getID() == connectionNodes[1])
				{
					return true;
				}
				i = i + 1;
				//cout << "i= " << i << endl;
			}
			else if (_connections[i+1]->getID() == connectionNodes[0])
			{
				if (_connections[i]->getID() == connectionNodes[1])
				{
					return true;
				}
				i=i+TWO;
			}
			else
			{
				i=i+TWO;
				
			}
			
				//cout << "@@@i=" << i <<endl;
		}
	}
	return false;
}
void ERModel::setConnectionNodes(int nodeOne)//設定要connect 點的vector
{
	_connectionNodesVector.push_back(nodeOne);
}
string ERModel::getWholeName(string type)//取得全名
{ 
	if (type == ATTRIBUTE)
		return ATTRIBUTE;
	else if (type == ENTITY)
		return ENTITY;
	else if (type == RELATIONSHIP)
		return RELATIONSHIP;
	else
		return NONAME;
}

void ERModel::setPrimaryKey()//設定primary key
{
	cout << "Enter the ID of the entity:" << endl << "> ";
	checkEntityLoop();
	displayAttributeOfEntity();//ok
	cout << "Enter the IDs of the attributes (use a comma to separate two attributes):" << endl << "> ";
	checkPrimaryKeyLoop();
	cout << "The entity '"<< getPKEntity() <<"' has the primary key ("<<endl;
	for (unsigned int i = 0; i < _primaryKeys.size()-1;i++)
	{
		cout << _primaryKeys[i]  <<COMMA;
	}
	cout << _primaryKeys[_primaryKeys.size()-1] <<")."<<endl;
}
vector<string> ERModel::splitString(string line, string reference)//分析string
{
	int pos=1;
	splitStringItem.clear();
	for (int i = 0; pos > 0; i++)
	{
		pos = line.find(reference);
		string stringItem = line.substr(0, pos);
		line = line.substr(pos+1,line.size());
		splitStringItem.push_back(stringItem);
	}
	return splitStringItem;
}
void ERModel::checkPrimaryKeyLoop()//檢查 primary key 直到正確
{
	_primaryKeys.clear();
	string PKString;
	cin >> PKString;
	vector<string> pkTemp = splitString(PKString,COMMA);//id is string
	for (unsigned int i = 0; i < pkTemp.size(); i++)
	{
		vector<Component*> entityAttributes =  _components[getPKEntity()]->getConnections();
		 _primaryKeys.push_back(_components[getPKEntity()]);
		for (unsigned int j = 0; j < entityAttributes.size();j++)
		{
			if(entityAttributes[j]->getType()=="A")
			{
				if (atoi(pkTemp[i].c_str()) == entityAttributes[j]->getID())
				{
					_primaryKeys.push_back(_components[atoi(pkTemp[i].c_str())]);
				}
			}
		}
		if(_primaryKeys.size() != i+1)
		{
			cout << "The node '"<< pkTemp[i] <<"' does not belong to Entity '"<< getPKEntity() <<"'. Please enter a valid one again."<<endl<<"> ";
			checkPrimaryKeyLoop();
		}
	}
	return ;
}
void ERModel::checkPrimaryKey()//檢查 primary key
{
	cin >> _primaryKey;
	splitString(_primaryKey, COMMA);
	for (unsigned int i = 0; i < _primaryKeyVector.size();i++)
	{
		_thisKey = 0;
		for (unsigned int j = 0; (j < _attributesId.size() && _thisKey == 0);j++)
		{	
			if (_attributesId[j] == atoi(_primaryKeyVector[i].c_str()))
			{
				_thisKey = 1;
			}
		}
		if (_thisKey == 0)
		{
			cout << "The node '" << _primaryKeyVector[i] <<"' does not belong to Entity '" << _entityTemp->getID() << "'. Please enter a valid one again." << endl << "> ";
			checkPrimaryKey();
		}
	}
}
void ERModel::displayAttributeOfEntity()//顯示Entity所有的attributes
{
	Component* entityTemp;
	entityTemp = _components[getPKEntity()];
	cout << "Attributes of the entity '"<< getPKEntity() <<"'"<<endl;
	cout << "---------------------------------" << endl;
	cout << "Type | ID | Name  " << endl;
	cout << "-----+----+----------------------" << endl;
	for (unsigned int i = 0; i < entityTemp->getConnections().size();i++)
	{
		if (entityTemp->getConnections()[i]->getType()=="A")
			cout << DOUBLE_BLANK << entityTemp->getConnections()[i]->getType() << "  |  " << entityTemp->getConnections()[i]->getID() << "  |  " << entityTemp->getConnections()[i]->getText()<< endl;
	}
	cout << "------------------------------------" << endl;
}
void ERModel::checkEntityLoop()//檢查Entity
{
	string entityId;
	cin >> entityId;
	if ((entityId == ZERO_STRING) && (_components[0]->getType() == ENTITY))
	{
		setPKEntity(atoi(entityId.c_str()));
		return;
	}
	else if (atoi(entityId.c_str()) == 0) //是字串
	{
		cout << "The node ID you entered does not exist. Please enter a valid one again." << endl << "> "<< endl;
		checkEntityLoop();
	}
	else if (_components[atoi(entityId.c_str())]->getType() != "E")
	{
		cout << "The node '" << entityId << "' is not an entity. Please enter a valid one again." << endl << "> "<< endl;
		checkEntityLoop();
	}
	else
	{
		setPKEntity(atoi(entityId.c_str()));
		return;
	}
}
void ERModel::setPKEntity(int entityid)//設定Entity 的 Primary key
{
	_entityID = entityid;
}
int ERModel::getPKEntity()//取得Entity 的 Primary key
{
	return _entityID;
}
void ERModel::displayEntityTable()//show Entities table
{
	cout << "Entities:" << endl;
	cout << "---------------------------------" << endl;
	cout << "Type | ID | Name  " << endl;
	cout << "-----+----+----------------------" << endl;
	for (unsigned int i = 0; i < _components.size();i++)
	{
		if (_components[i]->getType() == "E")
		{
			cout <<DOUBLE_BLANK<<_components[i]->getType()<< "  |  "<<_components[i]->getID()<<"  |  "<< _components[i]->getText()<<endl;
		}
	}
	cout << "---------------------------------" << endl;
}
void ERModel::showPrimary()//show primary key
{
	cout << "The entity '"<< _entityTemp->getID() <<"' has the primary key (";
	for (unsigned int s = 0; s < _primaryKeyVector.size();s++)
	{
		cout << _primaryKeyVector[s] <<COMMA;
	}
	cout <<"). "<< endl;
	for (unsigned int i = 0; i <_attributeWithOutPK.size();i++)
	{
		cout << "_attribute WithOut PK= " << _attributeWithOutPK[i]->getID() << endl;
	}
	_entityHasPrimaryKey.push_back(_entityTemp);
	_pkOfEntities.push_back(_primaryKeyVector);
}
void ERModel::displayTable()//show entity and it attributies table
{
	cout << "Tables:" << endl;
	cout << "-----------------------------------" << endl;
	cout << "Entity | Attribute  " << endl;
	cout << "-------+----------------------" << endl;
	for (unsigned int i = 0; i < _entityHasPrimaryKey.size();i++)
	{
			cout << DOUBLE_BLANK << _entityHasPrimaryKey[i]->getText() << "  |  " << "PK(";
			for (unsigned int j = 0; j < _pkOfEntities[i].size();j++)
				cout <<_pkOfEntities[i][j] << COMMA;
			cout << "), " ;
			cout << endl; 
	}
	cout << endl<<"------------------------------------" << endl;
}
string ERModel::displayConnectionTable()//show connection table
{
	string totalTable =  "Connections:\n------------------------------------\nConnection | node | node  \n------- ---+------+-----------------\n" ;
	for (unsigned int i = 0; i < _connections.size();i = i+THREE)
	{
		totalTable += intToString(_connections[i]->getID());
		totalTable += "     |  ";
		totalTable += intToString(_connections[i+1]->getID());
		totalTable += "  |  ";
		totalTable += intToString(_connections[i+TWO]->getID());
		totalTable += "\n";
	}
	return totalTable;
}
void ERModel::deleteComponent(int id)//delete component
{
	setDeleteID(id);
	if (_components[id]->getType() == CONNECTOR)
	{
		cout << _connections.size()<<endl;
		for (unsigned int i = 0; i < _connections.size();i++)
		{
			if(_connections[i]->getID() == id)
			{
				_connections.erase(_connections.begin()+i+TWO);
				_connections.erase(_connections.begin()+i+1);
				_connections.erase(_connections.begin()+i);
				continue;
			}
		}
		for (unsigned int i = 0; i < _components.size(); i++)
		{
			if (_components[i]->getID()==id)
			{
				_components.erase(_components.begin()+i);
			}
		}
	}
	else
	{
		int updateConnectionsSize = _connections.size();
		for(int i = 0; i < updateConnectionsSize;i++)
		{
			if(_connections[i]->getID() == id)
			{
				if(_connections[i-1]->getType() == CONNECTOR)//表i為node1
				{
					_connections.erase(_connections.begin()+i+1);
					_connections.erase(_connections.begin()+i);
					_components.erase(_components.begin()+getIndexOfComponentID(_connections[i-1]->getID()));
					_connections.erase(_connections.begin()+i-1);
				}
				else 
				{
					int temp = i-TWO;
					_connections.erase(_connections.begin()+temp+TWO);
					_connections.erase(_connections.begin()+temp+1);
					_components.erase(_components.begin()+getIndexOfComponentID(_connections[temp]->getID()));
					_connections.erase(_connections.begin()+temp);
				}
				updateConnectionsSize = _connections.size();
				i=0;
			}
		}
		for (unsigned int i = 0; i < _components.size(); i++)
		{
			if (_components[i]->getID()==id)
			{
				_components.erase(_components.begin()+i);
			}
		}
	}
}
int ERModel::getIndexOfComponentID(int componentID)//用 id 轉換成 components vector 的 index
{
	for (unsigned int i = 0; i < _components.size();i++)
	{
		if(_components[i]->getID() == componentID)
			return i;
	}
	return -2;
}
int ERModel::getIndexOfConnectionsID(int connectionsID)//用 id 轉換成connections vector 的 index
{
	for (unsigned int i = 0; i < _connections.size();i++)
	{
		if (_connections[i]->getID() == connectionsID)
			return i;
	}
	return -1;
}
int ERModel::checkAddConnectionNode(string nodeOne)
{
	if (nodeOne == ZERO_STRING)//string 不用轉換前就是0
	{
		_hint = true;
		return atoi(nodeOne.c_str());
	}
	else 
	{
		for (unsigned int i = 0; i < _components.size(); i++)
		{
			if ((atoi(nodeOne.c_str()) == _components[i]->getID()) && (atoi(nodeOne.c_str())!=0))
			{
				_hint = true;
				return atoi(nodeOne.c_str());
			}
		}
		_hint = false;
		return -1;
	}
}
bool ERModel::getHint()
{
	return _hint;
}