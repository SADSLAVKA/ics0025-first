#include "Data.h"
#include <iostream>
#include <algorithm>

Data::Data() { }

Data::Data(int n) {
	for (int i = 0; i < n; i++)
	{
		Item* new_item = new Item();
		if (InsertItem(new_item) == nullptr) {
			delete new_item;
		}
	}
}

Data::~Data() {
	for (auto group : DataStructure)
	{
		for (auto subgroup : *group.second) {
			for (auto item : *subgroup.second) {
				delete item;
			}
			delete subgroup.second;
		}
		delete group.second;
	}
}

void Data::PrintAll() {
	for (auto group : DataStructure)
	{
		std::cout << group.first << ":\n";
		for (auto subgroup : *group.second) {
			for (auto item : *subgroup.second) {
				Date &&date = item->getTimestamp();
				std::cout << subgroup.first << ": " << item->getName() << " " << date.GetDay()
					<< " " << date.GetMonth() << " " << date.GetYear() << "\n";
			}
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

Item* Data::InsertItem(Item *new_item) {
	char&& c = new_item->getGroup();
	int&& i = new_item->getSubgroup();
	std::string&& s = new_item->getName();
	Date&& d = new_item->getTimestamp();
	if (c < 'A' || c > 'Z')
	{
		return nullptr;
	} 
	else if (i < 0 || i > 99)
	{
		return nullptr;
	}
	else if (s.empty()) 
	{
		return nullptr;
	}
	auto group_iter = DataStructure.find(c);
	if (group_iter == DataStructure.end())
	{
		group_iter = DataStructure.insert(std::make_pair(c, new std::map<int, std::list<Item *> *>)).first;
	}
	auto subgroup_iter = group_iter->second->find(i);
	if (subgroup_iter == group_iter->second->end())
	{
		subgroup_iter = group_iter->second->insert(std::make_pair(i, new std::list<Item *>)).first;
	}
	std::list<Item *> *ptr_itemlist = subgroup_iter->second;
	auto item_iter = std::find_if(ptr_itemlist->begin(), ptr_itemlist->end(), [new_item](const Item* i)->bool { return *i == *new_item; });
	if (item_iter != ptr_itemlist->end())
	{
		return nullptr;
	}
	ptr_itemlist->push_back(new_item);
	return new_item;
}

Item* Data::InsertItem(char c, int i, std::string s, Date d) {
	return InsertItem(new Item(c, i, s, d));
}