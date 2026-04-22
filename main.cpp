// ═══════════════════════════════════════════════════════════════════════════════
//  main.cpp — Entry point & scene orchestration
//  Owns: global state, display(), start(), inigl(), main()
//  Delegates rendering to Member 1, 2, 3 modules.
// ═══════════════════════════════════════════════════════════════════════════════

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

#include "shared.h"
#include "member1_environment.h"
#include "member2_road.h"
#include "member3_animation.h"

// ── Global state definitions (declared extern in shared.h) ────────────────────
GLfloat position_cloud = 1.45f, speed_cloud = 0.008f;
GLfloat position_c1    = 1.6f,  speed_c1    = 0.01f;
GLfloat position_c2    = 2.4f,  speed_c2    = 0.01f;
GLfloat position_c3    = -0.9f, speed_c3    = 0.01f;
GLfloat position_c4    = 0.9f,  speed_c4    = 0.01f;
int     cnt            = 0;

// ── Shared circle primitive (single definition, used by all modules) ──────────
void circle(float cx, float cy, float r, int R, int G, int B) {
    float twicePi = 2.0f * PI;
    glColor3ub(R, G, B);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 50; i++)
        glVertex2f(cx + r * cos(i * twicePi / 50),
                   cy + r * sin(i * twicePi / 50));
    glEnd();
}

// ── Start / title screen ──────────────────────────────────────────────────────
void start() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Gradient background
    glBegin(GL_POLYGON);
    glColor3ub(255, 255,   0); glVertex2f(-2,  2);
    glColor3ub(147, 112, 219); glVertex2f( 2,  2);
    glColor3ub( 30, 144, 255); glVertex2f( 2, -2);
    glColor3ub( 70, 130, 180); glVertex2f(-2, -2);
    glEnd();

    bitmapStr("Traffic  Signal  In  The  City",
              -0.3f,  0.7f, GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);
    bitmapStr("Feature:",
              -1.5f,  0.3f, GLUT_BITMAP_TIMES_ROMAN_24,   0,   0,   0);
    bitmapStr("-> Press 'R' = Turn on RED signal for HORIZONTAL road"
              " and Turn on GREEN signal for VERTICAL road.",
              -1.5f,  0.2f, GLUT_BITMAP_TIMES_ROMAN_24,   0,   0,   0);
    bitmapStr("-> Press 'G' = Turn on GREEN signal for HORIZONTAL road"
              " and Turn on RED signal for VERTICAL road.",
              -1.5f,  0.1f, GLUT_BITMAP_TIMES_ROMAN_24,   0,   0,   0);
    bitmapStr("Press F to START the project",
              -0.3f, -0.7f, GLUT_BITMAP_TIMES_ROMAN_24, 255,   0,   0);
    glFlush();
}

// ── Main scene ────────────────────────────────────────────────────────────────
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // ── Layer 1: Ground ───────────────────────────────────────────────────────
    // Green background (grass / ground)
    rect(-2.0f, -1.0f, 2.0f, 1.0f, 51, 204, 51);

    // ── Layer 2: Road & Footpath ──────────────────────────────────────────────
    // Road must be drawn before buildings/trees so structures appear on top
    road_footpath();

    // ── Layer 3: Static environment (buildings & trees) ───────────────────────
    // Member 1: these sit on the ground / footpath, below moving objects
    tree();
    boys_hostel();
    girls_hostel();
    house();
    shop();
    university_diu();


    // Shop open sign (small overlay label on the shop building)
    rect(-1.72f, 0.57f, -1.65f, 0.60f, 255, 255, 204);
    bitmapStr("open", -1.715f, 0.58f, GLUT_BITMAP_HELVETICA_10, 255, 51, 0);

    // ── Layer 4: Animated vehicles & cloud ────────────────────────────────────
    // Member 3: drawn BEFORE lights so lights always appear on top of cars
    car1(); car2(); car3(); car4();
    moving_cloud();

    // ── Layer 5: Road infrastructure — always on top of vehicles ─────────────
    // Member 2: traffic lights, street lights, fence drawn LAST so cars
    // pass underneath them and never overlap the signal hardware.
    traffic_light1();
    traffic_light2();
    road_light();
    fence();

    // ── Layer 6: Active signal light glow (topmost overlay) ──────────────────
    if (cnt == 0) redgreen2(); else redgreen1();

    glFlush();
}

// ── OpenGL initialisation ─────────────────────────────────────────────────────
void inigl() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(-2, 2, -1, 1);
}

// ── Entry point ───────────────────────────────────────────────────────────────
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1430, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Traffic Signal In The City");

    cout << "Project Title: Traffic Signal In The City\n\n";
    cout << "Group Members:\n";
    cout << "Md. Sanaullah Islam Shovon\t0242310005101082\n";
    cout << "Md. Farvez Rakib\t\t0242310005101374\n";
    cout << "Omar Faruk\t\t\t0242310005101659\n";

    glutDisplayFunc(start);
    inigl();

    // Register animation timers (Member 3)
    glutTimerFunc(50, update_cloud, 0);
    glutTimerFunc(10, update_car1,  0);
    glutTimerFunc(10, update_car2,  0);
    glutTimerFunc(10, update_car3,  0);
    glutTimerFunc(10, update_car4,  0);

    // Register keyboard handler (Member 3)
    glutKeyboardFunc(button);

    glutMainLoop();
    return 0;
}
