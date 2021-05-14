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
	Item* InsertItem(Item* new_item);
	Item *InsertItem(char c, int i, std::string s, Date d);
};