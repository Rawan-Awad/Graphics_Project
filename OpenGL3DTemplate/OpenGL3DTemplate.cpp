#include "teamHeader.h"
#include <string>
#include <glut.h>
using namespace std;

// === GLOBAL DEFINITIONS ===
Player player = { 0.0f, 0.0f, 0.0f, 100.0f, 0, false };
float moveSpeed = 0.5f;
bool isFirstPerson = false;
GameLevel currentLevel = LEVEL1;

// === INIT ===
void initGame() {
    glEnable(GL_DEPTH_TEST);
    initLevel1();     // Team 2
    initLevel2();     // Team 3
    initSounds();     // Team 2
    initLighting();   // Team 3
}

// === INPUT ===
void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': case 'W': player.z -= moveSpeed; break;
    case 's': case 'S': player.z += moveSpeed; break;
    case 'a': case 'A': player.x -= moveSpeed; break;
    case 'd': case 'D': player.x += moveSpeed; break;
    case 27: exit(0); break; // ESC
    }
}

void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        toggleCameraView();
    }
}

void toggleCameraView() {
    isFirstPerson = !isFirstPerson;
}

// === CAMERA ===
void updateCamera() {
    if (isFirstPerson) {
        gluLookAt(player.x, player.y + 1.0f, player.z,
            player.x, player.y + 1.0f, player.z - 5,
            0.0f, 1.0f, 0.0f);
    }
    else {
        gluLookAt(player.x, player.y + 5.0f, player.z + 10.0f,
            player.x, player.y, player.z,
            0.0f, 1.0f, 0.0f);
    }
}

// === HUD ===
void drawHUD() {
    glColor3f(1, 1, 1);
    glRasterPos2f(-0.95f, 0.9f);
    string hud = "Score: " + to_string(player.score) + " | Stamina: " + to_string((int)player.stamina);
    for (char c : hud) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

// === LOGIC ===
void updateLevel1Logic() {
    // collision, pickups, stamina, level switch
}

void updateLevel2Logic() {
    // coin pickup, stamina loss, win check
}

// === LIGHTING ===
void updateLighting() {
    // dynamic lighting here
}

// === SOUND ===
void playSound(const std::string& type) {
    // play sfx by keyword
}

// === DISPLAY ===
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    updateCamera();
    if (currentLevel == LEVEL1) drawLevel1();
    else drawLevel2();

    drawHUD();
    glutSwapBuffers();
}

// === TIMER ===
void timer(int value) {
    if (currentLevel == LEVEL1) updateLevel1Logic();
    else updateLevel2Logic();

    animateLevel1Objects();
    animateLevel2Objects();
    updateLighting();

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// === MAIN ===
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Game Project");

    initGame();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(handleKeyboard);
    glutMouseFunc(handleMouse);

    glutMainLoop();
    return 0;
}
