#include "../../include/engine/core/Asset.h"

std::filesystem::path Asset::getFilePath() const {
    return filePath;
}

Asset::Asset(const std::filesystem::path &filePath, unsigned int id) {
    this->filePath = filePath;
    this->id = id;
}

unsigned int Asset::getID() const {
    return id;
}
