#include "..\..\Paavo-engine\include\Resource.h"


using namespace pv;

Resource::Resource(const unsigned int resourceHandle, const std::string& resourceName, const std::string& resourceFilePath = "./")
{
	if (!_name.empty())
		_name = resourceName;

	if (!_filePath.empty())
		_filePath = resourceFilePath;

	_handle = resourceHandle;

	if (!resourceName.empty() && !_filePath.empty())
		_fileName = resourceFilePath + resourceName;

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
