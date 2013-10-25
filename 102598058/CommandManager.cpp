#include "CommandManager.h"
#define BLANK " "
#define CANNOT_REDO "Cannot redo."
#define CANNOT_UNDO "Cannot undo."
#define REDO_SUCCESSED "Redo succeed!"
#define UNDO_SUCCESSED "Undo succeed!";
#include <stack>

CommandManager::CommandManager()
{
	_hint = BLANK;
}
CommandManager::~CommandManager()
{
	while(!_redoCommands.empty()){
		Command* command = _redoCommands.top();
		_redoCommands.pop();
		delete command;
	}
	while(!_undoCommands.empty()){
		Command* command = _undoCommands.top();
		_undoCommands.pop();
		delete command;
	}
}
void CommandManager::execute(Command* command)
{
	command->execute();
	_undoCommands.push(command);
	while(!_redoCommands.empty())
	{
		Command* c = _redoCommands.top();
		_redoCommands.pop();
		delete c;
	}
}
void CommandManager::redo()
{
	if (_redoCommands.size() == 0)
	{
		_hint = CANNOT_REDO;
		return;
	}
	_hint = REDO_SUCCESSED;	
	Command* c = _redoCommands.top();
	_redoCommands.pop();
	c->execute(); //redo the command
	_undoCommands.push(c);
}
void CommandManager::undo()
{
	if (_undoCommands.size() == 0)
	{
		_hint = CANNOT_UNDO;
		return;
	}
	_hint = UNDO_SUCCESSED;
	Command*  c = _undoCommands.top();
	_undoCommands.pop();
	c->unexecute();//undo the command
	_redoCommands.push(c);
}
string CommandManager::getHint()
{
	return _hint;
}