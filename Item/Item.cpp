#include "Item.h"
#include <random>
#include <fstream>
#include <iostream>
#include <exception>
#include <vector>

Item::Item() {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> groupDistribution('A', 'Z');
	this->Group = groupDistribution(generator);
	std::uniform_int_distribution<int> subgroupDistribution(0, 99);
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
	std::uniform_int_distribution<int> nameIndex(0, names.size() - 1);
	this->Name = std::move(names[nameIndex(generator)]);
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