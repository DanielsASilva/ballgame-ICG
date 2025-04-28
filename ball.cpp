#include "ball.h"
#include <cmath>
#include <algorithm>
#include <stdio.h>
ball::ball(float startX, float startY, float startZ, float r) {
    x = startX;
    y = startY;
    z = startZ;
    rad = r;
    velX = velY = velZ = 0.0f;
    R = 1.0f;
    G = 0.0f;
    B = 0.0f;
    isGrounded = true;
    cameraDistance = 10.0f;
    cameraTheta = 00.0f;
    cameraPhi = 70.0f;
    friction = 0.98f;
    isCharging = false;
    chargeTime = 0.0f;
}

void ball::updatePhysics(float deltaTime, const level& level) {
       
    float moveSpeed = 15.0f;
    float jumpForce = 5.5f;
    float accelX = 0.0f;
    float accelZ = 0.0f;

    float forwardX = -cos(degToRad(cameraTheta));
    float forwardZ = -sin(degToRad(cameraTheta));

    float rightX = sin(degToRad(cameraTheta));
    float rightZ = -cos(degToRad(cameraTheta));
    

        if(keyBuffer['w']){
            accelX += forwardX * moveSpeed;
            accelZ += forwardZ * moveSpeed;
        }
        if(keyBuffer['s']){
            accelX += -forwardX * moveSpeed;
            accelZ += -forwardZ * moveSpeed;
        }
        if(keyBuffer['a']){
            accelX += -rightX * moveSpeed;
            accelZ += -rightZ * moveSpeed;
        }
        if(keyBuffer['d']){
            accelX += rightX * moveSpeed;
            accelZ += rightZ * moveSpeed;
        }
        if(keyBuffer[' ']){
            if(isGrounded){ 
                velY = jumpForce;
                isGrounded = false;
            }
        }
        if(keyBuffer['q']){
            if(!isGrounded){
                velX = velZ = 0.0f;
                velY -= 19.6f * deltaTime;
            }
        }
        if(keyBuffer['e']){
                       
        }if(keyBuffer['1']){ // checkpoints for debug
            x = -15.0f;
            y = 5.5f;
            z = -10.0f;
        }if(keyBuffer['2']){
            x = 13.0f;
            y = 5.5f;
            z = -10.0f;
        }if(keyBuffer['3']){
            x = 13.0f;
            y = 3.0f;
            z = 10.0f;
        }
    
    if(isGrounded){
        velX += accelX * deltaTime;
        velZ += accelZ * deltaTime;
    }

    // Applying gravity if the ball is on air
    if(!isGrounded) {
        velY -= 9.8f * deltaTime;
    }

    if(isGrounded){
        velX *= friction;
        velZ *= friction;
    }

    x += velX * deltaTime;
    y += velY * deltaTime;
    z += velZ * deltaTime;
    

    bool ballCollision = level.obstacleCollision(x, y, z, rad, velX, velY, velZ);
    if(ballCollision == true && y > 0){
        isGrounded = true;
    } else if(ballCollision == false && y > 0){
        isGrounded = false;
    }
    // ground collision (0.0 = ground level)
    if(y - rad < 0.0f) {
        y = rad;
        velY = 0.0f;
        isGrounded = true;
    }
    
}

float ball::degToRad(float deg){
    return deg * M_PI / 180;
}

void ball::updateCamera(){
    // uses spherical coordinates to move the camera correctly
    camX = x + cameraDistance * sin(degToRad(cameraPhi)) * cos(degToRad(cameraTheta));
    camY = y + cameraDistance * cos(degToRad(cameraPhi));
    camZ = z + cameraDistance * sin(degToRad(cameraPhi)) * sin(degToRad(cameraTheta));
    gluLookAt(camX, camY, camZ, x, y, z, 0, 1, 0);
}

void ball::render() {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(R, G, B);
    glutSolidSphere(rad, 20, 20);
    glPopMatrix();
}

void ball::handleCameraInput(int key) {
    switch(key){
        case GLUT_KEY_UP:
                cameraPhi += 5.0f;
            break;
        case GLUT_KEY_DOWN:
                cameraPhi -= 5.0f; 
            break;
        case GLUT_KEY_LEFT:
                cameraTheta -= 5.0f;
            break;
        case GLUT_KEY_RIGHT:
                cameraTheta += 5.0f;
            break;
    }
    
    if(cameraTheta >= 360.0f){
        cameraTheta = 0.0f;
    } else if(cameraTheta <= 0.0f){
        cameraTheta = 360.0f;
    }
        
    cameraPhi = std::clamp(cameraPhi, 1.0f, 90.0f);
}

void ball::medalCollected(){
    if(medalsCollected <= 5){
        medalsCollected += 1;
    }
}

float ball::getX(){
    return x;
}

float ball::getY(){
    return y;
}

float ball::getZ(){
    return z;
}
