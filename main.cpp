#include <cstdlib>
#include <iostream>

#include <bsoncxx/builder/basic/document.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include "memorial/Vedomost.h"
#include "memorial/ParsePassport.h"

int main() {
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;

    mongocxx::instance inst;

    try {
        auto const uri = mongocxx::uri{"mongodb://admin:my_password@localhost:27017/memorial?authSource=admin"};

        auto client = mongocxx::client{uri};
        auto db = client["memorial"];
        auto vedomosti_collection = db["vedomosti"];

        PassportParser parser{vedomosti_collection, {"/home/user/dir/programming/C++/Yaroslava/Memorial/input/passport_new.xlsx"}};
        parser.Run();

        return EXIT_SUCCESS;
    } catch (std::exception const& ex) {
        std::cout << "connection failed: " << ex.what() << std::endl;
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