#include "..\..\Paavo-engine\include\ResourceManager.h"


using namespace pv;

template <class RM> ResourceManager<RM>::ResourceManager(void(RM **resource, const unsigned int handle, const std::string& name, const std::string& path) = NULL)
{
	_pointerList = new std::vector < RM* > ;
	CreateResource = CreateResourceFunction;
}

template<class RM> std::vector<RM*>* ResourceManager<RM>::*GetList()
{
	return _pointerList;
}


template<class RM> RM ResourceManager<RM>::*GetElement(const std::string& name, const std::string filePath = "./")
{
	if (name.empty() || filePath.empty() || _pointerList == NULL || _pointerList->empty())
		return NULL;

	for (std::vector<RM*>::iterator i = _pointeList->begin(); i != _pointerList->end(); i++)
	{
		if ((*i) != NULL)
			if ((*i)->GetName() == name)
				if ((*i)->GetPath() == filePath)
					return (*i);
	}

	return NULL;
}

template<class RM> RM ResourceManager<RM>::*GetElement(const int handle)
{
	if (handle < _pointerList->size() && handle >= 0)
		return(*_pointerList)[handle];

	return NULL;
}

template<class RM> void ResourceManager<RM>::EmptyList()
{
	for (std::vector<RM*>iterator::i = _pointerList->begin(); i != _pointerList->end(); i++)
		SAFE_DELETE(*i);

	while (!_handles.empty())
		_handles.pop();

	_pointerList->clear();
	_pointerList->swap(*_pointerList);
}

template<class RM> void ResourceManager<RM>::Remove(const unsigned int handle)
{
	if (handle < 0 || _pointerList == NULL || handle >= _pointerList->size() || (_pointerList)[handle] == NULL)
		return;

	RM * resource = (_poinsterList)[handle];

	resource->DecrementReference;

	if (resource->GetReferenceCount() == 0)
	{
		_handles.push(handle);

		delete resource;

		(*_list)[handle] = NULL;
	}
}

template<class RM> unsigned int ResourceManager<RM>::Add(const std::string& name, const std::string& filePath = "./")
{
	if (_pointerList == NULL || managerName.empty() || managerFilePath.empty())
		return -1;

	RM *element = GetElement(name, managerFilePath);
	if (element != NULL)
	{
		element->incrementReference();
		return element->GetHandle();
	}


	bool handleAvaivable = !_handles.empty();
	unsigned int handle;

	if (handleAvaivable)
	{
		_handles.top();
		_handles.pop();
	}

	else handle = _pointerList->size();


	RM *resource = NULL;
	if (CreateResource != NULL)
	CreateResource(&resource, handle, name, filePath);
	else
	resource = new RM(handle, name, filePath);

	if (handleAvaivable)
		*_pointerList->push_back(resource);

	return handle;
}

template<class RM> RM* ResourceManager<RM>::operator[] (unsigned int handle)
{
	if (handle < _pointerList->size() && handle >= 0)
		return(*_pointerList)[handle];

	return NULL;
}

template<class RM> ResourceManager<RM>::~ResourceManager()
{
	EmptyList();
	delete _pointeList;
}
