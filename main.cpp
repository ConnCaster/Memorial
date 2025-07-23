#include <cstdlib>
#include <iostream>

#include <bsoncxx/builder/basic/document.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include "memorial/Vedomost.h"
#include "memorial/ParsePassport.h"
#include "memorial/cxxopts/cxxopts.h"
#include "memorial/upload/Upload.h"

int main(int argc, char* argv[]) {
    cxxopts::Options options("Memorial",
        "Vedomost Searcher: программа для поиска ведомости захоронения, в которой больше всего воинов совпадает с заданным паспортом захоронения");

    options.add_options()
      ("p,passport", "Путь к файлу с паспортом .xlsx", cxxopts::value<std::string>())
      ("u,upload", "Режим загрузки ведомостей в БД: путь к директории с ведомостями в формате .xlsx", cxxopts::value<std::string>())
      ("h,help", "Вывести краткое руководство по запуску приложения")
      ;

    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
    }
    if (!result.count("passport")) {
        std::cerr << "Ошибка: необходимо указать путь к файлу с паспортом с помощью параметра -p или --passport" << std::endl;
        std::cout << options.help() << std::endl;
        return 1;
    }

    const mongocxx::uri uri = mongocxx::uri{"mongodb://admin:my_password@localhost:27017/memorial?authSource=admin"};
    if (result.count("upload")) {
        try {
            std::string vedomost_dir = result["upload"].as<std::string>();
            VedomostUploader vedomost_uploader{uri, vedomost_dir};
            if (!vedomost_uploader.Upload()) {
                std::cerr << "Ошибка при обработке директории с ведомостями" << std::endl;
                return 1;
            }
            //vedomost_uploader.InsertVedomost(100000, "date", "source");
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при создании БД или коллекции в БД: " << e.what() << std::endl;
        }
        return 0;
    }

    std::string passport_path = result["passport"].as<std::string>();
    std::cout << "Путь к файлу с паспортом: " << passport_path << std::endl;

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;

    mongocxx::instance inst;

    try {
        auto client = mongocxx::client{uri};
        auto db = client["memorial"];
        auto vedomosti_collection = db["vedomosti"];

        // TODO: переделать паспорта из коллекции в одиночный объект
        PassportParser parser{vedomosti_collection, {passport_path}};
        parser.Run();

        return EXIT_SUCCESS;
    } catch (std::exception const& ex) {
        std::cout << "[Error] " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}

/*
 * TODO:
 * 1. Механизм заливки в БД новых ведомостей
 * 2. Механизм перечитывания директории с паспортами (
 *          аргументом программе дается путь к директории с паспортами, а мы получаем из нее имена всех файлов паспортов
 *          и используем их для наших поисков)
 * 3.
 *
 */