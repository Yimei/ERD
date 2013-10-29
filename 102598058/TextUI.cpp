#include <string>
#include <iostream>
#include "TextUI.h"
#include "ERModel.h"
#define LOAD_FILE "1"
#define SAVE_FILE "2"
#define ADD_A_NODE "3"
#define CONNECT_TWO_NODES "4"
#define DISPLAY_DIAGRAM "5"
#define SET_PRIMARY_KEY "6"
#define DISPLAY_TABLE "7"
#define DELETE_COMPONENT "8"
#define UNDO "9"
#define REDO "10"
#define EXIT "11"
#define BLANK " "
using namespace std;
TextUI::TextUI(ERModel* model)
{
	_eRModel = model;
}
TextUI::~TextUI()
{
	//delete _eRModel;
}
void TextUI::displayMenu()
{
	cout << "1. Load ER diagram file" << endl;
	cout << "2. Save ER diagram file" << endl;
	cout << "3. Add a node" << endl;
	cout << "4. Connect two nodes" << endl;
	cout << "5. Display the current diagram" << endl;
	cout << "6. Set a primary key" << endl;
	cout << "7. Display the table" << endl;
	cout << "8. Delete a component"<< endl;
	cout << "9. Undo" << endl;
	cout << "10. Redo" << endl;
	cout << "11. Exit" << endl <<"> ";
	processCommand();
}
void TextUI::processCommand(){
	cin >> _command;
	if (_command == LOAD_FILE)
	{
		
		_eRModel = new ERModel();
		cout << "Please input a file path: ";
		cin >> _filePath;
		_eRModel->loadFile(_filePath);
		cout << _eRModel->printLoadFileHint() << endl;
		displayMenu();
	}
	else if (_command == SAVE_FILE)
	{
		cout << "Please input the file name: ";
		cin >> _fileName;//輸出的檔名路徑
		_eRModel->saveFile(_fileName);
		cout << _eRModel->printSaveFileHint() << endl;
		displayMenu();
	}
	else if (_command == ADD_A_NODE)
	{
		cout << "What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation" << endl<<"> ";
		cin >> _type;
		while ((_type != "A")&&(_type != "E")&&(_type != "R"))
		{
			cout << "You entered an invalid node. Please enter a valid one again.\n[A]Attribute [E]Entity [R]Relation" << endl <<"> ";
			cin >> _type;
		}
		cout<< "Enter the name of this node:" << endl<<"> ";
		cin >> _text;
		_eRModel->addNodePresentation(_type,_text);
		cout << "A node [" << _eRModel->getWholeName(_type) << "]" << " has been added. ID: " << _eRModel->getComponentsVector().back()->getID() << ", Name: " << _eRModel->getComponentsVector().back()->getText() << endl;
		cout << "Components: " << endl;
		_eRModel->displayComponentTable();
		displayMenu();
	}
	else if (_command == CONNECT_TWO_NODES)
	{
		cout << "Please enter the first node ID "<< endl << "> ";
		_eRModel->setConnectionNodes(checkAddConnectionNodeOneLoop());//nodeOne 丟進vector裡
		cout << "Please enter the second node ID "<< endl << "> ";
		setAddConnectionNodeTwo();//nodeTwo 丟進 vector 裡
		_eRModel->connectComponentPresentation();
		cout <<_eRModel->printConnectNodesHint();
		_eRModel->clearCheckConnectHint();
		if (_eRModel->getCanConnectBool())
		{
			Component* component = _eRModel->createConnector();
			setRelationConnectorText(component);
			_eRModel->setConnectionsVector();
			cout << _eRModel->displayConnectionTable() << endl;
		}
		_eRModel->clearConnectionNodesVector();
		displayMenu();
	}
	else if (_command == DISPLAY_DIAGRAM)
	{
		cout << "The ER diagram is displayed as follows:"<<endl<<"Nodes:"<<endl;
		cout << _eRModel->displayComponentTable() << endl;
		cout << _eRModel->displayConnectionTable() << endl;
		displayMenu();
	}
	else if (_command == SET_PRIMARY_KEY)
	{
		_eRModel->displayEntityTable();
		_eRModel->setPrimaryKey();
		displayMenu();
	}
	else if (_command == DISPLAY_TABLE)
	{
		_eRModel->displayTable();
		displayMenu();
	}
	else if (_command == DELETE_COMPONENT)
	{
		int deleteComponentID;
		cout << "Please enter the component ID" << endl <<"> ";
		deleteComponentID = _eRModel->checkDeleteComponentIDLoop();
		_eRModel->deleteComponentPresentation(deleteComponentID);
		cout << "The component '" << _eRModel->getDelelteID() <<"' has been deleted."<<endl;
		cout << "Component:"<<endl;
		_eRModel->displayComponentTable();
		_eRModel->displayConnectionTable();
		displayMenu();
	}
	else if (_command == UNDO)
	{
		_eRModel->undo();
		cout << "Components: " << endl;
		_eRModel->displayComponentTable();
		_eRModel->displayConnectionTable();
		displayMenu();
	}
	else if (_command == REDO)
	{
		_eRModel->redo();
		_eRModel->displayComponentTable();
		_eRModel->displayConnectionTable();
		displayMenu();
	}
	else if (_command == EXIT)
	{
		cout << "Goodbye!" <<endl;
		return;
	}
	else
	{
		cout << "No this option. Please enter the number again."<<endl;
		displayMenu();
	}
}
int TextUI::checkAddConnectionNodeOneLoop()//檢查第一個要connect的點
{
	cin >> _nodeIDOne;
	int nodeOneId = _eRModel->checkAddConnectionNode(_nodeIDOne);
	if (_eRModel->getHint())
	{
		return nodeOneId;
	}
	else
	{
		cout << "The node ID you entered does not exist. Please enter a valid one again." << endl <<"> ";
		checkAddConnectionNodeOneLoop();
		return 0;
	}
}
void TextUI::setAddConnectionNodeTwo()
{
	cin >> _nodeIDTwo;
	int nodeTwoId = _eRModel->checkAddConnectionNode(_nodeIDTwo);
	if (_eRModel->getHint())
	{
		_eRModel->setConnectionNodes(nodeTwoId);//nodeTwo 丟進vector裡
		//return;
	}
	else
	{
		cout << "The node ID you entered does not exist."<< endl;
		_eRModel->clearConnectionNodesVector();
		//return 0;
	}
}
void TextUI::setRelationConnectorText(Component* component)
{
	if(_eRModel->getHint())
	{
		string cardinality;
		string cardinalityTemp;
		cout << "Enter the type of the cardinality:" <<endl<<"[0]1 [1]N"<<endl<<"> ";
		cin >> cardinality;
		//_eRModel->setConnectorText(cardinality);
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
		else
		{
			cout << "Wrong cardinality number!"<<endl;
		}
		
		cout << "Its cardinality of the relationship is '"<< cardinalityTemp << "'."<< endl;
	}
	else
	{
		component->setText(BLANK);
	}
	_eRModel->setComponentsVector(component);
	_eRModel->setConnectionsVector(component);
}