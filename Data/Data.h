#pragma once
#include <map>
#include <list>
#include "../Item/Item.h"

class Data {

private:
	std::map<char, std::map<int, std::list<Item*>*>*> DataStructure;

public:
	Data();
	Data(int n);
	~Data();
	void PrintAll();
	int CountItems();
	std::map<int, std::list<Item*>*>* GetGroup(char c);
	void PrintGroup(char c);
	int CountGroupItems(char c);
	std::list<Item*>* GetSubgroup(char c, int i);
	void PrintSubgroupByNames(char c, int i);
	void PrintSubgroupByDates(char c, int i);
	int CountSubgroupItems(char c, int i);
	Item* GetItem(char c, int i, std::string s);
	void PrintItem(char c, int i, std::string s);
	Item* InsertItem(Item* new_item);
	Item *InsertItem(char c, int i, std::string s, Date d);
	std::list<Item*>* InsertSubgroup(char c, int i, std::initializer_list<Item*> items);
	std::map<int, std::list<Item*>*>* InsertGroup(char c, std::initializer_list<int> subgroups, 
		std::initializer_list<std::initializer_list<Item*>> items);
	bool RemoveItem(char c, int i, std::string s);
	bool RemoveSubgroup(char c, int i);
};