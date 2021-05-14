#pragma once
#include <string>
#include <vector>
#include <random>
#include "../Date/Date.h"

class Item {
	
private:
	char Group;
	int Subgroup;
	std::string Name;
	Date Timestamp;
	static std::vector<std::string> names;
	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> distribution;

public:
	Item();
	Item(char group, int subgroup, std::string name, Date timestamp);
	Item(const Item &item);
	~Item();
	bool operator==(const Item&) const;

	char getGroup() const {
		return this->Group;
	}

	int getSubgroup() const {
		return this->Subgroup;
	}

	std::string getName() const {
		return this->Name;
	}

	Date getTimestamp() const {
		return this->Timestamp;
	}
};