#include "level.h"

level::level(float size, float y) : groundSize(size), groundY(y) { }

void level::render() {
    glColor3f(0.4f, 0.6f, 0.2f);
    
    glBegin(GL_QUADS);
        glVertex3f(-groundSize, groundY, -groundSize); // Bottom-left
        glVertex3f( groundSize, groundY, -groundSize); // Bottom-right
        glVertex3f( groundSize, groundY,  groundSize); // Top-right
        glVertex3f(-groundSize, groundY,  groundSize); // Top-left
    glEnd();

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    for(float i = -groundSize; i <= groundSize; i += 1.0f) {
        // X-axis lines
        glVertex3f(i, groundY + 0.01f, -groundSize);
        glVertex3f(i, groundY + 0.01f,  groundSize);
        // Z-axis lines
        glVertex3f(-groundSize, groundY + 0.01f, i);
        glVertex3f( groundSize, groundY + 0.01f, i);
    }
    glEnd();
}

void level::addMedal(float x, float y, float z){
    medals.push_back({x, y, z, false});
}

void level::addObstacle(float x, float y, float z, float sizeX, float sizeY, float sizeZ){
    obstacles.push_back({x, y, z, sizeX, sizeY, sizeZ});
}
