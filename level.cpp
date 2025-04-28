#include "level.h"
#include <algorithm>
#include <cmath>
#include <stdio.h>

level::level(float size, float y) {
    groundSize = size;
    groundY = y;
    
    // initialize medal positions
    addMedal(-15.0f, 5.5f, -10.0f);
    addMedal(13.0f, 5.5f, -10.0f);
    addMedal(13.0f, 3.0f, 10.0f);
    // initialize obstacle positions
    addObstacle(-5.0f, 0.75f, 0.0f, 2.5f, 0.75f, 2.5f);
    addObstacle(-10.0f, 1.5f, 0.0f, 2.5f, 1.5f, 2.5f);
    addObstacle(-15.0f, 2.25f, 0.0f, 2.5f, 2.25f, 2.5f);
    addObstacle(-15.0f, 2.25f, -10.0f, 2.5f, 2.25f, 2.5f);
    addObstacle(-8.0f, 4.25f, -12.0f, 1.0f, 0.2f, 1.0f);
    addObstacle(-3.0f, 4.25f, -8.0f, 1.0f, 0.2f, 1.0f);
    addObstacle(2.0f, 4.25f, -12.0f, 1.0f, 0.2f, 1.0f);
    addObstacle(7.0f, 4.25f, -8.0f, 1.0f, 0.2f, 1.0f);
    addObstacle(13.0f, 4.25f, -7.0f, 2.25f, 0.2f, 7.0f);
    addObstacle(13.0f, 2.25f, 10.0f, 1.0f, 0.2f, 1.0f); 
}

void level::render() {
    // renders the ground
    glColor3f(0.4f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
        glVertex3f(-groundSize, groundY, -groundSize); // bottom left
        glVertex3f( groundSize, groundY, -groundSize); // bottom right
        glVertex3f( groundSize, groundY,  groundSize); // top right
        glVertex3f(-groundSize, groundY,  groundSize); // top left
    glEnd();

    // renders a grid
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
    
    for (const auto& obstacle : obstacles){
        renderObstacle(obstacle);
    }

    for (const auto& medal : medals){
        if(!medal.collected){
            renderMedal(medal);
        }
    }
}

void level::renderMedal(const medal& rMedal){
    glPushMatrix();
    glColor3f(0.937f, 0.749f, 0.016f);
    glTranslatef(rMedal.x, rMedal.y, rMedal.z);
    glutSolidCylinder(0.6f, 0.1f, 16, 1);
    glPopMatrix();
}

void level::renderObstacle(const obstacle& rObstacle){
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glTranslatef(rObstacle.x, rObstacle.y, rObstacle.z);
    glScalef(rObstacle.sizeX, rObstacle.sizeY, rObstacle.sizeZ);
    glutSolidCube(2.0f);
    glPopMatrix();
}


void level::addMedal(float x, float y, float z){
    medals.push_back({x, y, z, false});
}

void level::addObstacle(float x, float y, float z, float sizeX, float sizeY, float sizeZ){
    obstacles.push_back({x, y, z, sizeX, sizeY, sizeZ});
}

bool level::collectMedal(float ballX, float ballY, float ballZ, float r){
   for (auto& medal : medals){
        if(!medal.collected){
           // distances between ball and medal
           float dx = ballX - medal.x;
           float dy = ballY - medal.y;
           float dz = ballZ - medal.z;
           
           // all distances are squared, so i don't need to calculate the sqrt
           float distance = dx*dx + dy*dy + dz*dz;
           if(distance < (r + 0.3f) * (r + 0.3f)){ // the second term is the sum between the ball radius and the medal radius
                medal.collected = true;
                return true;
           }
                
        }
    }
   return false;
}

bool level::obstacleCollision(float& ballX, float& ballY, float& ballZ, float r, float& velX, float& velY, float& velZ) const{
    for (const auto& obstacle : obstacles) {
        // finds the limits of the bounding box
        float minX = obstacle.x - obstacle.sizeX;
        float maxX = obstacle.x + obstacle.sizeX;
        float minY = obstacle.y - obstacle.sizeY;
        float maxY = obstacle.y + obstacle.sizeY;
        float minZ = obstacle.z - obstacle.sizeZ;
        float maxZ = obstacle.z + obstacle.sizeZ;
        
        // find closest point to the ball
        float closestX = std::max(minX, std::min(ballX, maxX));
        float closestY = std::max(minY, std::min(ballY, maxY));
        float closestZ = std::max(minZ, std::min(ballZ, maxZ));
        
        // finds distance between the ball and the closest points
        float dx = ballX - closestX;
        float dy = ballY - closestY;
        float dz = ballZ - closestZ;
        float distance = dx*dx + dy*dy + dz*dz; // distance squared
        
        // if distance < radius (squared), a collision has occured
        if(distance < r * r){
            // finds the real distance
            float dist = std::sqrt(distance);
            
            // collision direction vector (points from obstacle to the ball)
            float nx = dx / dist;
            float ny = dy / dist;
            float nz = dz / dist;
            
            // top surface collision (fix nan glitch)
            if(closestY == maxY && dy > 0){
                ny = 1.0f; // normal pointing up
                nx = nz = 0.0f; // no horizontal components
              // side collision
            } else if (closestY != maxY && closestY != minY){
                ny = 0.0f; // remove vertical component
                           // had a bug where the ball would go up when hitting the obstacle sides
                float length = std::sqrt(nx*nx + nz*nz);
                if(length > 0){
                    // ensures that its a unit vector
                    nx /= length;
                    nz /= length;
                  // edge case
                } else {
                    nx = 1.0f;
                    nz = 0.0f;
                }
            }

            // move ball to the obstacle surface
            ballX = closestX + nx * r;
            ballY = closestY + ny * r;
            ballZ = closestZ + nz * r;

            // top collision
            if (closestY == maxY && dy > 0){
                    velY = 0; // stop any vertical movement
              // bottom collision
            } else if (closestY == minY && dy < 0){
                    velY *= -0.5f; // bounce with speed loss
              // side collision           
            } else {
                // reflect velocity with 20% speed loss
                float dot = velX * nx + velY * ny + velZ * nz;
                velX -= 2 * dot * nx * 0.8f;
                velY -= 2 * dot * ny * 0.8f;
                velZ -= 2 * dot * nz * 0.8f;
            }
            return true;
        }
    }
    // no collisions detected
    return false;
}
