//Copyright Sam Collier 2022
#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>

template <typename Resource, typename Identifier>
class ResourceHolder
{
	public:
		void load(Identifier id, const std::string &fileName);
		const Resource& get(Identifier id) const;
		Resource& get(Identifier id);

	private:
		std::map<Identifier,std::unique_ptr<Resource>> resourceMap;
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &fileName)
{
	std::unique_ptr<Resource> resource(new Resource());
	if(!resource->loadFromFile(fileName))
	{
		std::cout << "FAILED TO LOAD FILE\n";
	}
	resourceMap.insert(std::make_pair(id,std::move(resource)));
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = resourceMap.find(id);
	return *found->second;
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = resourceMap.find(id);
	return *found->second;
}

