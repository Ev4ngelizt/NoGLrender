
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<limits.h>
#include<unistd.h>
#include "MATH3D.h"
#include "VERTICES.h"
#define WIDTH 279
#define HEIGHT 69
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

char getLight(float intensity){
    const char lightMap[] = "..:-=+*#%@@";
    const int count = 10;
    return lightMap[(int)(intensity*count)];
}
char frameBuffer[HEIGHT][WIDTH];
float zBuffer[HEIGHT][WIDTH];
int fps = 144;
double currentFrame = 0;
double lastFrame = 0;
double deltaTime = 0;
vec3 lightPos = (vec3){1.0, 1.0, 1.0};

void draw2dLine(vec4 A, vec4 B, mat4 model, mat4 view, mat4 projection);
void drawLines(float vertices[], int count, mat4 model, mat4 view, mat4 projection);
void drawLinesCycl(float vertices[], int count, mat4 model, mat4 view, mat4 projection);
void drawTriangle(vec4 A, vec4 B, vec4 C, mat4 model, mat4 view, mat4 projection);
void drawTrianglesFromData(float vertices[], int count, mat4 model, mat4 view, mat4 projection);
void drawTrianglesFromIndexedData(float vertices[], int indices[], int indexCount,mat4 model, mat4 view, mat4 projection);
vec4 processVertex(vec4 v, mat4 model, mat4 view, mat4 projection);
vec3 homoToNdc(vec4 vertex);
vec2 ndcToScreen(vec3 ndc);

void setConsoleFont() {
    CONSOLE_FONT_INFOEX cfi;    
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 8; // largeur du caractère
    cfi.dwFontSize.Y = 8; // hauteur du caractère
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
int main(){
    setConsoleFont();
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            frameBuffer[i][j] = '@';
        }
        frameBuffer[i][WIDTH] = '\0';
    }

    setvbuf(stdout, NULL, _IONBF, 0);
    printf("\033[H\033[J");
    printf("\033[?25l");
    double angle = 0.0f;
    while(1){
        // Calculate deltaTime
        lastFrame = currentFrame;
        currentFrame = clock()/(double)CLOCKS_PER_SEC;
        deltaTime = currentFrame - lastFrame;

        // Clear buffer
        for(int i=0; i<HEIGHT; i++){
            for(int j=0; j<WIDTH; j++){
                frameBuffer[i][j] = ' ';
                zBuffer[i][j] = (float)INT_MAX;
            }
        }

        mat4 model = mat4_identity();
        double angularSpeed = M_PI/4;
        angle += angularSpeed*deltaTime; // *1.0 = vitesse
        model = mat4_scale(&model, (vec3){1.5, 1.5, 2.0});
        model = mat4_rotation(&model, angle, (vec3){0.0, 0.0, 1.0});
        model = mat4_rotation(&model, angle, (vec3){1.0, 0.0, 0.0});
        model = mat4_rotation(&model, angle, (vec3){0.0, 1.0, 0.0});
        
        mat4 view = mat4_translation((vec3){0.0f, 0.0f, -8.0f});
        mat4 projection = mat4_perspective(45.0f * M_PI / 180.0f, (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);
        // Draw line
        // Dessine chaque arête du cube cycliquement
        // int edgeCount = sizeof(cubeEdges)/sizeof(int);
        // for(int i=0; i<edgeCount; i+=2) {
        //     int ia = cubeEdges[i];
        //     int ib = cubeEdges[i+1];
        //     vec4 A = { cube[3*ia], cube[3*ia+1], cube[3*ia+2], 1.0f };
        //     vec4 B = { cube[3*ib], cube[3*ib+1], cube[3*ib+2], 1.0f };
        //     draw2dLine(A, B, model, view, projection);
        // }
        // drawTrianglesFromData(triangle, 9, model, view, projection);
        // drawLinesCycl(triangle, 9, model, view, projection);

        // DRAW THE CUBE !!
        // drawTrianglesFromIndexedData(cubeVert, indices, 36, model, view, projection);
        // drawTrianglesFromIndexedData(triforce, triforceIndices, 9, model, view, projection);
        drawTrianglesFromIndexedData(triforce3D, triforce3DIndices, sizeof(triforce3DIndices)/sizeof(int), model, view, projection);

        // Print screen
        char screen[HEIGHT*(WIDTH+1)+1];
        int pos = 0;
        for(int i=0; i<HEIGHT; i++){
            for(int j=0; j< WIDTH; j++){
                screen[pos++] = frameBuffer[i][j];
            }
            screen[pos++] = '\n';
        }
        screen[pos] = '\0';
        
        printf("\033[33m");
        write(1, "\033[H", 3); // curseur en haut
        write(1, screen, (WIDTH+1)*HEIGHT); 
        // fflush(stdout);
        Sleep(1000/fps); // Fixe le fps
    }
    return 0;
}
void processInput(){
    while(_kbhit()){
        int ch = _getch();
        switch(ch) {
            case 'w':
                break;
            case 'a':
                break;
            case 'd':
                break;
            case 's':
                break;
        }
    }
}

vec3 homoToNdc(vec4 vertex){
    return (vec3){vertex.x/vertex.w, vertex.y/vertex.w, vertex.z/vertex.w};
}
vec2 ndcToScreen(vec3 ndc){
    vec2 screen;
    float aspect = (float)WIDTH/(float)HEIGHT;
    screen.x = (ndc.x + 1.0f) * 0.5f * (WIDTH  - 1);
    screen.y = (1.0f - (ndc.y + 1.0f) * 0.5f) * (HEIGHT - 1); // Y inversé
    return screen;
}

vec4 processVertex(vec4 v, mat4 model, mat4 view, mat4 projection) {
    // rotation dans le plan XY (model transform simplifiée)
    mat4 out;
    out = mat4_mul(projection, mat4_mul(view, model));
    return mat4_mul_vec4(out, v);
}

void draw2dLine(vec4 A, vec4 B, mat4 model, mat4 view, mat4 projection) {
    // Vertex shader
    vec3 aNDC = homoToNdc(processVertex(A, model, view, projection));
    vec3 bNDC = homoToNdc(processVertex(B, model, view, projection));

    // Viewport transform
    vec2 aScreen = ndcToScreen(aNDC);
    vec2 bScreen = ndcToScreen(bNDC);

    int x0 = (int)aScreen.x;
    int y0 = (int)aScreen.y;
    int x1 = (int)bScreen.x;
    int y1 = (int)bScreen.y;

    // Bresenham identique
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    int stepIndex = 0;
    int steps = (dx > -dy ? dx : -dy);
    while (1) {
        float t = (steps == 0 ? 0.0f : (float)stepIndex/steps);
        float z = A.z*t + B.z*(1-t);
        if(x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT)
            if(zBuffer[y0][x0] > z){
                frameBuffer[y0][x0] = '@';
                zBuffer[y0][x0] = z;
            }
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
        stepIndex++;
    }
}


void drawTriangle(vec4 A, vec4 B, vec4 C, mat4 model, mat4 view, mat4 projection){
    // Vertex shader
    A = processVertex(A, model, view, projection);
    B = processVertex(B, model, view, projection);
    C = processVertex(C, model, view, projection);
    if (A.w <= 0 || B.w <= 0 || C.w <= 0) return;

    vec3 aNDC = homoToNdc(A);
    vec3 bNDC = homoToNdc(B);
    vec3 cNDC = homoToNdc(C);

    vec2 aScreen = ndcToScreen(aNDC);
    vec2 bScreen = ndcToScreen(bNDC);
    vec2 cScreen = ndcToScreen(cNDC);

    // Get normal vector
    vec3 A3 = {A.x, A.y, A.z};
    vec3 B3 = {B.x, B.y, B.z};
    vec3 C3 = {C.x, C.y, C.z};
    vec3 AB = vec3_sub(B3, A3);
    vec3 AC = vec3_sub(C3, A3);
    vec3 normal = vec3_normalize(vec3_cross(AB, AC));
    
    int xMin[HEIGHT], xMax[HEIGHT];
    for(int y = 0; y<HEIGHT; y++){
        xMin[y] = INT_MAX;
        xMax[y] = -INT_MAX;
    }
    vec3 fragPos[HEIGHT][WIDTH];

    //Bressenham
    vec4 pos[] = {A, B, C};
    vec3 NDC[] = {aNDC, bNDC, cNDC};
    vec2 Screen[] = {aScreen, bScreen, cScreen};

    for(int i = 0; i<3; i++){
        int x0 = (int)Screen[i%3].x, x1 = (int)Screen[(i+1)%3].x;
        int y0 = (int)Screen[i%3].y, y1 = (int)Screen[(i+1)%3].y; 
        float z0 = NDC[i%3].z, z1 = NDC[(i+1)%3].z;

        int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
        int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
        int err = dx+dy, e2;

        int stepIndex = 0;
        int steps = (dx>-dy ? dx : -dy);
        while(1) {
            float t = (steps == 0 ? 0.0f : (float)stepIndex/steps);
            if(x0>=0 && x0<WIDTH && y0>=0 && y0<HEIGHT){
                xMin[y0] = min(x0, xMin[y0]);
                xMax[y0] = max(x0, xMax[y0]);
                fragPos[y0][x0].x = pos[i%3].x*(1-t)+pos[(i+1)%3].x*t;
                fragPos[y0][x0].y = pos[i%3].y*(1-t)+pos[(i+1)%3].y*t;
                fragPos[y0][x0].z = pos[i].z*(1-t)+pos[(i+1)%3].z*t;
            }
            if(x0==x1 && y0==y1) break;
            e2 = 2*err;
            if (e2 >= dy) {err+=dy; x0+=sx;}
            if (e2<=dx) {err+=dx; y0+=sy;}
            stepIndex++;
        }
    }

    for (int y = 0; y < HEIGHT; y++) {
        if (xMin[y] <= xMax[y]) {
            for (int x = xMin[y]; x <= xMax[y]; x++) {
                float t = (float)(x-xMin[y])/(xMax[y]-xMin[y]);
                vec3 left  = fragPos[y][xMin[y]];
                vec3 right = fragPos[y][xMax[y]];
                vec3 currentPos = {
                    left.x*(1-t) + right.x*t,
                    left.y*(1-t) + right.y*t,
                    left.z*(1-t) + right.z*t
                };
                if (zBuffer[y][x] > currentPos.z){
                    vec3 lightDir = vec3_normalize(vec3_sub(currentPos, lightPos));
                    float intensity = fmax(0, fabs(vec3_dot(lightDir, normal)));
                    
                    frameBuffer[y][x] = getLight(intensity);
                    zBuffer[y][x] = currentPos.z;
                }
            }
        }
    }
}

void drawTrianglesFromData(float vertices[], int count, mat4 model, mat4 view, mat4 projection){
    if (count < 9) return;
    int n = count / 3;
    for (int i=0; i<n-2; i++){
        vec4 A = {vertices[3*i], vertices[3*i+1], vertices[3*i+2], 1.0};
        vec4 B = {vertices[3*(i+1)], vertices[3*(i+1)+1], vertices[3*(i+1)+2], 1.0};
        vec4 C = {vertices[3*(i+2)], vertices[3*(i+2)+1], vertices[3*(i+2)+2], 1.0};
        drawTriangle(A, B, C, model, view, projection);
    }
}
void drawTrianglesFromIndexedData(float vertices[], int indices[], int indexCount,
                                  mat4 model, mat4 view, mat4 projection) {
    for (int i = 0; i < indexCount; i += 3) {
        int i0 = indices[i] * 3;
        int i1 = indices[i+1] * 3;
        int i2 = indices[i+2] * 3;

        vec4 A = {vertices[i0],   vertices[i0+1],   vertices[i0+2],   1.0};
        vec4 B = {vertices[i1],   vertices[i1+1],   vertices[i1+2],   1.0};
        vec4 C = {vertices[i2],   vertices[i2+1],   vertices[i2+2],   1.0};

        drawTriangle(A, B, C, model, view, projection);
    }
}
void drawLines(float vertices[], int count, mat4 model, mat4 view, mat4 projection){
    if (count < 6) return;
    int n = count / 3;
    for (int i = 0; i < n-1; i++) {
        vec4 A = { vertices[3*i],     vertices[3*i+1],     vertices[3*i+2], 1.0f };
        vec4 B = { vertices[3*(i+1)], vertices[3*(i+1)+1], vertices[3*(i+1)+2], 1.0f };
        draw2dLine(A, B, model, view, projection);
    }
}

void drawLinesCycl(float vertices[], int count, mat4 model, mat4 view, mat4 projection){
    if (count < 6) return;
    drawLines(vertices, count, model, view, projection);
    int n = count / 3;
    vec4 A = { vertices[3*(n-1)], vertices[3*(n-1)+1], vertices[3*(n-1)+2], 1.0f };
    vec4 B = { vertices[0],       vertices[1],         vertices[2],         1.0f };
    draw2dLine(B, A, model, view, projection);
}