#ifndef VEDOMOSTSEARCHER_H
#define VEDOMOSTSEARCHER_H

#include "SoldierEntry.h"
#include "Vedomost.h"

#include <mongocxx/collection.hpp>
#include <OpenXLSX.hpp>

using namespace OpenXLSX;

class VedomostSearcher {
public:
    VedomostSearcher(const XLWorksheet& passport_worksheet, mongocxx::collection collection)
        : passport_worksheet_(std::move(passport_worksheet)),
            collection_(std::move(collection)),
            res_vedomosti_for_each_soldier_(),
            res_vedomosti_with_much_overlaps()
    {}

    Vedomost Search() {
        Vedomost max_soldiers_vedomost{};
        int pasport_iter_counter{0};
        for (auto& row_soldier_from_passport : passport_worksheet_.rows()) {
            if (pasport_iter_counter++ == 0) continue;
            if (row_soldier_from_passport.findCell(1).value().getString() == "Фамилия") continue;

            SoldierEntry soldier_from_passport = CreateSoldierEntry(row_soldier_from_passport);
            std::cout << "[" << pasport_iter_counter-2 << "] / " << passport_worksheet_.rows().rowCount()-2 <<  std::endl;

            auto opts = mongocxx::options::find{};
            opts.no_cursor_timeout(true);
            opts.batch_size(10);
            auto cursor = collection_.find({}, opts); // Создаем новый курсор для каждого солдата
            for (auto& vedomost: cursor) {
                Vedomost vdmst{vedomost};
                int counter_overlaps_in_one_vedomost{0};
                std::vector<SoldierEntry> soldiers_from_vedomost = vdmst.GetSoldiers();
                for (SoldierEntry& soldier_from_vedomost : soldiers_from_vedomost) {
                    if (soldier_from_passport == soldier_from_vedomost) {
                        AppendVedomostInfoForSoldierFromPassport(soldier_from_passport, vdmst);
                        counter_overlaps_in_one_vedomost++;
                    }
                }
                if (counter_overlaps_in_one_vedomost > 0) {
                    SaveOverlapsCounterForVedomost(vdmst, counter_overlaps_in_one_vedomost);
                }
            }
        }
        PrintVedomostInfoAboutEachSoldierFromVedomost();

        return max_soldiers_vedomost; // возврат названия подходящей ведомости
    }


private:

    void AppendVedomostInfoForSoldierFromPassport(SoldierEntry& soldier_from_passport, Vedomost& vedomost) {
        if (res_vedomosti_for_each_soldier_.contains(soldier_from_passport)) {
            res_vedomosti_for_each_soldier_[soldier_from_passport].push_back(vedomost);
        } else {
            res_vedomosti_for_each_soldier_[soldier_from_passport] = {vedomost};
        }
    }

    void SaveOverlapsCounterForVedomost(Vedomost& vedomost, int counter) {
        res_vedomosti_with_much_overlaps[vedomost] = counter;
    }

    std::pair<Vedomost, int> GetTopVedomostByOverlaps() const {
        Vedomost top_vedomost{};
        int max_overlaps = 0;
        for (auto pair : res_vedomosti_with_much_overlaps) {
            if (pair.second > max_overlaps) {
                max_overlaps = pair.second;
                top_vedomost = pair.first;
            }
        }
        return {top_vedomost, max_overlaps};
    }

    void PrintVedomostInfoAboutEachSoldierFromVedomost() const {
        std::cout << "=============================================\n";
        std::cout << "||                                         ||\n";
        std::cout << "||                                         ||\n";
        std::cout << "||                 Результаты              ||\n";
        std::cout << "||                                         ||\n";
        std::cout << "||                                         ||\n";
        std::cout << "=============================================\n";

        std::pair<Vedomost, int> pair = GetTopVedomostByOverlaps();
        if (!pair.first.IsEmpty()) {
            std::cout << "Ведомость с наибольшим количество совпадений с предложенным паспортом: \n\t";
            std::cout << pair.first.GetContent() << std::endl;

            std::cout << "Найденные солдаты в различных ведомостях\n";
            for (auto& pair : res_vedomosti_for_each_soldier_) {
                std::cout << pair.first.GetInfo() << "\n\t";
                for (auto& vedomost : pair.second) {
                    std::cout << vedomost.GetContent() << "\n\t";
                }
                std::cout << "=============================================\n";
            }
        } else {
            std::cout << "Не найдено ни одного совпадения в ведомостях:" << std::endl;
        }
    }

    SoldierEntry CreateSoldierEntry(XLRow& row_soldier) {
        auto CreateBurialPlace = [](const std::string& region, const std::string& place_in_region) -> std::string {
            return region + ", " + place_in_region;
        };
        return SoldierEntry{
            row_soldier.findCell(1).value().getString(),
            row_soldier.findCell(2).value().getString(),
            row_soldier.findCell(3).value().getString(),
            row_soldier.findCell(4).value().getString(),
            "",
            "",
            "",
            row_soldier.findCell(5).value().getString(),
            "",
            row_soldier.findCell(6).value().getString(),
            CreateBurialPlace(row_soldier.findCell(8).value().getString(), row_soldier.findCell(9).value().getString()),
            "",
            "",
            "",
            "",
            row_soldier.findCell(10).value().getString(),
            ""};
    }

private:
    XLWorksheet passport_worksheet_;
    // mongocxx::cursor cursor_;
    // std::vector<Vedomost> vedomosti_;

    mongocxx::collection collection_;

    unsigned int checked_soldiers_{0};
    std::map<SoldierEntry, std::vector<Vedomost>> res_vedomosti_for_each_soldier_;
    std::map<Vedomost, int> res_vedomosti_with_much_overlaps;
};


/*class VedomostSearcher {
public:
    VedomostSearcher(const XLWorksheet& passport_worksheet, mongocxx::cursor&& cursor)
    : passport_worksheet_(std::move(passport_worksheet)), res_vedomosti_for_each_soldier_()
    {}

    Vedomost Search() {
        Vedomost max_soldiers_vedomost{};
        int max_soldiers_found = 0;
        int iter_counter{0};
        for (auto& row_soldier_from_passport : passport_worksheet_.rows()) {
            if (iter_counter++ == 0) continue;
            if (row_soldier_from_passport.findCell(1).value().getString() == "Фамилия") continue;

            SoldierEntry soldier_from_passport = CreateSoldierEntry(row_soldier_from_passport);
            std::cout << "[" << iter_counter << "]" << soldier_from_passport.GetInfo() << std::endl;
            cursor_ = collection_.find({}); // Создаем новый курсор для каждого солдата
            for (auto& vedomost: cursor_) {
                Vedomost vdmst{vedomost};
                std::vector<SoldierEntry> soldiers_from_vedomost = vdmst.GetSoldiers();
                for (SoldierEntry& soldier_from_vedomost : soldiers_from_vedomost) {
                    if (soldier_from_passport == soldier_from_vedomost) {
                        AppendVedomostInfoForSoldierFromPassport(soldier_from_passport, vdmst);
                    }
                }
            }
        }
        PrintVedomostInfoAboutEachSoldierFromVedomost();


        /*for (auto& vedomost: cursor_) {
            Vedomost vdmst{vedomost};
            int soldiers_found = 0;
            std::vector<SoldierEntry> vedomost_soldiers = vdmst.GetSoldiers();
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
                        "", //CreateBurialPlace(line.findCell(8).value().getString(), line.findCell(9).value().getString()),
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
        }#1#
        // std::cout << "[Checked Soldiers from DB] " << checked_soldiers_ << std::endl;
        return max_soldiers_vedomost; // возврат названия подходящей ведомости
    }

    void AppendVedomostInfoForSoldierFromPassport(SoldierEntry& soldier_from_passport, Vedomost& vedomost) {
        if (res_vedomosti_for_each_soldier_.contains(soldier_from_passport)) {
            res_vedomosti_for_each_soldier_[soldier_from_passport].push_back(vedomost);
        } else {
            res_vedomosti_for_each_soldier_[soldier_from_passport] = {vedomost};
        }
    }

    void PrintVedomostInfoAboutEachSoldierFromVedomost() const {
        for (auto& pair : res_vedomosti_for_each_soldier_) {
            std::cout << pair.first.GetInfo() << ":\n\t\t";
            for (auto& vedomost : pair.second) {
                std::cout << vedomost.GetContent() << "\n\t\t";
            }
        }
    }


    SoldierEntry CreateSoldierEntry(XLRow& row_soldier) {
        auto CreateBurialPlace = [](const std::string& region, const std::string& place_in_region) -> std::string {
            return region + ", " + place_in_region;
        };
        return SoldierEntry{
            row_soldier.findCell(1).value().getString(),
            row_soldier.findCell(2).value().getString(),
            row_soldier.findCell(3).value().getString(),
            row_soldier.findCell(4).value().getString(),
            "",
            "",
            "",
            row_soldier.findCell(5).value().getString(),
            "",
            row_soldier.findCell(6).value().getString(),
            CreateBurialPlace(row_soldier.findCell(8).value().getString(), row_soldier.findCell(9).value().getString()),
            "",
            "",
            "",
            "",
            row_soldier.findCell(10).value().getString(),
            ""};
    }

private:
    XLWorksheet passport_worksheet_;
    // mongocxx::cursor cursor_;
    // std::vector<Vedomost> vedomosti_;

    unsigned int checked_soldiers_{0};
    std::map<SoldierEntry, std::vector<Vedomost>> res_vedomosti_for_each_soldier_;
};*/


#endif //VEDOMOSTSEARCHER_H
