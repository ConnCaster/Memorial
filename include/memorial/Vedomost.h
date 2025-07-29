#ifndef VEDOMOST_H
#define VEDOMOST_H

#include <iostream>
#include <vector>
#include <bsoncxx/builder/basic/document.hpp>

#include "memorial/SoldierEntry.h"

class Vedomost {
public:
    Vedomost() = default;
    Vedomost(const bsoncxx::v_noabi::document::view& vedomost) {
        try {
            if (vedomost["report_number"] && vedomost["report_number"].type() == bsoncxx::type::k_string) {
                report_number_ = vedomost["report_number"].get_string().value;
            }
            if (vedomost["report_date"] && vedomost["report_date"].type() == bsoncxx::type::k_string) {
                report_date_ = vedomost["report_date"].get_string().value;
            }
            if (vedomost["report_source"] && vedomost["report_source"].type() == bsoncxx::type::k_string) {
                report_source_ = vedomost["report_source"].get_string().value;
            }
            if (vedomost["soldiers"] && vedomost["soldiers"].type() == bsoncxx::type::k_array) {
                for (auto& soldier : vedomost["soldiers"].get_array().value) {
                    try {
                        soldiers_.emplace_back(soldier);
                    } catch (...) {}
                }
            }
        } catch (const std::exception& ex) {
            std::cout << "[ERROR] Error parsing bson vedomost: " << ex.what() << std::endl;
            throw;
        } catch (...) {
            std::cout << "[ERROR] Error parsing bson vedomost" << std::endl;
            throw;
        }
    };

    bool IsEmpty() const {
        return report_number_ == "" && report_date_ == "";
    }

    std::string GetContent() const {
        std::string content = \
                "Ведомость № " + report_number_ + "\n\t" +
                "Дата: " + report_date_ + "\n\t" +
                "Подразделение: " + report_source_ + "\n";
                /*"Список: \n\n";
        for (const SoldierEntry& soldier : soldiers_) {
            content += soldier.GetInfo() + "\n";
        }*/
        return content;
    }

    std::vector<SoldierEntry>& GetSoldiers() {
        return soldiers_;
    }

    friend bool operator<(const Vedomost &l, const Vedomost &r);

private:
    std::string report_number_;
    std::string report_date_;
    std::string report_source_;
    std::vector<SoldierEntry> soldiers_;
};

bool operator<(const Vedomost &l, const Vedomost &r) {
    if (l.report_number_ != r.report_number_) {
        return l.report_number_ < r.report_number_;
    }
    if (l.report_date_ != r.report_date_) {
        return l.report_date_ < r.report_date_;
    }
    return l.report_source_ < r.report_source_;
}

#endif //VEDOMOST_H
