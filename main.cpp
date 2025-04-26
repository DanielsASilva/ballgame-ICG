#include "ball.h"
#include "level.h"

ball*  playerBall;
level* renderLevel;

void display() {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    glLoadIdentity();
    playerBall->updateCamera();
    renderLevel->render();
    playerBall->render();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    playerBall->keyBuffer[key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
    playerBall->keyBuffer[key] = false;
}

void arrowkeys(int key, int x, int y){
    playerBall->handleCameraInput(key);
}

void update(int value) {
    float deltaTime = 0.016f;
    playerBall->updatePhysics(deltaTime);
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(int w, int h){
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, (float)w / h, 0.1f, 100.0f);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity(); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("ball game");

    playerBall = new ball(0.0f, 0.5f, 0.0f, 0.5f);
    renderLevel = new level(50.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard); // key pressed
    glutKeyboardUpFunc(keyboardUp); // key not pressed

    glutSpecialFunc(arrowkeys);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
