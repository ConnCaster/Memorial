#ifndef REGISTERENTRY_H
#define REGISTERENTRY_H

#include <string>

class RegistryEntry {
public:
    RegistryEntry(
            const std::string& last_name,
            const std::string& first_name,
            const std::string& second_name,
            const std::string& birthday,
            const std::string& birth_place,
            const std::string& date_and_place_conscription,
            const std::string& last_duty_place,
            const std::string& military_rank,
            const std::string& reason_of_leaving,
            const std::string& date_of_leaving,
            const std::string& primary_burial_side,
            const std::string& info_source,
            const std::string& fond_number,
            const std::string& inventory_number,
            const std::string& case_number,
            const std::string& link,
            const std::string& file
        ) : last_name_(last_name),
            first_name_(first_name),
            second_name_(second_name),
            birthday_(birthday),
            birth_place_(birth_place),
            date_and_place_conscription_(date_and_place_conscription),
            last_duty_place_(last_duty_place),
            military_rank_(military_rank),
            reason_of_leaving_(reason_of_leaving),
            date_of_leaving_(date_of_leaving),
            primary_burial_side_(primary_burial_side),
            info_source_(info_source),
            fond_number_(fond_number),
            inventory_number_(inventory_number),
            case_number_(case_number),
            link_(link),
            file_(file) {}



private:
    std::string last_name_;
    std::string first_name_;
    std::string second_name_;
    std::string birthday_;
    std::string birth_place_;
    std::string date_and_place_conscription_;
    std::string last_duty_place_;
    std::string military_rank_;
    std::string reason_of_leaving_;
    std::string date_of_leaving_;
    std::string primary_burial_side_;
    std::string info_source_;
    std::string fond_number_;
    std::string inventory_number_;
    std::string case_number_;
    std::string link_;
    std::string file_;
};

#endif //REGISTERENTRY_H
