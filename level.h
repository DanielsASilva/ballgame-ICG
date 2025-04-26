#pragma once

#include <GL/glut.h>

class level {
    public:
        level(float size, float y); // constructor
        void render();

    private:
        float groundSize;
        float groundY;
};
