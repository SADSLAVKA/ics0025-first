#include <iostream>
#include "Data/Data.h"

using namespace std;

int main()
{
    Date date1 { 10, 12, 2021 };
    Date date2 { 10, 12, 2021 };
    Data data = Data(298);
    // Manually 2 items to guarantee 2 items in the same subgroup.
    Item* ptr_item1 = data.InsertItem('a', 10, "Glados", Date::CreateRandomDate(date1, date2));
    Item* ptr_item2 = data.InsertItem('a', 10, "Xcom", Date::CreateRandomDate(date1, date2)); 
    // Test case 1: Printing and counting
    cout << "==========Test case 1==========\n";
    data.PrintAll();
    cout << "\n";
    cout << "Total number of items: " << data.CountItems() << "\n";
    cout << "==========Test case 2==========\n";
    // Test case 2: Selecting a group (here 'A'), printing and counting it
    data.PrintGroup('a');
    cout << "Number of items in group 'A': " << data.CountGroupItems('a') << "\n";
    cout << "==========Test case 3==========\n";
    // Test case 3: Selecting a subgroup with 2 items (here A10), printing it by dates and names and counting
    cout << "Printing subgroup A10 by names: \n";
    data.PrintSubgroupByNames('a', 10);
    cout << "Printing subgroup A10 by dates: \n";
    data.PrintSubgroupByDates('a', 10);
    cout << "Total number of in subgroup 'A10': " << data.CountSubgroupItems('a', 10) << "\n";
    cout << "==========Test case 4==========\n";
    // Test case 4: Selecting a subgroup with just 1 item (here A16)
    cout << "Printing subgroup A16 by names: \n";
    data.PrintSubgroupByNames('a', 16);
    cout << "Printing subgroup A16 by dates: \n";
    data.PrintSubgroupByDates('a', 16);
    cout << "Total number of in subgroup 'A16': " << data.CountSubgroupItems('a', 16) << "\n";
    cout << "==========Test case 5==========\n";
    // Test case 5: Selecting a non-existing subgroup (here A1000)
    try
    {
        cout << "Printing subgroup A1000 by names: \n";
        data.PrintSubgroupByNames('a', 1000);
        cout << "Printing subgroup A1000 by dates: \n";
        data.PrintSubgroupByDates('a', 1000);
        cout << "Total number of in subgroup 'A1000': " << data.CountSubgroupItems('a', 1000) << "\n";
        cout << "=====================\n";
    }
    catch (const std::invalid_argument& e)
    {
        cout << "Exception cought! " << e.what() << "\n";
        cout << "==========Test case 6==========\n";
    }
    // Test case 6: Printing an existing and non existing item
    cout << "Existing item: ";
    data.PrintItem('a', 10, "Glados");
    try
    {
        data.PrintItem('Z', 99, "DFasafa");
    }
    catch (const std::invalid_argument& e)
    {
        cout << "Exception cought! " << e.what() << "\n";
        cout << "==========Test case 7==========\n";
    }
    // Test case 7: New object containing 30 items and printing it
    Data data1 { 30 };
    data1.PrintAll();
    cout << "==========Test case 8==========\n";
    // Test case 8: Printing and conting non-existing group (here O)
    try
    {
        data1.PrintGroup('o');
    }
    catch (const std::invalid_argument& e)
    {
        cout << "Exception cought! " << e.what() << "\n";
    }
    cout << "Number of items in group 'O': " << data1.CountGroupItems('o');
    cout << "==========Test case 9==========\n";
    // Test case 9: Testing InsertItem
    data1.InsertItem('a', 57, "New item with existing group and subgroup", Date::CreateRandomDate(date1, date2));
    data1.InsertItem('a', 99, "New item with existing group", Date::CreateRandomDate(date1, date2));
    data1.InsertItem('o', 99, "New item with non-existing group", Date::CreateRandomDate(date1, date2));
    data1.InsertItem('o', 99, "New item with non-existing group", Date::CreateRandomDate(date1, date2));
    data1.PrintAll();
    cout << "==========Test case 10==========\n";
    // Test case 10: Testing InsertSubgroup
    data1.InsertSubgroup('o', 98, { new Item(), new Item() }); // group exists
    data1.InsertSubgroup('q', 99, { new Item(), new Item() }); // group doesn't exist
    data1.InsertSubgroup('o', 98, { new Item(), new Item() }); // subgroup already exists
    data1.PrintAll();
    cout << "==========Test case 11==========\n";
    // Test case 11: Testing InsertSubgroup
    data1.RemoveGroup('o');
    data1.InsertGroup('o', { 10, 98 }, { {new Item()}, {new Item(), new Item()} }); // new group
    data1.InsertGroup('o', { 10, 98 }, { {new Item()}, {new Item(), new Item()} }); // already existing group
    data1.PrintAll();
    cout << "==========Test case 12==========\n";
    // Test case 12: New object containing 100 items
    Data data2 { 100 };
    data2.PrintAll();
    cout << "==========Test case 13==========\n";
    // Test case 13: Testing RemoveItem
    data2.InsertItem('y', 22, "New item for test", Date::CreateRandomDate(date1, date2));
    data2.RemoveItem('y', 22, "New item for test"); // subgroup Y22 is kept
    data2.RemoveItem('y', 22, "Hermit"); // subgroup Y22 disappears
    data2.RemoveItem('r', 43, "Stork");
    data2.RemoveItem('r', 52, "Oriole"); // group R disappears
    data2.RemoveItem('r', 52, "Oriole"); // doesn't exist
    data2.PrintAll();
    cout << "==========Test case 14==========\n";
    // Test case 14: Testing RemoveSubgroup
    data2.RemoveSubgroup('p', 5); // group p is kept
    data2.RemoveSubgroup('u', 67);
    data2.RemoveSubgroup('u', 70); // group u disappears
    data2.RemoveSubgroup('u', 70); // doesn't exist
    data2.PrintAll();
    cout << "==========Test case 15==========\n";
    // Test case 15: Testing RemoveGroup
    data2.RemoveGroup('b'); // group b disappears
    data2.RemoveGroup('1'); // group doesn't exist
    data2.PrintAll();
    cout << "=====================\n";
    return 0;
}
