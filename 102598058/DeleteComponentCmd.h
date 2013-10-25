#ifndef DeleteComponentCmd_H_
#define DeleteComponentCmd_H_
#include "Command.h"
#include "ERModel.h"
using namespace std;
class DeleteComponentCmd:public Command{
public:
	DeleteComponentCmd(ERModel*,int);
	virtual ~DeleteComponentCmd();
	void execute();
	void unexecute();
private:
	ERModel* _eRModel;
	int _id;
	Component* _componentCopy;
	vector<Component*> _connectionCopy;
	bool _connectorBeDelete;
};
#endif