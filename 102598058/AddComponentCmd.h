#ifndef AddComponentCmd_H_
#define AddComponentCmd_H_
#include "Command.h"
#include "ERModel.h"
using namespace std;
class AddComponentCmd:public Command{
public:
		AddComponentCmd(ERModel*,string type,string text);
		virtual ~AddComponentCmd();
		void execute();
		void unexecute();
private:
	ERModel* _eRModel;
	string _componentType;
	Component* _componentCopy;
	string _componentText;
};
#endif