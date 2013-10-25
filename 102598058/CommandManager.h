#ifndef CommandManager_H_
#define CommandManager_H_
#include <stack>
#include "Command.h"
using namespace std;
class CommandManager{
public:
	CommandManager();
	virtual ~CommandManager();
	void execute(Command*);
	void redo();//���U�@��
	void undo();//�_��
	string getHint();
private:
	string _hint;
	stack<Command*> _redoCommands;
	stack<Command*> _undoCommands;
};
#endif