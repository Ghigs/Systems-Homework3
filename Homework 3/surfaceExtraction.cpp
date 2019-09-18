//
//  surfaceExtraction.cpp
//  Homework3
//
//  Created by Ben Jones on 1/6/17.
//  Copyright © 2017 Ben Jones. All rights reserved.
//  Edited by Jason Ghiglieri with emotional support from Evan Derby.
//
#include <cstdlib>
#include "surfaceExtraction.hpp"
#include "VoxelModelc.hpp"


inline void fillPlane(int a1, int a2, int b1, int b2, int c, int cInd, Triangle& t1, Triangle& t2){
    t1.v1[cInd] = c;
    t2.v1[cInd] = c;
    t1.v2[cInd] = c;
    t2.v2[cInd] = c;
    t1.v3[cInd] = c;
    t2.v3[cInd] = c;
    int aInd = (cInd +1) % 3;
    int bInd = (cInd +2) % 3;
    
    t1.v1[aInd] = a1;
    t1.v2[aInd] = a2;
    t1.v3[aInd] = a2;
    
    t2.v1[aInd] = a1;
    t2.v2[aInd] = a2;
    t2.v3[aInd] = a1;
    
    t1.v1[bInd] = b1;
    t1.v2[bInd] = b1;
    t1.v3[bInd] = b2;
    
    t2.v1[bInd] = b1;
    t2.v2[bInd] = b2;
    t2.v3[bInd] = b2;
    
}

void extractFace(int x, int y, int z, FaceType face, Triangle& t1, Triangle& t2){
    for(int i= 0; i < 3; i++){
        t1.normal[i] = 0;
        t2.normal[i] = 0;
    }
    switch(face){
        case NX:
            t1.normal[0] = -1;
            t2.normal[0] = -1;
            fillPlane(y + 1, y, z, z+1, x, 0, t1, t2);
            break;
        case NY:
            t1.normal[1] = -1;
            t2.normal[1] = -1;
            fillPlane(z + 1, z, x, x+1, y, 1, t1, t2);
            break;
        case NZ:
            t1.normal[2] = -1;
            t2.normal[2] = -1;
            fillPlane(x + 1, x, y, y + 1, z, 2, t1, t2);
            break;
        case PX:
            t1.normal[0] = 1;
            t2.normal[0] = 1;
            fillPlane(y, y + 1, z, z +1, x + 1, 0, t1, t2);
            break;
        case PY:
            t1.normal[1] = 1;
            t2.normal[1] = 1;
            fillPlane(z, z + 1, x, x + 1, y + 1, 1, t1, t2);
            break;
        case PZ:
            t1.normal[2] = 1;
            t2.normal[2] = 1;
            fillPlane(x, x + 1, y, y + 1, z + 1, 2, t1, t2);
            break;
    }
}



void writeTriangles(Triangle& t1, Triangle& t2, FILE* file)
{
    fwrite(&t1.normal, sizeof(float), 3, file);
    
    fwrite(&t1.v1, sizeof(float), 3, file);
    
    fwrite(&t1.v2, sizeof(float), 3, file);
    
    fwrite(&t1.v3, sizeof(float), 3, file);
    
    fseek(file, 2, SEEK_CUR);
    
    
    fwrite(&t2.normal, sizeof(float), 3, file);
    
    fwrite(&t2.v1, sizeof(float), 3, file);
    
    fwrite(&t2.v2, sizeof(float), 3, file);
    
    fwrite(&t2.v3, sizeof(float), 3, file);
    
    fseek(file, 2, SEEK_CUR);
    
}


uint32_t findTriangles(int x, int y, int z, uint64_t model, FILE* file)
{
    uint32_t numTris = 0;
    
    if (x-1 < 0 || !getBit(model, x-1, y, z))
    {
        FaceType f = NX;
        Triangle t1;
        Triangle t2;
            
        extractFace(x, y, z, f, t1, t2);
            
        writeTriangles(t1, t2, file);
        numTris += 2;
    }
        
    if (x+1 > 3 || !getBit(model, x+1, y, z))
    {
        FaceType f = PX;
        Triangle t1;
        Triangle t2;
        
        extractFace(x, y, z, f, t1, t2);
        
        writeTriangles(t1, t2, file);
        numTris += 2;
    }
    
    
    if (y-1 < 0 || !getBit(model, x, y-1, z))
    {
        FaceType f = NY;
        Triangle t1;
        Triangle t2;
        
        extractFace(x, y, z, f, t1, t2);
        
        writeTriangles(t1, t2, file);
        numTris += 2;
    }
    
    if (y+1 > 3 || !getBit(model, x, y+1, z))
    {
        FaceType f = PY;
        Triangle t1;
        Triangle t2;
        
        extractFace(x, y, z, f, t1, t2);
        
        writeTriangles(t1, t2, file);
        numTris += 2;
    }
    
    
    if (z-1 < 0 || !getBit(model, x, y, z+1))
    {
        FaceType f = NZ;
        Triangle t1;
        Triangle t2;
        
        extractFace(x, y, z, f, t1, t2);
        
        writeTriangles(t1, t2, file);
        numTris += 2;
    }
    
    if (z+1 > 3 || !getBit(model, x, y, z+1))
    {
        FaceType f = PZ;
        Triangle t1;
        Triangle t2;
        
        extractFace(x, y, z, f, t1, t2);
        
        writeTriangles(t1, t2, file);
        numTris += 2;
    }
    
    return numTris;
}



void writeSTL(uint64_t model, const char* filename)
{
    FILE* file = fopen(filename, "wb+");
    
    uint32_t numTris = 0;
    
    fseek(file, 84, SEEK_SET);
    
    
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            for (int z = 0; z < 4; z++)
            {
                if (getBit(model, x, y, z))
                {
                    numTris += findTriangles(x, y, z, model, file);
                }
            }
        }
    }
    
    
    fseek(file, 80, SEEK_SET);
    fwrite(&numTris, sizeof(uint32_t), 1, file);
    fclose(file);
}



