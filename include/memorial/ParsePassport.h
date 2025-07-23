#ifndef PARSEREGISTRY_H
#define PARSEREGISTRY_H

#include <fstream>

#include <OpenXLSX.hpp>
#include <mongocxx/collection.hpp>

#include "Vedomost.h"
#include "VedomostSearcher.h"


using namespace OpenXLSX;
using namespace std;


class PassportParser {
public:
    PassportParser(mongocxx::collection& vedomosti_collection, std::vector<std::string>&& file_names)
        : vedomosti_collection_(vedomosti_collection), file_names_{std::move(file_names)}
    {}

    void Run() {
        for (const auto& file_name : file_names_) {
            std::cout << "Parsing " << file_name << " ..." << std::endl;
            XLDocument xlsx_file;
            xlsx_file.open(file_name);
            if (!xlsx_file.isOpen()) {
                std::cout << "[Error] Error open file " << file_name << ". Continue..." << std::endl;
            }

            auto opts = mongocxx::options::find{};
            opts.no_cursor_timeout(true);
            opts.batch_size(10);
            auto cursor = vedomosti_collection_.find({}, opts);

            XLWorksheet passport_worksheet = xlsx_file.workbook().worksheet("Лист1");

            VedomostSearcher vedomost_searcher{passport_worksheet, std::move(cursor)};
            Vedomost found_vedomost = vedomost_searcher.Search();
            std::cout << "[FOUND] " << found_vedomost.GetContent() << std::endl;

            xlsx_file.close();
        }
    }

private:
    mongocxx::collection vedomosti_collection_;
    std::vector<std::string> file_names_;
};


#endif //PARSEREGISTRY_H
