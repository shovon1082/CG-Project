#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "member1_environment.h"
#include "shared.h"

// ── Graphics Primitives ───────────────────────────────────────────────────────

void rect(float x1, float y1, float x2, float y2, int R, int G, int B) {
    glColor3ub(R, G, B);
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1); glVertex2f(x1, y2);
    glVertex2f(x2, y2); glVertex2f(x2, y1);
    glEnd();
}

void bitmapStr(const char* s, float px, float py, void* font, int R, int G, int B) {
    glColor3ub(R, G, B);
    glRasterPos2f(px, py);
    for (int i = 0; s[i]; i++) glutBitmapCharacter(font, s[i]);
}

// Draw a row of 'cols' windows across [x0,x1], each window height [y0,y1]
void winRow(float x0, float y0, float x1, float y1, int cols,
            int R, int G, int B, int OR, int OG, int OB) {
    float step = (x1 - x0) / cols;
    float pw   = step * 0.55f;
    float pad  = step * 0.225f;
    for (int i = 0; i < cols; i++) {
        float lx = x0 + i * step + pad;
        rect(lx, y0, lx + pw, y1, R, G, B);
        glLineWidth(1.0f);
        glBegin(GL_LINES); glColor3ub(OR, OG, OB);
        glVertex2f(lx,          y0); glVertex2f(lx + pw,      y0);
        glVertex2f(lx + pw,     y0); glVertex2f(lx + pw,      y1);
        glVertex2f(lx + pw,     y1); glVertex2f(lx,           y1);
        glVertex2f(lx,          y1); glVertex2f(lx,           y0);
        glVertex2f(lx + pw / 2, y0); glVertex2f(lx + pw / 2, y1);
        glEnd();
    }
}

// Draw a red brick side wall with horizontal brick lines
void sideWall(float wx1, float wx2, float wy1, float wy2) {
    rect(wx1, wy1, wx2, wy2, 180, 30, 30);
    glLineWidth(1.5f);
    glBegin(GL_LINES); glColor3ub(120, 20, 20);
    glVertex2f(wx1, wy1); glVertex2f(wx2, wy1);
    glVertex2f(wx2, wy1); glVertex2f(wx2, wy2);
    glVertex2f(wx2, wy2); glVertex2f(wx1, wy2);
    glVertex2f(wx1, wy2); glVertex2f(wx1, wy1);
    for (float yy = wy1 + 0.1f; yy < wy2; yy += 0.1f) {
        glVertex2f(wx1, yy); glVertex2f(wx2, yy);
    }
    glEnd();
}

// ── Trees ─────────────────────────────────────────────────────────────────────

// Draw a circle-foliage tree at base position (tx, ty)
void circleTree(float tx, float ty) {
    glLineWidth(10.0f);
    glBegin(GL_LINES); glColor3ub(153, 51, 51);
    glVertex2f(tx, ty + 0.25f); glVertex2f(tx, ty);
    glEnd();
    circle(tx - 0.05f, ty + 0.27f, 0.08f, 0, 153, 51);
    circle(tx,         ty + 0.30f, 0.08f, 0, 153, 51);
    circle(tx + 0.05f, ty + 0.27f, 0.08f, 0, 153, 51);
    glPointSize(5.0f);
    glBegin(GL_POINTS); glColor3f(1, 0, 0);
    glVertex2f(tx - 0.03f, ty + 0.30f);
    glVertex2f(tx + 0.03f, ty + 0.25f);
    glEnd();
}

// Draw a triangle-foliage tree at base position (tx, ty)
void triTree(float tx, float ty) {
    glBegin(GL_LINES); glColor3ub(153, 51, 51);
    glVertex2f(tx, ty); glVertex2f(tx, ty + 0.15f);
    glEnd();
    glBegin(GL_TRIANGLES); glColor3ub(0, 153, 51);
    glVertex2f(tx - 0.1f, ty + 0.05f);
    glVertex2f(tx,        ty + 0.30f);
    glVertex2f(tx + 0.1f, ty + 0.05f);
    glEnd();
}

// Place all trees in the scene
void tree() {
    circleTree(-1.5f, 0.55f);
    circleTree(-0.8f, 0.57f);
    triTree(1.55f, 0.65f);
    triTree(-0.2f, 0.65f);
    triTree(1.9f,  0.70f);
}


void boys_hostel() {
    // Main body + roof strip
    rect(1.42f, 0.5f,  2.0f,  1.0f,  240, 220, 190);
    rect(1.42f, 1.0f,  2.0f,  1.02f, 140,  60,  60);

    // Horizontal floor divider lines
    glLineWidth(1.5f);
    glBegin(GL_LINES); glColor3ub(180, 160, 130);
    glVertex2f(1.42f, 0.625f); glVertex2f(2.0f, 0.625f);
    glVertex2f(1.42f, 0.75f);  glVertex2f(2.0f, 0.75f);
    glVertex2f(1.42f, 0.875f); glVertex2f(2.0f, 0.875f);
    glEnd();

    // Windows: 4 floors x 4 columns
    float fy[] = { 0.52f, 0.645f, 0.77f, 0.895f };
    for (int f = 0; f < 4; f++)
        winRow(1.42f, fy[f], 2.0f, fy[f] + 0.08f, 4, 135, 206, 235, 70, 70, 70);

    // Building outline
    glLineWidth(1.0f);
    glBegin(GL_LINES); glColor3ub(100, 80, 60);
    glVertex2f(1.42f, 0.5f); glVertex2f(2.0f,  0.5f);
    glVertex2f(2.0f,  0.5f); glVertex2f(2.0f,  1.0f);
    glVertex2f(2.0f,  1.0f); glVertex2f(1.42f, 1.0f);
    glVertex2f(1.42f, 1.0f); glVertex2f(1.42f, 0.5f);
    glEnd();

    // Door + door frame
    rect(1.66f, 0.5f, 1.76f, 0.62f, 101, 67, 33);
    glLineWidth(1.5f);
    glBegin(GL_LINES); glColor3ub(60, 30, 10);
    glVertex2f(1.66f, 0.5f);  glVertex2f(1.66f, 0.62f);
    glVertex2f(1.66f, 0.62f); glVertex2f(1.76f, 0.62f);
    glVertex2f(1.76f, 0.62f); glVertex2f(1.76f, 0.5f);
    glVertex2f(1.71f, 0.5f);  glVertex2f(1.71f, 0.62f);
    glEnd();

    // Name board
    rect(1.56f, 0.62f, 1.86f, 0.67f, 0, 51, 102);
    bitmapStr("YKSG-1", 1.685f, 0.633f, GLUT_BITMAP_HELVETICA_12, 255, 255, 255);

    // Red brick side walls
    sideWall(1.38f, 1.42f, 0.5f, 1.02f);
    sideWall(2.0f,  2.04f, 0.5f, 1.02f);
}

void girls_hostel() {
    // Main body + roof strip
    rect(1.45f, -1.0f,  2.05f, -0.55f, 255, 228, 225);
    rect(1.45f, -0.55f, 2.05f, -0.52f, 180,  60,  90);

    // Horizontal floor divider lines
    glLineWidth(1.5f);
    glBegin(GL_LINES); glColor3ub(200, 170, 165);
    glVertex2f(1.45f, -0.68f); glVertex2f(2.05f, -0.68f);
    glVertex2f(1.45f, -0.81f); glVertex2f(2.05f, -0.81f);
    glVertex2f(1.45f, -0.94f); glVertex2f(2.05f, -0.94f);
    glEnd();

    // Windows: 4 rows x 4 columns
    float fy[] = { -0.57f, -0.70f, -0.83f, -0.96f };
    for (int f = 0; f < 4; f++)
        winRow(1.45f, fy[f] - 0.08f, 2.05f, fy[f], 4, 173, 216, 230, 100, 80, 100);

    // Building outline
    glLineWidth(1.0f);
    glBegin(GL_LINES); glColor3ub(140, 80, 90);
    glVertex2f(1.45f, -0.55f); glVertex2f(2.05f, -0.55f);
    glVertex2f(2.05f, -0.55f); glVertex2f(2.05f, -1.0f);
    glVertex2f(2.05f, -1.0f);  glVertex2f(1.45f, -1.0f);
    glVertex2f(1.45f, -1.0f);  glVertex2f(1.45f, -0.55f);
    glEnd();

    // Door + door frame
    rect(1.70f, -1.0f, 1.80f, -0.82f, 130, 60, 80);
    glLineWidth(1.5f);
    glBegin(GL_LINES); glColor3ub(80, 20, 40);
    glVertex2f(1.70f, -1.0f);  glVertex2f(1.70f, -0.82f);
    glVertex2f(1.70f, -0.82f); glVertex2f(1.80f, -0.82f);
    glVertex2f(1.80f, -0.82f); glVertex2f(1.80f, -1.0f);
    glVertex2f(1.75f, -1.0f);  glVertex2f(1.75f, -0.82f);
    glEnd();

    // Name board
    rect(1.60f, -0.82f, 1.90f, -0.77f, 160, 30, 70);
    bitmapStr("RASG-2", 1.691f, -0.808f, GLUT_BITMAP_HELVETICA_12, 255, 255, 255);

    // Red brick side walls
    sideWall(1.41f, 1.45f, -1.0f, -0.52f);
    sideWall(2.05f, 2.09f, -1.0f, -0.52f);
}

void shop() {
    // ── Left shop ──────────────────────────────────────────────────────────────
    rect(-1.95f, 0.5f,  -1.55f, 0.75f, 255, 255, 255);  // body
    rect(-1.95f, 0.75f, -1.55f, 0.85f, 128,   0,   0);  // roof

    // Awning / shelter
    glBegin(GL_POLYGON); glColor3ub(255, 0, 0);
    glVertex2f(-2.0f, 0.65f); glVertex2f(-1.5f,  0.65f);
    glVertex2f(-1.5f, 0.7f);  glVertex2f(-1.55f, 0.75f);
    glVertex2f(-1.95f, 0.75f);glVertex2f(-2.0f,  0.7f);
    glEnd();

    rect(-1.9f,  0.5f,  -1.82f, 0.62f, 0, 230, 230);  // door
    rect(-1.77f, 0.55f, -1.6f,  0.62f, 0, 230, 230);  // window

    glBegin(GL_LINES); glColor3ub(128, 0, 0);
    glVertex2f(-1.52f, 0.5f); glVertex2f(-1.98f, 0.5f);
    glEnd();

    bitmapStr("BFC", -1.8f, 0.78f, GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

    // ── Right shop ─────────────────────────────────────────────────────────────
    rect(-0.75f, 0.5f,  -0.2f,  0.8f,  255, 204, 102);  // body
    rect(-0.75f, 0.8f,  -0.2f,  0.85f, 179,  89,   0);  // roof strip
    rect(-0.73f, 0.6f,  -0.22f, 0.75f,  77,  38,   0);  // interior display
    rect(-0.73f, 0.5f,  -0.22f, 0.6f,  128,  64,   0);  // counter / table

    // Awning / shelter
    glBegin(GL_POLYGON); glColor3ub(230, 115, 0);
    glVertex2f(-0.8f,  0.7f);  glVertex2f(-0.15f, 0.7f);
    glVertex2f(-0.15f, 0.75f); glVertex2f(-0.2f,  0.8f);
    glVertex2f(-0.75f, 0.8f);  glVertex2f(-0.8f,  0.75f);
    glEnd();

    bitmapStr("Candy Shop", -0.6f, 0.84f, GLUT_BITMAP_9_BY_15, 255, 255, 0);
}

void house() {
    // ── Left house ─────────────────────────────────────────────────────────────
    rect(-1.4f, 0.5f, -0.9f, 1.0f, 224, 228, 231);   // body

    // Windows
    rect(-1.35f, 0.55f, -1.25f, 0.65f, 179, 230, 255);
    rect(-1.05f, 0.55f, -0.95f, 0.65f, 179, 230, 255);
    rect(-1.35f, 0.85f, -1.25f, 0.95f, 179, 230, 255);
    rect(-1.2f,  0.85f, -1.1f,  0.95f, 179, 230, 255);
    rect(-1.05f, 0.85f, -0.95f, 0.95f, 179, 230, 255);

    rect(-1.2f, 0.5f, -1.1f, 0.65f, 153, 153, 153);  // door

    // Awning
    glBegin(GL_POLYGON); glColor3ub(76, 174, 218);
    glVertex2f(-1.4f,  0.8f);  glVertex2f(-1.45f, 0.75f);
    glVertex2f(-1.45f, 0.7f);  glVertex2f(-0.85f, 0.7f);
    glVertex2f(-0.85f, 0.75f); glVertex2f(-0.9f,  0.8f);
    glEnd();

    glLineWidth(1.5f);
    glBegin(GL_LINES); glColor3ub(128, 0, 0);
    glVertex2f(-0.87f, 0.5f); glVertex2f(-1.43f, 0.5f);
    glEnd();

    // ── Right house ────────────────────────────────────────────────────────────
    rect(-0.15f, 0.5f,  0.35f, 0.8f,  153,  51,   0);  // main body
    rect( 0.05f, 0.8f,  0.35f, 0.99f, 153,  51,   0);  // upper store room

    // Windows
    rect(0.05f, 0.6f,  0.15f, 0.7f,  77, 184, 255);
    rect(0.2f,  0.6f,  0.3f,  0.7f,  77, 184, 255);
    rect(0.15f, 0.85f, 0.25f, 0.95f, 77, 184, 255);

    rect(-0.1f, 0.5f, 0.0f, 0.65f, 77, 77, 77);  // door

    // Door canopy
    glBegin(GL_POLYGON); glColor3ub(230, 115, 0);
    glVertex2f(0.02f, 0.65f); glVertex2f(-0.05f, 0.7f); glVertex2f(-0.12f, 0.65f);
    glEnd();

    // Roof railing
    glLineWidth(2.0f);
    glBegin(GL_LINES); glColor3ub(255, 153, 51);
    glVertex2f(0.36f,  0.8f);  glVertex2f(-0.16f, 0.8f);
    glVertex2f(0.36f,  0.84f); glVertex2f(-0.16f, 0.84f);
    glVertex2f(-0.16f, 0.5f);  glVertex2f( 0.36f, 0.5f);
    glEnd();
}

void university_diu() {
    // Main building body
    rect(-2.0f, -1.0f, 0.35f, -0.55f, 245, 230, 200);

    // Central tower base + triangular roof
    rect(-0.95f, -0.62f, -0.55f, -0.55f, 210, 180, 140);
    glBegin(GL_TRIANGLES); glColor3ub(153, 0, 0);
    glVertex2f(-0.95f, -0.62f);
    glVertex2f(-0.75f, -0.8f);
    glVertex2f(-0.55f, -0.62f);
    glEnd();

    // Wing roofs
    rect(-2.0f,  -0.6f, -0.95f, -0.55f, 153, 0, 0);
    rect(-0.55f, -0.6f,  0.35f, -0.55f, 153, 0, 0);

    // Main entrance door + semicircular arch
    rect(-0.82f, -1.0f, -0.68f, -0.82f, 101, 67, 33);
    circle(-0.75f, -0.82f, 0.07f, 101, 67, 33);

    // Windows: 2 rows x 4 cols per wing
    float wr1[] = { -0.72f, -0.65f };
    float wr2[] = { -0.85f, -0.78f };
    winRow(-2.0f,  wr1[1], -1.05f, wr1[0], 4, 135, 206, 235, 80, 80, 80);
    winRow(-2.0f,  wr2[1], -1.05f, wr2[0], 4, 135, 206, 235, 80, 80, 80);
    winRow(-0.52f, wr1[1],  0.35f, wr1[0], 4, 135, 206, 235, 80, 80, 80);
    winRow(-0.52f, wr2[1],  0.35f, wr2[0], 4, 135, 206, 235, 80, 80, 80);

    // Building outline
    glLineWidth(1.5f);
    glBegin(GL_LINES); glColor3ub(100, 80, 60);
    glVertex2f(-2.0f, -0.55f); glVertex2f( 0.35f, -0.55f);
    glVertex2f(-2.0f, -1.0f);  glVertex2f( 0.35f, -1.0f);
    glVertex2f(-2.0f, -0.55f); glVertex2f(-2.0f,  -1.0f);
    glVertex2f( 0.35f,-0.55f); glVertex2f( 0.35f, -1.0f);
    glColor3ub(60, 30, 10);
    glVertex2f(-0.82f, -1.0f);  glVertex2f(-0.82f, -0.82f);
    glVertex2f(-0.68f, -1.0f);  glVertex2f(-0.68f, -0.82f);
    glVertex2f(-0.82f, -0.82f); glVertex2f(-0.68f, -0.82f);
    glEnd();

    // Entrance columns
    glLineWidth(3.0f);
    glBegin(GL_LINES); glColor3ub(180, 160, 120);
    glVertex2f(-0.88f, -1.0f); glVertex2f(-0.88f, -0.62f);
    glVertex2f(-0.62f, -1.0f); glVertex2f(-0.62f, -0.62f);
    glEnd();

    bitmapStr("DIU", -0.815f, -0.61f, GLUT_BITMAP_HELVETICA_18, 0, 51, 153);
    bitmapStr("Daffodil International University", -1.95f, -0.58f, GLUT_BITMAP_HELVETICA_10, 80, 0, 0);
}


