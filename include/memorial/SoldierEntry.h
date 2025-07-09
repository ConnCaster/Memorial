#ifndef SOLDIERENTRY_H
#define SOLDIERENTRY_H

#include <string>
#include <locale>
#include <codecvt>
#include <bsoncxx/builder/basic/document.hpp>

class SoldierEntry {
public:
    SoldierEntry(
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
            source_case_number_(source_case_number)
    {}

    SoldierEntry(const bsoncxx::array::element& soldier) {
        try {
            if (soldier["last_name"] && soldier["last_name"].type() == bsoncxx::type::k_string) {
                last_name_ = soldier["last_name"].get_string().value;
            }
            if (soldier["first_name"] && soldier["first_name"].type() == bsoncxx::type::k_string) {
                first_name_ = soldier["first_name"].get_string().value;
            }
            if (soldier["patronymic"] && soldier["patronymic"].type() == bsoncxx::type::k_string) {
                patronymic_ = soldier["patronymic"].get_string().value;
            }
            if (soldier["birthdate"] && soldier["birthdate"].type() == bsoncxx::type::k_string) {
                birthdate_ = soldier["birthdate"].get_string().value;
            }
            if (soldier["birth_place"] && soldier["birth_place"].type() == bsoncxx::type::k_string) {
                birth_place_ = soldier["birth_place"].get_string().value;
            }
            if (soldier["conscription_date_and_place"] && soldier["conscription_date_and_place"].type() == bsoncxx::type::k_string) {
                conscription_date_and_place_ = soldier["conscription_date_and_place"].get_string().value;
            }
            if (soldier["last_duty_place"] && soldier["last_duty_place"].type() == bsoncxx::type::k_string) {
                last_duty_place_ = soldier["last_duty_place"].get_string().value;
            }
            if (soldier["military_rank"] && soldier["military_rank"].type() == bsoncxx::type::k_string) {
                military_rank_ = soldier["military_rank"].get_string().value;
            }
            if (soldier["loss_reason"] && soldier["loss_reason"].type() == bsoncxx::type::k_string) {
                loss_reason_ = soldier["loss_reason"].get_string().value;
            }
            if (soldier["loss_date"] && soldier["loss_date"].type() == bsoncxx::type::k_string) {
                loss_date_ = soldier["loss_date"].get_string().value;
            }
            if (soldier["burial_place"] && soldier["burial_place"].type() == bsoncxx::type::k_string) {
                burial_place_ = soldier["burial_place"].get_string().value;
            }
            if (soldier["report_source"] && soldier["report_source"].type() == bsoncxx::type::k_string) {
                report_source_ = soldier["report_source"].get_string().value;
            }
            if (soldier["source_fund_number"] && soldier["source_fund_number"].type() == bsoncxx::type::k_int32) {
                source_fund_number_ = soldier["source_fund_number"].get_int32().value;
            }
            if (soldier["source_inventory_number"] && soldier["source_inventory_number"].type() == bsoncxx::type::k_int32) {
                source_inventory_number_ = soldier["source_inventory_number"].get_int32().value;
            }
            if (soldier["source_case_number"] && soldier["source_case_number"].type() == bsoncxx::type::k_int32) {
                source_case_number_ = soldier["source_case_number"].get_int32().value;
            }
        } catch (const std::exception& ex) {
            std::cout << "[ERROR] Error parsing bson soldier: " << ex.what() << std::endl;
            throw;
        } catch (...) {
            std::cout << "[ERROR] Error parsing bson soldier" << std::endl;
            throw;
        }
    }

    std::string GetInfo() const {
        // TODO: Доделать при необходимости
        std::string info = "\tФамилия: " + last_name_ +
                           "\n\tИмя: " + first_name_ +
                           "\n\tОтчество: " + patronymic_ +
                           "\n\tМесто захоронения: " + burial_place_ + "\n===========================\n";
        return info;
    }

    friend bool operator==(const SoldierEntry &l, const SoldierEntry &r);

#ifdef BUILD_GOOGLE_TEST
public:
#else
private:
#endif
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
    std::string link_{};   // TODO: добавить в БД, если нужно
    std::string file_{};   // TODO: добавить в БД, если нужно
};

namespace compare_utils {

    void StrToLower(std::string& str) {
        std::for_each(str.begin(), str.end(), [](char c){ return tolower(c); });
    }

    std::string StrToLower(const std::string& str) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        std::wstring wide_str = conv.from_bytes(str);

        std::locale loc("ru_RU.UTF-8");  // Локаль для кириллицы
        for (wchar_t& c : wide_str) {
            c = std::tolower(c, loc);
        }
        return conv.to_bytes(wide_str);
    }

    std::string Strip(const std::string& str) {
        if (str.empty()) {
            return str;
        }

        size_t start = 0;
        while (start < str.size() && (std::isspace(str[start]) || std::ispunct(str[start]))) {
            ++start;
        }

        if (start == str.size()) {
            return "";
        }

        size_t end = str.size() - 1;
        while (end > start && (std::isspace(str[end]) || std::ispunct(str[end]))) {
            --end;
        }

        return str.substr(start, end - start + 1);
    }

    size_t utf8_strlen(const std::string& str) {
        setlocale(LC_ALL, "en_US.utf8");  // Устанавливаем локаль для UTF-8

        size_t char_count = 0;
        mbstate_t state = {};
        const char* ptr = str.c_str();
        const char* end = ptr + str.size();

        while (ptr < end) {
            size_t len = mbrlen(ptr, end - ptr, &state);
            if (len == (size_t)-1 || len == (size_t)-2) {
                // Некорректный UTF-8 символ
                break;
            }
            ptr += len;
            char_count++;
        }

        return char_count;
    }

    // ===================================================================
    bool CompareLastName(const std::string& l, const std::string& r) {
        std::string left = StrToLower(l);
        std::string right = StrToLower(r);
        if (left == "null" || right == "null") return false;
        return left == right;
    }

    bool CompareFirstName(const std::string& l, const std::string& r) {
        std::string left = StrToLower(l);
        std::string right = StrToLower(r);
        if (left == "null" || right == "null") return false;
        if (utf8_strlen(left) == 1 || utf8_strlen(right) == 1) {
            return left[0] == right[0];
        }
        return left == right;
    }

    bool ComparePatronimic(const std::string& l, const std::string& r) {
        std::string left = StrToLower(l);
        std::string right = StrToLower(r);
        if (left == "null" || right == "null") return true;
        if (utf8_strlen(left) == 1 || utf8_strlen(right) == 1) {
            return left[0] == right[0];
        }
        return left == right;
    }

    bool CompareBirthdate(const std::string& l, const std::string& r) {
        // TODO: парсить год, месяц, день
        std::string left = StrToLower(l);
        std::string right = StrToLower(r);
        if (left == "null" || right == "null") return true;
        if (left == "/Возраст" || right == "/Возраст") return true;
        return left == right;
    }

}

bool operator==(const SoldierEntry &l, const SoldierEntry &r) {
    return compare_utils::CompareLastName(compare_utils::Strip(l.last_name_), compare_utils::Strip(r.last_name_)) &&
            compare_utils::CompareFirstName(compare_utils::Strip(l.first_name_), compare_utils::Strip(r.first_name_)) &&
            compare_utils::ComparePatronimic(compare_utils::Strip(l.patronymic_), compare_utils::Strip(r.patronymic_)) &&
            compare_utils::CompareBirthdate(l.birthdate_, r.birthdate_);  // TODO: пропускать при false
}

#endif //SOLDIERENTRY_H
