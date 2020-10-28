#include "record.hpp"
#include "linked_list.hpp"

class Workshop {
    private:
        LinkedList records;
    public:
        Workshop() = default;
        ~Workshop();
        void addRecord(std::string customer_name, std::string date, service_enum service_type);
        void printRecords();
};