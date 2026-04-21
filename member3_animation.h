#ifndef MEMBER3_ANIMATION_H
#define MEMBER3_ANIMATION_H

// ═══════════════════════════════════════════════════════════════════════════════
//  MEMBER 3 — Animation, Vehicles & Interaction Developer
//  Responsibility : Dynamic behaviour + user logic
//  Tasks          : Cars, Cloud, Animation timers, Signal logic, Keyboard input
// ═══════════════════════════════════════════════════════════════════════════════

// ── Vehicles ──────────────────────────────────────────────────────────────────
void drawCar (float r, float g, float b, bool trailer = false);
void car1();
void car2();
void car3();
void car4();

// ── Animated Objects ──────────────────────────────────────────────────────────
void moving_cloud();

// ── Animation Timer Callbacks ─────────────────────────────────────────────────
void update_car1  (int value);
void update_car2  (int value);
void update_car3  (int value);
void update_car4  (int value);
void update_cloud (int value);

// ── Signal Light State ────────────────────────────────────────────────────────
void redgreen1();   // red horizontal / green vertical
void redgreen2();   // green horizontal / red vertical

// ── User Interaction ──────────────────────────────────────────────────────────
void button (unsigned char key, int x, int y);

#endif
