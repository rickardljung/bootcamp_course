#include "record.hpp"

Record::Record(std::string _name, std::string _date, service_enum _service):customer_name(_name), date(_date), service(_service) {}

void Record::changePart(std::string part_name, float part_price) {
    this->parts[this->nbr_changed_parts].name = part_name;
    this->parts[this->nbr_changed_parts].price = part_price;
    this->nbr_changed_parts += 1;
}
void Record::pay(payment_method_enum payment, float amount) {
    this->payment.payment_type = payment;
    this->payment.amount = amount;
}
void Record::printRecordData() {
    std::cout << "Customer name: " << this->customer_name << "\nDate of visit: " << this->date << "\nService type: " << service_types[this->service] << std::endl;
    std::cout << "Changed parts: \n";
    if (this->nbr_changed_parts > 0) {
        for(int i = 0; i < this->nbr_changed_parts; i++) {
            std::cout << "    * " << this->parts[i].name << std::endl;
        }
    } else {
        std::cout << "    No parts are change yet!" << std::endl;
    }
    float total_price = this->totPartPrice();
    if (total_price > 0) {
        std::cout << "Total price of parts: " << total_price << std::endl;
    }
    if (this->payment.amount != -1) {
        std::cout << "Payment: \n" << this->payment.amount << " SEK with " << payment_types[this->payment.payment_type] << std::endl;
    } else {
        std::cout << "The customer have not payed yet!!" << std::endl;
    }
    std::cout << std::endl;
}
float Record::totPartPrice() {
    float total_price = 0;
    for(int i = 0; i < this->nbr_changed_parts; i++) {
        total_price += this->parts[i].price;
    }
    return total_price;
}