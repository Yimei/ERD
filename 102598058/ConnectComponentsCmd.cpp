#include "ConnectComponentsCmd.h"
#define CONNECTOR "C"
#define TWO 2
ConnectComponentsCmd::ConnectComponentsCmd(ERModel* model,string type):Command()
{
	_componentCopy = NULL;
	_componentType = type;
	_eRModel = model;
	for (unsigned int i = 0; i < _connectionsCopy.size();i++)
	{
		_connectionsCopy[i] = NULL;
	}
}
ConnectComponentsCmd::~ConnectComponentsCmd(){

}
void ConnectComponentsCmd::execute()
{
	if(_componentCopy==NULL)
	{
		_eRModel->examineTwoNodes();
		/*_componentCopy = _eRModel->clone(CONNECTOR);
		_connectionsCopy.push_back(_componentCopy);
		_connectionsCopy.push_back(_eRModel->componentsClone(_eRModel->getConnectionsVector()[_eRModel->getConnectionsVector().size()-TWO]->getType(),_eRModel->getConnectionsVector().size()-TWO));
		_connectionsCopy.push_back(_eRModel->componentsClone(_eRModel->getConnectionsVector()[_eRModel->getConnectionsVector().size()-1]->getType(),_eRModel->getConnectionsVector().size()-1));*/
	}
	else
	{
		_eRModel->setComponentsVector(_componentCopy);
		for (unsigned int i = 0; i < _connectionsCopy.size();i++)
		{
			_eRModel->setConnectionsVector(_connectionsCopy[i]);
		}
	}
}
void ConnectComponentsCmd::unexecute()
{
	_eRModel->deleteComponent(_componentCopy->getID());
}
