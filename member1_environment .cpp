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

