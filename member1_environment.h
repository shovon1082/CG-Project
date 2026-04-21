#ifndef MEMBER1_ENVIRONMENT_H
#define MEMBER1_ENVIRONMENT_H

// ═══════════════════════════════════════════════════════════════════════════════
//  MEMBER 1 — Environment & Static Scene Designer
//  Responsibility : All non-moving background elements
//  Tasks          : Trees, Buildings, Structures, Graphics Primitives
// ═══════════════════════════════════════════════════════════════════════════════

// ── Graphics Primitives ───────────────────────────────────────────────────────
void rect      (float x1, float y1, float x2, float y2, int R, int G, int B);
void bitmapStr (const char* s, float px, float py, void* font, int R, int G, int B);
void winRow    (float x0, float y0, float x1, float y1, int cols,
                int R, int G, int B, int OR, int OG, int OB);
void sideWall  (float wx1, float wx2, float wy1, float wy2);

// ── Trees ─────────────────────────────────────────────────────────────────────
void circleTree (float tx, float ty);
void triTree    (float tx, float ty);
void tree       ();

// ── Buildings & Structures ────────────────────────────────────────────────────
void boys_hostel   ();
void girls_hostel  ();
void house         ();
void shop          ();
void university_diu();

#endif
