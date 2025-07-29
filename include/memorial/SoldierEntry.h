#ifndef SOLDIERENTRY_H
#define SOLDIERENTRY_H

#include <string>
#include <locale>
#include <codecvt>
#include <numeric>
#include <bsoncxx/builder/basic/document.hpp>

class SoldierEntry {
public:
    SoldierEntry() = default;
    SoldierEntry(
        const std::string &last_name,
        const std::string &first_name,
        const std::string &patronymic,
        const std::string &birthdate,
        const std::string &birth_place,
        const std::string &conscription_date_and_place,
        const std::string &last_duty_place,
        const std::string &military_rank,
        const std::string &loss_reason,
        const std::string &loss_date,
        const std::string &burial_place,
        const std::string &report_source,
        const std::string &source_fund_number,
        const std::string &source_inventory_number,
        const std::string &source_case_number,
        const std::string &link,
        const std::string &file
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
        source_case_number_(source_case_number) {
    }

    SoldierEntry(const bsoncxx::array::element &soldier) {
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
            if (soldier["conscription_date_and_place"] && soldier["conscription_date_and_place"].type() ==
                bsoncxx::type::k_string) {
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
            if (soldier["source_inventory_number"] && soldier["source_inventory_number"].type() ==
                bsoncxx::type::k_int32) {
                source_inventory_number_ = soldier["source_inventory_number"].get_int32().value;
            }
            if (soldier["source_case_number"] && soldier["source_case_number"].type() == bsoncxx::type::k_int32) {
                source_case_number_ = soldier["source_case_number"].get_int32().value;
            }
        } catch (const std::exception &ex) {
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
                           "\n\tМесто захоронения: " + burial_place_ + "\n";
        return info;
    }

    friend bool operator==(const SoldierEntry &l, const SoldierEntry &r);
    friend bool operator<(const SoldierEntry &l, const SoldierEntry &r);

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
    std::string link_{}; // TODO: добавить в БД, если нужно
    std::string file_{}; // TODO: добавить в БД, если нужно
};

namespace compare_utils {
    void StrToLower(std::string &str) {
        std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
        std::wstring wide_str = conv.from_bytes(str);

        std::locale loc("ru_RU.UTF-8"); // Локаль для кириллицы
        for (wchar_t &c: wide_str) {
            c = std::tolower(c, loc);
        }
        str = conv.to_bytes(wide_str);
    }

    std::string StrToLower(const std::string &str) {
        std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
        std::wstring wide_str = conv.from_bytes(str);

        std::locale loc("ru_RU.UTF-8"); // Локаль для кириллицы
        for (wchar_t &c: wide_str) {
            c = std::tolower(c, loc);
        }
        return conv.to_bytes(wide_str);
    }

    std::string Strip(const std::string &str) {
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

    size_t UTF8_Strlen(const std::string &str) {
        setlocale(LC_ALL, "en_US.utf8"); // Устанавливаем локаль для UTF-8

        size_t char_count = 0;
        mbstate_t state = {};
        const char *ptr = str.c_str();
        const char *end = ptr + str.size();

        while (ptr < end) {
            size_t len = mbrlen(ptr, end - ptr, &state);
            if (len == (size_t) -1 || len == (size_t) -2) {
                // Некорректный UTF-8 символ
                break;
            }
            ptr += len;
            char_count++;
        }

        return char_count;
    }

    // TODO: покрытие unit-тестами
    void StripByUnderLine(std::string &str) {
        if (str.empty()) {
            return;
        }

        size_t start = 0;
        while (start < str.size() && (str[start] == '_')) {
            ++start;
        }

        if (start == str.size()) {
            return;
        }

        size_t end = str.size() - 1;
        // size_t end = UTF8_Strlen(str) - 1;
        while (end > start && (str[start] == '_')) {
            --end;
        }

        str = str.substr(start, end - start + 1);
    }


    // TODO: покрытие unit-тестами
    std::string RemoveSpaces(const std::string &str) {
        std::string str_to_remove_spaces{str};
        auto new_end = str_to_remove_spaces.erase(
            std::remove(str_to_remove_spaces.begin(), str_to_remove_spaces.end(), ' '), str_to_remove_spaces.end());
        return {str_to_remove_spaces.begin(), new_end};
    }

    // TODO: покрытие unit-тестами
    std::string ReplaceSpaces(const std::string &str, char c) {
        std::string str_to_replace_spaces{str};
        std::replace_if(str_to_replace_spaces.begin(), str_to_replace_spaces.end(), [](char c) {
            return c == ' ';
        }, c);
        return str_to_replace_spaces;
    }

    // TODO: покрытие unit-тестами
    std::vector<std::string> Split(const std::string &str, const std::string &delimeters) {
        std::vector<std::string> parts;
        size_t start = 0;
        size_t end = str.find_first_of(delimeters);

        while (end != std::string::npos) {
            parts.push_back(str.substr(start, end - start));
            start = end + 1;
            end = str.find_first_of(delimeters, start);
        }
        parts.push_back(str.substr(start));
        return parts;
    }

    // ===================================================================
    bool CompareLastName(const std::string &l, const std::string &r) {
        std::string left = StrToLower(l);
        std::string right = StrToLower(r);
        if (left == "null" || right == "null") return false;
        return left == right;
    }

    bool CompareFirstName(const std::string &l, const std::string &r) {
        std::string left = StrToLower(l);
        std::string right = StrToLower(r);
        if (left == "null" || right == "null") return false;
        if (UTF8_Strlen(left) == 1 || UTF8_Strlen(right) == 1) {
            return left[0] == right[0];
        }
        return left == right;
    }

    bool ComparePatronimic(const std::string &l, const std::string &r) {
        std::string left = StrToLower(l);
        std::string right = StrToLower(r);
        if (left == "null" || right == "null") return true;
        if (UTF8_Strlen(left) == 1 || UTF8_Strlen(right) == 1) {
            return left[0] == right[0];
        }
        return left == right;
    }

    struct Date {
        int year;
        int month;
        int day;

        Date(const std::string &str) {
            // Разбиваем строку по точкам
            std::vector<std::string> parts = Split(str, ".,-/\\");

            // Обрабатываем разные варианты
            if (parts.size() == 1) {
                // "1999"
                year = ParseNumber(parts[0]);
                month = 0; // не указан
                day = 0; // не указан
            } else if (parts.size() == 3) {
                // "__.__.1999"
                day = parts[0].empty() ? 0 : ParseNumber(parts[0]);
                month = parts[1].empty() ? 0 : ParseNumber(parts[1]);
                year = ParseNumber(parts[2]);
            } else {
                throw std::invalid_argument("Invalid date format. Expected '__[sep=.,/\\]__[sep=.,/\\]YYYY' or 'YYYY'");
            }
        }

    private:
        static int ParseNumber(const std::string &s) {
            if (s.empty()) return 0;
            long num = std::strtol(s.c_str(), nullptr, 10);
            return static_cast<int>(num);
        }
    };

    bool operator==(const Date &l, const Date &r) {
        return (l.year == r.year) &&
               (l.month == 0 || r.month == 0 || l.month == r.month) &&
               (l.day == 0 || r.day == 0 || l.day == r.day);
    }

    bool CompareBirthdate(const std::string &l, const std::string &r) {
        // NULL /Возраст __.__.1999 1999
        std::string left = StrToLower(l);
        std::string right = StrToLower(r);
        if (left == "null" || right == "null") return true;
        if (left == "/возраст" || right == "/возраст") return true;
        return Date{left} == Date{right};
    }

    bool CompareLossDate(const std::string &l, const std::string &r) {
        // NULL __.__.1999 1999
        std::string left = StrToLower(l);
        std::string right = StrToLower(r);
        if (left == "null" || right == "null") return true;
        return Date{left} == Date{right};
    }

    // TODO: покрытие unit-тестами
    // Функция нормализации звания (приводит все варианты к единому представлению)
    std::string NormalizeRank(const std::string &rank) {
        static const std::map<std::string, std::string> normalization_map = {
            {"красноармеец", "рядовой"},
            {"ряд", "рядовой"},
            {"ряд.", "рядовой"},
            {"красноарм", "рядовой"},
            {"красноарм.", "рядовой"},
            {"ефр", "ефрейтор"},
            {"ефр.", "ефрейтор"},
            {"мл.сержант", "младшийсержант"},
            {"мл. сержант", "младшийсержант"},
            {"мл. серж", "младшийсержант"},
            {"мл. серж.", "младшийсержант"},
            {"ст.сержант", "старшийсержант"},
            {"ст. сержант", "старшийсержант"},
            {"ст.серж", "старшийсержант"},
            {"ст. серж", "старшийсержант"},
            {"ст. серж.", "старшийсержант"},
            {"мл.лейтенант", "младшийлейтенант"},
            {"мл. лейтенант", "младшийлейтенант"},
            {"мл.л-т", "младшийлейтенант"},
            {"мл. л-т", "младшийлейтенант"},
            {"л-т", "лейтенант"},
            {"ст.лейтенант", "старшийлейтенант"},
            {"ст. лейтенант", "старшийлейтенант"},
            {"ст.л-т", "старшийлейтенант"},
            {"ст. л-т", "старшийлейтенант"},
            {"кап.", "капитан"},
            {"к-н", "капитан"},
            {"м-р", "майор"},
            {"подпол.", "подполковник"},
            {"п/п-к", "подполковник"},
            {"п\\п-к", "подполковник"},
            {"п-к", "полковник"}
        };

        // Приводим к нижнему регистру и удаляем пробелы
        std::string normalized_rank = rank;
        normalized_rank.erase(std::remove(normalized_rank.begin(), normalized_rank.end(), ' '), normalized_rank.end());

        // Ищем в карте нормализации
        auto it = normalization_map.find(normalized_rank);
        if (it != normalization_map.end()) {
            return it->second;
        }

        // Если не нашли, возвращаем нормализованную версию (без пробелов, в нижнем регистре)
        return normalized_rank;
    }

    bool CompareMilitaryRank(const std::string &l, const std::string &r) {
        std::string left = StrToLower(l);
        std::string right = StrToLower(r);

        // Специальная обработка для "null"
        if (left == "null" || right == "null") return true;

        left = NormalizeRank(left);
        right = NormalizeRank(right);
        return left == right;
    }

    static const std::map<std::string, std::string> normalization_map_geo = {
        {"обл.", "область"},
        {"обл", "область"},
        {"область", "область"},

        {"край", "край"},
        {"край.", "край"},
        {"кр", "край"},
        {"кр.", "край"},

        {"республика.", "республика"},
        {"республика", "республика"},
        {"р-ка.", "республика"},
        {"р-ка", "республика"},
        {"респ.", "республика"},
        {"респ", "республика"},

        {"район.", "район"},
        {"район", "район"},
        {"р-н.", "район"},
        {"р-н", "район"},

        {"сельсовет.", "сельсовет"},
        {"сельсовет", "сельсовет"},
        {"с/с.", "сельсовет"},
        {"с/с", "сельсовет"},

        {"деревня.", "деревня"},
        {"деревня", "деревня"},
        {"д-ня.", "деревня"},
        {"д-ня", "деревня"},
        {"дер.", "деревня"},
        {"дер", "деревня"},
        {"д.", "деревня"},

        {"город.", "город"},
        {"город", "город"},
        {"г-д.", "город"},
        {"г-д", "город"},
        {"г.", "город"},

        {"село.", "село"},
        {"село", "село"},
        {"с.", "село"},

        {"поселок.", "поселок"},
        {"поселок", "поселок"},
        {"п-к.", "поселок"},
        {"п-к", "поселок"},
        {"пос.", "поселок"},
        {"пос", "поселок"},

        {"хутор.", "хутор"},
        {"хутор", "хутор"},
        {"хут.", "хутор"},
        {"хут", "хутор"},
        {"х-р.", "хутор"},
        {"х-р", "хутор"},

        {"колхоз.", "колхоз"},
        {"колхоз", "колхоз"},
        {"кол.", "колхоз"},
        {"кол", "колхоз"},
        {"к-з.", "колхоз"},
        {"к-з", "колхоз"},

        {"кишлак.", "кишлак"},
        {"кишлак", "кишлак"},
        {"киш-к.", "кишлак"},
        {"киш-к", "кишлак"},
        {"киш.", "кишлак"},
        {"киш", "кишлак"},

        {"улица.", "улица"},
        {"улица", "улица"},
        {"у-ца.", "улица"},
        {"у-ца", "улица"},
        {"ул.", "улица"},
        {"уд", "улица"},

        {"шоссе.", "шоссе"},
        {"шоссе", "шоссе"},
        {"шос.", "шоссе"},
        {"шос", "шоссе"},

        {"переулок.", "переулок"},
        {"переулок", "переулок"},
        {"пер.", "переулок"},
        {"пер", "переулок"},
        {"пер-к.", "переулок"},
        {"пер-к", "переулок"},

        {"проезд.", "проезд"},
        {"проезд", "проезд"},
        {"п-д.", "проезд"},
        {"п-д", "проезд"},

        {"проспект.", "проспект"},
        {"проспект", "проспект"},
        {"пр-т.", "проспект"},
        {"пр-т", "проспект"},
        {"просп.", "проспект"},
        {"просп", "проспект"},

        {"аллея.", "аллея"},
        {"аллея", "аллея"},
        {"ал-я.", "аллея"},
        {"ал-я", "аллея"},
        {"ал.", "аллея"},
        {"ал", "аллея"},

        {"квартира.", "квартира"},
        {"квартира", "квартира"},
        {"кв.", "квартира"},
        {"кв", "квартира"}
    };

    /*// TODO: покрытие unit-тестами
    // Функция нормализации сокращений географических обозначений (приводит все варианты к единому представлению)
    std::string NormalizeGeo(const std::string &place) {
        // Ищем в карте нормализации
        auto it = normalization_map_geo.find(place);
        if (it != normalization_map_geo.end()) {
            return it->second;
        }

        // Если не нашли, возвращаем нормализованную версию (без пробелов, в нижнем регистре)
        return place;
    }*/

    std::pair<std::string, std::string> FindGeoAbbr(std::vector<std::string> geo_elems) {
        for (auto [abbr, full_place]: normalization_map_geo) {
            auto it = std::find_if(geo_elems.begin(), geo_elems.end(), [abbr](const std::string &elem) {
                return abbr == elem;
            });
            if (it != geo_elems.end()) {
                // нашли аббревиатуру
                return {abbr, full_place};
            }
        }
        return {};
    }

    struct BurialPlace {
        std::unordered_map<std::string, std::string> places_;

        // TODO: покрытие unit-тестами [TOP-1!!]
        BurialPlace(const std::string &burial_place) {
            std::string place_string{Strip(burial_place)};
            StrToLower(place_string);
            place_string = ReplaceSpaces(place_string, '_');
            std::vector<std::string> places = Split(place_string, ",");

            // удаляем _ в начале и в конце кусочков местности
            std::for_each(places.begin(), places.end(), StripByUnderLine);

            for (std::string &place: places) {
                std::vector<std::string> geo_elems = Split(place, "_");
                std::pair abbr_pair = FindGeoAbbr(geo_elems);
                if (!abbr_pair.first.empty()) {
                    geo_elems.erase(std::remove_if(geo_elems.begin(), geo_elems.end(),
                                                   [abbr_pair](const std::string &geo_elem) {
                                                       return abbr_pair.first == geo_elem;
                                                   }), geo_elems.end());

                    std::string geo_full_string = std::accumulate(
                        geo_elems.begin(),
                        geo_elems.end(),
                        std::string{},
                        [](std::string l, const std::string &r) {
                            return l.empty() ? r : std::move(l) + " " + r;
                        }
                    );
                    // ключом будет полное название геометки
                    places_[abbr_pair.second] = Strip(geo_full_string);
                }
            }
        }
    };

    bool operator==(const BurialPlace &l, const BurialPlace &r) {
        return l.places_ == r.places_;
    }

    bool CompareBurialPlace(const std::string &l, const std::string &r) {
        std::string left = StrToLower(l);
        std::string right = StrToLower(r);
        if (left == "null" || right == "null") return true;
        return BurialPlace{left} == BurialPlace{right};
    }
}

bool operator==(const SoldierEntry &l, const SoldierEntry &r) {
    return (compare_utils::CompareLastName(compare_utils::Strip(l.last_name_), compare_utils::Strip(r.last_name_)) &&
           compare_utils::CompareFirstName(compare_utils::Strip(l.first_name_), compare_utils::Strip(r.first_name_)) &&
           compare_utils::ComparePatronimic(compare_utils::Strip(l.patronymic_), compare_utils::Strip(r.patronymic_)) &&
           compare_utils::CompareBirthdate(compare_utils::Strip(l.birthdate_), compare_utils::Strip(r.birthdate_)))
            ||
                (compare_utils::CompareLastName(compare_utils::Strip(l.last_name_), compare_utils::Strip(r.last_name_)) &&
           compare_utils::ComparePatronimic(compare_utils::Strip(l.patronymic_), compare_utils::Strip(r.patronymic_)) &&
           compare_utils::CompareBirthdate(compare_utils::Strip(l.birthdate_), compare_utils::Strip(r.birthdate_)) &&
           compare_utils::ComparePatronimic(compare_utils::Strip(l.loss_date_), compare_utils::Strip(r.loss_date_))
           )
            ||
                (compare_utils::CompareLastName(compare_utils::Strip(l.last_name_), compare_utils::Strip(r.last_name_)) &&
           compare_utils::CompareBirthdate(compare_utils::Strip(l.birthdate_), compare_utils::Strip(r.birthdate_)) &&
           compare_utils::ComparePatronimic(compare_utils::Strip(l.loss_date_), compare_utils::Strip(r.loss_date_))
           )
    ;

           /*||
           (
               compare_utils::CompareBurialPlace(compare_utils::Strip(l.burial_place_),compare_utils::Strip(l.burial_place_)) &&
    compare_utils::CompareMilitaryRank(compare_utils::Strip(l.military_rank_), compare_utils::Strip(l.military_rank_))
           );*/
}

bool operator<(const SoldierEntry &l, const SoldierEntry &r) {
    if (l.last_name_ != r.last_name_) {
        return l.last_name_ < r.last_name_;
    }
    if (l.first_name_ != r.first_name_) {
        return l.first_name_ < r.first_name_;
    }
    return l.patronymic_ < r.patronymic_;
}

#endif //SOLDIERENTRY_H
