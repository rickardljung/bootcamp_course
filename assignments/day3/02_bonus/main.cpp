#include "linked_list.hpp"
#include "record.hpp"

int main () {
    Record *record = new Record("Rickard Ljung", "20201021", service_enum::TireChange);
    record->changePart("Tire", 40);
    record->changePart("SW upgrade", 626.66);
    record->pay(payment_method_enum::Swish, 13.37);

    LinkedList list;
    list.add(record, 0);
    list.add(new Record("Goran", "20191224", service_enum::WindScreenChange), 0);

    record = static_cast<Record*>(list.getObject(0));
    record->printRecordData();
    record = static_cast<Record*>(list.getObject(1));
    record->printRecordData();

    record = static_cast<Record*>(list.getObject(0));
    //list.remove(0);
    delete record;
    record = static_cast<Record*>(list.getObject(1)); //list.getObject(0)
    //list.remove(0);
    delete record;
}