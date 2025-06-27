#ifndef PARSEREGISTRY_H
#define PARSEREGISTRY_H

#include <fstream>

#include <OpenXLSX.hpp>
#include <mongocxx/collection.hpp>

#include "Vedomost.h"


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

            XLWorksheet wks = xlsx_file.workbook().worksheet("Sheet1");
            XLCellRange rng = wks.range(XLCellReference("A1"), XLCellReference("Q2"));
            cout << "Cell count: " << std::distance(rng.begin(), rng.end()) << endl;

            for (const auto& line : wks.rows()) {
                for (const auto& cell : line.cells()) {
                    std::cout << cell.value() << std::endl;
                    // TODO: искать солдата в списках ведомостей
                    for (auto& vedomost: cursor) {
                        Vedomost vdmst{vedomost};
                        std::cout << vdmst.GetContent() << std::endl;
                    }
                }
            }
            xlsx_file.close();
        }
    }

private:
    mongocxx::collection vedomosti_collection_;
    std::vector<std::string> file_names_;
};


#endif //PARSEREGISTRY_H
