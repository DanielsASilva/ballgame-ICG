#pragma once

#include <GL/glut.h>

class ball {
    public:
        ball(float startX, float startY, float startZ, float r); // constructor
        
        void updatePhysics(float deltaTime);                     // update physics
        void updateCamera();                                     // update camera
        void render();                                           // renders the ball
        void handleInput(unsigned char key);
        void handleCameraInput(int key);

        bool keyBuffer[256] = {false};                           // holds key states for smooth input

    private:
        float x, y, z;                // position
        float rad;                    // ball radius
        float velX, velY, velZ;       // ball speed
        bool  isGrounded;             // checks if it's grounded
        bool  isCharging;             // checks if it's charging spin dash
        float chargeTime;             // tracks for how long it's been charging
        float R, G, B;                // colors since i don't have textures yet
        
        float camX, camY, camZ;       // cartesian camera positions
        float cameraDistance;         // desired distance from ball to camera
        float cameraTheta;            // rotation around the ball (degrees)
        float cameraPhi;              // rotation over the ball (degrees)
       
        float friction;               // ground friction (deceleration)

        float degToRad(float deg);    // converts degrees to radians
};
