#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>

const std::string service_types[3] = {"TireChange", "WindScreenChange", "YearlyService"};
enum service_enum {TireChange, WindScreenChange, YearlyService};
typedef struct struct_part{
    std::string name = "";
    float price;
} part_struct;
const std::string payment_types[3] = {"Cash", "Card", "Swish"};
enum payment_method_enum {Cash, Card, Swish};
typedef struct struct_payment{
    payment_method_enum payment_type;
    float amount = -1;
} payment_struct;

class Record {
    private:
        std::string customer_name, date;
        service_enum service;
        part_struct parts[10]; //?? object with parts?
        payment_struct payment;
        unsigned int nbr_changed_parts = 0;
    public:
        Record() = delete;
        Record(std::string _name, std::string _date, service_enum _service);
        void changePart(std::string part_name, float part_price);
        void pay(payment_method_enum payment, float amount);
        void printRecordData();
        float totPartPrice();
};

#endif