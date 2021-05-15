#include <iostream>
#include "Data/Data.h"

using namespace std;

int main()
{
    Data data = Data(400);
    Item *ptr_item = data.InsertItem('A', 10, "Glados", Date::CreateRandomDate(Date{ 1, 1, 2021 }, Date{ 1, 1, 2022 }));
    Item *item2 = data.InsertItem('A', 10, "Xcom", Date::CreateRandomDate(Date{ 1, 1, 2021 }, Date{ 1, 1, 2022 }));
    data.PrintAll();
    cout << data.CountItems() << endl;
    try {
        data.PrintGroup('a');
    }
    catch (...) {

    }
    cout << "Count of group 'A': " << data.CountGroupItems('A') << endl;
    cout << "Printing subgroup by names: \n";
    data.PrintSubgroupByNames('a', 10);
    cout << "Printing subgroup by dates: \n";
    data.PrintSubgroupByDates('a', 10);
    cout << "Number of items in subgroup A10: " << data.CountSubgroupItems('a', 10) << "\n";
    cout << "Attempting to find item: ";
    data.PrintItem('a', 10, "Glados");
    return 0;
}
