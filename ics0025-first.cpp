#include <iostream>
#include "Data/Data.h"

using namespace std;

int main()
{
    Data data = Data(400);
    Item *ptr_item = new Item('A', 11, "Glados", Date::CreateRandomDate(Date{ 1, 1, 2021 }, Date{ 1, 1, 2022 }));
    Item *item2 = new Item('A', 11, "Xcom", Date::CreateRandomDate(Date{ 1, 1, 2021 }, Date{ 1, 1, 2022 }));
    data.PrintAll();
    cout << data.CountItems() << endl;
    try {
        data.PrintGroup('a');
        data.InsertSubgroup('a', 11, { ptr_item, item2 });
        cout << "Count of group 'A': " << data.CountGroupItems('A') << endl;
        cout << "Printing subgroup by names: \n";
        data.PrintSubgroupByNames('a', 11);
        cout << "Printing subgroup by dates: \n";
        data.PrintSubgroupByDates('a', 11);
        cout << "Number of items in subgroup A10: " << data.CountSubgroupItems('a', 11) << "\n";
        cout << "Attempting to find item: ";
        data.PrintItem('a', 11, "Glados");
    }
    catch (...) {

    }
    return 0;
}
