#pragma once
#include <cstdint>
#include <vector>
#include "../Format.h"
#include <string>

// This file needs to be windows only for some parts :0
std::vector<float> ProcessImage
(
    std::vector<uint8_t> &pData,
    FTextureInfo &stFormat
);

void SerialiseImage
(
    std::vector<float>& pData,
    FTextureInfo& stFormat,
    std::string &&strFormat
);