#include <iostream>
#include "Date/Date.h"
#include "Item/Item.h"
#include "Data/Data.h"

int main()
{
    std::cout << "Hello World!\n";
    Date date = Date();
    Item item = Item();
    Data data = Data(10);
    Item *ptr_item = data.InsertItem('A', 13, "Glados", Date::CreateRandomDate(Date{ 1, 1, 2021 }, Date{ 1, 1, 2022 }));
    data.PrintAll();
    return 0;
}
