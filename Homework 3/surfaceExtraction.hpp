//
//  surfaceExtraction.hpp
//  Homework3
//
//  Created by Ben Jones on 1/6/17.
//  Copyright © 2017 Ben Jones. All rights reserved.
//  Edited by Jason Ghiglieri with emotional support from Evan Derby.
//

#pragma once
#include <cstdio>

enum FaceType {
    NX,
    NY,
    NZ,
    PX,
    PY,
    PZ
};

struct Triangle{
    float normal[3];
    float v1[3];
    float v2[3];
    float v3[3];
};

void writeSTL(uint64_t model, const char* filename);

uint32_t findTriangles(int x, int y, int z, uint64_t model, FILE* file);

void writeTriangles(Triangle& t1, Triangle& t2, FILE* file);

void extractFace(int x, int y, int z, FaceType face, Triangle& t1, Triangle& t2);

