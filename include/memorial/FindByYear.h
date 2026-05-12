#ifndef MEMORIAL_FINDBYYEAR_H
#define MEMORIAL_FINDBYYEAR_H

#include <unordered_set>

#include "Vedomost.h"

class FindInAllVedomosty {
public:
    FindInAllVedomosty(mongocxx::collection& vedomosti_collection, const std::vector<int>& years)
        : vedomosti_collection_(vedomosti_collection), years_{years.begin(), years.end()}
    {}

    void Find() {
        auto opts = mongocxx::options::find{};
        opts.no_cursor_timeout(true);
        opts.batch_size(10);
        auto cursor = vedomosti_collection_.find({}, opts);
        for (auto& vedomost: cursor) {
            Vedomost vdmst{vedomost};
            std::vector<SoldierEntry> soldiers_from_vedomost = vdmst.GetSoldiers();

            // Фильтрация в C++
            std::vector<SoldierEntry> filtered_soldiers;

            for (const auto& soldier : soldiers_from_vedomost) {
                int year = soldier.GetYear();
                if (years_.contains((year))) {
                    filtered_soldiers.push_back(soldier);
                    std::cout << soldier.GetInfo() << std::endl;
                }
            }
        }
    }

private:
    mongocxx::collection vedomosti_collection_;
    std::unordered_set<int> years_;
};

std::vector<int> ParseYearsFromArg(const std::string& arg) {
    if (arg.empty()) {
        return {};
    }

    std::vector<int> years;
    std::stringstream ss(arg);
    std::string token;

    while (std::getline(ss, token, ',')) {
        // 1. Удаляем пробелы по краям
        const auto start = token.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) {
            continue; // Пропускаем пустые токены (например, при "1943, , 1945")
        }
        const auto end = token.find_last_not_of(" \t\r\n");
        std::string trimmed = token.substr(start, end - start + 1);

        // 2. Преобразуем в число
        try {
            size_t pos = 0;
            int year = std::stoi(trimmed, &pos);

            // Убеждаемся, что в строке были только цифры (нет мусора вроде "1943x")
            if (pos != trimmed.length()) {
                throw std::invalid_argument("Неверный формат года: " + trimmed);
            }

            // 3. Проверяем диапазон [1939, 1946]
            if (year < 1939 || year > 1946) {
                throw std::out_of_range("Год вне допустимого диапазона [1939, 1946]: " + trimmed);
            }

            years.push_back(year);
        }
        catch (const std::invalid_argument&) {
            throw std::invalid_argument("Не удалось распознать год: " + trimmed);
        }
        catch (const std::out_of_range&) {
            throw std::out_of_range("Год вне допустимого диапазона [1939, 1946]: " + trimmed);
        }
    }

    return years;
}

#endif //MEMORIAL_FINDBYYEAR_H
