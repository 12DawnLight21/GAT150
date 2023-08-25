#pragma once 

//michael needs all this
//add this to core.h

namespace umbra
{
    class Rect
    {
    public:
        int x, y, w, h; //x y width height

    public:
        Rect() : x{ 0 }, y{ 0 }, w{ 0 }, h{ 0 } {}
        Rect(int x, int y, int w, int h) : x{ x }, y{ y }, w{ w }, h{ h } {}

        int operator [] (size_t index) const { return (&x)[index]; } //gets the address of first variable to get the next ones
        int& operator [] (size_t index) { return (&x)[index]; } //micheal also needs this
    };
}