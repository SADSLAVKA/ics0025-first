#pragma once
#include <string>
#include "../Date/Date.h"

class Item {
	
private:
	char Group;
	int Subgroup;
	std::string Name;
	Date Timestamp;

public:
	Item();
	Item(char group, int subgroup, std::string name, Date timestamp);
	Item(const Item &item);
	~Item();
};