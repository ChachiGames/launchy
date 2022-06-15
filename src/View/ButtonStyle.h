#pragma once

#include <string>
#include <cstdint>

struct ButtonStyle
{
    // Image* image;
    uint32_t color;
    std::string text;

    uint32_t hoverColor;
    uint32_t clickedColor;
};
