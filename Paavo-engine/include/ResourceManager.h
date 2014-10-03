#pragma once

#include <string>
#include <stack>
#include <vector>

#define SAFE_DELETE(p) {if(p) { delete(p); (p)= NULL; } }

namespace pv
{
	template <class RM>
	class ResourceManager
	{
	public:
		ResourceManager(void(*CreateResourceFunction)(RM **resource,const unsigned int handle, const std::string& name, const std::string& filePath) = NULL);
		unsigned int Add(const std::string& name, const std::string& filePath);
		void EmptyList();
		RM* GetElement(const int handle);
		RM* GetElement(const std::string& name, const std::string& filePath);
		std::vector<RM*>* Getlist();
		RM* operator[](unsigned int handle);
		void Remove(const unsigned int handle);
		
		~ResourceManager();
	private:
		std::stack<unsigned int> _handles;
		std::vector<RM*> *_pointerList;
		void(*CreateResource)(RM **Resource, const unsigned int handle, const std::string& name, const std::string& path);
	};
}
