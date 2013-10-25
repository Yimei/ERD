//#include <QtCore/QCoreApplication>
#include <iostream>
#include "TextUI.h"
#include "ERModel.h"
using namespace std;
int main()
{
	ERModel* model = new ERModel;
	TextUI* textUI = new TextUI(model);
	textUI->displayMenu();
	system("pause");
	delete model;
	delete textUI;
	return 0;
}
