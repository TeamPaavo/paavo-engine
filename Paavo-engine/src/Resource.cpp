#include "Resource.h"


using namespace pv;

Resource::Resource(const unsigned int handle, const std::string& name, const std::string& filePath = "./")
{
	if (!_name.empty())
		_name = name;

	if (!_filePath.empty())
		_filePath = filePath;

	_handle = handle;

	if (!name.empty() && !_filePath.empty())
		_fileName = filePath + name;

	_referenceCount = 1;

}

std::string Resource::GetName()
{
	return _name;
}

std::string Resource::GetFileName()
{
	return _fileName;
}

std::string Resource::GetFilePath()
{
	return _filePath;
}

unsigned int Resource::GetHandle()
{
	return _handle;
}

void Resource::IncrementReference()
{
	_referenceCount++;
}

void Resource::DecrementReference()
{
	_referenceCount--;
}

unsigned long Resource::GetReferenceCount()
{
	return _referenceCount;
}

Resource::~Resource()
{

}
