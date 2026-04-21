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
