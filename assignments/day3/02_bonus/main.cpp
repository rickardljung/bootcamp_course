#include "linked_list.hpp"
#include "record.hpp"
#include "workshop_system.hpp"

int main () {

    Workshop* shop = new Workshop();
    shop->addRecord("Rickard Ljung", "20201021", service_enum::TireChange);
    shop->addRecord("Goran", "20191224", service_enum::WindScreenChange);

    std::cout << "hejhej" << std::endl;

    shop->printRecords();

    /*
    Record *record = new Record("Rickard Ljung", "20201021", service_enum::TireChange);
    record->changePart("Tire", 40);
    record->changePart("SW upgrade", 626.66);
    record->pay(payment_method_enum::Swish, 13.37);

    LinkedList list;
    list.add(record, 0);
    list.add(new Record("Goran", "20191224", service_enum::WindScreenChange), 0);

    int i = 0;
    void* object = list.getObject(0);
    while(object != nullptr) {
        Record* record = static_cast<Record*>(object);
        record->printRecordData();
        i++;
        object = list.getObject(i);
    }
*/
}