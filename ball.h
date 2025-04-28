#pragma once

#include <GL/glut.h>
#include "level.h"
class ball {
    public:
        ball(float startX, float startY, float startZ, float r); // constructor
        
        float getX();
        float getY();
        float getZ();
        
        void updatePhysics(float deltaTime, const level& level); // update physics
        void updateCamera();                                     // update camera
        void render();                                           // renders the ball
        void handleInput(unsigned char key);
        void handleCameraInput(int key);
        void medalCollected();                                   // collects a medal and checks if the game was won

        bool keyBuffer[256] = {false};                           // holds key states for smooth input
        
    private:
        float x, y, z;                // position
        float rad;                    // ball radius
        float velX, velY, velZ;       // ball speed
        float R, G, B;                // colors since i don't have textures yet
        float medalsCollected;        // how many medals the player have collected
        bool  isGrounded;             // checks if it's grounded
        
        float camX, camY, camZ;       // cartesian camera positions
        float cameraDistance;         // desired distance from ball to camera
        float cameraTheta;            // rotation around the ball (degrees)
        float cameraPhi;              // rotation over the ball (degrees)
       
        float friction;               // ground friction (deceleration)

        float degToRad(float deg);    // converts degrees to radians
};
