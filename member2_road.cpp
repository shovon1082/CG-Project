// ═══════════════════════════════════════════════════════════════════════════════
//  MEMBER 2 — Road System, Lighting & Layout Engineer
//  Responsibility : Infrastructure + scene layout
//  Tasks          : Road/footpath, Traffic lights, Street lights, Fence
// ═══════════════════════════════════════════════════════════════════════════════

#include <windows.h>
#include <GL/glut.h>
#include "member2_road.h"
#include "member1_environment.h"   // rect()
#include "shared.h"                // circle()

// ── Road & Footpath ───────────────────────────────────────────────────────────

void road_footpath() {
    // Road surfaces
    rect(-2.0f, -0.5f, 2.0f, 0.5f, 95, 96, 91);   // horizontal road
    rect( 0.4f, -1.0f, 1.4f, 1.0f, 95, 96, 91);   // vertical road

    // Footpath slabs (grey border strips around road)
    float fp[][4] = {
        {-2.0f,  0.3f,  0.6f,  0.5f},   // top-left footpath
        {-2.0f, -0.5f,  0.6f, -0.3f},   // bottom-left footpath
        { 1.2f,  0.3f,  2.0f,  0.5f},   // top-right footpath
        { 1.2f, -0.5f,  2.0f, -0.3f},   // bottom-right footpath
        { 0.4f, -1.0f,  0.6f, -0.3f},   // left-vert footpath
        { 1.2f, -1.0f,  1.4f, -0.3f},   // right-vert footpath
        { 0.4f,  0.3f,  0.6f,  1.0f},   // top-left-vert footpath
        { 1.2f,  0.3f,  1.4f,  1.0f}    // top-right-vert footpath
    };
    for (auto& f : fp) rect(f[0], f[1], f[2], f[3], 176, 191, 189);

    // Center lane divider (dashed)
    glLineWidth(3.0f);
    glBegin(GL_LINES); glColor3ub(255, 255, 255);
    float segs[] = { -2.0f,-1.8f, -1.7f,-1.5f, -1.4f,-1.2f, -1.1f,-0.9f,
                     -0.8f,-0.6f, -0.5f,-0.3f, -0.2f, 0.0f,  1.7f, 1.9f };
    for (int i = 0; i < 16; i += 2) {
        glVertex2f(segs[i], 0); glVertex2f(segs[i + 1], 0);
    }
    glVertex2f(0.9f,  0.8f);  glVertex2f(0.9f,  0.97f);
    glVertex2f(0.9f, -0.97f); glVertex2f(0.9f, -0.8f);
    glEnd();

    // Zebra crossing stripes (thick horizontal / vertical bars)
    glLineWidth(10.0f);
    glBegin(GL_LINES); glColor3ub(255, 255, 255);
    for (float yy = -0.2f; yy <= 0.21f; yy += 0.1f) {
        glVertex2f(0.2f, yy); glVertex2f(0.4f, yy);   // left crossing
        glVertex2f(1.4f, yy); glVertex2f(1.6f, yy);   // right crossing
    }
    for (float xx = 0.7f; xx <= 1.11f; xx += 0.1f) {
        glVertex2f(xx,  0.5f); glVertex2f(xx,  0.7f); // top crossing
        glVertex2f(xx, -0.5f); glVertex2f(xx, -0.7f); // bottom crossing
    }
    glEnd();