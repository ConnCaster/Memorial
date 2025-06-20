#ifndef REGISTRY_H
#define REGISTRY_H

#include <unordered_map>
#include <vector>

class Vedomost {
public:
    Vedomost() = default;


private:
    unsigned int report_number_;
    std::string report_date_;
    std::string report_source_;
    std::vector<RegistryEntry> soldiers_;

};

#endif //REGISTRY_H
