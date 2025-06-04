#ifndef REGISTRY_H
#define REGISTRY_H

#include <unordered_map>
#include <vector>

class RegistryStorage {
public:
    RegistryStorage() = default;

    void AppendRegistry(const std::string& file_name) {
        if (content_.find(file_name) == content_.end()) {
            content_[file_name] = {};
        }
    }

    void AppendEntryToRegistry(const std::string& file_name, const RegistryEntry& entry) {
        if (content_.find(file_name) != content_.end()) {
            content_[file_name].push_back(entry);
        }
    }

private:
    /*
     * key   [std::string] - имя файла ведомости
     * value [std::vector<RegistryEntry>] - набор записей (строк) из ведомости
     */
    std::unordered_map<std::string, std::vector<RegistryEntry>> content_{};
};

#endif //REGISTRY_H
