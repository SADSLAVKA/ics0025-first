#include <iostream>
#include "Date/Date.h"
#include "Item/Item.h"
#include "Data/Data.h"

using namespace std;

int main()
{
    Data data = Data(200);
    Item *ptr_item = data.InsertItem('A', 13, "Glados", Date::CreateRandomDate(Date{ 1, 1, 2021 }, Date{ 1, 1, 2022 }));
    data.PrintAll();
    cout << data.CountItems() << endl;
    try {
        data.PrintGroup('a');
    }
    catch (...) {

    }
    cout << data.CountGroupItems('a') << endl;
    cout << data.GetSubgroup('a', 9) << endl;
    return 0;
}
