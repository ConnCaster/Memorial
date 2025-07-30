#ifndef UPLOAD_H
#define UPLOAD_H

#include <iostream>
#include <vector>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>

#include <bsoncxx/builder/stream/array.hpp>

#include <filesystem>

namespace fs = std::filesystem;
using bsoncxx::builder::basic::kvp;

class VedomostUploader {
public:
    VedomostUploader(const mongocxx::uri& uri, const std::string& vedomost_dir)
        : vedomost_dir_{vedomost_dir}
    {
        mongocxx::instance instance{};
        client_ = mongocxx::client{uri};
        db_ = client_["memorial"];
        db_.create_collection("vedomosti");
        std::cout << "Коллекция 'vedomosti' успешно создана." << std::endl;
        collection_ = db_["vedomosti"];
    }

    bool Upload() {
        if (fs::exists(vedomost_dir_)) {
            try {
                if (!fs::is_directory(vedomost_dir_)) {
                    std::cerr << "Указанный путь не является директорией: " << vedomost_dir_ << std::endl;
                    return false;
                }

                for (const auto& vedomost_path : fs::directory_iterator(vedomost_dir_)) {
                    std::cout << "Parsing " << vedomost_path << " ..." << std::endl;
                    XLDocument xlsx_file;
                    xlsx_file.open(vedomost_path.path());
                    if (!xlsx_file.isOpen()) {
                        std::cout << "[Error] Error open vedomost file " << vedomost_path << ". Continue..." << std::endl;
                    }
                    XLWorksheet vedomost_worksheet{};  //= xlsx_file.workbook().worksheet("Лист1");

                    auto workbook = xlsx_file.workbook();
                    auto worksheetNames = workbook.worksheetNames();

                    bool found = false;
                    for (const auto& name : worksheetNames) {
                        if (name == "Лист1" || name == "Sheet1") {
                            vedomost_worksheet = workbook.worksheet(name);
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        xlsx_file.close();
                        throw std::runtime_error("Valid worksheet name is not found in Vedomost: " + vedomost_path.path().string());
                    }

                    bsoncxx::builder::basic::document doc = CreateMongoDocumentFromVedomost(vedomost_worksheet);
                    if (!InsertVedomost(doc)) {
                        continue;
                    }
                }
                return true;
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Ошибка доступа к директории: " << e.what() << std::endl;
                return false;
            }
        } else {
            std::cerr << "Директория не существует: " << vedomost_dir_ << std::endl;
            return false;
        }
    }

    bsoncxx::document::value CreateSoldier(
        const std::string& last_name,
        const std::string& first_name,
        const std::string& patronymic,
        const std::string& birthdate,
        const std::string& birth_place,
        const std::string& conscription,
        const std::string& last_duty,
        const std::string& rank,
        const std::string& loss_reason,
        const std::string& loss_date,
        const std::string& burial_place,
        const std::string& report_source,
        int fund_num,
        int inventory_num,
        int case_num)
    {
        return bsoncxx::builder::basic::make_document(
            kvp("last_name", last_name),
            kvp("first_name", first_name),
            kvp("patronymic", patronymic),
            kvp("birthdate", birthdate),
            kvp("birth_place", birth_place),
            kvp("conscription_date_and_place", conscription),
            kvp("last_duty_place", last_duty),
            kvp("military_rank", rank),
            kvp("loss_reason", loss_reason),
            kvp("loss_date", loss_date),
            kvp("burial_place", burial_place),
            kvp("report_source", report_source),
            kvp("source_fund_number", fund_num),
            kvp("source_inventory_number", inventory_num),
            kvp("source_case_number", case_num)
        );
    }

    bsoncxx::builder::basic::document CreateMongoDocumentFromVedomost(XLWorksheet& vedomost_worksheet) {
        auto vedomost = bsoncxx::builder::basic::document();
        auto soldiers = bsoncxx::builder::basic::array{};
        int line_counter{0};
        for (auto& line : vedomost_worksheet.rows()) {
            if (line_counter++ == 0) {
                vedomost.append(kvp("report_number", line.findCell(1).value().getString()));
                vedomost.append(kvp("report_date", line.findCell(2).value().getString()));
                vedomost.append(kvp("report_source", line.findCell(3).value().getString()));

                // vedomost.append(kvp("report_number", 100000));          // line.findCell(1).value().getInt()
                // vedomost.append(kvp("report_date", "01.01.1941"));      // line.findCell(2).value().getString()
                // vedomost.append(kvp("report_source", "штаб ХХ сд"));    // line.findCell(3).value().getString()
                continue;
            }
            if (line.findCell(1).value().getString() == "Фамилия") continue;
            auto soldier = CreateSoldier(
                line.findCell(1).value().getString(),
                line.findCell(2).value().getString(),
                line.findCell(3).value().getString(),
                line.findCell(4).value().getString(),
                line.findCell(5).value().getString(),
                line.findCell(6).value().getString(),
                line.findCell(7).value().getString(),
                line.findCell(8).value().getString(),
                line.findCell(9).value().getString(),
                line.findCell(10).value().getString(),
                line.findCell(11).value().getString(),
                line.findCell(12).value().getString(),
                strtol(line.findCell(13).value().getString().c_str(), nullptr, 10),
                strtol(line.findCell(14).value().getString().c_str(), nullptr, 10),
                strtol(line.findCell(15).value().getString().c_str(), nullptr, 10)
                );
            soldiers.append(soldier.view());
        }
        vedomost.append(kvp("soldiers", soldiers));
        return vedomost;
    }

    bool InsertVedomost(bsoncxx::builder::basic::document& doc) {
        try {
            auto result = collection_.insert_one(doc.view());
            if (result) {
                std::cout << "Ведомость успешно добавлена с ID: "
                         << result->inserted_id().get_oid().value.to_string() << std::endl;
            }
            return 1;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
            return 0;
        }
    }

private:
    mongocxx::client client_;
    mongocxx::database db_;
    mongocxx::collection collection_;
    std::string vedomost_dir_;
};

#endif //UPLOAD_H
