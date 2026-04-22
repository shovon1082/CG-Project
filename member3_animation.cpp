#include <windows.h>
#include <GL/glut.h>
#include "member3_animation.h"
#include "member1_environment.h"   // rect()
#include "shared.h"                // circle(), position/speed globals, cnt

// ── Shared Car Body Shape ─────────────────────────────────────────────────────
// The body is drawn facing right (+x direction); callers apply
// glTranslatef / glRotatef before calling this function.
void drawCar(float r, float g, float b, bool trailer) {
    // Main body
    glBegin(GL_POLYGON); glColor3ub(r, g, b);
    glVertex2f(-0.2f,  0.25f); glVertex2f( 0.07f, 0.25f);
    glVertex2f( 0.15f, 0.23f); glVertex2f( 0.17f, 0.2f);
    glVertex2f( 0.17f, 0.1f);  glVertex2f( 0.15f, 0.07f);
    glVertex2f( 0.07f, 0.05f); glVertex2f(-0.2f,  0.05f);
    glVertex2f(-0.22f, 0.07f); glVertex2f(-0.22f, 0.23f);
    glEnd();

    // Window (black glass)
    glBegin(GL_POLYGON); glColor3ub(0, 0, 0);
    glVertex2f( 0.07f, 0.24f); glVertex2f( 0.07f, 0.06f);
    glVertex2f(-0.18f, 0.06f); glVertex2f(-0.18f, 0.24f);
    glEnd();

    // Roof (body colour strip inside window)
    glBegin(GL_POLYGON); glColor3ub(r, g, b);
    glVertex2f( 0.03f, 0.09f); glVertex2f( 0.03f, 0.21f);
    glVertex2f(-0.15f, 0.21f); glVertex2f(-0.15f, 0.09f);
    glEnd();

    // Headlights
    rect(0.14f, 0.20f, 0.17f, 0.23f, 242, 242, 242);
    rect(0.14f, 0.07f, 0.17f, 0.10f, 242, 242, 242);

    // Optional trailer (truck / lorry body)
    if (trailer) rect(-0.5f, 0.05f, -0.06f, 0.25f, 242, 242, 242);
}

// ── Individual Car Render Functions ──────────────────────────────────────────

// Car 1 — red, drives left→right along horizontal road
void car1() {
    glPushMatrix();
    glTranslatef(position_c1, 0.0f, 0.0f);
    drawCar(230, 0, 0);
    glPopMatrix();
}

// Car 2 — yellow lorry, drives right→left (rotated 180°)
void car2() {
    glPushMatrix();
    glTranslatef(position_c2, 0.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 0.0f);
    drawCar(255, 204, 0, true);
    glPopMatrix();
}

// Car 3 — white, drives bottom→top along vertical road (rotated 90°)
void car3() {
    glPushMatrix();
    glTranslatef(0.9f, position_c3, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    drawCar(255, 255, 255);
    glPopMatrix();
}

// Car 4 — blue, drives top→bottom along vertical road (rotated 270°)
void car4() {
    glPushMatrix();
    glTranslatef(0.9f, position_c4, 0.0f);
    glRotatef(270.0f, 0.0f, 0.0f, 1.0f);
    drawCar(51, 102, 255);
    glPopMatrix();
}

// Cloud drifts left-to-right above the girls hostel area
void moving_cloud() {
    glPushMatrix();
    glTranslatef(position_cloud, 0.0f, 0.0f);

    // Base row of circles
    circle(0.0f,  -0.38f, 0.07f,  255, 255, 255);
    circle(0.1f,  -0.38f, 0.08f,  255, 255, 255);
    circle(0.2f,  -0.38f, 0.07f,  255, 255, 255);

    // Upper bumps
    circle(0.05f, -0.32f, 0.065f, 255, 255, 255);
    circle(0.15f, -0.30f, 0.07f,  255, 255, 255);

    // Flat bottom fill to clean up underside
    rect(-0.07f, -0.42f, 0.27f, -0.37f, 255, 255, 255);

    glPopMatrix();
}

// ── Animation Timer Callbacks ─────────────────────────────────────────────────

// Car 1: moves right when green (cnt==0), stops when red
void update_car1(int) {
    if (cnt == 0) {
        speed_c1 = 0.01f;
        if (position_c1 > 2.7f) position_c1 = -2.7f;  // wrap around
    } else {
        if (position_c1 > 0.0f) { speed_c1 = 0.0f; position_c1 = 0.0f; }
    }
    position_c1 += speed_c1;
    glutPostRedisplay();
    glutTimerFunc(10, update_car1, 0);
}

// Car 2: moves left when green (cnt==0), stops when red
void update_car2(int) {
    if (cnt == 0) {
        speed_c2 = 0.01f;
        if (position_c2 < -2.7f) position_c2 = 2.7f;  // wrap around
    } else {
        if (position_c2 < 1.8f) { speed_c2 = 0.0f; position_c2 = 1.8f; }
    }
    position_c2 -= speed_c2;
    glutPostRedisplay();
    glutTimerFunc(10, update_car2, 0);
}

// Car 3: moves upward when red (cnt!=0), stops when green
void update_car3(int) {
    if (cnt == 0) {
        if (position_c3 > -0.9f) { speed_c3 = 0.0f; position_c3 = -0.9f; }
    } else {
        speed_c3 = 0.01f;
        if (position_c3 > 1.7f) position_c3 = -1.7f;  // wrap around
    }
    position_c3 += speed_c3;
    glutPostRedisplay();
    glutTimerFunc(10, update_car3, 0);
}

// Car 4: moves downward when red (cnt!=0), stops when green
void update_car4(int) {
    if (cnt == 0) {
        if (position_c4 < 0.9f) { speed_c4 = 0.0f; position_c4 = 0.9f; }
    } else {
        speed_c4 = 0.01f;
        if (position_c4 < -1.7f) position_c4 = 1.7f;  // wrap around
    }
    position_c4 -= speed_c4;
    glutPostRedisplay();
    glutTimerFunc(10, update_car4, 0);
}

// Cloud animation: drift right, loop back when off-screen
void update_cloud(int) {
    position_cloud += speed_cloud;
    if (position_cloud > 2.1f) position_cloud = 1.1f;
    glutPostRedisplay();
    glutTimerFunc(50, update_cloud, 0);
}

// ── Signal Light State ────────────────────────────────────────────────────────

// Signal state 1: RED for horizontal road, GREEN for vertical road
void redgreen1() {
    circle(0.7f,  0.1f,  0.02f, 255,  51,  51);  // red   — traffic_light1
    circle(0.95f,-0.25f, 0.02f,   0, 255,   0);  // green — traffic_light2
}

// Signal state 2: GREEN for horizontal road, RED for vertical road
void redgreen2() {
    circle(0.7f,  0.0f,  0.02f,   0, 255,   0);  // green — traffic_light1
    circle(0.95f,-0.15f, 0.02f, 255,  51,  51);  // red   — traffic_light2
}

// ── Keyboard Input Handler ────────────────────────────────────────────────────
// F — switch from start screen to main scene
// R — set horizontal RED / vertical GREEN  (cnt becomes non-zero)
// G — set horizontal GREEN / vertical RED  (cnt = 0)
void button(unsigned char key, int, int) {
    extern void display();  // defined in main.cpp
    if      (key == 'f') { glutDisplayFunc(display); glutPostRedisplay(); }
    else if (key == 'r') cnt++;
    else if (key == 'g') cnt = 0;
}
