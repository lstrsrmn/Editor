#include "../../include/engine/core/Asset.h"

std::string Asset::getFilePath() const {
    return filePath;
}

Asset::Asset(const std::string &filePath, unsigned int id) {
    this->filePath = filePath;
    this->id = id;
}

unsigned int Asset::getID() const {
    return id;
}
