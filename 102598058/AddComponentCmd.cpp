#include "AddComponentCmd.h"
AddComponentCmd::AddComponentCmd(ERModel* model, string type,string text):Command()
{
	_eRModel = model;
	_componentType = type;
	_componentCopy =NULL;
	_componentText = text;
}
AddComponentCmd::~AddComponentCmd()
{
}
void AddComponentCmd::execute()
{
	if(_componentCopy==NULL)
	{
		_eRModel->addNode(_componentType, _componentText);
		_componentCopy = _eRModel->clone(_componentType);
	}
	else
	{
		_eRModel->setComponentsVector(_componentCopy);
	}
}
void AddComponentCmd::unexecute()
{
	_eRModel->deleteComponent(_componentCopy->getID());
}
