#pragma once

#include <GL/freeglut.h>
#include <vector>

struct medal{
    float x, y, z;
    bool  collected;
};

struct obstacle {
    float x, y, z;
    float sizeX, sizeY, sizeZ;
};

class level {
    public:
        level(float size, float y); // constructor
        void addMedal(float x, float y, float z);
        void addObstacle(float x, float y, float z, float sizeX, float sizeY, float sizeZ);
        bool collectMedal(float ballX, float ballY, float ballZ, float r);
        bool obstacleCollision(float& ballX, float& ballY, float& ballZ, float r, float& velX, float& velY, float& velZ) const;
        void render();
        void renderMedal(const medal& rMedal);
        void renderObstacle(const obstacle& rObstacle);
    private:
        float groundSize;
        float groundY;
        
        std::vector<medal> medals;
        std::vector<obstacle> obstacles;
};
