// Triforce 3D avec épaisseur
// 12 sommets (6 avant, 6 arrière)
float triforce3D[] = {
    // Face avant (z = +0.1)
     0.0,  2.0,  0.1,
    -1.0,  0.0,  0.1,
     1.0,  0.0,  0.1,
    -2.0, -2.0,  0.1,
     0.0, -2.0,  0.1,
     2.0, -2.0,  0.1,
    // Face arrière (z = -0.1)
     0.0,  2.0, -0.1,
    -1.0,  0.0, -0.1,
     1.0,  0.0, -0.1,
    -2.0, -2.0, -0.1,
     0.0, -2.0, -0.1,
     2.0, -2.0, -0.1
};

// Indices pour triangles (faces avant, arrière, latérales)
int triforce3DIndices[] = {
    // Face avant
    0, 1, 2,
    1, 3, 4,
    2, 4, 5,
    // Face arrière
    6, 8, 7,
    7, 10, 9,
    8, 11, 10,
    // Faces latérales extérieures
    0, 6, 1,  1, 6, 7,
    1, 7, 3,  3, 7, 9,
    3, 9, 4,  4, 9, 10,
    4, 10, 5, 5, 10, 11,
    5, 11, 2, 2, 11, 8,
    2, 8, 0, 0, 8, 6,
    // Pas de faces latérales intérieures pour garder le trou central
    1, 7, 8, 1, 2, 8,
    1, 7, 4, 1, 10, 4,
    2, 8, 4, 2, 10, 4
};
// 8 sommets du cube
float cubeVert[] = {
    -0.5, -0.5, -0.5, // v0
     0.5, -0.5, -0.5, // v1
     0.5,  0.5, -0.5, // v2
    -0.5,  0.5, -0.5, // v3
    -0.5, -0.5,  0.5, // v4
     0.5, -0.5,  0.5, // v5
     0.5,  0.5,  0.5, // v6
    -0.5,  0.5,  0.5  // v7
};
// Triforce de Zelda : 6 sommets, 3 triangles
float triforce[] = {
    0.0, 2.0, 0.0,    // sommet haut
   -1.0, 0.0, 0.0,    // gauche haut
    1.0, 0.0, 0.0,    // droite haut
   -2.0, -2.0, 0.0,   // gauche bas
    0.0, -2.0, 0.0,   // centre bas
    2.0, -2.0, 0.0    // droite bas
};
int triforceIndices[] = {
    0, 1, 2, // triangle du haut
    1, 3, 4, // triangle bas gauche
    2, 4, 5  // triangle bas droite
};
// 12 triangles, 36 indices
int indices[] = {
    // Face avant (z = +0.5) -> v4,v5,v6,v7
    4, 5, 6,
    4, 6, 7,

    // Face arrière (z = -0.5) -> v0,v1,v2,v3
    0, 2, 1,
    0, 3, 2,

    // Face gauche (x = -0.5) -> v0,v3,v7,v4
    0, 7, 3,
    0, 4, 7,

    // Face droite (x = +0.5) -> v1,v2,v6,v5
    1, 2, 6,
    1, 6, 5,

    // Face dessous (y = -0.5) -> v0,v1,v5,v4
    0, 1, 5,
    0, 5, 4,

    // Face dessus (y = +0.5) -> v3,v2,v6,v7
    3, 6, 2,
    3, 7, 6
};

float triangle[] = {
    -0.5, -0.5, 0.0,
    -0.5,  0.5, 0.0,
        0.5,  0.0, 0.0
};
float cube[] = {
    -0.5, -0.5, -0.5, // 0
    -0.5,  0.5, -0.5, // 1
        0.5,  0.5, -0.5, // 2
        0.5, -0.5, -0.5, // 3
    -0.5, -0.5,  0.5, // 4
    -0.5,  0.5,  0.5, // 5
        0.5,  0.5,  0.5, // 6
        0.5, -0.5,  0.5  // 7
};
int cubeEdges[] = {
    0,1, 1,2, 2,3, 3,0, // base
    4,5, 5,6, 6,7, 7,4, // top
    0,4, 1,5, 2,6, 3,7  // verticals
};