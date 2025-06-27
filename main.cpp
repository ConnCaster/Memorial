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

        // auto opts = mongocxx::options::find{};
        // opts.no_cursor_timeout(true);
        // opts.batch_size(10);
        //
        // auto cursor = vedomosti_collection.find({}, opts);   // make_document(kvp("report_number", 11879))
        // for (auto& vedomost: cursor) {
        //     Vedomost vdmst{vedomost};
        //     std::cout << vdmst.GetContent() << std::endl;
        // }
        return EXIT_SUCCESS;
    } catch (std::exception const& ex) {
        std::cout << "connection failed: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}


/*#include <iostream>

#include "memorial/ParseRegistry.h"

int main() {

    // RegistryStorage registry_storage{};
    //
    // XLSParser parser{registry_storage, {"/home/user/dir/programming/C++/Yaroslava/Memorial/input/vedomost.xlsx"}};
    // parser.Run();



    return 0;
}*/