#include "DeleteComponentCmd.h"
DeleteComponentCmd::DeleteComponentCmd(ERModel* model,int id):Command()
{
	_id = id;
	_eRModel = model;
	_componentCopy = NULL;
	_connectorBeDelete = false;
	for (unsigned int i = 0; i < _connectionCopy.size();i++)
	{
		_connectionCopy.push_back(NULL);
	}
}
DeleteComponentCmd::~DeleteComponentCmd(){
}
void DeleteComponentCmd::execute()
{
	if (_eRModel->getComponentsVector()[_eRModel->getIndexOfComponentID(_id)]->getType()=="C")
	{
		_componentCopy = _eRModel->componentsClone("C",_eRModel->getIndexOfComponentID(_id));
		_connectionCopy.push_back(_componentCopy);
		_connectionCopy.push_back(_eRModel->componentsClone(_eRModel->getConnectionsVector()[_eRModel->getIndexOfConnectionsID(_id)+1]->getType(),_eRModel->getIndexOfConnectionsID(_id)+1));
		_connectionCopy.push_back(_eRModel->componentsClone(_eRModel->getConnectionsVector()[_eRModel->getIndexOfConnectionsID(_id)+1+1]->getType(),_eRModel->getIndexOfConnectionsID(_id)+1+1));
		cout << "conectionCopy ==>"<<endl;
		for (unsigned int i = 0; i < _connectionCopy.size();i++)
		{
			cout << _connectionCopy[i]->getID() <<"  "; 
		}
	}
	else
	{
		_componentCopy = _eRModel->componentsClone(_eRModel->getComponentsVector()[_eRModel->getIndexOfComponentID(_id)]->getType(),_eRModel->getIndexOfComponentID(_id));
		for (unsigned int i = 0; i < _eRModel->getConnectionsVector().size();i++)
		{
			if ((_eRModel->getConnectionsVector()[i]->getID() == _id) && (_eRModel->getConnectionsVector()[i-1]->getType() == "C"))
			{//node1
				_connectorBeDelete = true;
				_connectionCopy.push_back(_eRModel->componentsClone(_eRModel->getConnectionsVector()[i-1]->getType(), _eRModel->getIndexOfComponentID(_eRModel->getConnectionsVector()[i-1]->getID())));
				_connectionCopy.push_back(_eRModel->componentsClone(_eRModel->getConnectionsVector()[i]->getType(), _eRModel->getIndexOfComponentID(_eRModel->getConnectionsVector()[i]->getID())));
				_connectionCopy.push_back(_eRModel->componentsClone(_eRModel->getConnectionsVector()[i+1]->getType(), _eRModel->getIndexOfComponentID(_eRModel->getConnectionsVector()[i+1]->getID())));
			}
			else if ((_eRModel->getConnectionsVector()[i]->getID() == _id) && (_eRModel->getConnectionsVector()[i-1-1]->getType() == "C"))
			{//node2
				_connectorBeDelete = true;
				_connectionCopy.push_back(_eRModel->componentsClone(_eRModel->getConnectionsVector()[i-2]->getType(), _eRModel->getIndexOfComponentID(_eRModel->getConnectionsVector()[i-2]->getID())));
				_connectionCopy.push_back(_eRModel->componentsClone(_eRModel->getConnectionsVector()[i-1]->getType(), _eRModel->getIndexOfComponentID(_eRModel->getConnectionsVector()[i-1]->getID())));
				_connectionCopy.push_back(_eRModel->componentsClone(_eRModel->getConnectionsVector()[i]->getType(), _eRModel->getIndexOfComponentID(_eRModel->getConnectionsVector()[i]->getID())));
			}
		}
		cout << "conectionCopy ==>"<<endl;
		for (unsigned int i = 0; i < _connectionCopy.size();i++)
		{
			cout << _connectionCopy[i]->getID() <<"  "; 
		}
	}
	_eRModel->deleteComponent(_id);
}
void DeleteComponentCmd::unexecute()
{
	if (_connectorBeDelete)
	{
		_eRModel->setComponentsVector(_connectionCopy[0]);
	}
	_eRModel->setComponentsVector(_componentCopy);
	for (unsigned int i = 0; i < _connectionCopy.size();i++)
	{
		_eRModel->setConnectionsVector(_connectionCopy[i]);
	}
	cout <<"= =!!"<<endl;
}
