//
// Created by lstrsrmn on 22/05/2020.
//

#ifndef ENGINE_EDITOR_UTILS_H
#define ENGINE_EDITOR_UTILS_H

#include <string>
#include <fstream>

float clamp(float, float, float);
std::string removeExtension(const std::string&);
void copyFile(const std::string&, const std::string&);

#endif //ENGINE_EDITOR_UTILS_H
