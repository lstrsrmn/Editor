#ifndef ENGINE_EDITOR_ASSETMANAGER_H
#define ENGINE_EDITOR_ASSETMANAGER_H

#include <string>
#include <map>
#include <fstream>
#include "Asset.h"


#define ASSET_MAP(type) \
template<> std::map<unsigned int, type*> AssetManager<type>::_loadedAssets;

template<typename AssetType>
class AssetManager {
public:
    static void writeAssetMeta(const std::string &);

    static void readAssetMeta(const std::string &);

    static bool requestAssetID(const std::string &, unsigned int &);

    static void addAsset(AssetType *, unsigned int);

    static AssetType *getAsset(unsigned int);

    static AssetType *createAsset(const std::string&, const std::string&);

    static std::map<unsigned int, AssetType *> getLoadedAssets();

    static void deleteAsset(unsigned int );

private:
    static std::map<unsigned int, AssetType *> _loadedAssets;
};

template<typename AssetType>
std::map<unsigned int, AssetType*> AssetManager<AssetType>::_loadedAssets;

template<typename AssetType>
void AssetManager<AssetType>::writeAssetMeta(const std::string &metaFile) {
    std::ofstream assetMeta(metaFile);
    nlohmann::json assets;
    for (std::pair<unsigned int, AssetType*> entry: _loadedAssets) {
        // TODO: replace with a function to get the meta data from the asset object
        assets[std::to_string(entry.first)]["path"] = entry.second->getFilePath();
        assets[std::to_string(entry.first)]["name"] = entry.second->name;
    }
    assetMeta << assets.dump(4) << std::endl;
    assetMeta.close();
}

template<typename AssetType>
void AssetManager<AssetType>::readAssetMeta(const std::string &metaFile) {
    std::ifstream assetsMeta(metaFile);
    nlohmann::json assets;
    assetsMeta >> assets;
    for (nlohmann::json::iterator it = assets.begin(); it != assets.end(); it++) {
        createAsset(it.value()["name"], it.value()["path"]);
    }
    assetsMeta.close();
}

template<typename AssetType>
bool AssetManager<AssetType>::requestAssetID(const std::string &filePath, unsigned int &id) {
    id = std::hash<std::string>()(filePath);
    return _loadedAssets.find(id) == _loadedAssets.end();
}

template<typename AssetType>
void AssetManager<AssetType>::addAsset(AssetType *asset, unsigned int id) {
    _loadedAssets[id] = asset;
}

template<typename AssetType>
AssetType *AssetManager<AssetType>::getAsset(unsigned int id) {
    return _loadedAssets[id];
}

template<typename AssetType>
AssetType *AssetManager<AssetType>::createAsset(const std::string &name, const std::string &path) {
    unsigned int id;
    std::string fullPath = path;
    if (requestAssetID(fullPath, id)) {
        AssetType* newAsset = new AssetType(fullPath, id);
        newAsset->name = name;
        addAsset(newAsset, id);
        return newAsset;
    }
    return getAsset(id);
}

template<typename AssetType>
std::map<unsigned int, AssetType *> AssetManager<AssetType>::getLoadedAssets() {
    return _loadedAssets;
}

template<typename AssetType>
void AssetManager<AssetType>::deleteAsset(unsigned int id) {
    _loadedAssets.erase(id);
}


#endif //ENGINE_EDITOR_ASSETMANAGER_H
