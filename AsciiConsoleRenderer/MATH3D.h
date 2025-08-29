#ifndef MATH3D_H
#define MATH3D_H

#include <math.h>
#include <stdio.h>

// ---------------- VECTEURS ----------------

// Vecteur 2D
typedef struct { float x, y; } vec2;
static inline vec2 make_vec2(float x, float y) { return (vec2){ x, y }; }
vec2 vec2_add(vec2 a, vec2 b) { return (vec2){a.x+b.x, a.y+b.y}; }
vec2 vec2_sub(vec2 a, vec2 b) { return (vec2){a.x-b.x, a.y-b.y}; }
vec2 vec2_scale(vec2 v, float s) { return (vec2){v.x*s, v.y*s}; }
float vec2_dot(vec2 a, vec2 b) { return a.x*b.x + a.y*b.y; }

// Vecteur 3D
typedef struct { float x, y, z; } vec3;
static inline vec3 make_vec3(float x, float y, float z) { return (vec3){ x, y, z }; }
vec3 vec3_add(vec3 a, vec3 b) { return (vec3){a.x+b.x, a.y+b.y, a.z+b.z}; }
vec3 vec3_sub(vec3 a, vec3 b) { return (vec3){a.x-b.x, a.y-b.y, a.z-b.z}; }
vec3 vec3_scale(vec3 v, float s) { return (vec3){v.x*s, v.y*s, v.z*s}; }
float vec3_dot(vec3 a, vec3 b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
vec3 vec3_cross(vec3 a, vec3 b) {
    return (vec3){a.y*b.z - a.z*b.y,
                  a.z*b.x - a.x*b.z,
                  a.x*b.y - a.y*b.x};
}
float vec3_length(vec3 v) { return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z); }
vec3 vec3_normalize(vec3 v) {
    float len = vec3_length(v);
    if(len == 0) return v;
    return vec3_scale(v, 1.0f/len);
}

// Vecteur 4D
typedef struct { float x, y, z, w; } vec4;
static inline vec4 make_vec4(float x, float y, float z, float w) { return (vec4){ x, y, z, w }; }
vec4 vec4_add(vec4 a, vec4 b) { return (vec4){a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w}; }
vec4 vec4_sub(vec4 a, vec4 b) { return (vec4){a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w}; }
vec4 vec4_scale(vec4 v, float s) { return (vec4){v.x*s, v.y*s, v.z*s, v.w*s}; }
float vec4_dot(vec4 a, vec4 b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; }

// ---------------- MATRICES ----------------

// Matrice 2x2
typedef struct { float m[2][2]; } mat2;
mat2 mat2_identity() { return (mat2){{{1,0},{0,1}}}; }
mat2 mat2_mul(mat2 a, mat2 b){
    mat2 r;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            r.m[i][j] = a.m[i][0]*b.m[0][j] + a.m[i][1]*b.m[1][j];
    return r;
}
vec2 mat2_mul_vec2(mat2 m, vec2 v) {
    return (vec2){ m.m[0][0]*v.x + m.m[0][1]*v.y,
                   m.m[1][0]*v.x + m.m[1][1]*v.y };
}

// Matrice 3x3
typedef struct { float m[3][3]; } mat3;
mat3 mat3_identity() {
    return (mat3){{{1,0,0},{0,1,0},{0,0,1}}};
}
mat3 mat3_mul(mat3 a, mat3 b){
    mat3 r;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            r.m[i][j]=0;
            for(int k=0;k<3;k++)
                r.m[i][j]+=a.m[i][k]*b.m[k][j];
        }
    return r;
}
vec3 mat3_mul_vec3(mat3 m, vec3 v){
    return (vec3){ m.m[0][0]*v.x + m.m[0][1]*v.y + m.m[0][2]*v.z,
                   m.m[1][0]*v.x + m.m[1][1]*v.y + m.m[1][2]*v.z,
                   m.m[2][0]*v.x + m.m[2][1]*v.y + m.m[2][2]*v.z };
}

// Matrice 4x4
typedef struct { float m[4][4]; } mat4;
mat4 mat4_identity(){
    mat4 r = {{{0}}};
    for(int i=0;i<4;i++) r.m[i][i]=1.0f;
    return r;
}
// Génère une matrice de translation
mat4 mat4_translation(vec3 t) {
    mat4 m = mat4_identity();
    m.m[0][3] = t.x;
    m.m[1][3] = t.y;
    m.m[2][3] = t.z;
    return m;
}
mat4 mat4_mul(mat4 a, mat4 b){
    mat4 r = {{{0}}};
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            for(int k=0;k<4;k++)
                r.m[i][j]+=a.m[i][k]*b.m[k][j];
    return r;
}
vec4 mat4_mul_vec4(mat4 m, vec4 v){
    return (vec4){
        m.m[0][0]*v.x + m.m[0][1]*v.y + m.m[0][2]*v.z + m.m[0][3]*v.w,
        m.m[1][0]*v.x + m.m[1][1]*v.y + m.m[1][2]*v.z + m.m[1][3]*v.w,
        m.m[2][0]*v.x + m.m[2][1]*v.y + m.m[2][2]*v.z + m.m[2][3]*v.w,
        m.m[3][0]*v.x + m.m[3][1]*v.y + m.m[3][2]*v.z + m.m[3][3]*v.w
    };
}
mat4 mat4_perspective(float fovY, float aspect, float nearp, float farp) {
    float f = 1.0f / tanf(fovY * 0.5f);
    mat4 m;
    int i, j;
    for(i=0;i<4;i++) for(j=0;j<4;j++) m.m[i][j]=0.0f;
    m.m[0][0] = f / aspect;
    m.m[1][1] = f;
    m.m[2][2] = -(farp + nearp) / (farp - nearp);
    m.m[2][3] = -(2.0f * farp * nearp) / (farp - nearp);
    m.m[3][2] = -1.0f;
    return m;
}
// Applique une rotation à une matrice 4x4 existante
mat4 mat4_rotation(mat4* mat, float angle, vec3 axis) {
    float c = cosf(angle);
    float s = sinf(angle);
    float t = 1.0f - c;
    axis = vec3_normalize(axis);
    float x = axis.x, y = axis.y, z = axis.z;

    mat4 rot = {{{0}}};
    rot.m[0][0] = t*x*x + c;
    rot.m[0][1] = t*x*y - s*z;
    rot.m[0][2] = t*x*z + s*y;
    rot.m[0][3] = 0.0f;

    rot.m[1][0] = t*x*y + s*z;
    rot.m[1][1] = t*y*y + c;
    rot.m[1][2] = t*y*z - s*x;
    rot.m[1][3] = 0.0f;

    rot.m[2][0] = t*x*z - s*y;
    rot.m[2][1] = t*y*z + s*x;
    rot.m[2][2] = t*z*z + c;
    rot.m[2][3] = 0.0f;

    rot.m[3][0] = 0.0f;
    rot.m[3][1] = 0.0f;
    rot.m[3][2] = 0.0f;
    rot.m[3][3] = 1.0f;

    return mat4_mul(*mat, rot);
}
mat4 mat4_scale(mat4* mat, vec3 k){
    mat4 scale = {{{0}}};
    scale.m[0][0] = k.x;
    scale.m[1][1] = k.y;
    scale.m[2][2] = k.z;
    scale.m[3][3] = 1.0;
    return mat4_mul(*mat, scale); 
}

// ---------------- UTILITAIRES ----------------
void vec3_print(vec3 v){ printf("[%f,%f,%f]\n",v.x,v.y,v.z); }
void vec4_print(vec4 v){ printf("[%f,%f,%f,%f]\n",v.x,v.y,v.z,v.w); }

#endif // MATH3D_H
