//
// Created by lstrsrmn on 25/05/2020.
//

#ifndef ENGINE_EDITOR_ASSET_H
#define ENGINE_EDITOR_ASSET_H

#include <string>
#include <nlohmann/json.hpp>
#include <filesystem>

class Asset {
public:
    unsigned int getID() const;
    std::filesystem::path getFilePath() const;
    std::string name;
protected:
    Asset(const std::filesystem::path&, unsigned int);
    std::filesystem::path filePath;
    unsigned int id;
};

#define ASSET(type) friend class AssetManager<type>;

#endif //ENGINE_EDITOR_ASSET_H
