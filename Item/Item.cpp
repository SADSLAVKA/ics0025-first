#include "Item.h"
#include <fstream>
#include <iostream>
#include <exception>

std::vector<std::string> Item::names = { 
	[] {
		std::fstream birdsFile;
		birdsFile.open("Birds.txt", std::ios::in);
		if (!birdsFile)
		{
			throw std::exception("File 'Birds.txt' wasn't found!");
		}
		std::vector<std::string> names;
		std::string str;
		while (!birdsFile.eof()) {
			birdsFile >> str;
			if (!str.empty())
			{
				names.push_back(std::move(str));
			}
		}
		return names;
	}() 
};

std::default_random_engine Item::generator;
std::uniform_int_distribution<int> Item::distribution;

Item::Item() {
	this->Group = distribution(generator) % 26 + 65;
	this->Subgroup = distribution(generator) % 100;
	this->Name = names[distribution(generator) % names.size()];
	this->Timestamp = Date::CreateRandomDate(Date{ 1, 1, 2021 }, Date{1, 1, 2022});
}

Item::Item(char group, int subgroup, std::string name, Date timestamp) : 
	Group(group), Subgroup(subgroup), Name(name), Timestamp(timestamp) {}

Item::Item(const Item& item) {
	this->Group = item.Group;
	this->Subgroup = item.Subgroup;
	this->Name = item.Name;
	this->Timestamp = item.Timestamp;
}

Item::~Item() {}

bool Item::operator==(const Item& i) const {
	if (Group == i.Group && Subgroup == i.Subgroup && Name == i.Name && Timestamp == i.Timestamp)
	{
		return true;
	} 
	return false;
}