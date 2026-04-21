#ifndef SHARED_H
#define SHARED_H

// ═══════════════════════════════════════════════════════════════════════════════
//  shared.h — Global variables & shared primitive shared by all three members
//  Include this in every .cpp that needs the globals or circle()
// ═══════════════════════════════════════════════════════════════════════════════

#include <math.h>
#define PI 3.14159265358979323846f

// ── Animation state (defined once in main.cpp) ────────────────────────────────
extern GLfloat position_cloud, speed_cloud;
extern GLfloat position_c1, speed_c1;
extern GLfloat position_c2, speed_c2;
extern GLfloat position_c3, speed_c3;
extern GLfloat position_c4, speed_c4;
extern int     cnt;   // 0 = green horizontal, non-zero = red horizontal

// ── Shared drawing primitive ──────────────────────────────────────────────────
// Draws a filled circle using GL_TRIANGLE_FAN.
// Used by Member 1 (trees, door arch), Member 2 (signal dots), Member 3 (cloud, signals).
void circle(float cx, float cy, float r, int R, int G, int B);

#endif
