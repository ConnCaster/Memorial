#ifndef REGISTERENTRY_H
#define REGISTERENTRY_H

#include <string>

class RegistryEntry {
public:
    RegistryEntry(
            const std::string& last_name,
            const std::string& first_name,
            const std::string& patronymic,
            const std::string& birthdate,
            const std::string& birth_place,
            const std::string& conscription_date_and_place,
            const std::string& last_duty_place,
            const std::string& military_rank,
            const std::string& loss_reason,
            const std::string& loss_date,
            const std::string& burial_place,
            const std::string& report_source,
            const std::string& source_fund_number,
            const std::string& source_inventory_number,
            const std::string& source_case_number,
            const std::string& link,
            const std::string& file
        ) : last_name_(last_name),
            first_name_(first_name),
            patronymic_(patronymic),
            birthdate_(birthdate),
            birth_place_(birth_place),
            conscription_date_and_place_(conscription_date_and_place),
            last_duty_place_(last_duty_place),
            military_rank_(military_rank),
            loss_reason_(loss_reason),
            loss_date_(loss_date),
            burial_place_(burial_place),
            report_source_(report_source),
            source_fund_number_(source_fund_number),
            source_inventory_number_(source_inventory_number),
            source_case_number_(source_case_number),
            link_(link),
            file_(file) {}



private:
    std::string last_name_;
    std::string first_name_;
    std::string patronymic_;
    std::string birthdate_;
    std::string birth_place_;
    std::string conscription_date_and_place_;
    std::string last_duty_place_;
    std::string military_rank_;
    std::string loss_reason_;
    std::string loss_date_;
    std::string burial_place_;
    std::string report_source_;
    std::string source_fund_number_;
    std::string source_inventory_number_;
    std::string source_case_number_;
    std::string link_;
    std::string file_;
};

#endif //REGISTERENTRY_H
