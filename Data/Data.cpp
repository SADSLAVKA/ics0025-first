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

int Data::CountItems() {
	int count = 0;
	for (auto group : DataStructure)
	{
		for (auto subgroup : *group.second) {
			for (auto item : *subgroup.second) {
				count++;
			}
		}
	}
	return count;
}

std::map<int, std::list<Item*>*>* Data::GetGroup(char c) {
	c &= ~' ';
	auto group_iter = DataStructure.find(c);
	if (group_iter == DataStructure.end())
	{
		return nullptr;
	}
	return group_iter->second;
}

void Data::PrintGroup(char c) {
	c &= ~' ';
	auto group_iter = DataStructure.find(c);
	if (group_iter == DataStructure.end())
	{
		throw std::invalid_argument("Group doesn't exist!");
	}
	std::cout << group_iter->first << ":\n";
	for (auto subgroup : *group_iter->second) {
		for (auto item : *subgroup.second) {
			Date&& date = item->getTimestamp();
			std::cout << subgroup.first << ": " << item->getName() << " " << date.GetDay()
				<< " " << date.GetMonth() << " " << date.GetYear() << "\n";
		}
	}
	std::cout << std::endl;
}

int Data::CountGroupItems(char c) {
	c &= ~' ';
	int count = 0;
	auto group_iter = DataStructure.find(c);
	if (group_iter == DataStructure.end())
	{
		return 0;
	}
	for (auto subgroup : *group_iter->second) {
		for (auto item : *subgroup.second) {
			count++;
		}
	}
	return count;
}

std::list<Item*>* Data::GetSubgroup(char c, int i) {
	if (i < 0 || i > 99)
	{
		return nullptr;
	}
	auto group = GetGroup(c);
	if (!group)
	{
		return nullptr;
	}
	auto subgroup_iter = group->find(i);
	if (subgroup_iter == group->end())
	{
		return nullptr;
	}
	return subgroup_iter->second;
}

void Data::PrintSubgroupByNames(char c, int i) {
	std::list<Item*>* p_subgroup = GetSubgroup(c, i);
	if (!p_subgroup)
	{
		throw std::invalid_argument("Selected subgroup doesn't exist!");
	}
	std::list<Item*> subgroup = *p_subgroup;
	subgroup.sort([](const Item* a, const Item* b)->bool {return a->getName() < b->getName(); });
	for (auto item : subgroup) {
		Date&& date = item->getTimestamp();
		std::cout << i << ": " << item->getName() << " " << date.GetDay()
			<< " " << date.GetMonth() << " " << date.GetYear() << "\n";
	}
	std::cout << std::endl;
}

void Data::PrintSubgroupByDates(char c, int i) {
	std::list<Item*>* p_subgroup = GetSubgroup(c, i);
	if (!p_subgroup)
	{
		throw std::invalid_argument("Selected subgroup doesn't exist!");
	}
	std::list<Item*> subgroup = *p_subgroup;
	subgroup.sort([](const Item* a, const Item* b)->bool {return a->getTimestamp() < b->getTimestamp(); });
	for (auto item : subgroup) {
		Date&& date = item->getTimestamp();
		std::cout << i << ": " << item->getName() << " " << date.GetDay()
			<< " " << date.GetMonth() << " " << date.GetYear() << "\n";
	}
	std::cout << std::endl;
}

int Data::CountSubgroupItems(char c, int i) {
	std::list<Item*>* p_subgroup = GetSubgroup(c, i);
	if (!p_subgroup)
	{
		return 0;
	}
	return p_subgroup->size();
}

Item* Data::GetItem(char c, int i, std::string s) {
	if (s.empty())
	{
		return nullptr;
	}
	std::list<Item*>* p_subgroup = GetSubgroup(c, i);
	if (!p_subgroup)
	{
		return nullptr;
	}
	auto item_iter = std::find_if(p_subgroup->begin(), p_subgroup->end(),
		[s](const Item* item)->bool { return s == item->getName(); });
	if (item_iter != p_subgroup->end())
	{
		return *item_iter;
	}
	return nullptr;
}

void Data::PrintItem(char c, int i, std::string s) {
	Item* item = GetItem(c, i, s);
	if (!item)
	{
		throw std::invalid_argument("Item doesn't exist!");
	}
	Date&& date = item->getTimestamp();
	std::cout << i << ": " << item->getName() << " " << date.GetDay()
		<< " " << date.GetMonth() << " " << date.GetYear() << std::endl;
}

Item* Data::InsertItem(Item *new_item) {
	char&& c = new_item->getGroup();
	int&& i = new_item->getSubgroup();
	std::string&& s = new_item->getName();
	Date&& d = new_item->getTimestamp();
	c &= ~' ';
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
	return InsertItem(new Item(c & ~' ', i, s, d));
}

std::list<Item*>* Data::InsertSubgroup(char c, int i, std::initializer_list<Item*> items) {
	c &= ~' ';
	if (c < 'A' || c > 'Z' || i < 0 || i > 99 || items.size() == 0)
	{
		return nullptr;
	}
	auto group_iter = DataStructure.find(c);
	if (group_iter == DataStructure.end())
	{
		group_iter = DataStructure.insert(std::make_pair(c, new std::map<int, std::list<Item*>*>)).first;
	}
	auto subgroup_iter = group_iter->second->find(i);
	if (subgroup_iter != group_iter->second->end())
	{
		return nullptr;
	}
	std::list<Item*>* p_subgroup = new std::list<Item*>( items );
	group_iter->second->insert(std::make_pair(i, p_subgroup));
	return p_subgroup;
}

std::map<int, std::list<Item*>*>* Data::InsertGroup(char c, std::initializer_list<int> subgroups,
	std::initializer_list<std::initializer_list<Item*>> items) {
	c &= ~' ';
	if (DataStructure.find(c) != DataStructure.end() || c < 'A' || c > 'Z' || subgroups.size() != items.size())
	{
		return nullptr;
	}
	auto sb = subgroups.begin();
	auto it = items.begin();
	size_t size = subgroups.size();
	auto group = new std::map<int, std::list<Item*>*>;
	for (size_t i = 0; i < size; i++, sb++, it++) {
		group->insert({ *sb, new std::list<Item*>(*it) });
	}
	DataStructure.insert({ c, group });
	return group;
}

bool Data::RemoveItem(char c, int i, std::string s) {
	c &= ~' ';
	if (c < 'A' || c > 'Z')
	{
		return false;
	}
	else if (i < 0 || i > 99)
	{
		return false;
	}
	else if (s.empty())
	{
		return false;
	}
	auto group_iter = DataStructure.find(c);
	if (group_iter == DataStructure.end())
	{
		return false;
	}
	auto subgroup_iter = group_iter->second->find(i);
	if (subgroup_iter == group_iter->second->end())
	{
		return false;
	}
	auto item_iter = std::find_if(subgroup_iter->second->begin(), subgroup_iter->second->end(),
		[s](const Item* item)->bool { return s == item->getName(); });
	if (item_iter == subgroup_iter->second->end())
	{
		return false;
	}
	delete* item_iter;
	subgroup_iter->second->erase(item_iter);
	if (subgroup_iter->second->size() == 0)
	{
		delete subgroup_iter->second;
		group_iter->second->erase(subgroup_iter);
	}
	if (group_iter->second->size() == 0)
	{
		delete group_iter->second;
		DataStructure.erase(group_iter);
	}
	return true;
}
	