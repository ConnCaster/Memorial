#ifndef VEDOMOSTSEARCHER_H
#define VEDOMOSTSEARCHER_H

#include "SoldierEntry.h"
#include "Vedomost.h"

#include <mongocxx/collection.hpp>
#include <OpenXLSX.hpp>

using namespace OpenXLSX;

class VedomostSearcher {
public:
    VedomostSearcher(const XLWorksheet& passport_worksheet, mongocxx::cursor&& cursor)
        : passport_worksheet_(std::move(passport_worksheet)), cursor_(std::move(cursor))
    {}

    Vedomost Search() {
        auto CreateBurialPlace = [](const std::string& region, const std::string& place_in_region) -> std::string {
            return region + ", " + place_in_region;
        };
        Vedomost max_soldiers_vedomost{};
        int max_soldiers_found = 0;
        for (auto& vedomost: cursor_) {
            Vedomost vdmst{vedomost};
            int soldiers_found = 0;
            std::vector<SoldierEntry> vedomost_soldiers = vdmst.GetSoldierd();
            for (const SoldierEntry& vedomost_soldier : vedomost_soldiers) {
                checked_soldiers_++;
                for (auto& line : passport_worksheet_.rows()) {
                    if (line.findCell(1).value().getString() == "Фамилия") continue;
                    SoldierEntry passport_soldier{
                        line.findCell(1).value().getString(),
                        line.findCell(2).value().getString(),
                        line.findCell(3).value().getString(),
                        line.findCell(4).value().getString(),
                        "",
                        "",
                        "",
                        line.findCell(5).value().getString(),
                        "",
                        line.findCell(6).value().getString(),
                        CreateBurialPlace(line.findCell(8).value().getString(), line.findCell(9).value().getString()),
                        "",
                        "",
                        "",
                        "",
                        line.findCell(10).value().getString(),
                        ""};
                    std::cout << passport_soldier.GetInfo() << std::endl;
                    if (vedomost_soldier == passport_soldier) {
                        soldiers_found++;
                    }
                }
                if (soldiers_found > max_soldiers_found) {
                    max_soldiers_vedomost = vdmst;
                    max_soldiers_found = soldiers_found;
                }
            }
        }
        std::cout << "[Checked Soldiers from DB] " << checked_soldiers_ << std::endl;
        return max_soldiers_vedomost; // возврат названия подходящей ведомости
    }

private:
    XLWorksheet passport_worksheet_;
    mongocxx::cursor cursor_;

    unsigned int checked_soldiers_{0};
};


#endif //VEDOMOSTSEARCHER_H
