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
using namespace std;
TextUI::TextUI(ERModel* model)
{
	_eRModel = model;
}
TextUI::~TextUI()
{
	delete _eRModel;
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
		cout << _eRModel->printHint() << endl;
			
		displayMenu();
	}
	else if (_command == SAVE_FILE)
	{
		cout << "Please input the file name: ";
		cin >> _fileName;//輸出的檔名路徑
		_eRModel->saveFile(_fileName);
		displayMenu();
	}
	else if (_command == ADD_A_NODE)
	{
		cout << "What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation" << endl<<"> ";
		cin >> _type;
		while ((_type != "A")&&(_type != "E")&&(_type != "R"))
		{
			cout << "You entered an invalid node. Please enter a valid one again.\n[A]Attribute [E]Entity [R]Relation" << endl<<"> ";
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
		_eRModel->setConnectionNodes(_eRModel->checkAddConnectionNodeOneLoop());
		cout << "Please enter the second node ID "<< endl << "> ";
		_eRModel->connectComponentPresentation();
		displayMenu();
	}
	else if (_command == DISPLAY_DIAGRAM)
	{
		cout << "The ER diagram is displayed as follows:"<<endl<<"Nodes:"<<endl;
		_eRModel->displayComponentTable();
		_eRModel->displayConnectionTable();
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
//void TextUI::printHintFile()
//{
//	if (_eRModel->printHint())
//	{
//		cout << "The ER diagram is displayed as follows:" << endl<<"Components: " << endl;
//		_eRModel->displayComponentTable();
//		_eRModel->displayConnectionTable();
//	}
//	else
//		cout << "File not found!!"<<endl;
//}

