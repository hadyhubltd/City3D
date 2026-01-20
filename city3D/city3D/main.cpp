#include <GLUT/glut.h>
#include <cmath>
#include <vector>

// Camera settings
float cameraX = 0.0f, cameraY = 5.0f, cameraZ = 25.0f;
float cameraAngleX = 0.0f, cameraAngleY = 0.0f;
int lastMouseX = 0, lastMouseY = 0;
bool mousePressed = false;

// Animation
float carPosition = 0.0f;
float sunAngle = 45.0f;

// Building structure
struct Building {
    float x, z, width, height, depth;
    float r, g, b;
};

std::vector<Building> buildings;

void initBuildings() {
    // Create random buildings
    buildings.push_back({-15, -10, 3, 8, 3, 0.7f, 0.7f, 0.8f});
    buildings.push_back({-15, -3, 2.5f, 12, 2.5f, 0.6f, 0.6f, 0.7f});
    buildings.push_back({-15, 3, 3, 6, 3, 0.8f, 0.7f, 0.7f});
    buildings.push_back({-15, 9, 2, 15, 2, 0.5f, 0.5f, 0.6f});
    
    buildings.push_back({-8, -10, 2, 10, 2, 0.6f, 0.7f, 0.8f});
    buildings.push_back({-8, -5, 3.5f, 7, 3.5f, 0.7f, 0.6f, 0.7f});
    buildings.push_back({-8, 2, 2.5f, 13, 2.5f, 0.65f, 0.65f, 0.75f});
    buildings.push_back({-8, 8, 3, 9, 3, 0.7f, 0.7f, 0.8f});
    
    buildings.push_back({8, -10, 2.5f, 11, 2.5f, 0.6f, 0.6f, 0.7f});
    buildings.push_back({8, -4, 3, 8, 3, 0.75f, 0.7f, 0.75f});
    buildings.push_back({8, 3, 2, 14, 2, 0.55f, 0.55f, 0.65f});
    buildings.push_back({8, 9, 3.5f, 10, 3.5f, 0.7f, 0.65f, 0.75f});
    
    buildings.push_back({15, -10, 3, 7, 3, 0.65f, 0.7f, 0.8f});
    buildings.push_back({15, -4, 2, 12, 2, 0.6f, 0.65f, 0.7f});
    buildings.push_back({15, 4, 3, 9, 3, 0.7f, 0.7f, 0.75f});
    buildings.push_back({15, 10, 2.5f, 6, 2.5f, 0.75f, 0.7f, 0.8f});
}

void drawCube(float w, float h, float d) {
    float hw = w / 2, hh = h / 2, hd = d / 2;
    
    glBegin(GL_QUADS);
    // Front
    glNormal3f(0, 0, 1);
    glVertex3f(-hw, 0, hd); glVertex3f(hw, 0, hd);
    glVertex3f(hw, h, hd); glVertex3f(-hw, h, hd);
    // Back
    glNormal3f(0, 0, -1);
    glVertex3f(-hw, 0, -hd); glVertex3f(-hw, h, -hd);
    glVertex3f(hw, h, -hd); glVertex3f(hw, 0, -hd);
    // Left
    glNormal3f(-1, 0, 0);
    glVertex3f(-hw, 0, -hd); glVertex3f(-hw, 0, hd);
    glVertex3f(-hw, h, hd); glVertex3f(-hw, h, -hd);
    // Right
    glNormal3f(1, 0, 0);
    glVertex3f(hw, 0, -hd); glVertex3f(hw, h, -hd);
    glVertex3f(hw, h, hd); glVertex3f(hw, 0, hd);
    // Top
    glNormal3f(0, 1, 0);
    glVertex3f(-hw, h, -hd); glVertex3f(-hw, h, hd);
    glVertex3f(hw, h, hd); glVertex3f(hw, h, -hd);
    glEnd();
}

void drawBuilding(Building &b) {
    glPushMatrix();
    glTranslatef(b.x, 0, b.z);
    glColor3f(b.r, b.g, b.b);
    drawCube(b.width, b.height, b.depth);
    
    // Windows
    glColor3f(1.0f, 1.0f, 0.8f);
    for (float y = 1.0f; y < b.height - 0.5f; y += 1.5f) {
        for (float wx = -b.width/2 + 0.5f; wx < b.width/2 - 0.3f; wx += 0.8f) {
            glPushMatrix();
            glTranslatef(wx, y, b.depth/2 + 0.01f);
            glBegin(GL_QUADS);
            glVertex3f(-0.2f, 0, 0); glVertex3f(0.2f, 0, 0);
            glVertex3f(0.2f, 0.4f, 0); glVertex3f(-0.2f, 0.4f, 0);
            glEnd();
            glPopMatrix();
        }
    }
    glPopMatrix();
}

void drawGround() {
    glColor3f(0.3f, 0.3f, 0.35f);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-50, 0, -50);
    glVertex3f(50, 0, -50);
    glVertex3f(50, 0, 50);
    glVertex3f(-50, 0, 50);
    glEnd();
    
    // Roads
    glColor3f(0.2f, 0.2f, 0.2f);
    // Main road
    glBegin(GL_QUADS);
    glVertex3f(-2, 0.01f, -50);
    glVertex3f(2, 0.01f, -50);
    glVertex3f(2, 0.01f, 50);
    glVertex3f(-2, 0.01f, 50);
    glEnd();
    
    // Road lines
    glColor3f(1.0f, 1.0f, 0.0f);
    for (float z = -50; z < 50; z += 5) {
        glBegin(GL_QUADS);
        glVertex3f(-0.1f, 0.02f, z);
        glVertex3f(0.1f, 0.02f, z);
        glVertex3f(0.1f, 0.02f, z + 2);
        glVertex3f(-0.1f, 0.02f, z + 2);
        glEnd();
    }
}

void drawCar() {
    glPushMatrix();
    glTranslatef(0, 0.3f, carPosition);
    
    // Car body
    glColor3f(0.9f, 0.1f, 0.1f);
    glPushMatrix();
    glScalef(1.2f, 0.5f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Car top
    glPushMatrix();
    glTranslatef(0, 0.5f, -0.2f);
    glScalef(0.9f, 0.4f, 1.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Wheels
    glColor3f(0.1f, 0.1f, 0.1f);
    float wheelPositions[][2] = {{-0.5f, -0.7f}, {0.5f, -0.7f}, {-0.5f, 0.7f}, {0.5f, 0.7f}};
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(wheelPositions[i][0], -0.3f, wheelPositions[i][1]);
        glRotatef(90, 0, 1, 0);
        glutSolidTorus(0.1, 0.2, 10, 10);
        glPopMatrix();
    }
    
    glPopMatrix();
}

void drawSun() {
    glPushMatrix();
    glRotatef(sunAngle, 1, 0, 0);
    glTranslatef(0, 0, 30);
    glColor3f(1.0f, 0.9f, 0.3f);
    glutSolidSphere(2.0, 20, 20);
    glPopMatrix();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat lightPos[] = {0, 20, 0, 1};
    GLfloat lightAmb[] = {0.3f, 0.3f, 0.4f, 1};
    GLfloat lightDif[] = {0.8f, 0.8f, 0.7f, 1};
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    
    glClearColor(0.5f, 0.7f, 0.9f, 1.0f);
    
    initBuildings();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Camera
    glTranslatef(-cameraX, -cameraY, -cameraZ);
    glRotatef(cameraAngleX, 1, 0, 0);
    glRotatef(cameraAngleY, 0, 1, 0);
    
    drawSun();
    drawGround();
    
    for (auto &b : buildings) {
        drawBuilding(b);
    }
    
    drawCar();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void update(int value) {
    carPosition += 0.3f;
    if (carPosition > 50) carPosition = -50;
    
    sunAngle += 0.2f;
    if (sunAngle > 360) sunAngle -= 360;
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w': cameraZ -= 0.5f; break;
        case 's': cameraZ += 0.5f; break;
        case 'a': cameraX -= 0.5f; break;
        case 'd': cameraX += 0.5f; break;
        case 'q': cameraY += 0.5f; break;
        case 'e': cameraY -= 0.5f; break;
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        mousePressed = (state == GLUT_DOWN);
        lastMouseX = x;
        lastMouseY = y;
    }
}

void mouseMotion(int x, int y) {
    if (mousePressed) {
        cameraAngleY += (x - lastMouseX) * 0.5f;
        cameraAngleX += (y - lastMouseY) * 0.5f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("3D City - OpenGL");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();
    return 0;
}
