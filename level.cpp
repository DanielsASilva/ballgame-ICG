#include "level.h"

level::level(float size, float y) {
    groundSize = size;
    groundY = y;
    addMedal(5.0f, 1.0f, 5.0f);
}

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

void level::addMedal(float x, float y, float z){
    medals.push_back({x, y, z, false});
}

void level::addObstacle(float x, float y, float z, float sizeX, float sizeY, float sizeZ){
    obstacles.push_back({x, y, z, sizeX, sizeY, sizeZ});
}

bool level::collectMedal(float ballX, float ballY, float ballZ, float r){
   for (auto& medal : medals){
        if(!medal.collected){
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
