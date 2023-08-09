#pragma once
#include "MathUtils.h"

#include <cstdint>
#include <string>
#include<iostream>

namespace umbra
{
    class Color
    {
    public:
        float r, g, b, a;
    public:
        Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 1 } {}
        Color(float r, float g, float b, float a) : r{ r }, g{ g }, b{ b }, a{ a } {}

        static uint8_t ToInt(float c) { return static_cast<uint8_t>(Clamp(c, 0.0f, 1.0f) * 255); }

        //friend std::istream& operator >> (std::istream& stream, Color& color);

    };
    inline std::istream& operator >> (std::istream& stream, Color& color)
    {

        std::string line;
        std::getline(stream, line);
        std::string str = line.substr(line.find("{") + 1);

        color.r = std::stof(str);

        str = str.substr(str.find(",") + 1);
        color.g = std::stof(str);

        //blue
        str = str.substr(str.find(",") + 1);
        color.b = std::stof(str);

        //alpha
        color.a = 1;

        return stream;
    }
}