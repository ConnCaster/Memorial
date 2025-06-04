#ifndef PARSEREGISTRY_H
#define PARSEREGISTRY_H

#include <fstream>

#include <OpenXLSX.hpp>
#include "RegisterEntry.h"
#include "RegistryStorage.h"

using namespace OpenXLSX;
using namespace std;

class XLSParser {
public:
    XLSParser(RegistryStorage& registry_storage, std::vector<std::string>&& file_names)
        : storage_{registry_storage}, file_names_{std::move(file_names)}
    {}

    void Run() {
        for (const auto& file_name : file_names_) {
            std::cout << "Parsing " << file_name << " ..." << std::endl;
            XLDocument xlsx_file;
            xlsx_file.open(file_name);
            if (!xlsx_file.isOpen()) {
                std::cout << "[Error] Error open file " << file_name << ". Continue..." << std::endl;
            }

            XLWorksheet wks = xlsx_file.workbook().worksheet("Sheet1");
            XLCellRange rng = wks.range(XLCellReference("A1"), XLCellReference("Q2"));
            cout << "Cell count: " << std::distance(rng.begin(), rng.end()) << endl;

            for (const auto& line : wks.rows()) {
                for (const auto& cell : line.cells()) {
                    std::cout << cell.value() << std::endl;
                }
            }
            xlsx_file.close();
        }
    }

private:
    RegistryStorage& storage_;
    std::vector<std::string> file_names_;
};

#endif //PARSEREGISTRY_H
