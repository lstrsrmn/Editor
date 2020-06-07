#include "../../include/engine/core/Utils.h"

float clamp(float value, float min, float max) {
    if (min > value)
        return min;
    if (max < value)
        return max;
    return value;
}

std::string removeExtension(const std::string &filename) {
    size_t lastdot = filename.find_last_of(".");
    if (lastdot == std::string::npos) return filename;
    return filename.substr(0, lastdot);
}

void copyFile(const std::string& source, const std::string &destination) {
    std::ifstream src(source.c_str());
    std::ofstream dest(destination.c_str());
    dest << src.rdbuf();
}