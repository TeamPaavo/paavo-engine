#pragma once

#include <string>
#
namespace pv
{
	class Resource
	{
	public:
		Resource(const unsigned int resourceHandle, const std::string& resourceName, const std::string& resourceFilePath);

		void DecrementReference();
		void IncrementReference();
		unsigned int GetHandle();

		unsigned long GetReferenceCount();
		std::string GetName();
		std::string GetFileName();
		std::string GetFilePath();


		virtual ~Resource();

	protected:
		std::string _name;
		std::string _filePath;
		std::string _fileName;
		unsigned int _handle;
		unsigned long _referenceCount;
	};
} //namespace pv
