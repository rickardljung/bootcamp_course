#include "workshop_system.hpp"

void Workshop::addRecord(std::string customer_name, std::string date, service_enum service_type) {
    Record* record = new Record(customer_name, date, service_type);
    this->records->add(record, 0);
}

void Workshop::printRecords() {
    LinkedList *list = this->records;
    int i = 0;
    void* object = list->getObject(0);
    while(object != nullptr) {
        Record* record = static_cast<Record*>(object);
        record->printRecordData();
        i++;
        object = list->getObject(i);
    }
}

Workshop::Workshop() {
    this->records = new LinkedList();
}

Workshop::~Workshop() {
    LinkedList *list = this->records;
    int i = 0;
    void* object = list->getObject(0);
    while(object != nullptr) {
        Record* record = static_cast<Record*>(object);
        delete record;
        i++;
        object = list->getObject(i);
    }
    delete list;
}