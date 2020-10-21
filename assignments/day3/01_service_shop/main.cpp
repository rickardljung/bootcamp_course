#include "record.hpp"

int main() {
    Record record("Rickard Ljung", "20201021", service_enum::TireChange);

    record.printRecordData();
    record.changePart("Tire", 40);
    record.changePart("SW upgrade", 626.66);
    record.printRecordData();

    record.pay(payment_method_enum::Swish, 13.37);
    record.printRecordData();
}