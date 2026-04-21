#ifndef MEMBER2_ROAD_H
#define MEMBER2_ROAD_H

// ═══════════════════════════════════════════════════════════════════════════════
//  MEMBER 2 — Road System, Lighting & Layout Engineer
//  Responsibility : Infrastructure + scene layout
//  Tasks          : Road/footpath, Traffic lights, Street lights, Fence
// ═══════════════════════════════════════════════════════════════════════════════

// ── Road & Footpath ───────────────────────────────────────────────────────────
void road_footpath();

// ── Traffic Signal Structures ─────────────────────────────────────────────────
void lightBox      (float bx,  float by,  float bx2, float by2,
                    float rx,  float ry,
                    float yx,  float yy,
                    float gx,  float gy);
void traffic_light1();
void traffic_light2();

// ── Street Lights ─────────────────────────────────────────────────────────────
void lamp      (float ax, float ay, float bx, float by,
                float cx, float cy, float cx2, float cy2);
void road_light();

// ── Fence ─────────────────────────────────────────────────────────────────────
void fence();

#endif
