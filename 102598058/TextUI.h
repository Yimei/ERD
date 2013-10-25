#ifndef _TextUI_H_ 
#define _TextUI_H_
#include "ERModel.h"
#include <string>
using namespace std;
class TextUI{
public:
	TextUI(ERModel*);
	virtual ~TextUI();
	void displayMenu();
	void processCommand();
	void action_addCommand();
	void action_redo();
	void action_undo();
	void printHintFile();
private:
	ERModel* _eRModel;
	int _firstId;
	string _command;
	string _type;
	string _text;
	string _filePath;
	string _fileName;
};
#endif