//
// Created by lstrsrmn on 25/05/2020.
//

#ifndef ENGINE_EDITOR_ASSET_H
#define ENGINE_EDITOR_ASSET_H

#include <string>

class Asset {
public:
    unsigned int getID() const;
    std::string getFilePath() const;
    std::string name;
protected:
    Asset(const std::string&, unsigned int);
    std::string filePath;
    unsigned int id;
};

#define ASSET(type) friend class AssetManager<type>;

#endif //ENGINE_EDITOR_ASSET_H
